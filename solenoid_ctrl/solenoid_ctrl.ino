// Momentary presses for the Enyo front-panel buttons, and the coax LED on A0.
// D1 pulses Optical (pins 1 and 2). D2 pulses Coax (pins 3 and 4).
// The saved Sonos room selects Coax while that room's group is playing, and
// Optical 30 minutes after Sonos reports stopped or paused.
// Open https://solenoid.local — the certificate is self-signed, so the browser warns.
// The first boot copies the Wi-Fi name and password below into EEPROM.
// Override either one with -DSTASSID=... and -DSTAPSK=... on the command line.

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#ifndef STASSID
#define STASSID "Williams"
#define STAPSK "teletubby443"
#endif

// D1 mini silk: D1 is GPIO5, D2 is GPIO4. The generic ESP8266 board entry
// does not define those names.
#ifndef D1
#define D1 5
#endif
#ifndef D2
#define D2 4
#endif

const uint8_t opticalPin = D1;
const uint8_t coaxPin = D2;
const unsigned long pressMs = 400;
// Pin 6 sits near 0 when coax is off and near 250 (about 0.8 V) when it is on.
const int coaxOnThreshold = 100;
const unsigned long sonosPollMs = 5000;
const unsigned long leaderRefreshMs = 30000;
const unsigned long idleWaitMs = 30UL * 60UL * 1000UL;
const unsigned long wifiTryMs = 20000;
const uint32_t configMagic = 0x454e5902;

const IPAddress staticIp(192, 168, 50, 40);
const IPAddress staticGateway(192, 168, 50, 1);
const IPAddress staticMask(255, 255, 255, 0);
const IPAddress staticDns(192, 168, 50, 1);

BearSSL::ESP8266WebServerSecure server(443);
BearSSL::ServerSessions serverCache(2);

struct Config {
  uint32_t magic;
  char ssid[33];
  char password[64];
  char hostname[32];
  char room[32];
};

Config config;
char prevSsid[33];
char prevPass[64];
bool wifiPending = false;
bool mdnsUp = false;

enum SonosKind { SONOS_UNKNOWN, SONOS_SESSION, SONOS_IDLE };

IPAddress playerIp;
bool playerKnown = false;
IPAddress leaderIp;
bool leaderKnown = false;
unsigned long lastLeaderRefresh = 0;
IPAddress announcedPlayer;
bool announcedPlayerValid = false;
IPAddress announcedLeader;
bool leaderAnnounced = false;
char lastTransport[24] = "";
SonosKind lastKind = SONOS_UNKNOWN;
bool reachable = false;
bool downAnnounced = false;
bool timerArmed = false;
bool timerFrozen = false;
bool opticalDone = false;
unsigned long idleAccum = 0;
unsigned long idleMark = 0;

// Group-state replies for a few rooms are a few KB. /status/topology on this
// Connect firmware is an empty page, so the group list comes from SOAP.
char sonosBuf[8192];

static const char serverCert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIBqzCCAVKgAwIBAgIUdghK9ol7BnIXlEC8vv7qtdzYP6swCgYIKoZIzj0EAwIw
GTEXMBUGA1UEAwwOc29sZW5vaWQubG9jYWwwHhcNMjYxMDA2MDAwMjQ4WhcNMzYx
MDAzMDAwMjQ4WjAZMRcwFQYDVQQDDA5zb2xlbm9pZC5sb2NhbDBZMBMGByqGSM49
AgEGCCqGSM49AwEHA0IABCSquK7qX58MfBV31M1+qn08cQfaDAm0SQ3iWvjITh3w
OFbhcEmOUqpAniCmM2OihuzYfNAYb59gfkSY6U28jNmjeDB2MB0GA1UdDgQWBBQ4
nET4/pGwnp1TymV16PisQLNA2zAfBgNVHSMEGDAWgBQ4nET4/pGwnp1TymV16Pis
QLNA2zAPBgNVHRMBAf8EBTADAQH/MCMGA1UdEQQcMBqCDnNvbGVub2lkLmxvY2Fs
gghzb2xlbm9pZDAKBggqhkjOPQQDAgNHADBEAiAoV7V+56tRn+JfCcNh0mObU7U2
mA7Ol40wZ6TvPPcWsgIgTQmwjjR7k2dcNMtCmIrOdXGv6RmRFb1kZVjr9i2mkGg=
-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM = R"EOF(
-----BEGIN EC PRIVATE KEY-----
MHcCAQEEIF5/8Z5Q8GWJSsgg66nWVNJx5XkEvL3U0IPZzUPGlwC4oAoGCCqGSM49
AwEHoUQDQgAEJKq4rupfnwx8FXfUzX6qfTxxB9oMCbRJDeJa+MhOHfA4VuFwSY5S
qkCeIKYzY6KG7Nh80Bhvn2B+RJjpTbyM2Q==
-----END EC PRIVATE KEY-----
)EOF";

