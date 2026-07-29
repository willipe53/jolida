# Connectors (C1–C6)

> **ARCHIVED 2026-07-12** — superseded by the per-component docs, which carry the corrected harness definitions (C3 was redefined; C2 fully mapped). Current owners: **C1** → [`large-cap-board.md`](../docs/large-cap-board.md) · **C2** → [`preamp-board.md`](../docs/preamp-board.md) · **C3/C4** → [`8-pin-chassis.md`](../docs/8-pin-chassis.md) · **C5** → [`front-panel.md`](../docs/front-panel.md) · **C6** → [`back-panel.md`](../docs/back-panel.md) · grounding → [`chassis.md`](../docs/chassis.md). Some harness details below are **known-wrong** (e.g. C3 rails, "−B not on C2").

Modular rebuild plan for **this chassis**. Goal: segment the project into testable assemblies and **confirm success at each step** as parts arrive.

**Status:** Plan · pinouts **TBD** — assign during reassembly; cross-check with [`wire-tags.md`](wire-tags.md).

---

## Rules (two only)

| Wire       | Treatment                                                                                      |
| ---------- | ---------------------------------------------------------------------------------------------- |
| **18 AWG** | **Solder / hardwire only** — never through a connector. Keep heater pairs **twisted tightly**. |
| **22 AWG** | **Molex Micro-Fit 3.0** — all signal and panel paths.                                          |

**Power harnesses C1–C3** are named solder boundaries (not pluggable). **Signal harnesses C4–C6** are Micro-Fit plugs.

### Why 18 AWG never uses connectors

| Concern                    | Reason                                                                |
| -------------------------- | --------------------------------------------------------------------- |
| **B+ voltage** (~425 V DC) | Micro-Fit 3.0 is 250 V rated — not suitable for B+ or HV              |
| **Heater hum**             | Connectors break the twist at the junction                            |
| **Assembly risk**          | Routing fat power leads through housings adds bulk and failure points |

C1–C3 require desoldering to separate — accepted trade-off for a safe power path.

---

## Six components

| Component           | What it is                                                                                                                                                    |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Preamp Board**    | Green PCB with four 9-pin (noval) sockets                                                                                                                     |
| **Large Cap Board** | Vertical AC/DC PCB (see [`large-cap-board.md`](../docs/large-cap-board.md))                                                                                   |
| **8-pin Chassis**   | Rear four octal (EL34) sockets — chassis point-to-point                                                                                                       |
| **Transformers**    | Power Transformer + Output Transformer                                                                                                                        |
| **Back Panel**      | AC inlet, fuse, RCA inputs, speaker binding posts                                                                                                             |
| **Front Panel**     | Volume, power LED (LED **GRN** on preamp socket · **BLU** to panel — not on **C5**) — **input selector not used** (four RCAs paralleled at preamp via **C6**) |

---

## Assembly: Transformers And Back Panel

Treat **Transformers** and **Back Panel** as one built unit before connecting anything else.

### Hardwired inside this assembly (no connector)

| Connection                                                        | Notes             |
| ----------------------------------------------------------------- | ----------------- |
| Back Panel AC inlet → Power Transformer primary                   | 18 AWG — hardwire |
| Output Transformer secondaries → Back Panel speaker binding posts | Heavy gauge       |
| Chassis ground → Back Panel earth / RCA ground reference          | Hardwire          |
| Output Transformer primary-side wiring toward **8-pin Chassis**   | Hardwire          |

**C1** is the wiring bundle out of this assembly to the **Large Cap Board** — soldered on both ends.

---

## Interface summary

