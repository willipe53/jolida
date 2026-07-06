# jolida

Reverse-engineering and restoration documentation for a **Jolida SJ202A / JD202** integrated tube amplifier (EL34 ×4, 12AX7 ×2, 12AT7 ×2).

## Documentation

Read [`docs/SOURCES.md`](docs/SOURCES.md) first — **physical unit and empirical bench notes outrank the sourced factory PDF.**

| Document                                                               | Role                                                 |
| ---------------------------------------------------------------------- | ---------------------------------------------------- |
| [`docs/SOURCES.md`](docs/SOURCES.md)                                   | Authority order & methodology                        |
| [`docs/gemini-restoration-notes.md`](docs/gemini-restoration-notes.md) | **Primary** — empirical chassis breakdown & parts    |
| [`docs/schematic-comparison.md`](docs/schematic-comparison.md)         | PDF vs this unit (delta log)                         |
| [`docs/open-issues.md`](docs/open-issues.md)                           | Unresolved bench questions                           |
| [`docs/hand-schematic-notes.md`](docs/hand-schematic-notes.md)         | Disassembly wiring map                               |
| [`docs/wire-tags.md`](docs/wire-tags.md)                               | Cut-wire tag reference                               |
| [`docs/CONNECTORS.md`](docs/CONNECTORS.md)                             | Modular rebuild — C1–C6 harness plan                 |
| [`docs/PT.md`](docs/PT.md)                                             | **Power Transformer** — coil ID, DCR, harness        |
| [`docs/OT.md`](docs/OT.md)                                             | **Output Transformers** — two units, speaker + 8-pin |
| [`docs/TRANSFORMERS.md`](docs/TRANSFORMERS.md)                         | Transformers index (links to PT + OT)                |
| [`docs/power-board.md`](docs/power-board.md)                           | **Power board schematic** (as-built)                 |
| [`docs/power-board.png`](docs/power-board.png)                         | Power board visual schematic                         |
| [`docs/power-board.svg`](docs/power-board.svg)                         | Power board SVG (browser/Inkscape)                   |
| [`docs/Jolida-JD202A-int-sch.pdf`](docs/Jolida-JD202A-int-sch.pdf)     | Secondary — randomly sourced factory drawing         |
| [`photos/`](photos/)                                                   | Board and chassis photos                             |

## Boards (project convention)

- **Power board** — AC/DC PCB with large caps
- **Preamp board** — PCB with four 9-pin (noval) tube sockets
- **8-pin** — rear four octal (EL34) sockets, chassis point-to-point

## Planned output

- Per-board KiCad schematics derived from photos + bench data
- As-built BOM for this chassis

---

## Rebuild plan

Goal: **build and test one assembly at a time** before wiring the next. Tubes stay out until **Part 6**. Pinouts and harness checklists live in [`docs/CONNECTORS.md`](docs/CONNECTORS.md); transformer detail in [`docs/PT.md`](docs/PT.md) and [`docs/OT.md`](docs/OT.md).

**Starting state:** Amp is **fully desoldered** — no live harness continuity. Tag stubs and hand schematic ([`hand_schematic.png`](photos/hand_schematic.png)) are the wiring map.

**Wire treatment (two rules):**

| Wire       | Treatment                                                                                                               |
| ---------- | ----------------------------------------------------------------------------------------------------------------------- |
| **18 AWG** | **Solder / hardwire only** — never through a connector. Keep heater pairs **twisted tightly**. (**C1**, **C2**, **C3**) |
| **22 AWG** | **Molex Micro-Fit 3.0** — all signal and panel paths (**C4**, **C5**, **C6**)                                           |

See [`docs/CONNECTORS.md`](docs/CONNECTORS.md). **C1–C3** are solder boundaries; **C4–C6** unplug for service and dry-fit.

