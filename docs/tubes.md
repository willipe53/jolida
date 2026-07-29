# Tube designators (V1–V8)

**Unit:** Jolida SJ202A / JD202  
**Authority:** Chassis silkscreen + factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)) — see [`SOURCES.md`](SOURCES.md)

This doc is the **naming reference** for all project docs and for the planned Fusion 360 → Eagle schematic. Use **V1–V8** everywhere; do not invent alternate tube names.

Photo: [`../photos/assembled amp.png`](../photos/assembled%20amp.png) (deck layout).

---

## Naming rules

| Rule                                                       | Example                                                                  |
| ---------------------------------------------------------- | ------------------------------------------------------------------------ |
| **Tube = one designator (V1–V8)**                          | “Bias **V3** at TP1” — not “left outer EL34” alone                       |
| **Channel = LFT or RT** in harness / panel docs            | LFT OT → **V3** + **V4**; RT OT → **V7** + **V8**                        |
| **Dual-triode section = (A) or (B)** on 12AX7 / 12AT7 only | NFB on **V1(A)** cathode — pin **3**                                     |
| **Push-pull pair ≠ mirror pair**                           | **V3** + **V4** share one OT (LFT); **V7** + **V8** share the other (RT) |
| **Pot refs ≠ tube refs**                                   | **RV2** is a bias trim pot — not tube **V2**                             |

---

## Complement

| Designator | Type  | Channel | Role (factory PDF)                    |
| ---------- | ----- | ------- | ------------------------------------- |
| **V1**     | 12AX7 | **LFT** | Input / gain (dual triode)            |
| **V2**     | 12AT7 | **LFT** | Phase inverter + driver (dual triode) |
| **V3**     | EL34  | **LFT** | Power pentode — push-pull half A      |
| **V4**     | EL34  | **LFT** | Power pentode — push-pull half B      |
| **V5**     | 12AX7 | **RT**  | Same as **V1**                        |
| **V6**     | 12AT7 | **RT**  | Same as **V2**                        |
| **V7**     | EL34  | **RT**  | Same as **V3**                        |
| **V8**     | EL34  | **RT**  | Same as **V4**                        |

Factory note on schematic: **“R CH SAME AS L CH.”**

---

## Physical layout (chassis silk, front view)

Left → right on the top deck. Rear row = EL34s; front row = preamp novals.

| Position | Tube   | Type  | Channel | Row                         |
| -------- | ------ | ----- | ------- | --------------------------- |
| 1        | **V3** | EL34  | LFT     | rear, left                  |
| 2        | **V4** | EL34  | LFT     | rear, center-left           |
| 3        | **V8** | EL34  | RT      | rear, center-right          |
| 4        | **V7** | EL34  | RT      | rear, right                 |
| 5        | **V2** | 12AT7 | LFT     | front, left (outer)         |
| 6        | **V1** | 12AX7 | LFT     | front, center-left (inner)  |
| 7        | **V5** | 12AX7 | RT      | front, center-right (inner) |
| 8        | **V6** | 12AT7 | RT      | front, right (outer)        |

Within each channel the EL34 pair reads **V3–V4** (LFT) vs **V8–V7** (RT) — **spatially reversed** on the deck even though the circuits mirror.

---

## Mirror pairs (circuit)

Cross-channel equivalents — same schematic block, opposite channel:

| Left   | Right  |
| ------ | ------ |
| **V1** | **V5** |
| **V2** | **V6** |
| **V3** | **V7** |
| **V4** | **V8** |

## Push-pull pairs (within one channel)

Same OT, same speaker posts — do **not** swap between channels:

| Channel | Tubes           | OT       | Speaker tags                       |
| ------- | --------------- | -------- | ---------------------------------- |
| **LFT** | **V3** + **V4** | left OT  | **1** G · **15** 4 Ω · **19** 8 Ω  |
| **RT**  | **V7** + **V8** | right OT | **11** G · **17** 4 Ω · **13** 8 Ω |