| ID     | Between                                           | Treatment                    | Wire   | Carries                                                                                                                                                                       |
| ------ | ------------------------------------------------- | ---------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **C1** | Transformers And Back Panel ↔ **Large Cap Board** | **Hardwire**                 | 18 AWG | PT HV AC, 50 V aux, mains primary, safety earth, GND (+ heater WHT to preamp, BRN/YEL to EL34 sockets — see [C1](#c1--transformers-and-back-panel--large-cap-board-hardwire)) |
| **C2** | **Large Cap Board** ↔ **Preamp Board**            | **Hardwire**                 | 18 AWG | **+B1**, **+B2**, GND (heater WHT if via Large Cap Board — otherwise direct from PT)                                                                                          |
| **C3** | **Large Cap Board** ↔ **8-pin Chassis**           | **Hardwire**                 | 18 AWG | **+B**, **+B1**, **+B2**, **−B1** (bias), GND — the four GRN wires at TP1                                                                                                     |
| **C4** | **Preamp Board** ↔ **8-pin Chassis**              | **Micro-Fit 4-pin**          | 22 AWG | Driver → EL34 grids                                                                                                                                                           |
| **C5** | **Front Panel** ↔ **Preamp Board**                | **Micro-Fit 6-pin** (3 used) | 22 AWG | Volume pot only — **LED not on C5** (see [C5](#c5--front-panel--preamp-board-micro-fit-30-6-pin-housing-3-used))                                                              |
| **C6** | **Back Panel** ↔ **Preamp Board**                 | **Micro-Fit 4-pin**          | 22 AWG | RCA input centers (×4, paralleled at preamp)                                                                                                                                  |

---

## Grounding — chassis star point

All circuit grounds meet at **one chassis stud** — the **star**. On this unit it sits center-frame, just right of the **TP1** test-point header, in the shadow between the Large Cap Board and the filter-cap bank ([`assembled from bottom.png`](../photos/assembled%20from%20bottom.png)).

### Two kinds of "ground" (do not confuse)

| Kind                       | Job                                           | Path                                                            |
| -------------------------- | --------------------------------------------- | --------------------------------------------------------------- |
| **Safety earth** (GRN/YEL) | Fault current → mains earth (protects you)    | IEC inlet earth pin → **chassis stud**, short/thick/most secure |
| **Signal / circuit GND**   | 0 V reference for audio + DC (protects sound) | Each assembly → star, without daisy-chaining through the preamp |

**AC mains:** only the **earth** prong touches the chassis. **HOT** → fuse → PT primary; **NEUTRAL** → PT primary. **Never** bond neutral to the chassis.

### What lands on the star (this chassis)

| Lug at star             | Path                                                                           | Confidence                             |
| ----------------------- | ------------------------------------------------------------------------------ | -------------------------------------- |
| **Large Cap Board GND** | Heavy black lead from board ground pour                                        | High (owner recall)                    |
| **Preamp Board GND**    | Black lead from preamp pour (**PT tag-9 BLK**, PT-L5)                          | High (owner recall)                    |
| **OT / speaker G**      | OT secondary common (**BLK**) → speaker **G** binding post → black wire → star | High (photo)                           |
| **IEC safety earth**    | GRN/YEL from AC inlet                                                          | **Verify on rebuild** — must land here |

**Not wired to the star:** **RCA shells** reference through the **back-panel metal** (panel-to-chassis), not a discrete wire.

### How they were joined (as-built)

The grounds appeared to **all arrive at the star together**: leads wound/twisted together, crimped into a single **ring terminal**, then the whole joint **soldered over**. Practical to replicate, but note the trade-off:

- **Pro:** one solid mechanical/electrical tie; nothing floats.
- **Con:** it is a **daisy-tie**, not true independent star legs — the board and speaker returns share the last bit of that ring. For this amp it evidently worked; if hum shows up at power-up, separate the legs so each ground arrives at the stud on its own before combining.

### Rebuild checklist

- [ ] **IEC earth (GRN/YEL)** on the star stud — shortest, thickest, tightened hard; serrated/star washer; **bare metal-to-metal** (no paint/powder-coat under the lug).
- [ ] Confirm **PT / OT frames** have continuity to chassis through their mounting bolts (coated feet can leave a frame floating — add a star washer or bonding strap).
- [ ] Speaker **G** post references back to the star (OT common tie).
- [ ] Large Cap Board + Preamp Board grounds land at the star.
- [ ] If replicating the wound-ring-then-solder joint, still bring **IEC earth as its own lug** — do not bury safety earth inside a soldered bundle where a cold joint could isolate it.

---

## C1 — Transformers And Back Panel ↔ Large Cap Board (hardwire)

Solder joints. Documented here as a **verification checklist**, not a connector pinout.

| Wire                                | Function                                                                                                                      | Tag    |
| ----------------------------------- | ----------------------------------------------------------------------------------------------------------------------------- | ------ |
| **PT HV** — **RED** (PT-L1)         | ~300 V AC → **VD3–VD6** bridge ([`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png)) | **21** |
| **PT HV return** — **BLK** (PT-L2)  | 0 V of HV winding                                                                                                             | **11** |
| **PT 50 V aux** — **BLU** (PT-L3)   | Twisted pair to Large Cap Board → **VD7** / **C7** ("70V IN" silk)                                                            | **17** |
| **PT 50 V aux** — **BLU** (PT-L4)   | Same twisted pair                                                                                                             | **19** |
| **PT preamp GND** — **BLK** (PT-L5) | Label **0** → preamp board GND pour (not Large Cap Board)                                                                     | **9**  |
| **Chassis / star GND**              | Star point at chassis stud                                                                                                    | —      |
| **PT primary 115 V** — **RED**      | Merged **RED1 + RED2** → AC inlet **HOT**                                                                                     | **21** |
| **PT primary 115 V** — **ORG**      | Merged **ORG1 + ORG2** → AC inlet **NEUTRAL**                                                                                 | **23** |
| **IEC safety earth** — **GRN/YEL**  | AC inlet earth pin → chassis stud (short, thick, star point)                                                                  | —      |

**Heater harness — three 6.3 V pairs (routed separately from C1 to their tube destinations):**

| Pair (at coil) | Coil DCR (PT.md) | Tag at coil      | Destination                                                         | Load                                   |
| -------------- | ---------------- | ---------------- | ------------------------------------------------------------------- | -------------------------------------- |
| **WHT / WHT**  | 2.5 Ω            | **5×2** (tagged) | **Preamp board** (via bottom-left edge — see photo)                 | 4 preamp tubes @ ~0.3 A ea = **1.2 A** |
| **BRN / BRN**  | 2.2 Ω            | untagged at coil | **EL34 heaters — one channel** (V3/V4 **or** V7/V8, PTP at sockets) | 2 EL34 @ 1.5 A = **3.0 A**             |
| **YEL / YEL**  | 2.2 Ω            | untagged at coil | **EL34 heaters — other channel**                                    | 2 EL34 @ 1.5 A = **3.0 A**             |

**Notes:**

- Only **WHT** has a factory tag at the coil (**tag 5**, pair notation `5×2`). **BRN** and **YEL** pairs were **untagged at the coil** — see [`PT.md`](../docs/PT.md) DCR table. Hand-schematic notations `1×2` / `10×2` are legacy labels from disassembly-side stubs, not coil tags — **use color at the coil as ground truth**.
- **Channel-separated heaters** (BRN one channel, YEL the other) keeps at max 3 A per 3 A-rated winding — matches PT nameplate.
- **Do NOT parallel the two EL34 windings** unless you first confirm identical phase (dot both ends, meter for 0 V between paralleled hot legs before energizing). Wrong phase = **short across the winding** = smoke.
- Which color goes to which channel (BRN=LFT vs YEL=LFT) is arbitrary — pick one, label it, be consistent.

**Not on C1:** Output Transformer speaker leads (Back Panel wiring, hardwired inside Back Panel assembly).

---

## C2 — Large Cap Board ↔ Preamp Board (hardwire)

Preamp tubes (**12AX7A** V1 / V5, **12AT7** V2 / V6) need HV anode supply + heater + ground — **not** bias.

| Wire                       | Function                                                                   | Tag         |
| -------------------------- | -------------------------------------------------------------------------- | ----------- |
| GND                        | Signal ground → preamp copper pour                                         | TBD         |
| **+B1** (~370 V)           | Driver plate loads **R7 / R8** (22K / 24K) — per factory PDF               | TBD         |
| **+B2** (~220 V)           | Input-stage anode / bias divider — verify against preamp board at bench    | TBD         |
| Heater **WHT/WHT** (tag 5) | Preamp 6.3 V — twisted; **only** if routed via Large Cap Board (see below) | **5×2 WHT** |

**Not on C2:**

- **+B** (~425 V) → goes to **OT primary center tap** via chassis PTP, **not** preamp
- **−B / −B1** (bias) → goes to **bias-trim pots V3/V4/V7/V8** via **C3** / chassis PTP, **not** preamp (12AX7 / 12AT7 are cathode-biased)

**Heater routing:** Per [`photos/preamp board top.png`](../photos/preamp%20board%20top.png), a **WHT/WHT** twisted pair enters the preamp board at the bottom-left edge — the **tag 5** 6.3 V winding feeds the preamp tubes directly. If it enters the preamp board on its own harness (not through the Large Cap Board), the heater row above **belongs on that harness, not C2**.

**Tag numbers:** Numbers **11, 17, 19, 21, 23** appear on **both** the C3 harness (green wires from Large Cap Board TP1 → 8-pin chassis) **and** in the preamp / octal areas of the hand schematic. Those are **separate physical wires** that happened to reuse the same numeric labels during disassembly. **Do not** assume C2 uses tags 11/23/21/19/17 — those are C3. C2 tags need identification at rebuild (or new labels applied).

To bench-test the Large Cap Board alone, unsolder these once at the Preamp Board end.

---

## C3 — Large Cap Board ↔ 8-pin Chassis (hardwire)

**Solder on Large Cap Board:** **TP1** pad cluster (five pads by **AC IN** bridge) — see [`../archive/open-issues.md`](../archive/open-issues.md) **OI-6**.

| Wire color | Tag | Net (Large Cap Board) | 8-pin Chassis                |
| ---------- | --- | --------------------- | ---------------------------- |
| **GRN**    | 23  | **+B**                | Harness / PTP                |
| **GRN**    | 21  | **+B1**               | Harness / PTP                |
| **GRN**    | 19  | **+B2**               | Harness / PTP                |
| **GRN**    | 17  | **−B1** / bias        | Harness / PTP                |
| —          | —   | **GND**               | TP1 center pad → chassis GND |

**EL34 socket pin:** Factory **Vx-TP** (**V3-TP**, **V4-TP**, **V7-TP**, **V8-TP**) = **pin 8** on [`Jolida-JD202A-int-sch.pdf`](../docs/Jolida-JD202A-int-sch.pdf) — bias test (~**40 mV** across **R17/R18** 1 Ω). **Grids** = **pin 5** + **1 kΩ** stopper (**OI-1**, **C4**); **screens** = **pin 4** (OT UL tap).

**Pad ↔ tag order** on the five **TP1** pads was not recorded — label and buzz at rebuild. **18 AWG** green (or match original). Heater pair to octals if routed via Large Cap Board (twisted **18 AWG**).

To bench-test the 8-pin Chassis alone, unsolder **C3** once at the Large Cap Board **TP1** end.

---

## C4 — Preamp Board ↔ 8-pin Chassis (Micro-Fit 3.0, 4-pin)

**One plug + one receptacle, 22 AWG.**

| Pin | Function              |
| --- | --------------------- |
| 1–4 | EL34 control grids ×4 |

### Wires carry DC bias, not just AC signal

Each C4 wire sits on the EL34 grid downstream of coupling cap **C3 / C4** (0.22 µF, per factory PDF) and downstream of the bias-trim pot **V3 / V4 / V7 / V8** wiper. At the socket end it rides at the bias voltage — **≈ −40 V to −54 V DC** (grid-to-ground, tube-dependent) — with the audio riding on top of that DC.

Consequences at rebuild / bench:

- **Do not** measure C4 pins to ground with a scope AC-coupled and expect 0 V baseline; DC offset is real.
- **Do not** short C4 pins to chassis with the amp powered — you'll pull the grid to 0 V, unbias the EL34, and draw runaway plate current.
- When unplugging C4 for bench isolation, always power down + **verify caps discharged** ([`../README.md`](../README.md) Prep) first.
- 22 AWG is fine: current is ~μA (grid draw), voltage is well within Micro-Fit 3.0 rating.

### Hardwired (not on C4)

Output Transformer primaries, cathode/screen PTP on **8-pin Chassis**, anything at tube socket pins — **18 AWG, soldered**.

Unplug **C4** to isolate the **Preamp Board** signal from the power tubes.

---

## C5 — Front Panel ↔ Preamp Board (Micro-Fit 3.0, 6-pin housing, 3 used)

**One plug + one receptacle, 22 AWG.** Kit has no 5-pin housing, so **C5 carries the volume pot only** — pins **4–6** empty.

| Pin | Function   |
| --- | ---------- |
| 1–3 | Volume pot |
| 4–6 | **empty**  |

Input selector **not used** — see **C6** for RCA inputs.

Unplug **C5** to lift the **Front Panel** for pot service.

### Power LED — original wiring (not on C5)

On this chassis the power LED does **not** terminate at a Molex receptacle on the preamp board. Photo evidence ([`LED wires.png`](../photos/LED%20wires.png)):

| Wire (at disassembly) | Factory color           | Preamp end                                                                               | Front panel end            |
| --------------------- | ----------------------- | ---------------------------------------------------------------------------------------- | -------------------------- |
| LED return / drive    | **GRN**                 | **Soldered to a noval (9-pin) socket pin** on the preamp board — not a free harness tail | —                          |
| LED other leg         | **DK BLU** (light blue) | — (series resistor / limit network is on the board near the socket)                      | **Front-panel LED holder** |

Hand schematic ([`hand_schematic.png`](../photos/hand_schematic.png)) marks the indicator pair near the preamp area as **GRN 23 VOL** / **RED 23 VOL** — tag **23** there is the **volume pot** bundle, not the LED; the LED pair had **no numeric tag** ([`../archive/wire-tags.md`](../archive/wire-tags.md)).

**Rebuild:**

1. **GRN** — replicate factory: solder to the same noval socket pin once you buzz it at bench (likely heater-related or +B2-derived — confirm against factory PDF before power-up).
2. **DK BLU** — hardwire to the front-panel LED (+ holder); polarity matters — test with a bench supply / 9 V battery + series 1 kΩ before tube power.
3. **Do not** put both LED legs on **C5** unless you deliberately redesign the harness; the original preamp-board solder point is the reference.

Removing the front panel for service: unplug **C5** (volume) and disconnect the **BLU** lead at the LED holder; **GRN** stays on the preamp board.

---

## C6 — Back Panel ↔ Preamp Board (Micro-Fit 3.0, 4-pin)

**One plug + one receptacle, 22 AWG.** Factory had four RCA inputs and a selector; this rebuild **parallels all four** to one preamp input (same as factory “all inputs active” wiring without the switch).

| Pin | Back Panel end   | Preamp end                          |
| --- | ---------------- | ----------------------------------- |
| 1   | RCA **1** center | Tie to **common preamp input** with |
| 2   | RCA **2** center | pins 3–4 at the **Preamp Board**    |
| 3   | RCA **3** center | receptacle (one signal net)         |
| 4   | RCA **4** center |                                     |

Label each pin with the jack name (AUX / CD / TAPE / TUNER — assign at bench to match panel silk).

**RCA shells** → panel/chassis ground (metal-to-metal; no **C6** pin needed).

### Unused RCA jacks (antenna / hum mitigation)

Paralleled inputs mean any **unconnected** jack acts as an antenna into the preamp. Choose one of these for each unused jack:

| Option                             | Effect                                                                                  |
| ---------------------------------- | --------------------------------------------------------------------------------------- |
| **3D-printed shorting cap** (best) | Center pin shorted to shell → antenna dead; recommended for jacks left empty long-term  |
| **Do not crimp** the C6 pin        | Center wire absent → antenna disconnected from preamp (jack still floats, but harmless) |
| Dust cap only                      | Cosmetic; antenna still lives if C6 pin is populated                                    |

Unplug **C6** to separate **Back Panel** from **Preamp Board** for mount-order dry-fit ([`README.md`](../README.md) Q1).

---

## Back Panel and Preamp Board

| Path                                        | Verdict                                               |
| ------------------------------------------- | ----------------------------------------------------- |
| Back Panel RCA centers → preamp input       | **C6** (22 AWG Micro-Fit)                             |
| Back Panel RCA grounds → chassis            | Panel metal / ground strap to chassis star            |
| Back Panel speaker posts → **Preamp Board** | **No** — **Output Transformer** → **Back Panel** only |

---

## Parts status

### Purchased — JRready ST6515 (Micro-Fit 3.0 kit, 118 pcs)

Amazon: [`JRready ST6515`](https://www.amazon.com/JRready-ST6516-Receptacle-Automotive-Connectors/dp/B0DRHJQSTX) — Molex Micro-Fit 3.0 compatible, 4-pin + 6-pin housings, 20–24 AWG terminals.

**Molex equivalents** (for reference / re-order):

| Item                          | Molex #           | Used for                                      |
| ----------------------------- | ----------------- | --------------------------------------------- |
| Plug housing, 4 circuit       | 43020-0401        | **C4** — EL34 grids; **C6** — RCA inputs      |
| Receptacle housing, 4 circuit | 43025-0400        | **C4**; **C6**                                |
| Plug housing, 6 circuit       | 43020-0601        | **C5** — volume only (3 wires, 3 slots empty) |
| Receptacle housing, 6 circuit | 43025-0600        | **C5**                                        |
| Male pin terminal             | 43031-0001 / 0007 | **C4**, **C5**, **C6**                        |
| Female socket terminal        | 43030-0001 / 0007 | **C4**, **C5**, **C6**                        |

**Crimper:** owned (Micro-Fit 3.0 dies, 20–24 AWG).

Kit ships with ~50+ terminals of each polarity — plenty for practice crimps and mistakes.

### C5 uses 6-pin housing

Kit has no 5-pin, so **C5 = 6-pin housing with three positions used** (volume pot). Pin plan:

| Pin | Function   |
| --- | ---------- |
| 1–3 | Volume pot |
| 4–6 | **empty**  |

Power **LED** is **not** on C5 — see [C5 LED section](#power-led--original-wiring-not-on-c5).

Kit includes **one** 4-pin plug + receptacle pair — used for **C4**. Order a **second 4-pin pair** (43020-0401 + 43025-0400) for **C6**, or a second JRready kit.

### Ordered — wire and heat-shrink

- **22 AWG** stranded — **C4**, **C5**, **C6**
- **18 AWG** stranded — **C1** / **C2** / **C3** solder joints (heaters twisted)
- **Heat-shrink** — over C1–C3 joints and harness strain relief
- **Solder** — assumed on hand for rebuild

Twist heater pairs tightly (~1 turn per cm).

### Connectors — still to buy

- **Second 4-pin** Micro-Fit 3.0 plug + receptacle for **C6** (if not reusing a spare from kit inventory)

**C1–C3** use no connector parts.

---

## Solder-joint checklist (C1–C3)

Run on **every 18 AWG joint** before energizing.

| Step | Action                                                                | ☐   |
| ---- | --------------------------------------------------------------------- | --- |
| 1    | Strip 18 AWG, tin lead, mechanical hook or lap joint                  |     |
| 2    | Solder — bright joint, wire not moving in the joint                   |     |
| 3    | Heat-shrink over the joint; strain-relief at the board                |     |
| 4    | Label each wire near both ends: net + tag (e.g. `+B / tag 23`)        |     |
| 5    | Twist heater pairs tightly, full length                               |     |
| 6    | Cold meter: no short between adjacent nets; GND continuity to chassis |     |
| 7    | After first power-up: visual re-check for discoloration or lift       |     |

## Crimp checklist (C4–C6 Micro-Fit)

| Step | Action                                                   | ☐   |
| ---- | -------------------------------------------------------- | --- |
| 1    | Strip 22 AWG to Micro-Fit spec (short, no stray strands) |     |
| 2    | Crimp terminal — tug test, no movement                   |     |
| 3    | Insert terminal until housing latch clicks               |     |
| 4    | Mark pin 1 on both housings                              |     |
| 5    | Cold meter: no short between adjacent pins               |     |
| 6    | Mate plug into receptacle; unmate once to verify         |     |

---

## Build and test order

Each step ends with a **pass/fail you can see on a meter** before adding the next assembly.

| Step | Assemblies connected                  | Test (tubes out unless noted)                               |
| ---- | ------------------------------------- | ----------------------------------------------------------- |
| 1    | **Transformers And Back Panel** only  | Cold resistance, earth bond                                 |
| 2    | + **C1** solder + **Large Cap Board** | Variac / bulb limiter; B+ rails at Large Cap Board          |
| 3    | + **C2** solder + **Preamp Board**    | Rails + heater at Preamp Board                              |
| 4    | + **C3** solder + **8-pin Chassis**   | B+ and bias at octal sockets                                |
| 5    | + **C4** plug in                      | Grid signal path prep (low voltage checks)                  |
| 6    | + **C5** plug in + **Front Panel**    | Volume pot; LED **GRN** on preamp socket · **BLU** to panel |
| 7    | + **C6** plug in                      | RCA → preamp input                                          |
| 8    | Full                                  | Bias trim → tubes in → signal                               |

**Unplug C4** to isolate Preamp signal from power tubes. **Unplug C5** for Front Panel service. **Unplug C6** to separate Back Panel from Preamp for fit checks. **C1–C3** require desoldering to separate.

---

## Pinout worksheets (fill at bench)

### C1 — solder joints (hardwire)

| Wire | Function            | Tag | Color   | ☐ Soldered | ☐ Metered |
| ---- | ------------------- | --- | ------- | ---------- | --------- |
| 1    | PT HV               | 21  | RED     | ☐          | ☐         |
| 2    | PT HV return        | 11  | BLK     | ☐          | ☐         |
| 3    | PT 50 V aux         | 17  | BLU     | ☐          | ☐         |
| 4    | PT 50 V aux         | 19  | BLU     | ☐          | ☐         |
| 5    | PT preamp GND       | 9   | BLK     | ☐          | ☐         |
| 6    | PT primary HOT      | 21  | RED×2   | ☐          | ☐         |
| 7    | PT primary NEUT     | 23  | ORG×2   | ☐          | ☐         |
| 8    | IEC safety earth    | —   | GRN/YEL | ☐          | ☐         |
| 9    | Chassis star ground | —   |         | ☐          | ☐         |

### Heater harness (separate from C1 bundle — routes direct to tube destinations)

| Pair          | Coil DCR | Tag | Destination                          | ☐ Twisted | ☐ Metered |
| ------------- | -------- | --- | ------------------------------------ | --------- | --------- |
| **WHT / WHT** | 2.5 Ω    | 5×2 | Preamp board bottom-left             | ☐         | ☐         |
| **BRN / BRN** | 2.2 Ω    | —   | EL34 pair — channel **A** (pins 2/7) | ☐         | ☐         |
| **YEL / YEL** | 2.2 Ω    | —   | EL34 pair — channel **B** (pins 2/7) | ☐         | ☐         |

### C2 — solder joints (hardwire)

| Wire | Function            | Tag | Color | ☐ Soldered | ☐ Metered |
| ---- | ------------------- | --- | ----- | ---------- | --------- |
| 1    | GND                 | TBD |       | ☐          | ☐         |
| 2    | **+B1** (~370 V)    | TBD |       | ☐          | ☐         |
| 3    | **+B2** (~220 V)    | TBD |       | ☐          | ☐         |
| 4    | Heater WHT (if via) | 5×2 | WHT   | ☐          | ☐         |
| 5    | Heater WHT return   | 5×2 | WHT   | ☐          | ☐         |

### C3 — solder joints (hardwire)

| Wire | Function | Tag | Color | ☐ Soldered | ☐ Metered |
| ---- | -------- | --- | ----- | ---------- | --------- |
| 1–n  |          |     |       | ☐          | ☐         |

### C4 — Micro-Fit 4-pin

| Pin | Function  | Tag | Color | ☐ Crimped | ☐ Metered |
| --- | --------- | --- | ----- | --------- | --------- |
| 1   | EL34 grid |     |       | ☐         | ☐         |
| 2   | EL34 grid |     |       | ☐         | ☐         |
| 3   | EL34 grid |     |       | ☐         | ☐         |
| 4   | EL34 grid |     |       | ☐         | ☐         |

### C5 — Micro-Fit 6-pin (3 used)

| Pin | Function | Tag | Color | ☐ Crimped | ☐ Metered |
| --- | -------- | --- | ----- | --------- | --------- |
| 1   | Volume   | 23  |       | ☐         | ☐         |
| 2   | Volume   |     |       | ☐         | ☐         |
| 3   | Volume   |     |       | ☐         | ☐         |
| 4–6 | empty    | —   | —     | —         | —         |

**LED (not on C5):** **GRN** → noval socket pin on preamp board · **DK BLU** → front-panel LED — see [C5 LED section](#power-led--original-wiring-not-on-c5).

### C6 — Micro-Fit 4-pin (RCA inputs)

| Pin | Function   | Jack (label at bench) | Color | ☐ Crimped | ☐ Metered |
| --- | ---------- | --------------------- | ----- | --------- | --------- |
| 1   | RCA center |                       |       | ☐         | ☐         |
| 2   | RCA center |                       |       | ☐         | ☐         |
| 3   | RCA center |                       |       | ☐         | ☐         |
| 4   | RCA center |                       |       | ☐         | ☐         |

At **Preamp Board** receptacle: pins **1–4** → common input net.

---

## Related documents

- [`wire-tags.md`](wire-tags.md) — disassembly tag index  
- [`hand-schematic-notes.md`](../docs/hand-schematic-notes.md) — wiring map  
- [`large-cap-board.md`](../docs/large-cap-board.md) — Large Cap Board nets and harness  
- [`../archive/open-issues.md`](../archive/open-issues.md) — bench Q&A tracker (archived)  
- [`gemini-restoration-notes.md`](gemini-restoration-notes.md) — parts and recap planning  

---

## Changelog

| Date       | Change                                                                                     |
| ---------- | ------------------------------------------------------------------------------------------ |
| 2026-07-05 | Initial plan: C1–C5, Transformers And Back Panel assembly                                  |
| 2026-07-05 | 22 AWG Micro-Fit for C4/C5; input selector removed; RCA parallel hardwire                  |
| 2026-07-05 | **Final rule:** 18 AWG hardwired (C1–C3); connectors on **C4/C5 only** (Micro-Fit 3.0)     |
| 2026-07-05 | Purchased JRready ST6515 (4-pin + 6-pin kit); C5 uses 6-pin with one empty slot            |
| 2026-07-05 | Ordered 18 AWG + 22 AWG wire and heat-shrink                                               |
| 2026-07-06 | **Two rules:** 18 AWG solder only; 22 AWG Micro-Fit. **C6** RCA (4-pin); drop RCA hardwire |