static const char zoneAttrBody[] PROGMEM =
    "<?xml version=\"1.0\"?>"
    "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
    "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
    "<s:Body><u:GetZoneAttributes xmlns:u=\"urn:schemas-upnp-org:service:DeviceProperties:1\">"
    "</u:GetZoneAttributes></s:Body></s:Envelope>";

static const char groupStateBody[] PROGMEM =
    "<?xml version=\"1.0\"?>"
    "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
    "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
    "<s:Body><u:GetZoneGroupState xmlns:u=\"urn:schemas-upnp-org:service:ZoneGroupTopology:1\">"
    "</u:GetZoneGroupState></s:Body></s:Envelope>";

static const char transportBody[] PROGMEM =
    "<?xml version=\"1.0\"?>"
    "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
    "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
    "<s:Body><u:GetTransportInfo xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\">"
    "<InstanceID>0</InstanceID></u:GetTransportInfo></s:Body></s:Envelope>";

static const char ssdpSearch[] PROGMEM =
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST: 239.255.255.250:1900\r\n"
    "MAN: \"ssdp:discover\"\r\n"
    "MX: 1\r\n"
    "ST: urn:schemas-upnp-org:device:ZonePlayer:1\r\n"
    "\r\n";

static const char INDEX_HTML[] PROGMEM = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Enyo</title>
<style>
  body { font: 18px system-ui, sans-serif; margin: 2rem; color: #222; }
  button { font: inherit; margin: 0 0.6rem 0.6rem 0; padding: 0.5rem 1rem; }
  p { max-width: 28rem; }
  label { display: block; margin: 0.4rem 0; }
  input { font: inherit; width: 16rem; }
</style>
</head>
<body>
  <button type="button" id="optical">Optical</button>
  <button type="button" id="coax">Coax</button>
  <p id="status">A0 —</p>
  <form id="cfg">
    <label>SSID <input id="ssid" name="ssid" maxlength="32" required></label>
    <label>Password <input id="password" name="password" maxlength="63"></label>
    <label>Hostname <input id="hostname" name="hostname" maxlength="31" required></label>
    <label>Room <input id="room" name="room" maxlength="31" required></label>
    <button type="submit">Save</button>
    <p id="saved"></p>
  </form>
  <p>The certificate name stays solenoid.local.</p>
<script>
const status = document.getElementById("status");
const optical = document.getElementById("optical");
const coax = document.getElementById("coax");
const saved = document.getElementById("saved");
function show(state) {
  let line = "A0 " + state.a0 + (state.coax ? "  coax" : "  not coax") + "  " + state.sonos;
  if (state.sonos === "idle" && state.waitMin >= 0) {
    line += ", optical in " + state.waitMin + " min";
  }
  status.textContent = line;
}
async function refresh() {
  show(await (await fetch("/state")).json());
}
async function press(path) {
  optical.disabled = true;
  coax.disabled = true;
  try {
    const res = await fetch(path, {method: "POST"});
    if (!res.ok) throw new Error(String(res.status));
    show(await res.json());
  } catch (err) {
    status.textContent = "Press failed.";
  }
  optical.disabled = false;
  coax.disabled = false;
}
optical.addEventListener("click", () => press("/optical"));
coax.addEventListener("click", () => press("/coax"));
async function loadSettings() {
  const cfg = await (await fetch("/settings")).json();
  document.getElementById("ssid").value = cfg.ssid;
  document.getElementById("password").value = cfg.password;
  document.getElementById("hostname").value = cfg.hostname;
  document.getElementById("room").value = cfg.room;
}
document.getElementById("cfg").addEventListener("submit", async (event) => {
  event.preventDefault();
  saved.textContent = "Saving.";
  const body = new URLSearchParams(new FormData(event.target));
  try {
    const res = await fetch("/config", {
      method: "POST",
      headers: {"Content-Type": "application/x-www-form-urlencoded"},
      body
    });
    const text = await res.text();
    if (!res.ok) {
      saved.textContent = "Save failed.";
      return;
    }
    saved.textContent = text === "rejoining" ? "Saved. Rejoining Wi-Fi." : "Saved.";
  } catch (err) {
    saved.textContent = "No reply. The board rejoins when the Wi-Fi name or password changed.";
  }
});
refresh().catch(() => { status.textContent = "Could not read A0."; });
loadSettings().catch(() => { saved.textContent = "Could not read settings."; });
setInterval(() => refresh().catch(() => {}), 2000);
</script>
</body>
</html>
)html";