OT primary landings (**ORG/YEL/BRN/WHT**) are per channel, not per tube designator — see [`OT.md`](OT.md). Which socket is “plate A” vs “plate B” is your choice; label and stay consistent.

---

## Pin-by-pin maps

**Socket view:** bottom of the chassis, looking up at the pins.

| Base  | Key faces | Pin **1** side of gap | Numbering     |
| ----- | --------- | --------------------- | ------------- |
| Octal | rear      | ~**1:00**             | **1 → 8** CW  |
| Noval | front     | ~**7:00**             | **1 → 9** CCW |

**Column guide:** **Tube function** = standard data-sheet name. **This amp** = net, harness, or part on **this** rebuild. Items marked **buzz** still need a continuity check at Part 5.

**PCB silk ≠ PDF on EL34 pads** (trace-read on [`preamp board top center.png`](../photos/preamp%20board%20top%20center.png)):

| PCB silk | EL34 pin(s)   | PDF role                        | Notes                                                                                                    |
| -------- | ------------- | ------------------------------- | -------------------------------------------------------------------------------------------------------- |
| **R13**  | **5**         | **R13** / **R16** grid path     | Landing for **C4**; **1 kΩ** stopper body is on the **octal socket** ([8-pin chassis](8-pin-chassis.md)) |
| **R16**  | **1** + **8** | **R17** / **R18** cathode sense | **1 Ω** white ceramic to **GND**; **GRN** branches to **TP1** (probe only)                               |

### V3 — EL34 (LFT, push-pull half A)

| Pin   | Tube function     | This amp                                                                                                                                        |
| ----- | ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| **1** | Suppressor (g3)   | Tied to pin **8** at socket and on preamp PCB → pad **R16**                                                                                     |
| **2** | Heater            | **V3/V4 HEAT** — **BLK/WHT** twisted (PT coil **BRN/BRN**)                                                                                      |
| **3** | Plate             | OT primary **ORG** (label **V3 PIN 3/4** with **YEL** on pin **4**)                                                                             |
| **4** | Screen (UL)       | OT primary **YEL** (twisted with **ORG** on pin **3**)                                                                                          |
| **5** | Control grid (g1) | Pad **R13** ← **C4** ← **RV2** wiper → harness → **1 kΩ** stopper at socket → pin **5**                                                         |
| **6** | —                 | NC (no factory connection)                                                                                                                      |
| **7** | Heater            | **V3/V4 HEAT** — other leg of twisted pair                                                                                                      |
| **8** | Cathode           | Tied to pin **1** · pad **R16** → **1 Ω** ceramic (PDF **R17**) → GND · **BLK** from chassis socket · **GRN** → **TP1** pad **V3** (~**40 mV**) |

### V4 — EL34 (LFT, push-pull half B)

| Pin   | Tube function     | This amp                                                                                                                |
| ----- | ----------------- | ----------------------------------------------------------------------------------------------------------------------- |
| **1** | Suppressor (g3)   | Tied to pin **8** → pad **R16′**                                                                                        |
| **2** | Heater            | **V3/V4 HEAT** — **BLK/WHT** twisted                                                                                    |
| **3** | Plate             | OT primary **BRN** (label **V4 PIN 3/4** with **WHT** on pin **4**)                                                     |
| **4** | Screen (UL)       | OT primary **WHT** (twisted with **BRN** on pin **3**)                                                                  |
| **5** | Control grid (g1) | Pad **R13′** ← **C4** ← **RV3** wiper → harness → **1 kΩ** stopper at socket → pin **5**                                |
| **6** | —                 | NC                                                                                                                      |
| **7** | Heater            | **V3/V4 HEAT** — other leg                                                                                              |
| **8** | Cathode           | Tied to pin **1** · pad **R16′** → **1 Ω** ceramic (PDF **R18**) → GND · **BLK** from socket · **GRN** → **TP1** **V4** |