**Mount order on the base is open — see [Q1](#q1-mount-order-on-the-base).** Hardwired **C1–C3** may force some sequencing once you trial-fit parts.

---

### Prep (before Part 1)

Documentation and bench ID — no new parts required.

| Task                                                                       | Success criteria                                                              |
| -------------------------------------------------------------------------- | ----------------------------------------------------------------------------- |
| Fill **PT / OT** worksheets ([`PT.md`](docs/PT.md), [`OT.md`](docs/OT.md)) | Winding groups, tag stubs keyed to channel (**LFT** 1/15/19, **RT** 11/17/13) |
| Draft **C1–C6** worksheets in [`CONNECTORS.md`](docs/CONNECTORS.md)        | Every planned wire has function + tag + color                                 |
| Practice **Micro-Fit** crimps on scrap 22 AWG                              | 5 consecutive crimps pass tug test                                            |

---

### Part 1 — Transformers

Prepare **PT** + both **OT** units on the bench before mounting.

| Step                       | Work                                                                                                                                                     |
| -------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Extensions                 | Solder new wire onto cut stubs where harness length is short; heat-shrink every joint                                                                    |
| Twisted pairs              | Keep **PT** heater pairs twisted end-to-end (**WHT/WHT**, **BRN/BRN**, **YEL/YEL** per [`PT.md`](docs/PT.md))                                            |
| **18 AWG** (hardwire)      | **C1** bundle from **PT**: HV **RED/BLK**, 50 V **BLU/BLU**, heaters (twisted), **PT-L5** ground **BLK**, primary **115 V** — label each lead at the cut |
| **18 AWG** (hardwire)      | **OT primary** five leads (**RED, YEL, ORG, WHT, BRN**) — extensions toward **8-pin Chassis** (not Molex); role map **T-2** at reassembly                |
| **Heavy gauge** (hardwire) | **OT secondary** three leads per unit (**BLK** = G, **BLU** = 4 Ω, **BRN** = 8 Ω) — extensions toward **Back Panel** posts                               |
| Molex                      | **None** on transformers — all power paths are soldered                                                                                                  |
| Mount                      | Attach **PT** + **OT** units to base; install transformer covers                                                                                         |

**Independent tests (Part 1 gate):**

| Check                           | Pass                                                                                                        |
| ------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| **PT** primary **115 V** halves | **RED1↔ORG1** & **RED2↔ORG2** ~5 Ω; cross halves **OL** ([`PT.md`](docs/PT.md))                             |
| **OT** winding groups           | Five primary + three secondary per unit; primary ↔ secondary **OL**                                         |
| Stub tags                       | **LFT** stubs **1 / 15 / 19** on one OT; **RT** stubs **11 / 17 / 13** on the other ([`OT.md`](docs/OT.md)) |
| Mechanical                      | Covers clear wire dress; no lead pinched under mounts                                                       |

---

### Part 2 — Back Panel

| Step                | Work                                                                                                                |
| ------------------- | ------------------------------------------------------------------------------------------------------------------- |
| New components      | **AC inlet** (Schurter 6100.3300), **fuse holder** (P-H155), **speaker binding posts** (trim rear threads ≤ ~10 mm) |
| **18 AWG** hardwire | AC inlet → **PT** primary (**115 V** strap per [`PT.md`](docs/PT.md))                                               |
| **18 AWG** hardwire | **OT** secondaries → binding posts (**LFT** tags **1/15/19**, **RT** tags **11/17/13**)                             |
| **18 AWG** hardwire | Chassis **GND** star → panel earth / RCA shell reference                                                            |
| Molex **C6**        | RCA jack centers → **4-pin** Micro-Fit on panel harness (shells on chassis via panel metal)                         |
| Molex               | **None** on back panel                                                                                              |
| Mount               | Attach back panel to base — **order vs other assemblies: [Q1](#q1-mount-order-on-the-base)**                        |

**Independent tests (Part 2 gate):**

| Check                 | Pass                                                                        |
| --------------------- | --------------------------------------------------------------------------- |
| **PT** primary cold Ω | No short to chassis before full power wiring                                |
| Speaker posts         | **BLK/BLU/BRN** (coil) land on correct **G / 4 Ω / 8 Ω** labels per channel |
| Clearance             | No binding post hits transformer when panel is seated                       |
| **C1** PT pigtails    | Built, labeled, **not** connected to Power Board yet                        |

---

### Part 3 — Power Board

| Step                | Work                                                                                                            |
| ------------------- | --------------------------------------------------------------------------------------------------------------- |
| New components      | Recap / repopulate per [`power-board.md`](docs/power-board.md)                                                  |
| **18 AWG** hardwire | **C1** pigtails on board end — mate to **PT** harness from Part 2                                               |
| **18 AWG** hardwire | **C2** pigtails (**+B**, **+B1**, **+B2**, **−B1**, GND, heater if via board) — labeled, floating at Preamp end |
| **18 AWG** hardwire | **C3** pigtails (B+ taps, bias, GND, octal heater if routed here) — labeled, floating at 8-pin end              |
| Molex               | **None** on power board                                                                                         |
| Mount               | Attach Power Board to base — **[Q1](#q1-mount-order-on-the-base)**                                              |

**Independent tests (Part 3 gate):**

| Check            | Pass                                                                                                     |
| ---------------- | -------------------------------------------------------------------------------------------------------- |
| Cold audit       | No short B+ ↔ GND on board alone; bridge diode orientation correct                                       |
| **C1** connected | Solder **PT** harness ↔ Power Board **C1** pigtails                                                      |
| First energize   | Variac or bulb limiter, **tubes out** — no smoke; PT heaters warm                                        |
| Rails            | **+B**, **+B1**, **+B2**, **−B1** within ~±15% of [`power-board.md`](docs/power-board.md); record values |
| Isolation        | Preamp and 8-pin harnesses still **disconnected**                                                        |

---

### Part 4 — 8-Pin Chassis

| Step                | Work                                                                                                                |
| ------------------- | ------------------------------------------------------------------------------------------------------------------- |
| New components      | Replace parts as needed; rebuild **point-to-point** at octal sockets (screens, cathodes, bias trim **V3/V4/V7/V8**) |
| **18 AWG** hardwire | **OT primaries** → socket / **+B** / UL taps (**T-2** color map); **C3** from Power Board                           |
| Molex               | Build **C4** harness (**4-pin** Micro-Fit, 22 AWG) — Preamp end + 8-pin end; **leave unplugged** until Part 5/6     |
| Mount               | Attach socket wiring / chassis area to base — **[Q1](#q1-mount-order-on-the-base)**                                 |

**Independent tests (Part 4 gate):**

| Check            | Pass                                                                                                 |
| ---------------- | ---------------------------------------------------------------------------------------------------- |
| **OI-1**         | **Closed** — all four **1 kΩ** ([`assembled from bottom.png`](photos/assembled%20from%20bottom.png)) |
| **C3** connected | B+ and bias present at octal sockets (**tubes out**); readings logged                                |
| **C4** built     | Grid nets continuous when plug inserted; **no** DC short grid → B+                                   |
| **C4** unplugged | 8-pin power stage isolated from Preamp signal                                                        |

---

### Part 5 — Preamp Board

| Step                | Work                                                                                                         |
| ------------------- | ------------------------------------------------------------------------------------------------------------ |
| New components      | Recap / verify noval sockets, resistors as needed                                                            |
| **18 AWG** hardwire | **C2** — solder Power Board ↔ Preamp Board pigtails                                                          |
| Molex **C5**        | Crimp **6-pin** housing (5 wires) — Front Panel ↔ Preamp; build volume + LED tails                           |
| Molex **C6**        | Crimp **4-pin** — Preamp receptacle end; tie pins **1–4** to common input; plug mates Back Panel from Part 2 |
| Molex **C4**        | Plug when ready to test grids (may wait until Part 6)                                                        |
| Mount               | Attach Preamp Board to base — **[Q1](#q1-mount-order-on-the-base)**                                          |

**Independent tests (Part 5 gate):**

| Check           | Pass                                                           |
| --------------- | -------------------------------------------------------------- |
| Rails at preamp | **C2** live — B+ / heater / GND at board (**noval tubes out**) |
| **C5**          | Volume pot sweeps; LED polarity correct when Front Panel wired |
| **C6** optional | Plug in Back Panel harness; continuity pin-to-pin before tubes |
| **C4** optional | Plug in for grid continuity check before power tubes           |

---

### Part 6 — Power up

Full integration — tubes in, music out.

| Step    | Work                                                                                                                         |
| ------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Tubes   | Install full complement (EL34 ×4, 12AX7 ×2, 12AT7 ×2)                                                                        |
| Connect | Mains (fuse in), speakers on **4 Ω** or **8 Ω** taps, **C4** + **C5** + **C6** seated, RCA input                             |
| Bias    | Adjust underside trim pots **V3, V4, V7, V8** — idle current per EL34 spec (~**40 mV** across 1 Ω resistors per factory PDF) |
| Signal  | Line in → both channels; check hum with shorted input                                                                        |

**Part 6 gate:** clean audio both channels; **C4** / **C5** / **C6** unplug for service or dry-fit as designed.

---

### Q1: Mount order on the base

**Open question:** The correct sequence to physically mount **Back Panel**, **Power Board**, **8-Pin Chassis**, **Preamp Board**, and the **base** is not fully settled. Expect **trial and error** on first assembly.

Why it matters:

| Factor                        | Effect                                                                                   |
| ----------------------------- | ---------------------------------------------------------------------------------------- |
| **C1–C3 are hardwired**       | Once soldered, you cannot easily reorder boards without cutting wire                     |
| **C4 / C5 / C6 are Molex**    | Preamp ↔ 8-pin, Front Panel ↔ Preamp, and Back Panel ↔ Preamp can unplug for fit checks  |
| **Back Panel ↔ Transformers** | AC inlet and speaker posts need reach to **PT** / **OT** — panel often early             |
| **Wire length**               | Pigtails must be long enough for whichever mount order works — label before final solder |

**Suggested trial sequence** (adjust after dry-fit):

1. Transformers on base (Part 1)
2. Back Panel — verify post clearance vs transformers (Part 2)
3. Power Board — **C1** reach to **PT** (Part 3)
4. Preamp Board — **C2** reach (Part 5)
5. 8-Pin Chassis — **C3** + **OT** primary reach (Part 4)

Dry-fit each assembly with harnesses **not** fully soldered (or with Molex unplugged) before committing **C1–C3** joints. Record what worked in [`docs/CONNECTORS.md`](docs/CONNECTORS.md) or a bench note.

---

### Parts vs parts (quick reference)

| Parts arriving                                                  | Unblocks               |
| --------------------------------------------------------------- | ---------------------- |
| Caps, R25, **R23/R24 (68 kΩ / 3 W ×2)**, power board BOM        | Part 3                 |
| **18 AWG** + heat-shrink                                        | Parts 1–3 (C1, C2, C3) |
| **22 AWG** + Micro-Fit kit (+ **second 4-pin** pair for **C6**) | Parts 2–6 (C4, C5, C6) |
| Chassis hardware (IEC, fuse, posts)                             | Part 2                 |
| Tubes                                                           | Part 6                 |

---

### Open issues to close during rebuild

| ID                        | Close during    |
| ------------------------- | --------------- |
| **T-2** OT primary colors | Part 1 / Part 4 |

Full list: [`docs/open-issues.md`](docs/open-issues.md).