const char *wifiStatusName(int status) {
  switch (status) {
    case WL_IDLE_STATUS: return "idle";
    case WL_NO_SSID_AVAIL: return "ssid not found";
    case WL_SCAN_COMPLETED: return "scan done";
    case WL_CONNECTED: return "connected";
    case WL_CONNECT_FAILED: return "authentication failed";
    case WL_CONNECTION_LOST: return "connection lost";
    case WL_DISCONNECTED: return "disconnected";
    default: return "unknown";
  }
}

void copyFit(char *dst, size_t dstLen, const char *src) {
  size_t i = 0;
  if (dstLen == 0) {
    return;
  }
  while (src[i] != 0 && i + 1 < dstLen) {
    dst[i] = src[i];
    i++;
  }
  dst[i] = 0;
}

bool copyExact(char *dst, size_t dstLen, const char *src, size_t maxLen) {
  size_t n = strlen(src);
  if (n > maxLen || n + 1 > dstLen) {
    return false;
  }
  memcpy(dst, src, n + 1);
  return true;
}

void ipToChars(const IPAddress &ip, char *out, size_t outLen) {
  snprintf(out, outLen, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}

void jsonEscape(const char *in, char *out, size_t outLen) {
  size_t j = 0;
  for (size_t i = 0; in[i] != 0 && j + 2 < outLen; i++) {
    unsigned char c = (unsigned char)in[i];
    if (c < 0x20) {
      continue;
    }
    if (c == '"' || c == '\\') {
      out[j++] = '\\';
    }
    out[j++] = (char)c;
  }
  out[j] = 0;
}

bool storeConfig() {
  config.magic = configMagic;
  EEPROM.put(0, config);
  if (!EEPROM.commit()) {
    Serial.println("eeprom commit failed");
    return false;
  }
  return true;
}

void loadConfig() {
  EEPROM.begin(512);
  EEPROM.get(0, config);
  config.ssid[sizeof(config.ssid) - 1] = 0;
  config.password[sizeof(config.password) - 1] = 0;
  config.hostname[sizeof(config.hostname) - 1] = 0;
  config.room[sizeof(config.room) - 1] = 0;
  if (config.magic != configMagic || config.ssid[0] == 0 || config.hostname[0] == 0 ||
      config.room[0] == 0) {
    memset(&config, 0, sizeof(config));
    config.magic = configMagic;
    copyFit(config.ssid, sizeof(config.ssid), STASSID);
    copyFit(config.password, sizeof(config.password), STAPSK);
    copyFit(config.hostname, sizeof(config.hostname), "solenoid");
    copyFit(config.room, sizeof(config.room), "Tube Amp");
    storeConfig();
    Serial.println("eeprom defaults saved");
  }
}

void applyMdns() {
  if (mdnsUp) {
    MDNS.close();
    mdnsUp = false;
  }
  mdnsUp = MDNS.begin(config.hostname);
  if (mdnsUp) {
    MDNS.addService("https", "tcp", 443);
    Serial.printf("mdns %s.local\n", config.hostname);
  } else {
    Serial.println("mdns failed; use the ip address");
  }
}

void startWifi(const char *name, const char *pass) {
  WiFi.disconnect(false);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.hostname(config.hostname);
  if (!WiFi.config(staticIp, staticGateway, staticMask, staticDns)) {
    Serial.println("static ip config failed");
  }
  WiFi.begin(name, pass);
}

void tryNewWifi() {
  Serial.printf("trying ssid \"%s\"\n", config.ssid);
  delay(300);
  startWifi(config.ssid, config.password);
  unsigned long started = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - started < wifiTryMs) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("new wifi failed, restoring previous");
    copyFit(config.ssid, sizeof(config.ssid), prevSsid);
    copyFit(config.password, sizeof(config.password), prevPass);
    storeConfig();
    startWifi(config.ssid, config.password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
  }
  Serial.printf("wifi connected\n");
  applyMdns();
}

void logRequest() {
  String ip = server.client().remoteIP().toString();
  const char *method = "OTHER";
  if (server.method() == HTTP_GET) {
    method = "GET";
  } else if (server.method() == HTTP_POST) {
    method = "POST";
  }
  Serial.printf("request %s %s from %s\n", method, server.uri().c_str(), ip.c_str());
}

int readCoax() {
  return analogRead(A0);
}