### V7 — EL34 (RT, push-pull half A)

Same as **V3** except:

| Pin          | This amp (RT deltas vs **V3**)                                              |
| ------------ | --------------------------------------------------------------------------- |
| **2**, **7** | **V7/V8 HEAT** — **YEL/YEL** twisted (PT coil **YEL/YEL**)                  |
| **3**, **4** | OT **ORG** + **YEL** — label **V7 PIN 3/4**                                 |
| **5**        | Pad **R13** (RT) ← **C4** ← **RV2′** wiper                                  |
| **8**        | Pad **R16** (RT) → **1 Ω** ceramic (PDF **R17**) · **GRN** → **TP1** **V7** |

### V8 — EL34 (RT, push-pull half B)

Same as **V4** except:

| Pin          | This amp (RT deltas vs **V4**)                                               |
| ------------ | ---------------------------------------------------------------------------- |
| **2**, **7** | **V7/V8 HEAT** — **YEL/YEL** twisted                                         |
| **3**, **4** | OT **BRN** + **WHT** — label **V8 PIN 3/4**                                  |
| **5**        | Pad **R13′** (RT) ← **C4** ← **RV3′** wiper                                  |
| **8**        | Pad **R16′** (RT) → **1 Ω** ceramic (PDF **R18**) · **GRN** → **TP1** **V8** |

### V1 — 12AX7 (LFT input / gain — SRPP)

The 12AX7 is an **SRPP** (two triodes stacked): bottom triode = input stage, top triode rides on it, and the stage **output is the top cathode**, **direct-coupled** (no cap) to the 12AT7 grid. On **V1** the **top** triode is pins **6/7/8** — confirmed by the desoldered **R51 + \*C51 series** chain spanning pins **6 ↔ 8** ([`preamp board bottom.png`](../photos/preamp%20board%20bottom.png)). **V5 uses the opposite halves** (mirrored layout).

| Pin   | Section   | Tube function | This amp                                                                                                                          |
| ----- | --------- | ------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| **1** | (B) input | Plate         | Direct-coupled node — ties to pin **7** (top grid) and PDF **R2** **1 kΩ** → pin **8** (**buzz** — locate R2 pads)                |
| **2** | (B) input | Grid          | **L IN** ← selector + volume · grid leak PDF **R26** **100 kΩ** → GND (**buzz** silk pad)                                         |
| **3** | (B) input | Cathode       | PDF **R3** **470 Ω** → GND · global NFB in — **R5′ 27 kΩ** ∥ **\*C2 20 pF** ← pad **LFN** ← **LEFT FEEDBACK** (**buzz**)          |
| **4** | Heater    | —             | **PREAMP HEAT** **WHT/WHT** (PT tag **5**) — pins **4+5** tied · **PDF RF1 1 kΩ → GND** at this socket (heater reference)         |
| **5** | Heater    | —             | **PREAMP HEAT** (other **WHT**)                                                                                                   |
| **6** | (A) top   | Plate         | **+B** (front-end rail) · **R51 10 kΩ + \*C51 100 pF in series → pin 8** (socket-pin; disc end at pin **6** as-built)             |
| **7** | (A) top   | Grid          | Direct to pin **1** (input-triode plate) — **no coupling cap** (SRPP)                                                             |
| **8** | (A) top   | Cathode       | **SRPP output** — direct-coupled to **V2** signal grid (sits ≈ ½ B+) · far end of pin-6 series network · PDF **R2** → pin **1/7** |
| **9** | Heater    | —             | Other **6.3 V** leg (heater legs are pins **4+5** vs **9** — **buzz** at socket)                                                  |

### V2 — 12AT7 (LFT phase inverter + driver)

Long-tail pair, **direct-coupled** from the **V1** SRPP output (both grids sit ≈ ½ B+ — hence tail **R6 15 kΩ / 3 W**). **No R51/\*C51 here** — that network lives on the **12AX7** sockets. Which triode half is the signal side (pins **1/2/3** vs **6/7/8**) is **not yet confirmed** — **buzz** from **V1 pin 8**.

