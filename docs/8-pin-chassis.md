# 8-Pin Chassis (EL34 octal point-to-point)

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-12  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

Four octal (8-pin) sockets at the rear of the chassis, wired **point-to-point** — no PCB. The EL34s mount here and poke up through the clearance cutouts in the [Preamp Board](preamp-board.md). Power tubes **V3 / V4** (LFT) and **V7 / V8** (RT): [`tubes.md`](tubes.md).

## Files

| File                                                                             | Purpose                                 |
| -------------------------------------------------------------------------------- | --------------------------------------- |
| [`../photos/8 pin 1.png`](../photos/8%20pin%201.png)                             | Socket close-up                         |
| [`../photos/8 pin 2.png`](../photos/8%20pin%202.png)                             | Socket close-up                         |
| [`../photos/8 pin 3.png`](../photos/8%20pin%203.png)                             | Socket close-up                         |
| [`../photos/8 pin 4.png`](../photos/8%20pin%204.png)                             | Socket close-up                         |
| [`../photos/8 pin 5.png`](../photos/8%20pin%205.png)                             | Socket close-up                         |
| [`../photos/8 pin chassis top.png`](../photos/8%20pin%20chassis%20top.png)       | Chassis area, top                       |
| [`../photos/8 pin chassis bottom.png`](../photos/8%20pin%20chassis%20bottom.png) | Chassis area, underside                 |
| [`../photos/assembled from bottom.png`](../photos/assembled%20from%20bottom.png) | As-built wiring (grid stoppers visible) |
| [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)                         | Factory topology (V3/V4/V7/V8, Vx-TP)   |

---

## EL34 socket pin map

Per factory PDF, confirmed against photos where noted:

