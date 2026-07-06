# Connectors (C1–C6)

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

| Component         | What it is                                                                                  |
| ----------------- | ------------------------------------------------------------------------------------------- |
| **Preamp Board**  | Green PCB with four 9-pin (noval) sockets                                                   |
| **Power Board**   | Vertical AC/DC PCB (see [`power-board.md`](power-board.md))                                 |
| **8-pin Chassis** | Rear four octal (EL34) sockets — chassis point-to-point                                     |
| **Transformers**  | Power Transformer + Output Transformer                                                      |
| **Back Panel**    | AC inlet, fuse, RCA inputs, speaker binding posts                                           |
| **Front Panel**   | Volume, power LED — **input selector not used** (four RCAs paralleled at preamp via **C6**) |

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

**C1** is the wiring bundle out of this assembly to the **Power Board** — soldered on both ends.

---

## Interface summary

| ID     | Between                                       | Treatment                    | Wire   | Carries                                        |
| ------ | --------------------------------------------- | ---------------------------- | ------ | ---------------------------------------------- |
| **C1** | Transformers And Back Panel ↔ **Power Board** | **Hardwire**                 | 18 AWG | PT HV AC, heaters (twisted), aux, GND          |
| **C2** | **Power Board** ↔ **Preamp Board**            | **Hardwire**                 | 18 AWG | **+B**, **+B1**, **+B2**, **−B1**, GND         |
| **C3** | **Power Board** ↔ **8-pin Chassis**           | **Hardwire**                 | 18 AWG | B+ taps, bias, GND, heater to octals (twisted) |
| **C4** | **Preamp Board** ↔ **8-pin Chassis**          | **Micro-Fit 4-pin**          | 22 AWG | Driver → EL34 grids                            |
| **C5** | **Front Panel** ↔ **Preamp Board**            | **Micro-Fit 6-pin** (5 used) | 22 AWG | Volume, LED                                    |
| **C6** | **Back Panel** ↔ **Preamp Board**             | **Micro-Fit 4-pin**          | 22 AWG | RCA input centers (×4, paralleled at preamp)   |

---

## C1 — Transformers And Back Panel ↔ Power Board (hardwire)

Solder joints. Documented here as a **verification checklist**, not a connector pinout.

| Wire                    | Function                                                             | Tag |
| ----------------------- | -------------------------------------------------------------------- | --- |
| PT HV AC                | To **VD3–VD6** bridge — [`flat_power.png`](../photos/flat_power.png) |     |
| PT HV AC                |                                                                      |     |
| Bias / aux winding      | If separate from HV                                                  |     |
| Bias / aux return       |                                                                      |     |
| Heater pair A (twisted) | Tag **1×2 YEL**                                                      |     |
| Heater pair B (twisted) | Tag **5×2 WHT**                                                      |     |
| Heater pair C (twisted) | Tag **10×2 BRN**                                                     |     |
| Ground                  | Chassis / star                                                       |     |

**Not on C1:** Output Transformer speaker leads.

---

## C2 — Power Board ↔ Preamp Board (hardwire)

| Wire             | Function                      | Tag    |
| ---------------- | ----------------------------- | ------ |
| GND              | Ground                        | **11** |
| +B               |                               | **23** |
| +B1              |                               | **21** |
| +B2              |                               | **19** |
| −B1 / bias       |                               | **17** |
| Heater (twisted) | If routed via **Power Board** |        |

To bench-test the Power Board alone, unsolder these once at the Preamp Board end.

---

## C3 — Power Board ↔ 8-pin Chassis (hardwire)

**Solder on Power Board:** **TP1** pad cluster (five pads by **AC IN** bridge) — see [`open-issues.md`](open-issues.md) **OI-6**.

| Wire color | Tag | Net (Power Board) | 8-pin Chassis                |
| ---------- | --- | ----------------- | ---------------------------- |
| **GRN**    | 23  | **+B**            | Harness / PTP                |
| **GRN**    | 21  | **+B1**           | Harness / PTP                |
| **GRN**    | 19  | **+B2**           | Harness / PTP                |
| **GRN**    | 17  | **−B1** / bias    | Harness / PTP                |
| —          | —   | **GND**           | TP1 center pad → chassis GND |

**EL34 socket pin:** Factory **Vx-TP** (**V3-TP**, **V4-TP**, **V7-TP**, **V8-TP**) = **pin 8** on [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) — bias test (~**40 mV** across **R17/R18** 1 Ω). **Grids** = **pin 4** + **1 kΩ** (**OI-1**, **C4**).

**Pad ↔ tag order** on the five **TP1** pads was not recorded — label and buzz at rebuild. **18 AWG** green (or match original). Heater pair to octals if routed via Power Board (twisted **18 AWG**).

To bench-test the 8-pin Chassis alone, unsolder **C3** once at the Power Board **TP1** end.

