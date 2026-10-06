// HTTPS toggles for the two solenoid gates.
// Solenoid A is D1. Solenoid B is D2.
// Open https://solenoid.local — the certificate is self-signed, so the browser warns.
// Fill in the Wi-Fi name and password before uploading. Override either one with
// -DSTASSID=... and -DSTAPSK=... if you pass them on the command line.

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Williams"
#define STAPSK "teletubby443"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
const char *hostname = "solenoid";

const uint8_t solenoidA = D1;
const uint8_t solenoidB = D2;

BearSSL::ESP8266WebServerSecure server(443);
BearSSL::ServerSessions serverCache(2);

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

static const char INDEX_HTML[] PROGMEM = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Solenoids</title>
<style>
  body { font: 18px system-ui, sans-serif; margin: 2rem; color: #222; }
  label { display: flex; justify-content: space-between; align-items: center;
          max-width: 22rem; padding: 0.9rem 0; border-bottom: 1px solid #ddd; }
  input { width: 3rem; height: 1.7rem; }
  p { max-width: 22rem; color: #555; font-size: 15px; }
</style>
</head>
<body>
  <label>Solenoid A <input id="a" type="checkbox" role="switch"></label>
  <label>Solenoid B <input id="b" type="checkbox" role="switch"></label>
  <p id="status">Leaving a solenoid on heats the coil.</p>
<script>
const status = document.getElementById("status");
async function load() {
  const state = await (await fetch("/state")).json();
  for (const id of ["a", "b"]) {
    const input = document.getElementById(id);
    input.checked = state[id];
    input.disabled = false;
  }
}
async function send(id, on) {
  const body = new URLSearchParams({on: on ? "1" : "0"});
  const res = await fetch("/" + id, {method: "POST", body});
  if (!res.ok) throw new Error(String(res.status));
}
for (const id of ["a", "b"]) {
  const input = document.getElementById(id);
  input.disabled = true;
  input.addEventListener("change", async () => {
    try {
      await send(id, input.checked);
      status.textContent = "Leaving a solenoid on heats the coil.";
    } catch (err) {
      input.checked = !input.checked;
      status.textContent = "Update failed.";
    }
  });
}
load().catch(() => { status.textContent = "Could not read the solenoids."; });
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

void sendState() {
  logRequest();
  char json[40];
  snprintf(json, sizeof(json), "{\"a\":%s,\"b\":%s}",
           digitalRead(solenoidA) == HIGH ? "true" : "false",
           digitalRead(solenoidB) == HIGH ? "true" : "false");
  server.send(200, "application/json", json);
}

void applyPin(uint8_t pin) {
  logRequest();
  if (!server.hasArg("on")) {
    server.send(400, "text/plain", "missing on");
    return;
  }
  bool on = server.arg("on") == "1";
  digitalWrite(pin, on ? HIGH : LOW);
  Serial.printf("Solenoid %c %s\n", pin == solenoidA ? 'A' : 'B', on ? "on" : "off");
  sendState();
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("solenoid_ctrl boot");
  Serial.println("serial 115200");

  digitalWrite(solenoidA, LOW);
  digitalWrite(solenoidB, LOW);
  pinMode(solenoidA, OUTPUT);
  pinMode(solenoidB, OUTPUT);
  Serial.println("solenoid pins low (A=D1/GPIO5, B=D2/GPIO4)");

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  String mac = WiFi.macAddress();
  Serial.printf("hostname %s\n", hostname);
  Serial.printf("mac %s\n", mac.c_str());
  Serial.printf("joining ssid \"%s\" (password length %u)\n", ssid, strlen(password));

  Serial.println("scanning");
  int networks = WiFi.scanNetworks();
  bool ssidSeen = false;
  if (networks < 0) {
    Serial.printf("scan failed (%d)\n", networks);
  } else {
    Serial.printf("%d networks\n", networks);
    for (int i = 0; i < networks; i++) {
      bool match = WiFi.SSID(i) == ssid;
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
  // This network's gateway is 192.168.50.1, so use a fixed address on that subnet.
  IPAddress staticIp(192, 168, 50, 40);
  IPAddress staticGateway(192, 168, 50, 1);
  IPAddress staticMask(255, 255, 255, 0);
  IPAddress staticDns(192, 168, 50, 1);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  if (!WiFi.config(staticIp, staticGateway, staticMask, staticDns)) {
    Serial.println("static ip config failed");
  }
  Serial.println("static ip 192.168.50.40  gateway 192.168.50.1  mask 255.255.255.0");

  WiFi.begin(ssid, password);
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

  if (MDNS.begin(hostname)) {
    MDNS.addService("https", "tcp", 443);
    Serial.printf("mdns %s.local\n", hostname);
  } else {
    Serial.println("mdns failed; use the ip address");
  }

  BearSSL::X509List *cert = new BearSSL::X509List(serverCert);
  BearSSL::PrivateKey *key = new BearSSL::PrivateKey(serverKey);
  Serial.printf("certificate %s, key %s\n", cert->getCount() ? "loaded" : "FAILED",
                key->isEC() ? "loaded" : "FAILED");
  server.getServer().setECCert(cert, BR_KEYTYPE_KEYX | BR_KEYTYPE_SIGN, key);
  server.getServer().setCache(&serverCache);

  server.on("/", HTTP_GET, []() {
    logRequest();
    server.send_P(200, PSTR("text/html"), INDEX_HTML);
  });
  server.on("/state", HTTP_GET, sendState);
  server.on("/a", HTTP_POST, []() { applyPin(solenoidA); });
  server.on("/b", HTTP_POST, []() { applyPin(solenoidB); });
  server.onNotFound([]() {
    logRequest();
    server.send(404, "text/plain", "not found");
  });
  server.begin();

  Serial.printf("https://%s.local\n", hostname);
  Serial.printf("https://%s\n", ip.c_str());
  Serial.printf("free heap %u\n", ESP.getFreeHeap());
  Serial.println("ready");
}

void loop() {
  int status = WiFi.status();
  static int lastStatus = WL_CONNECTED;
  if (status != lastStatus) {
    Serial.printf("wifi status %s\n", wifiStatusName(status));
    lastStatus = status;
  }

  static unsigned long lastBeat = 0;
  unsigned long now = millis();
  if (now - lastBeat >= 10000) {
    lastBeat = now;
    String ip = WiFi.localIP().toString();
    Serial.printf("alive  ip=%s  rssi=%d dBm  status=%s  https://%s.local\n", ip.c_str(),
                  WiFi.RSSI(), wifiStatusName(status), hostname);
  }

  server.handleClient();
  MDNS.update();
}