const char *sonosLabel() {
  if (!reachable || lastKind == SONOS_UNKNOWN) {
    return "unreachable";
  }
  if (lastKind == SONOS_SESSION) {
    return "playing";
  }
  return "idle";
}

int waitMinutes() {
  if (!timerArmed) {
    return -1;
  }
  unsigned long shown = idleAccum;
  if (reachable && !timerFrozen) {
    shown += millis() - idleMark;
  }
  if (shown >= idleWaitMs) {
    return 0;
  }
  return (int)((idleWaitMs - shown + 59999UL) / 60000UL);
}

void sendState() {
  int reading = readCoax();
  char json[96];
  snprintf(json, sizeof(json), "{\"a0\":%d,\"coax\":%s,\"sonos\":\"%s\",\"waitMin\":%d}", reading,
           reading >= coaxOnThreshold ? "true" : "false", sonosLabel(), waitMinutes());
  server.send(200, "application/json", json);
}

void sendSettings() {
  char ssidEsc[70];
  char passEsc[140];
  char hostEsc[70];
  char roomEsc[70];
  jsonEscape(config.ssid, ssidEsc, sizeof(ssidEsc));
  jsonEscape(config.password, passEsc, sizeof(passEsc));
  jsonEscape(config.hostname, hostEsc, sizeof(hostEsc));
  jsonEscape(config.room, roomEsc, sizeof(roomEsc));
  static char json[512];
  snprintf(json, sizeof(json),
           "{\"ssid\":\"%s\",\"password\":\"%s\",\"hostname\":\"%s\",\"room\":\"%s\"}", ssidEsc,
           passEsc, hostEsc, roomEsc);
  server.send(200, "application/json", json);
}

void pressButton(uint8_t pin, const char *name) {
  Serial.printf("press %s\n", name);
  digitalWrite(pin, HIGH);
  delay(pressMs);
  digitalWrite(pin, LOW);
  int reading = readCoax();
  Serial.printf("a0 %d  coax %s\n", reading, reading >= coaxOnThreshold ? "on" : "off");
}

bool hostOk(const char *s) {
  if (s[0] == 0 || s[0] == '-') {
    return false;
  }
  for (size_t i = 0; s[i] != 0; i++) {
    char c = s[i];
    bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-';
    if (!ok) {
      return false;
    }
  }
  return true;
}

bool roomOk(const char *s) {
  if (s[0] == 0) {
    return false;
  }
  for (size_t i = 0; s[i] != 0; i++) {
    unsigned char c = (unsigned char)s[i];
    if (c < 0x20 || c == '&' || c == '"' || c == '<' || c == '>') {
      return false;
    }
  }
  return true;
}

bool ssidOk(const char *s) {
  if (s[0] == 0) {
    return false;
  }
  for (size_t i = 0; s[i] != 0; i++) {
    if ((unsigned char)s[i] < 0x20) {
      return false;
    }
  }
  return true;
}

void forgetPlayer() {
  playerKnown = false;
  leaderKnown = false;
}

void handleConfig() {
  logRequest();
  if (!server.hasArg("ssid") || !server.hasArg("password") || !server.hasArg("hostname") ||
      !server.hasArg("room")) {
    server.send(400, "text/plain", "missing");
    return;
  }
  String ssidArg = server.arg("ssid");
  String passArg = server.arg("password");
  String hostArg = server.arg("hostname");
  String roomArg = server.arg("room");
  char newSsid[33];
  char newPass[64];
  char newHost[32];
  char newRoom[32];
  if (!ssidOk(ssidArg.c_str()) || !copyExact(newSsid, sizeof(newSsid), ssidArg.c_str(), 32) ||
      !copyExact(newPass, sizeof(newPass), passArg.c_str(), 63) ||
      !copyExact(newHost, sizeof(newHost), hostArg.c_str(), 31) || !hostOk(newHost) ||
      !copyExact(newRoom, sizeof(newRoom), roomArg.c_str(), 31) || !roomOk(newRoom)) {
    server.send(400, "text/plain", "rejected");
    return;
  }
  bool wifiChanged = strcmp(config.ssid, newSsid) != 0 || strcmp(config.password, newPass) != 0;
  bool hostChanged = strcmp(config.hostname, newHost) != 0;
  bool roomChanged = strcmp(config.room, newRoom) != 0;
  if (wifiChanged) {
    copyFit(prevSsid, sizeof(prevSsid), config.ssid);
    copyFit(prevPass, sizeof(prevPass), config.password);
  }
  copyFit(config.ssid, sizeof(config.ssid), newSsid);
  copyFit(config.password, sizeof(config.password), newPass);
  copyFit(config.hostname, sizeof(config.hostname), newHost);
  copyFit(config.room, sizeof(config.room), newRoom);
  if (!storeConfig()) {
    server.send(500, "text/plain", "eeprom failed");
    return;
  }
  if (roomChanged) {
    forgetPlayer();
    lastKind = SONOS_UNKNOWN;
    reachable = false;
    timerArmed = false;
    timerFrozen = false;
    idleAccum = 0;
    opticalDone = false;
    Serial.printf("room \"%s\"\n", config.room);
  }
  if (hostChanged && !wifiChanged) {
    WiFi.hostname(config.hostname);
    applyMdns();
  }
  server.send(200, "text/plain", wifiChanged ? "rejoining" : "saved");
  wifiPending = wifiChanged;
}