---

## C4 — Preamp Board ↔ 8-pin Chassis (Micro-Fit 3.0, 4-pin)

**One plug + one receptacle, 22 AWG.**

| Pin | Function              |
| --- | --------------------- |
| 1–4 | EL34 control grids ×4 |

### Hardwired (not on C4)

Output Transformer primaries, cathode/screen PTP on **8-pin Chassis**, anything at tube socket pins — **18 AWG, soldered**.

Unplug **C4** to isolate the **Preamp Board** signal from the power tubes.

---

## C5 — Front Panel ↔ Preamp Board (Micro-Fit 3.0, 6-pin housing, 5 used)

**One plug + one receptacle, 22 AWG.** Kit has no 5-pin housing, so pin 6 is left empty.

| Pin | Function   |
| --- | ---------- |
| 1–3 | Volume pot |
| 4   | LED +      |
| 5   | LED −      |
| 6   | empty      |

Input selector **not used** — see **C6** for RCA inputs.

Unplug **C5** to lift the **Front Panel** for pot or LED service.

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
| Plug housing, 6 circuit       | 43020-0601        | **C5** — volume + LED (5 wires, 1 slot empty) |
| Receptacle housing, 6 circuit | 43025-0600        | **C5**                                        |
| Male pin terminal             | 43031-0001 / 0007 | **C4**, **C5**, **C6**                        |
| Female socket terminal        | 43030-0001 / 0007 | **C4**, **C5**, **C6**                        |

**Crimper:** owned (Micro-Fit 3.0 dies, 20–24 AWG).

Kit ships with ~50+ terminals of each polarity — plenty for practice crimps and mistakes.

### C5 uses 6-pin housing

Kit has no 5-pin, so **C5 = 6-pin housing with one position empty** (pin 6 unused; don't crimp a terminal for that slot). Pin plan:

| Pin | Function   |
| --- | ---------- |
| 1–3 | Volume pot |
| 4   | LED +      |
| 5   | LED −      |
| 6   | **empty**  |

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

| Step | Assemblies connected                 | Test (tubes out unless noted)                  |
| ---- | ------------------------------------ | ---------------------------------------------- |
| 1    | **Transformers And Back Panel** only | Cold resistance, earth bond                    |
| 2    | + **C1** solder + **Power Board**    | Variac / bulb limiter; B+ rails at Power Board |
| 3    | + **C2** solder + **Preamp Board**   | Rails + heater at Preamp Board                 |
| 4    | + **C3** solder + **8-pin Chassis**  | B+ and bias at octal sockets                   |
| 5    | + **C4** plug in                     | Grid signal path prep (low voltage checks)     |
| 6    | + **C5** plug in + **Front Panel**   | Volume, LED                                    |
| 7    | + **C6** plug in                     | RCA → preamp input                             |
| 8    | Full                                 | Bias trim → tubes in → signal                  |

**Unplug C4** to isolate Preamp signal from power tubes. **Unplug C5** for Front Panel service. **Unplug C6** to separate Back Panel from Preamp for fit checks. **C1–C3** require desoldering to separate.

---

## Pinout worksheets (fill at bench)

### C1 — solder joints (hardwire)

| Wire | Function | Tag | Color | ☐ Soldered | ☐ Metered |
| ---- | -------- | --- | ----- | ---------- | --------- |
| 1    |          |     |       | ☐          | ☐         |
| 2    |          |     |       | ☐          | ☐         |
| …    |          |     |       | ☐          | ☐         |

### C2 — solder joints (hardwire)

| Wire | Function | Tag | Color | ☐ Soldered | ☐ Metered |
| ---- | -------- | --- | ----- | ---------- | --------- |
| 1    | GND      | 11  |       | ☐          | ☐         |
| 2    | +B       | 23  |       | ☐          | ☐         |
| 3    | +B1      | 21  |       | ☐          | ☐         |
| 4    | +B2      | 19  |       | ☐          | ☐         |
| 5    | −B1      | 17  |       | ☐          | ☐         |

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

### C5 — Micro-Fit 6-pin (5 used)

| Pin | Function | Tag | Color | ☐ Crimped | ☐ Metered |
| --- | -------- | --- | ----- | --------- | --------- |
| 1   | Volume   | 23  |       | ☐         | ☐         |
| 2   | Volume   |     |       | ☐         | ☐         |
| 3   | Volume   |     |       | ☐         | ☐         |
| 4   | LED +    |     |       | ☐         | ☐         |
| 5   | LED −    |     |       | ☐         | ☐         |
| 6   | empty    | —   | —     | —         | —         |

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
- [`hand-schematic-notes.md`](hand-schematic-notes.md) — wiring map  
- [`power-board.md`](power-board.md) — Power Board nets and harness  
- [`open-issues.md`](open-issues.md) — unresolved bench items  
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