| Pin   | Section | Tube function | This amp                                                                                                           |
| ----- | ------- | ------------- | ------------------------------------------------------------------------------------------------------------------ |
| **1** | **(A)** | Plate         | LTP plate — load **R7 22 kΩ** or **R8 24 kΩ** → B+ · coupling cap (**C3**/**C4**) → one EL34 grid (**buzz** which) |
| **2** | **(A)** | Grid          | Signal grid ← **direct** from **V1 pin 8** (≈ ½ B+, no cap) — **or** the AC-ground grid; **buzz** which half       |
| **3** | **(A)** | Cathode       | LTP common cathode with pin **8** → tail **R6** **15 kΩ / 3 W** → GND                                              |
| **4** | Heater  | —             | **PREAMP HEAT**                                                                                                    |
| **5** | Heater  | —             | **PREAMP HEAT**                                                                                                    |
| **6** | **(B)** | Plate         | LTP plate — the other of **R7**/**R8** · coupling cap → the other EL34 grid (**V3**/**V4** pin **5** via stopper)  |
| **7** | **(B)** | Grid          | AC-ground grid — **R4 1 MΩ** ← signal grid · **C1 0.47 µF** → GND — **or** the signal grid; **buzz**               |
| **8** | **(B)** | Cathode       | Common with pin **3**                                                                                              |
| **9** | Heater  | —             | Other **6.3 V** leg (**buzz**)                                                                                     |

### V5 — 12AX7 (RT input / gain — SRPP)

Same SRPP as **V1** but on the **opposite triode halves**: on **V5** the **top** triode is pins **1/2/3** — confirmed by the desoldered **R51 + \*C51 series** chain spanning pins **1 ↔ 3**.

| Pin   | Section   | Tube function | This amp                                                                                                                      |
| ----- | --------- | ------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| **1** | (A) top   | Plate         | **+B** (front-end rail) · **R51 10 kΩ + \*C51 100 pF in series → pin 3** (socket-pin; disc end at pin **3** as-built)         |
| **2** | (A) top   | Grid          | Direct to pin **6** (input-triode plate) — **no coupling cap** (SRPP)                                                         |
| **3** | (A) top   | Cathode       | **SRPP output** — direct-coupled to **V6** signal grid (≈ ½ B+) · far end of pin-1 series network · PDF **R2′** → pin **6/2** |
| **4** | Heater    | —             | **PREAMP HEAT** — pins **4+5** tied                                                                                           |
| **5** | Heater    | —             | **PREAMP HEAT**                                                                                                               |
| **6** | (B) input | Plate         | Direct-coupled node — ties to pin **2** (top grid) and PDF **R2′** **1 kΩ** → pin **3** (**buzz**)                            |
| **7** | (B) input | Grid          | RT input net ← selector + volume · grid leak PDF **R26′** **100 kΩ** → GND (**buzz**)                                         |
| **8** | (B) input | Cathode       | PDF **R3′** **470 Ω** → GND · global NFB in — **R5 ∥ \*C2** ← pad **RFN** ← **RIGHT FEEDBACK** (**buzz**)                     |
| **9** | Heater    | —             | Other **6.3 V** leg · **PDF RF2 1 kΩ → GND** at this socket (heater reference)                                                |

### V6 — 12AT7 (RT phase inverter + driver)

Same as **V2** with RT / primed parts; signal grid ← **direct** from **V5 pin 3** (SRPP output). **No R51/\*C51 here.**

| Pin   | Section | Tube function | This amp                                                                                      |
| ----- | ------- | ------------- | --------------------------------------------------------------------------------------------- |
| **1** | **(A)** | Plate         | LTP plate — **R7′**/**R8′** load · coupling cap → one EL34 grid (**buzz** which)              |
| **2** | **(A)** | Grid          | Signal grid ← **direct** from **V5 pin 3** — **or** AC-ground grid; **buzz** which half       |
| **3** | **(A)** | Cathode       | LTP common cathode with pin **8** → tail **R6′** **15 kΩ / 3 W** → GND                        |
| **4** | Heater  | —             | **PREAMP HEAT**                                                                               |
| **5** | Heater  | —             | **PREAMP HEAT**                                                                               |
| **6** | **(B)** | Plate         | LTP plate — the other load · coupling cap → the other EL34 grid (**V7**/**V8** pin **5**)     |
| **7** | **(B)** | Grid          | AC-ground grid — **R4′ 1 MΩ** ← signal grid · **C1′ 0.47 µF** → GND — **or** signal; **buzz** |
| **8** | **(B)** | Cathode       | Common with pin **3**                                                                         |
| **9** | Heater  | —             | Other **6.3 V** leg (**buzz**)                                                                |

Detail for harness landings: [`8-pin-chassis.md`](8-pin-chassis.md) · [`preamp-board.md`](preamp-board.md) · [`OT.md`](OT.md).

---

## Dual-triode sections — (A) and (B)

**V1**, **V2**, **V5**, and **V6** are each **one glass envelope, one noval socket, two triodes.** The factory schematic draws them as **V1(A)** + **V1(B)** (same for V2, V5, V6).

Pin labels on the PDF use **`1(6)` `2(7)` `3(8)`** — number before **`(`** = section **(A)**; inside **`(`** = section **(B)**.

### 12AX7 / 12AT7 — 9-pin noval (standard pinout)

| Section | Plate | Grid  | Cathode | Heater                          |
| ------- | ----- | ----- | ------- | ------------------------------- |
| **(A)** | **1** | **2** | **3**   | **4**, **5** (often **9** tied) |
| **(B)** | **6** | **7** | **8**   | shared with (A)                 |

### Left channel signal path (factory PDF)

The 12AX7 front end is an **SRPP** (stacked triodes, output at the top cathode), **direct-coupled** into the 12AT7 long-tail pair — no coupling cap between the AX7 and AT7, so the LTP grids sit at ≈ ½ B+ (that DC is why tail **R6** is a **3 W** part).

| Stage      | Tube           | Pins (P/G/K)        | Function                                                                                                                |
| ---------- | -------------- | ------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| SRPP input | **V1(B)**      | **1 / 2 / 3**       | Input triode — selector + volume → grid **2**; **R3 470 Ω** cathode; **global NFB** (**R5′ ∥ \*C2**) → cathode **3**    |
| SRPP top   | **V1(A)**      | **6 / 7 / 8**       | Stacked triode — grid **7** direct to plate **1**; **R2 1 kΩ** 8→1; output at cathode **8**; **R51 + \*C51 series** 6→8 |
| LTP        | **V2**         | **1,6 / 2,7 / 3,8** | Phase inverter — signal grid ← **V1 pin 8** direct; other grid **R4 1 MΩ** + **C1** → AC GND; tail **R6 15 kΩ / 3 W**   |
| Output     | **V3**, **V4** | see below           | Each LTP plate → coupling cap (**C3**/**C4**) → EL34 grid; push-pull → OT → speakers                                    |

Right channel: replace **V1** → **V5**, **V2** → **V6**, **V3** → **V7**, **V4** → **V8**, **R5′** → **R5**, LFT posts → RT posts — **and swap the triode halves**: on **V5** the SRPP top is pins **1/2/3** and the input triode is **6/7/8** (mirrored PCB; confirmed by the desoldered **R51 + \*C51** chains — **V1: 6 ↔ 8**, **V5: 1 ↔ 3**).

Per-pin tables: [V1](#v1--12ax7-lft-input--gain--srpp) · [V2](#v2--12at7-lft-phase-inverter--driver) · [V5](#v5--12ax7-rt-input--gain--srpp) · [V6](#v6--12at7-rt-phase-inverter--driver).

Detail: [`preamp-board.md`](preamp-board.md) (NFB, bias, **C4**) · [`8-pin-chassis.md`](8-pin-chassis.md) (EL34 sockets).

---

## EL34 — one tube, one socket (V3, V4, V7, V8)

No **(A)/(B)** split. Per-pin tables: [V3](#v3--el34-lft-push-pull-half-a) · [V4](#v4--el34-lft-push-pull-half-b) · [V7](#v7--el34-rt-push-pull-half-a) · [V8](#v8--el34-rt-push-pull-half-b). Summary (octal, key toward rear):

| Pin          | Function        | This amp                                                                                                      |
| ------------ | --------------- | ------------------------------------------------------------------------------------------------------------- |
| **2**, **7** | Heater 6.3 V    | **V3/V4 HEAT** (**BLK/WHT**, coil **BRN/BRN**) · **V7/V8 HEAT** (**YEL/YEL**) — [`labels.md`](labels.md)      |
| **3**        | Plate           | OT primary **ORG** or **BRN**                                                                                 |
| **4**        | Screen (UL tap) | OT primary **YEL** or **WHT**                                                                                 |
| **1**, **8** | g3 + cathode    | Tied · preamp pad **R16** → **1 Ω** ceramic → GND · **GRN** → **TP1** (sense only)                            |
| **5**        | Control grid    | Preamp pad **R13** ← **C4** · **1 kΩ** stopper at socket ([socket-pin parts](parts-list.md#socket-pin-parts)) |

Factory test labels: **V3-TP**, **V4-TP**, **V7-TP**, **V8-TP** = pin **8** (~**40 mV** target across the **1 Ω** sense resistor on the preamp board — **replace** those resistors at rebuild).

---

## EL34 cathode sense (PDF **R17 / R18**)

**Replace** four **1 Ω / 5 W** white ceramics at rebuild. Each sits on the [**preamp board**](preamp-board.md) between pad **R16** (pins **1** + **8** side) and **GND** — **not** on the octal socket. **Do not confuse** PCB silk **R16** (cathode / sense) with silk **R13** (pin **5** grid landing) or PDF **R13** / **R16** (the **1 kΩ** grid stopper at the socket).

| PDF     | PCB silk (cathode pad) | Value   | Tube   | Channel |
| ------- | ---------------------- | ------- | ------ | ------- |
| **R17** | **R16**                | **1 Ω** | **V3** | LFT     |
| **R18** | **R16′**               | **1 Ω** | **V4** | LFT     |
| **R17** | **R16** (RT / primed)  | **1 Ω** | **V7** | RT      |
| **R18** | **R16′** (RT / primed) | **1 Ω** | **V8** | RT      |

```text
Each EL34 (octal on 8-pin chassis; pins 1+8 tied at socket and on preamp PCB):
  pin 5:  pad R13 ──► C4 ◄── RV wiper; harness ──► 1 kΩ at socket ──► pin 5
  pin 8:  pins 1+8 ── pad R16 ──┬── 1 Ω ceramic (PDF R17/R18) ──► GND
                                ├── BLK from chassis socket
                                └── GRN ──► TP1 (bias read ~40 mV; sense only)
```

**Install:** one new **1 Ω** per tube at the **R16-family** pad; **BLK** from that tube’s socket **pin 8** to the pad; **GRN** from **pin 8** to the named **TP1** pad ([`8-pin-chassis.md`](8-pin-chassis.md)). Inventory: [`parts-list.md`](parts-list.md).

**Check:** ~**1 Ω** pin **8** → **GND** before trusting **TP1** (~**40 mV** = ~**40 mA** idle).

---

## Parts soldered at socket pins

Parts that mount **on the socket lugs** (octal or noval), not on preamp PCB silk **R1–R15**. Inventory: [`parts-list.md`](parts-list.md#socket-pin-parts).

**PCB at tube pads (not socket-pin):** **R17 / R18** cathode sense — [above](#el34-cathode-sense-pdf-r17--r18). **Silk R2** (metered 10 kΩ) is a **PCB** part, not **PDF R51**. Note: **PDF R2** (SRPP, cathode→grid of the top triode) draws **1 kΩ** — re-meter silk **R2/R2′** (5-band brn-blk-blk-**red**-brn = 10 k, but a **brn** 4th band = 1 k) and buzz its pads before stuffing.

### Octal — EL34 grid stopper (PDF **R13** / **R16**)

One **1 kΩ** per power tube, body at the socket, **pin 5** in series with the grid. **C4** lands on preamp pad **R13** / **R13′**; the stopper sits in the harness at the **octal socket**.

| Tube   | Channel | Socket pin | Part         | Value    | Preamp pad | Harness / notes               |
| ------ | ------- | ---------- | ------------ | -------- | ---------- | ----------------------------- |
| **V3** | LFT     | **5**      | Grid stopper | **1 kΩ** | **R13**    | **C4** → pad → stopper → grid |
| **V4** | LFT     | **5**      | Grid stopper | **1 kΩ** | **R13′**   | same                          |
| **V7** | RT      | **5**      | Grid stopper | **1 kΩ** | **R13**    | same                          |
| **V8** | RT      | **5**      | Grid stopper | **1 kΩ** | **R13′**   | same                          |

Detail: [`8-pin-chassis.md`](8-pin-chassis.md) · photos [`8 pin 5.png`](../photos/8%20pin%205.png).

### Noval — PDF **R51** + **\*C51** in **series** (12AX7 SRPP)

**No R51 silk** on the Jolida preamp PCB. Factory PDF **R51** = **10 kΩ** **in series with** **\*C51** (**100 pF / 1 kV** disc), soldered at the **12AX7** sockets (**V1** / **V5**) from the SRPP **top-triode plate** to its **cathode**. The plate is on the front-end B+ rail (AC ground), so the network is an HF shunt across the top triode / SRPP output. Confirmed against the factory PDF and the desoldered parts (2026-07-28) — earlier notes calling this a **parallel** network on the **12AT7** plate were **wrong**.

| Tube   | Channel | Socket pins                     | Network (as-built order)               | Status                   |
| ------ | ------- | ------------------------------- | -------------------------------------- | ------------------------ |
| **V1** | LFT     | **6** (plate) ↔ **8** (cathode) | pin 6 → **100 pF** → **10 kΩ** → pin 8 | on hand (desoldered set) |
| **V5** | RT      | **1** (plate) ↔ **3** (cathode) | pin 3 → **100 pF** → **10 kΩ** → pin 1 | on hand (desoldered set) |

Series order (which end carries the disc) doesn't matter electrically — match the photos ([`preamp board bottom.png`](../photos/preamp%20board%20bottom.png)). The old **100 pF** discs and **10 kΩ** resistors can be reused; new **brn-blk-org** 10 kΩ are on hand if a lead is too short.

Inventory: [`parts-list.md`](parts-list.md#socket-pin-parts).

### Noval — PDF **RF1** / **RF2** heater reference (1 kΩ → GND)

The small-tube **6.3 V** heater winding is referenced to ground by a **1 kΩ from each leg** (split artificial center tap, bottom-right of the PDF heater section — the pilot LED also hangs off this winding). Physically each resistor sits at a noval socket:

| PDF     | Tube   | Socket pin           | Value    | Connection | Status                   |
| ------- | ------ | -------------------- | -------- | ---------- | ------------------------ |
| **RF1** | **V1** | **4** (heater leg A) | **1 kΩ** | pin → GND  | on hand (desoldered set) |
| **RF2** | **V5** | **9** (heater leg B) | **1 kΩ** | pin → GND  | on hand (desoldered set) |

One resistor per **leg** (not per socket) — that's why the pair lands on different pins of different sockets.

**\*C2** (20 pF, NFB) is a **board** part in parallel with silk **R5** — not a socket-pin network.

---

## Preamp **C1** (PDF)

Factory blue **CBB 400 V** film (**0.47 µF** / **474J** class) on the [**preamp board**](preamp-board.md) — **left in place** on this rebuild (not replaced). Per the factory PDF, **C1** grounds the **non-signal grid of the 12AT7 long-tail pair** for AC (with **R4 1 MΩ** feeding that grid its DC bias) — one per channel. Bodies are on the **solder side** as-built.

| PDF **C1** | Value               | Role                                     | Board      | Status                                          |
| ---------- | ------------------- | ---------------------------------------- | ---------- | ----------------------------------------------- |
| **C1**     | **0.47 µF / 400 V** | LTP non-signal grid → AC GND (**V2/V6**) | Preamp PCB | **in place** — [`parts-list.md`](parts-list.md) |

---

## Bias trim pots (naming collision)

| Pot (PCB silk) | PDF / factory role | Adjusts                           |
| -------------- | ------------------ | --------------------------------- |
| **RV2**        | Bias trim          | **V3** grid (LFT)                 |
| **RV3**        | Bias trim          | **V4** grid (LFT)                 |
| **RV2′**       | Bias trim          | **V7** grid (RT) — map at rebuild |
| **RV3′**       | Bias trim          | **V8** grid (RT) — map at rebuild |

**RV2** is **not** tube **V2**. Large Cap Board **TP1** silk **V3/V4** names the **bias sense pads** for those tubes — not the trim pots.

---

## Quick lookup

```text
LFT:  V2 (driver)  V1 (12AX7)     |  rear: V3  V4
RT:        V5 (12AX7)  V6 (driver)  |  rear: V8  V7   ← rear order mirrored

Circuit mirror:  V1↔V5   V2↔V6   V3↔V7   V4↔V8
Push-pull:       V3+V4 (LFT)        V7+V8 (RT)
```

---

## Related

- [`preamp-board.md`](preamp-board.md) — noval sockets, NFB, bias network, **C4**
- [`8-pin-chassis.md`](8-pin-chassis.md) — EL34 PTP, heaters, **C3** sense
- [`OT.md`](OT.md) — OT primaries per channel
- [`large-cap-board.md`](large-cap-board.md) — **TP1** pads (**V3/V4/GND/V3/V4** silk)
- [`labels.md`](labels.md) — applied PT labels (**WALL AC**, **PT HV**, **70V IN**, **PT GND**, **PREAMP HEAT**, **V3/V4 HEAT**, **V7/V8 HEAT**)
- [`parts-list.md`](parts-list.md) — tube stock · [socket-pin parts](parts-list.md#socket-pin-parts)
- [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) — topology reference

## Changelog

| Date       | Change                                                                                                                                                                                                                                                           |
| ---------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 2026-07-28 | **SRPP front end** — **R51 + \*C51 in series** at the **12AX7** plate→cathode (**V1 6↔8**, **V5 1↔3**), not parallel on the 12AT7; **RF1/RF2** 1 kΩ heater refs (V1 pin 4, V5 pin 9); V1/V5/V2/V6 maps + signal path rewritten; **C1** role = LTP grid AC-ground |
| 2026-07-27 | **Pin-by-pin maps** — V1–V8; PCB **R13** = pin **5**, **R16** = pin **1+8** / **1 Ω** sense                                                                                                                                                                      |
| 2026-07-20 | **C1** blue film **in place**; **R17/R18** replace at rebuild                                                                                                                                                                                                    |
| 2026-07-20 | Socket-pin parts table (**R51**, grid stoppers)                                                                                                                                                                                                                  |
| 2026-07-18 | Created — V1–V8 naming authority for docs and future Eagle export                                                                                                                                                                                                |