int readLine(WiFiClient &client, char *line, size_t len) {
  size_t n = 0;
  unsigned long started = millis();
  while (millis() - started < 2000) {
    if (!client.available()) {
      if (!client.connected()) {
        break;
      }
      delay(1);
      continue;
    }
    char c = client.read();
    if (c == '\n') {
      if (n > 0 && line[n - 1] == '\r') {
        n--;
      }
      line[n] = 0;
      return (int)n;
    }
    if (n + 1 < len) {
      line[n++] = c;
    }
  }
  line[n] = 0;
  return -1;
}

bool readHttp(WiFiClient &client, char *out, size_t outLen) {
  out[0] = 0;
  char line[160];
  if (readLine(client, line, sizeof(line)) < 0) {
    return false;
  }
  int status = 0;
  char *sp = strchr(line, ' ');
  if (sp != nullptr) {
    status = atoi(sp + 1);
  }
  int contentLength = -1;
  while (true) {
    int n = readLine(client, line, sizeof(line));
    if (n < 0) {
      return false;
    }
    if (n == 0) {
      break;
    }
    if (strncasecmp(line, "Content-Length:", 15) == 0) {
      contentLength = atoi(line + 15);
    }
  }
  if (status != 200) {
    return false;
  }
  if (contentLength > (int)outLen - 1) {
    return false;
  }
  size_t got = 0;
  unsigned long started = millis();
  while (got + 1 < outLen) {
    if (contentLength >= 0 && (int)got >= contentLength) {
      break;
    }
    if (client.available()) {
      int c = client.read();
      if (c < 0) {
        break;
      }
      out[got++] = (char)c;
      continue;
    }
    if (!client.connected()) {
      break;
    }
    if (millis() - started > 2000) {
      break;
    }
    delay(1);
  }
  out[got] = 0;
  if (contentLength >= 0 && (int)got < contentLength) {
    return false;
  }
  return got > 0;
}

bool soapCall(const IPAddress &ip, const char *path, const char *action, const char *bodyProgmem) {
  WiFiClient client;
  client.setTimeout(2000);
  if (!client.connect(ip, 1400)) {
    return false;
  }
  char ipText[16];
  ipToChars(ip, ipText, sizeof(ipText));
  client.print("POST ");
  client.print(path);
  client.print(" HTTP/1.1\r\nHost: ");
  client.print(ipText);
  client.print(":1400\r\nContent-Type: text/xml; charset=\"utf-8\"\r\nSOAPACTION: \"");
  client.print(action);
  client.print("\"\r\nContent-Length: ");
  client.print(strlen_P(bodyProgmem));
  client.print("\r\nConnection: close\r\n\r\n");
  client.print(FPSTR(bodyProgmem));
  bool ok = readHttp(client, sonosBuf, sizeof(sonosBuf));
  client.stop();
  return ok;
}

bool extractTag(const char *xml, const char *tag, char *dest, size_t destLen) {
  char openTag[40];
  char closeTag[40];
  snprintf(openTag, sizeof(openTag), "<%s>", tag);
  snprintf(closeTag, sizeof(closeTag), "</%s>", tag);
  const char *start = strstr(xml, openTag);
  if (start == nullptr) {
    return false;
  }
  start += strlen(openTag);
  const char *end = strstr(start, closeTag);
  if (end == nullptr || (size_t)(end - start) >= destLen) {
    return false;
  }
  memcpy(dest, start, end - start);
  dest[end - start] = 0;
  return true;
}

bool zoneNameOf(const IPAddress &ip, char *name, size_t nameLen) {
  if (!soapCall(ip, "/DeviceProperties/Control",
                "urn:schemas-upnp-org:service:DeviceProperties:1#GetZoneAttributes", zoneAttrBody)) {
    return false;
  }
  return extractTag(sonosBuf, "CurrentZoneName", name, nameLen);
}