| Pin   | Function          | Wiring at this assembly                                                                                    | Conf.        |
| ----- | ----------------- | ---------------------------------------------------------------------------------------------------------- | ------------ |
| **2** | Heater            | **V3/V4 HEAT** (**BLK/WHT**) or **V7/V8 HEAT** (**YEL/YEL**) from PT — see [Heaters](#heaters)             | High         |
| **3** | Plate             | **ORG** (**V3**, **V7**) or **BRN** (**V4**, **V8**) — see [OT primary landing](#ot-primary-landing)       | High         |
| **4** | Screen grid       | **YEL** (with **V3**, **V7**) or **WHT** (with **V4**, **V8**) — same socket as pin **3**                  | High         |
| **5** | Control grid      | **1 kΩ grid stopper** at socket (OI-1 closed — all four confirmed) ← **C4** wire from preamp               | High (photo) |
| **7** | Heater return     | Other leg of the twisted pair                                                                              | High         |
| **8** | Cathode (`Vx-TP`) | → **1 Ω** cathode sense on **preamp board** (replace at rebuild) · **BLK** from socket · **GRN** → **TP1** | High         |

**Bias is not set here.** The bias trim pots are on the **preamp board** solder side ([`preamp-board.md`](preamp-board.md#bias-network-el34-fixed-bias)); the bias DC reaches the grids through the **C4** wires. Bias is *measured* from here via the pin-8 sense wires at **TP1**.

---

## OT primary landing

Each channel's OT brings **five primary leads** to this assembly. **Rebuild (2026-07-20)** — same rule both channels ([`OT.md`](OT.md)):

| OT pair     | Twist | Tube   | Pin **3** | Pin **4** | P-touch        |
| ----------- | ----- | ------ | --------- | --------- | -------------- |
| **ORG+YEL** | yes   | **V3** | **ORG**   | **YEL**   | **V3 PIN 3/4** |
| **BRN+WHT** | yes   | **V4** | **BRN**   | **WHT**   | **V4 PIN 3/4** |
| **ORG+YEL** | yes   | **V7** | **ORG**   | **YEL**   | **V7 PIN 3/4** |
| **BRN+WHT** | yes   | **V8** | **BRN**   | **WHT**   | **V8 PIN 3/4** |

| Coil **RED** | **+B center tap** — **C3** **RED**; label **+B LEFT** (LFT) or **+B RIGHT** (RT) at OT stub |

**Never split a pair** across sockets. Primary **BRN** ≠ secondary **BRN** (8 Ω speaker tap).

---

## Harness C3 — Large Cap Board ↔ 8-Pin Chassis (hardwire, this doc owns it)

**Redefined 2026-07-12.** C3 is **not** a rail-delivery harness (the old +B/+B1/+B2/−B1 description was wrong — those rails go to the OT center taps and the preamp board). C3 is:

| Group                | Wires                  | From                                           | To                                               |
| -------------------- | ---------------------- | ---------------------------------------------- | ------------------------------------------------ |
| **+B feeds**         | **2× RED** (18 AWG)    | Large Cap Board **+B** node (top 470 µF cap +) | One to each **OT center tap** (RED primary lead) |
| **Bias sense lines** | **4× GRN** (22 AWG OK) | EL34 **pin 8** at each socket                  | Large Cap Board **TP1** pad named for that tube  |
| **Ground reference** | 1× (18 AWG)            | Chassis GND                                    | **TP1** center pad                               |

Historical tags: the +B feeds carried tags **13** and **23** (RED); the sense wires carried tags **23 / 21 / 19 / 17** (GRN). Same numbers, different wires — identity is **color + number**, never number alone.

**TP1 pads are isolated test points** — they have no other connectivity on the Large Cap Board. Pad silk names the tube; at rebuild, wire each socket's pin 8 to its named pad. Pad↔tag order from disassembly does not matter.

### C3 worksheet (fill at solder)

| Wire | Function        | Color | Label           | From               | To                | ☐ Soldered | ☐ Metered |
| ---- | --------------- | ----- | --------------- | ------------------ | ----------------- | ---------- | --------- |
| 1    | +B feed, LFT OT | RED   | **+B LEFT**     | Large Cap Board +B | LFT OT center tap | ☐          | ☐         |
| 2    | +B feed, RT OT  | RED   | **+B RIGHT**    | Large Cap Board +B | RT OT center tap  | ☐          | ☐         |
| 3    | V3 pin-8 sense  | GRN   | V3 socket pin 8 | TP1 pad V3         | ☐                 | ☐          |           |
| 4    | V4 pin-8 sense  | GRN   | V4 socket pin 8 | TP1 pad V4         | ☐                 | ☐          |           |
| 5    | V7 pin-8 sense  | GRN   | V7 socket pin 8 | TP1 pad V7         | ☐                 | ☐          |           |
| 6    | V8 pin-8 sense  | GRN   | V8 socket pin 8 | TP1 pad V8         | ☐                 | ☐          |           |
| 7    | GND reference   |       | Chassis GND     | TP1 center pad     | ☐                 | ☐          |           |

To bench-test this assembly alone, unsolder C3 at the Large Cap Board end.

---

## Harness C4 — Preamp Board ↔ 8-Pin Chassis (Micro-Fit 3.0, 4-pin, this doc owns it)

**One plug + one receptacle, 22 AWG.**

| Pin | Function              |
| --- | --------------------- |
| 1–4 | EL34 control grids ×4 |

Each wire runs from the preamp board (downstream of the coupling cap and the bias-trim wiper) to an EL34 **pin 5** through the **1 kΩ** stopper at the socket.

### Wires carry DC bias, not just AC signal

At the socket end each C4 wire rides at the bias voltage — **≈ −40 V to −54 V DC** — with the audio on top.

- **Do not** short C4 pins to chassis with the amp powered — that unbiases the EL34 and draws runaway plate current.
- **Do not** expect a 0 V baseline on a scope; the DC offset is real.
- When unplugging C4 for bench isolation, power down and **verify caps discharged** ([`../README.md`](../README.md) Prep) first.
- 22 AWG is fine: grid current is ~µA; voltage is within Micro-Fit 3.0 rating.

### C4 worksheet (fill at crimp)

| Pin | Function  | EL34 socket | Color | ☐ Crimped | ☐ Metered |
| --- | --------- | ----------- | ----- | --------- | --------- |
| 1   | EL34 grid |             |       | ☐         | ☐         |
| 2   | EL34 grid |             |       | ☐         | ☐         |
| 3   | EL34 grid |             |       | ☐         | ☐         |
| 4   | EL34 grid |             |       | ☐         | ☐         |

Unplug **C4** to isolate the Preamp Board signal from the power tubes.

---

## Heaters

Two twisted 6.3 V pairs arrive **direct from the PT** (not via any board):

| Harness dress | Coil at PT (DCR) | Label (applied) | Destination                     | Load              |
| ------------- | ---------------- | --------------- | ------------------------------- | ----------------- |
| **BLK / WHT** | **BRN / BRN**    | **V3/V4 HEAT**  | **V3**, **V4** — pins **2 / 7** | 2 × 1.5 A = 3.0 A |
| **YEL / YEL** | **YEL / YEL**    | **V7/V8 HEAT**  | **V7**, **V8** — pins **2 / 7** | 2 × 1.5 A = 3.0 A |

- **BLK/WHT** here is the PT heater extension only — not OT primary **WHT** (UL screen). Map: [`PT.md`](PT.md).
- **Do not parallel the two windings** without first confirming identical phase (dot both ends, meter 0 V AC between paralleled hot legs before energizing). Wrong phase = short across the winding = smoke.
- Keep pairs twisted tightly (~1 turn per cm) end to end.

---

## Bench tests (Part 4 gate)

| Check              | Pass                                                                                                         |
| ------------------ | ------------------------------------------------------------------------------------------------------------ |
| Grid stoppers      | **OI-1 closed** — all four **1 kΩ** ([`assembled from bottom.png`](../photos/assembled%20from%20bottom.png)) |
| **C3** +B feeds    | +B present at both OT center taps (**tubes out**); readings logged                                           |
| **C3** sense lines | Each TP1 pad buzzes to its socket's pin 8; ~**1 Ω** pin 8 → GND (through the R17/R18 sense resistor)         |
| **C4** built       | Grid nets continuous when plug inserted; **no** DC short grid → +B                                           |
| **C4** unplugged   | Power stage isolated from Preamp signal                                                                      |

---

## Related

- [`tubes.md`](tubes.md) — **V3/V4/V7/V8**, EL34 pin map, **TP1** sense names
- [`large-cap-board.md`](large-cap-board.md) — +B node, TP1 sense header
- [`preamp-board.md`](preamp-board.md) — bias trims, C4 preamp end, cathode sense resistors
- [`OT.md`](OT.md) — primary DCR matrix and color map (T-2)
- [`PT.md`](PT.md) — heater windings
- [`chassis.md`](chassis.md) — star ground
- [`../README.md`](../README.md) — Part 4 build order

## Changelog

| Date       | Change                                                                                                              |
| ---------- | ------------------------------------------------------------------------------------------------------------------- |
| 2026-07-20 | P-touch **+B LEFT/RIGHT**, **Vn PIN 3/4** — [`labels.md`](labels.md)                                                |
| 2026-07-20 | OT primary landing **V3/V7** ORG+YEL, **V4/V8** BRN+WHT — sync [`OT.md`](OT.md)                                     |
| 2026-07-12 | Created from CONNECTORS.md C3/C4 sections; C3 redefined (2× +B feeds + 4× pin-8 sense + GND); T-2 color map applied |