bool leaderFromGroupState(const char *xml, const char *room, IPAddress &out) {
  char pattern[80];
  snprintf(pattern, sizeof(pattern), "ZoneName=&quot;%s&quot;", room);
  const char *at = strstr(xml, pattern);
  if (at == nullptr) {
    return false;
  }
  const char *key = "Coordinator=&quot;";
  size_t keyLen = strlen(key);
  const char *coord = nullptr;
  for (const char *p = at; p >= xml + keyLen; p--) {
    if (memcmp(p, key, keyLen) == 0) {
      coord = p + keyLen;
      break;
    }
  }
  if (coord == nullptr) {
    return false;
  }
  char uuid[40];
  size_t n = 0;
  while (coord[n] != 0 && coord[n] != '&' && n + 1 < sizeof(uuid)) {
    uuid[n] = coord[n];
    n++;
  }
  uuid[n] = 0;
  if (n == 0) {
    return false;
  }
  char member[64];
  snprintf(member, sizeof(member), "UUID=&quot;%s&quot;", uuid);
  const char *tag = strstr(xml, member);
  if (tag == nullptr) {
    return false;
  }
  const char *loc = strstr(tag, "Location=&quot;http://");
  if (loc == nullptr || loc - tag > 400) {
    return false;
  }
  loc += strlen("Location=&quot;http://");
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  if (sscanf(loc, "%d.%d.%d.%d", &a, &b, &c, &d) != 4) {
    return false;
  }
  if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) {
    return false;
  }
  out = IPAddress(a, b, c, d);
  return true;
}

bool discoverPlayer() {
  WiFiUDP udp;
  if (!udp.begin(1901)) {
    Serial.println("ssdp socket failed");
    return false;
  }
  char search[180];
  strncpy_P(search, ssdpSearch, sizeof(search) - 1);
  search[sizeof(search) - 1] = 0;
  IPAddress mcast(239, 255, 255, 250);
  if (!udp.beginPacketMulticast(mcast, 1900, WiFi.localIP())) {
    udp.stop();
    Serial.println("ssdp send failed");
    return false;
  }
  udp.write(search, strlen(search));
  if (!udp.endPacket()) {
    udp.stop();
    Serial.println("ssdp send failed");
    return false;
  }

  IPAddress found[8];
  int count = 0;
  unsigned long started = millis();
  while (millis() - started < 1200 && count < 8) {
    int packetSize = udp.parsePacket();
    if (packetSize <= 0) {
      delay(10);
      continue;
    }
    IPAddress ip = udp.remoteIP();
    while (udp.available() > 0) {
      udp.read();
    }
    bool dup = false;
    for (int i = 0; i < count; i++) {
      if (found[i] == ip) {
        dup = true;
      }
    }
    if (!dup) {
      found[count++] = ip;
    }
  }
  udp.stop();

  IPAddress match;
  bool matched = false;
  char seen[160];
  seen[0] = 0;
  for (int i = 0; i < count; i++) {
    char name[32];
    if (!zoneNameOf(found[i], name, sizeof(name))) {
      continue;
    }
    if (strlen(seen) + strlen(name) + 3 < sizeof(seen)) {
      if (seen[0] != 0) {
        strcat(seen, ", ");
      }
      strcat(seen, name);
    }
    if (strcmp(name, config.room) == 0) {
      match = found[i];
      matched = true;
    }
  }
  if (!matched) {
    playerKnown = false;
    if (!downAnnounced) {
      Serial.printf("room \"%s\" not found. saw %s\n", config.room, seen[0] != 0 ? seen : "none");
    }
    announcedPlayerValid = false;
    return false;
  }
  if (!announcedPlayerValid || announcedPlayer != match) {
    char ipText[16];
    ipToChars(match, ipText, sizeof(ipText));
    Serial.printf("sonos room \"%s\" at %s\n", config.room, ipText);
    announcedPlayer = match;
    announcedPlayerValid = true;
  }
  playerIp = match;
  playerKnown = true;
  return true;
}

bool refreshLeader() {
  if (!soapCall(playerIp, "/ZoneGroupTopology/Control",
                "urn:schemas-upnp-org:service:ZoneGroupTopology:1#GetZoneGroupState",
                groupStateBody)) {
    return false;
  }
  IPAddress next;
  if (!leaderFromGroupState(sonosBuf, config.room, next)) {
    return false;
  }
  leaderIp = next;
  leaderKnown = true;
  return true;
}

bool readTransport(char *state, size_t stateLen) {
  if (!soapCall(leaderIp, "/MediaRenderer/AVTransport/Control",
                "urn:schemas-upnp-org:service:AVTransport:1#GetTransportInfo", transportBody)) {
    return false;
  }
  return extractTag(sonosBuf, "CurrentTransportState", state, stateLen);
}

void noteUnreachable() {
  if (timerArmed) {
    timerFrozen = true;
  }
  reachable = false;
  leaderAnnounced = false;
  if (!downAnnounced) {
    Serial.println("sonos unreachable");
    downAnnounced = true;
  }
}

void applyTransport(const char *state) {
  bool session = strcmp(state, "PLAYING") == 0 || strcmp(state, "TRANSITIONING") == 0;
  bool idle = strcmp(state, "PAUSED_PLAYBACK") == 0 || strcmp(state, "STOPPED") == 0 ||
              strcmp(state, "NO_MEDIA_PRESENT") == 0;
  if (!session && !idle) {
    noteUnreachable();
    return;
  }
  reachable = true;
  downAnnounced = false;
  char ipText[16];
  ipToChars(leaderIp, ipText, sizeof(ipText));
  if (strcmp(lastTransport, state) != 0 || !leaderAnnounced || announcedLeader != leaderIp) {
    Serial.printf("sonos %s leader %s\n", state, ipText);
    copyFit(lastTransport, sizeof(lastTransport), state);
    announcedLeader = leaderIp;
    leaderAnnounced = true;
  }
  if (session) {
    if (timerArmed) {
      timerArmed = false;
      timerFrozen = false;
      idleAccum = 0;
      opticalDone = false;
      Serial.println("optical wait canceled");
    }
    bool entered = lastKind != SONOS_SESSION;
    lastKind = SONOS_SESSION;
    if (entered && readCoax() < coaxOnThreshold) {
      pressButton(coaxPin, "coax");
    }
    return;
  }
  if (lastKind == SONOS_SESSION) {
    timerArmed = true;
    timerFrozen = false;
    idleAccum = 0;
    idleMark = millis();
    opticalDone = false;
    Serial.println("optical wait started");
  }
  lastKind = SONOS_IDLE;
  if (!timerArmed || opticalDone) {
    return;
  }
  unsigned long now = millis();
  if (timerFrozen) {
    idleMark = now;
    timerFrozen = false;
  } else {
    idleAccum += now - idleMark;
    idleMark = now;
  }
  if (idleAccum >= idleWaitMs) {
    opticalDone = true;
    if (readCoax() >= coaxOnThreshold) {
      pressButton(opticalPin, "optical");
    }
  }
}

void pollSonos() {
  if (!playerKnown) {
    if (!discoverPlayer()) {
      noteUnreachable();
      return;
    }
    leaderKnown = false;
  }
  if (!leaderKnown || millis() - lastLeaderRefresh >= leaderRefreshMs) {
    if (!refreshLeader()) {
      forgetPlayer();
      noteUnreachable();
      return;
    }
    lastLeaderRefresh = millis();
  }
  char state[32];
  if (!readTransport(state, sizeof(state))) {
    forgetPlayer();
    noteUnreachable();
    return;
  }
  applyTransport(state);
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("enyo button boot");
  Serial.println("serial 115200");

  digitalWrite(opticalPin, LOW);
  digitalWrite(coaxPin, LOW);
  pinMode(opticalPin, OUTPUT);
  pinMode(coaxPin, OUTPUT);
  Serial.println("D1 optical pulse, D2 coax pulse, A0 pin 6");
  Serial.printf("coax on when a0 >= %d\n", coaxOnThreshold);

  loadConfig();
  Serial.printf("hostname %s\n", config.hostname);
  Serial.printf("mac %s\n", WiFi.macAddress().c_str());
  Serial.printf("joining ssid \"%s\" (password length %u)\n", config.ssid, strlen(config.password));
  Serial.printf("sonos room \"%s\"\n", config.room);

  Serial.println("scanning");
  int networks = WiFi.scanNetworks();
  bool ssidSeen = false;
  if (networks < 0) {
    Serial.printf("scan failed (%d)\n", networks);
  } else {
    Serial.printf("%d networks\n", networks);
    for (int i = 0; i < networks; i++) {
      bool match = WiFi.SSID(i) == config.ssid;
      if (match) {
        ssidSeen = true;
      }
      Serial.printf("  %s  rssi %d dBm  ch %d%s\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i),
                    WiFi.channel(i), match ? "  <-- target" : "");
    }
  }
  WiFi.scanDelete();
  if (!ssidSeen) {
    Serial.println("target ssid was not in the scan");
  }

  // 169.254.x.x is a link-local address: DHCP never placed the board on the LAN.
  Serial.println("static ip 192.168.50.40  gateway 192.168.50.1  mask 255.255.255.0");
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(config.hostname);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  if (!WiFi.config(staticIp, staticGateway, staticMask, staticDns)) {
    Serial.println("static ip config failed");
  }
  WiFi.begin(config.ssid, config.password);
  Serial.println("waiting for association");
  unsigned long started = millis();
  unsigned long lastReport = 0;
  while (WiFi.status() != WL_CONNECTED) {
    unsigned long now = millis();
    if (now - lastReport >= 2000) {
      lastReport = now;
      Serial.printf("  still waiting  %lus  status=%s\n", (now - started) / 1000,
                    wifiStatusName(WiFi.status()));
    }
    delay(100);
  }

  String ip = WiFi.localIP().toString();
  String gateway = WiFi.gatewayIP().toString();
  String mask = WiFi.subnetMask().toString();
  String dns = WiFi.dnsIP().toString();
  Serial.println("wifi connected");
  Serial.printf("ip %s\n", ip.c_str());
  if (WiFi.localIP()[0] == 169 && WiFi.localIP()[1] == 254) {
    Serial.println("link-local address: the board is not on 192.168.50.0");
  }
  Serial.printf("gateway %s  mask %s  dns %s\n", gateway.c_str(), mask.c_str(), dns.c_str());
  Serial.printf("rssi %d dBm  channel %d\n", WiFi.RSSI(), WiFi.channel());
  WiFi.printDiag(Serial);
  applyMdns();

  BearSSL::X509List *cert = new BearSSL::X509List(serverCert);
  BearSSL::PrivateKey *key = new BearSSL::PrivateKey(serverKey);
  Serial.printf("certificate %s, key %s\n", cert->getCount() ? "loaded" : "FAILED",
                key->isEC() ? "loaded" : "FAILED");
  server.getServer().setECCert(cert, BR_KEYTYPE_KEYX | BR_KEYTYPE_SIGN, key);
  server.getServer().setCache(&serverCache);
  // BearSSL's default input buffer is 16709 bytes, allocated for the whole
  // time a browser is connected. mDNS runs from yield() while the page is
  // sent and allocates answer records with operator new, which resets the
  // chip on failure. 6KB still holds a browser ClientHello.
  server.getServer().setBufferSizes(6144 + 325, 837);

  server.on("/", HTTP_GET, []() {
    logRequest();
    server.send_P(200, PSTR("text/html"), INDEX_HTML);
  });
  server.on("/state", HTTP_GET, sendState);
  server.on("/settings", HTTP_GET, sendSettings);
  server.on("/config", HTTP_POST, handleConfig);
  server.on("/optical", HTTP_POST, []() {
    logRequest();
    pressButton(opticalPin, "optical");
    sendState();
  });
  server.on("/coax", HTTP_POST, []() {
    logRequest();
    pressButton(coaxPin, "coax");
    sendState();
  });
  server.onNotFound([]() {
    logRequest();
    server.send(404, "text/plain", "not found");
  });
  server.begin();

  Serial.printf("https://%s.local\n", config.hostname);
  Serial.printf("https://%s\n", ip.c_str());
  Serial.printf("free heap %u\n", ESP.getFreeHeap());
  Serial.println("ready");
}

void loop() {
  if (wifiPending) {
    wifiPending = false;
    tryNewWifi();
  }

  int status = WiFi.status();
  static int lastStatus = WL_CONNECTED;
  if (status != lastStatus) {
    Serial.printf("wifi status %s\n", wifiStatusName(status));
    lastStatus = status;
  }

  static unsigned long lastBeat = 0;
  static unsigned long lastPoll = 0;
  unsigned long now = millis();
  if (now - lastBeat >= 10000) {
    lastBeat = now;
    String ip = WiFi.localIP().toString();
    int reading = readCoax();
    Serial.printf("alive  ip=%s  rssi=%d dBm  status=%s  a0=%d  coax=%s  sonos=%s  https://%s.local\n",
                  ip.c_str(), WiFi.RSSI(), wifiStatusName(status), reading,
                  reading >= coaxOnThreshold ? "on" : "off", sonosLabel(), config.hostname);
  }

  if (status == WL_CONNECTED && now - lastPoll >= sonosPollMs) {
    lastPoll = now;
    pollSonos();
  } else if (status != WL_CONNECTED) {
    noteUnreachable();
  }

  server.handleClient();
  if (mdnsUp) {
    MDNS.update();
  }
}
