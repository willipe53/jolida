# Rebuild plan (archived)

**Superseded** by the story in [`../README.md`](../README.md). Kept as a memorial of the step-by-step Parts 1–6 rebuild checklist used during the chassis work. Active power-up notes (if any) lived in [`../REMAINING_ITEMS.md`](../REMAINING_ITEMS.md).

---

## Boards (project convention)

- **Large Cap Board** — HT/bias filter PCB (bridge, large caps, **C1** / **C2** / **C3**)
- **Preamp board** — PCB with four 9-pin (noval) tube sockets
- **8-pin** — rear four octal (EL34) sockets, chassis point-to-point

## Planned output

- Per-board schematics (Fusion 360 → Eagle export for review) — tube refs **V1–V8** per `[docs/tubes.md](../docs/tubes.md)`
- As-built BOM for this chassis

---

## Rebuild plan

Goal: **build and test one assembly at a time** before wiring the next. Tubes stay out until **Part 6**. Pinouts and harness checklists live in the component docs ([`../README.md`](../README.md#documentation)); transformer detail in [`../docs/PT.md`](../docs/PT.md) and [`../docs/OT.md`](../docs/OT.md).

**Starting state:** Amp is **fully desoldered** — no live harness continuity. Tag stubs and hand schematic (`[hand_schematic.png](../photos/hand_schematic.png)`) are the wiring map.

**Wire treatment (this rebuild):** **18 AWG hardwire only** — solder every run; no Molex connectors and no 22 AWG. Keep heater pairs **twisted tightly**.

**Harness names C1–C6** are logical groups in the component docs (which board owns which wires). All are **soldered end-to-end** — there are no unplug boundaries for service. Owners: **C1** → `[large-cap-board.md](../docs/large-cap-board.md)` · **C2** → `[preamp-board.md](../docs/preamp-board.md)` · **C3**, **C4** → `[8-pin-chassis.md](../docs/8-pin-chassis.md)` · **C5** → `[front-panel.md](../docs/front-panel.md)` · **C6** → `[back-panel.md](../docs/back-panel.md)`.

**Mount order on the base is open — see [Q1](#q1-mount-order-on-the-base).** Hardwired **C1–C3** may force some sequencing once you trial-fit parts.

---

### Prep (before Part 1)

Documentation and bench ID — no new parts required.

| Task                                        | Success criteria                                                                                                                                                                                                                                                |
| ------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Safety — discharge check** on all HV caps | Meter each cap terminal → GND reads **≤ 5 V DC** (fully desoldered = should already be dead; verify anyway). If any cap reads > 10 V, short across a 10 kΩ / 5 W resistor for 30 s and re-check. See [Cap-discharge procedure](#cap-discharge-procedure) below. |
|                                             |                                                                                                                                                                                                                                                                 |

#### Do now (no parts needed)

Bench work that needs only the meter and the bare boards

- [x] **Second OT cold-Ω pass** — run [bench verification](../docs/OT.md#bench-verification-both-ots--no-power-up-on-the-ot) on the other OT using P-touch labels; log **LFT** vs **RT** from stub tags **1/15/19** vs **11/17/13**.
- [x] **OI-7** — meter the two disc ceramics still on the preamp board corners; log all four pad sites (two came off with their resistors).
- [x] **Preamp blue R1–R15 meter pass** — done 2026-07-12; every desoldered resistor value-identified (`[parts-list.md](../docs/parts-list.md#desoldered-resistor-pile--metered-inventory-2026-07-12)`). Silk-position mapping moves to Part 5.
- [x] **Film cap / electrolytic body reads** — preamp films (224/474, voltage) and large-cap-board **C10/C11** green caps.
- [x] **LED hookup** — **GRN** + **BLU** on **V7/V8** heater pins **2/7** as-built (`[LED wires.png](../photos/LED%20wires.png)`, `[front-panel.md](../docs/front-panel.md)`).
- [x] **Noval type per socket** — **V1** / **V5** = **12AX7**, **V2** / **V6** = **12AT7** (chassis silk + PDF — `[tubes.md](../docs/tubes.md)`).
- [x] **Bias pot → tube mapping** — trace each trim wiper to its C4 exit pad (`[preamp-board.md](../docs/preamp-board.md)` worksheet); log the fixed resistor values (bias range).
- [x] **Q1 dry-fit** — trial-mount the bare boards and panels on the base; record what worked in `[chassis.md](../docs/chassis.md)`.

#### Cap-discharge procedure

Repeat **every time** the amp has been powered, before touching any wire on the Large Cap Board or 8-pin chassis:

1. Unplug mains. Wait 60 s.
2. With one hand behind your back, meter **DC voltage** across each big cap (C5, C6, C8, C9) — probe (+) to cap (+), probe (−) to cap (−) or chassis GND.
3. If any cap reads > 25 V, discharge via **10 kΩ / 5 W resistor** clipped across the terminals for 30 s (do **not** short with a screwdriver — that spot-welds the cap and pits the plates).
4. Re-meter until all caps read ≤ 5 V. Only then start work.
5. During Part 3 first energize, verify **bleeder time constant** — with **68 kΩ ∥ 68 kΩ = 34 kΩ** across **C8 + C9** series (≈ 235 µF equivalent), τ ≈ 8 s. Powered-off caps should drop from ~425 V to ~5 V in **~30 s** (about 4τ). If discharge takes minutes, **R23 or R24 is open** — do not proceed.

---

### Part 1 — Transformers (complete)

Prepare **PT** + both **OT** units on the bench before mounting.

| Step                        | Work                                                                                                                                                                                                                                                            |
| --------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Extensions                  | Solder new wire onto cut stubs where harness length is short; heat-shrink every joint                                                                                                                                                                           |
| Twisted pairs               | **PREAMP HEAT** (**WHT/WHT**); **V3/V4 HEAT** (**BLK/WHT**); **V7/V8 HEAT** (**YEL/YEL**) — see `[PT.md](../docs/PT.md)`                                                                                                                                        |
| **18 AWG** (hardwire)       | **C1** from **PT**: **PT HV** (**RED/BLK**), **70V IN** (**BLU/BLU**), **PT GND** (tag **9**), **WALL AC** (**WHT/BLK** to IEC, splices at PT), IEC **GRN/YEL** earth — `[labels.md](../docs/labels.md)`                                                        |
| **18 AWG** (heater routing) | **PREAMP HEAT** → preamp; **V3/V4 HEAT** → **V3**+**V4** pins **2/7**; **V7/V8 HEAT** → **V7**+**V8**                                                                                                                                                           |
| **18 AWG** (hardwire)       | **OT primary** five leads — extensions toward **8-pin Chassis**; role map decoded (**T-2 closed**): **RED** = +B CT · **ORG/YEL** = plate/UL pair A · **BRN/WHT** = pair B (`[OT.md](../docs/OT.md)`)                                                           |
| **18 AWG** (hardwire)       | **OT secondary** three labeled leads per unit (**LEFT/RIGHT COM**, **4Ω**, **8Ω**) → binding posts; **LEFT FEEDBACK** / **RIGHT FEEDBACK** from each **8 Ω** post; second **BLK** from each **G** post → preamp pour (`[back-panel.md](../docs/back-panel.md)`) |
| Mount                       | Attach **PT** + **OT** units to base; **transformer covers** after **PT** secondary check — see [Q1](#q1-mount-order-on-the-base)                                                                                                                               |

**Independent tests (Part 1 gate):**

| Check                           | Pass                                                                                                           |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| **PT** primary **115 V** halves | **RED1↔ORG1** & **RED2↔ORG2** ~5 Ω; cross halves **OL** (`[PT.md](../docs/PT.md)`)                             |
| **OT** winding groups           | Five primary + three secondary per unit; primary ↔ secondary **OL**                                            |
| Stub tags                       | **LFT** stubs **1 / 15 / 19** on one OT; **RT** stubs **11 / 17 / 13** on the other (`[OT.md](../docs/OT.md)`) |
| Mechanical                      | Covers clear wire dress; no lead pinched under mounts                                                          |

---

### Part 2 — Back Panel (complete)

| Step                | Work                                                                                                                                                                                                                                                        |
| ------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| New components      | **AC inlet** (Schurter 6100.3300), **fuse holder** (P-H155) with **2.5 A slo-blow 5×20 mm** (T2.5A/250V; per ~200 W @ 115 V ≈ 1.7 A load), **speaker binding posts** (trim rear threads ≤ ~10 mm), **4× RCA dust caps** (3D-print or buy) for unused inputs |
| **18 AWG** hardwire | AC inlet → **PT** primary (**115 V** strap per `[PT.md](../docs/PT.md)`); fuse in HOT leg before PT                                                                                                                                                         |
| **18 AWG** hardwire | **OT** secondaries → binding posts (**LFT** tags **1/15/19**, **RT** tags **11/17/13**); **LEFT FEEDBACK** / **RIGHT FEEDBACK** from **8 Ω**; **two BLK** at each **G** post (OT + preamp **GND**)                                                          |
| **18 AWG** hardwire | Speaker **G** signal **BLK** + RCA **shell** bus → **Large Cap Board GND pour**; **star** via board strap + IEC earth — [`chassis.md`](../docs/chassis.md)                                                                                                  |
| **18 AWG** hardwire | **IEC safety earth (GRN/YEL)** → chassis stud with serrated washer, **shortest / thickest / most secure** wire in the amp — bare metal-to-metal contact, tightened hard                                                                                     |
| **18 AWG** hardwire | RCA **centers** → preamp input net (**C6**); **shells** → **Large Cap Board GND pour** — see [Unused RCA jacks](#unused-rca-jacks)                                                                                                                          |
| Mount               | Attach back panel to base — **order vs other assemblies: [Q1](#q1-mount-order-on-the-base)**                                                                                                                                                                |

#### Unused RCA jacks

Four RCAs are paralleled to one preamp input (**C6** — no selector switch). Any **unconnected** jack acts as an antenna and adds hum. Handle unused inputs one of these ways:

| Option                                         | Notes                                                                                      |
| ---------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **3D-printed shorting cap** on each unused RCA | Best — shorts center to shell, kills antenna pickup completely                             |
| **No center wire** on unused jacks             | Leave that RCA center unconnected — jack floats but antenna disconnected from preamp       |
| Leave open with dust cap only                  | Cosmetic; antenna still coupled if center is wired. Only OK if you always use all 4 inputs |

Label each RCA at the panel; tie all used **centers** to the common preamp input (**C6**).

**Independent tests (Part 2 gate):**

| Check                 | Pass                                                                                                                                         |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| **PT** primary cold Ω | No short to chassis before full power wiring                                                                                                 |
| Speaker posts         | **BLK/BLU/BRN** (coil) on **G / 4 Ω / 8 Ω**; **LEFT FEEDBACK** / **RIGHT FEEDBACK** at **8 Ω**; **two BLK** at each **G** (OT + preamp pour) |
| Clearance             | No binding post hits transformer when panel is seated                                                                                        |
| **C1** PT pigtails    | Built, labeled, **not** connected to Large Cap Board yet                                                                                     |

---

### Part 3 — Large Cap Board (complete)

| Step                | Work                                                                                                                                                                                                        |
| ------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Prep                | Read **C10/C11** green cap bodies before reinstall (Do-now item)                                                                                                                                            |
| New components      | Recap / repopulate per `[large-cap-board.md](../docs/large-cap-board.md)`                                                                                                                                   |
| **18 AWG** hardwire | **C1** pigtails on board end — mate to **PT** harness from Part 2 (`[large-cap-board.md](../docs/large-cap-board.md)`)                                                                                      |
| **18 AWG** hardwire | **C2** pigtails — exactly four wires: **+B1** (15 RED), **+B2** (7 YEL), **−B1** (9 BLU), **GND** (6 BLK) — labeled, floating at Preamp end. **No heaters on C2** (all heater pairs run direct from the PT) |
| **18 AWG** hardwire | **C3** pigtails — **2× RED +B feeds** from the +B node (one per OT center tap) + GND; TP1 pads await the pin-8 sense wires at Part 4 (`[8-pin-chassis.md](../docs/8-pin-chassis.md)`)                       |
| Mount               | Attach Large Cap Board to base — **[Q1](#q1-mount-order-on-the-base)**                                                                                                                                      |

**Independent tests (Part 3 gate):**

| Check            | Pass                                                                                                                |
| ---------------- | ------------------------------------------------------------------------------------------------------------------- |
| Cold audit       | No short B+ ↔ GND on board alone; bridge diode orientation correct                                                  |
| **C1** connected | Solder **PT** harness ↔ Large Cap Board **C1** pigtails                                                             |
| First energize   | Variac or bulb limiter, **tubes out** — no smoke; PT heaters warm                                                   |
| Rails            | **+B**, **+B1**, **+B2**, **−B1** within ~±15% of `[large-cap-board.md](../docs/large-cap-board.md)`; record values |
| Isolation        | Preamp and 8-pin harnesses still **disconnected**                                                                   |

---

### Part 4 — 8-Pin Chassis (complete)

**Physical note:** Complete [8-pin phase A](#physical-assembly-sequence) (**OT → sockets**, heaters, stoppers, **C4** at pin **5**) **before** mounting/soldering the Large Cap Board if access is tight. **Phase B** (+B at OT **RED**, **GRN** → **TP1**) requires the Large Cap Board (`[8-pin-chassis.md](../docs/8-pin-chassis.md)`).

| Step                | Work                                                                                                                                                   |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| New components      | Replace parts as needed; rebuild **point-to-point** at octal sockets (`[8-pin-chassis.md](../docs/8-pin-chassis.md)`); grid stoppers **1 kΩ** at pin 5 |
| **18 AWG** hardwire | **OT primaries** → **V3/V7** **ORG+YEL**, **V4/V8** **BRN+WHT** (pins **3/4**); **RED** CT → **C3** +B — `[OT.md](../docs/OT.md)`                      |
| **Sense wires**     | **C3** GRN pin-8 sense lines: each socket's pin 8 → its named **TP1** pad on the Large Cap Board; GND to center pad                                    |
| **18 AWG** hardwire | **C4** — bias grid path: preamp **R13** pads → octal pin **5** (via **1 kΩ** stoppers); solder both ends when preamp is accessible                     |
| Mount               | Attach socket wiring / chassis area to base — **[Q1](#q1-mount-order-on-the-base)**                                                                    |

**Independent tests (Part 4 gate):**

| Check              | Pass                                                                                                                                                                       |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **OI-1**           | **Closed** — all four **1 kΩ** (`[assembled from bottom.png](../photos/assembled%20from%20bottom.png)`)                                                                    |
| **C3** +B feeds    | **+B present at both OT center taps** (**tubes out**); readings logged. (Bias reaches the grids via **C2 → preamp bias network → C4**, checked at Part 6 — not through C3) |
| **C3** sense lines | Each TP1 pad buzzes to its socket's pin 8                                                                                                                                  |
| **C4** grid path   | Grid nets continuous preamp → socket; **no** DC short grid → B+                                                                                                            |

---

### Part 5 — Preamp Board

| Step                  | Work                                                                                                                                                                                                                                   |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| New components        | Recap / verify noval sockets, resistors as needed; install **Bourns 3296** bias trims — **A** (top lug) → **−B**, **B** → GND, **pin 2** wiper → grid path ([`preamp-board.md`](../docs/preamp-board.md#bias-network-el34-fixed-bias)) |
| **18 AWG** hardwire   | **C2** — solder Large Cap Board ↔ Preamp Board pigtails                                                                                                                                                                                |
| Bias trim cold preset | **C2** live, **all tubes out** — see [Bias trim cold preset](#bias-trim-cold-preset-bourns-3296) below; repeat before EL34s in Part 6                                                                                                  |
| **18 AWG** hardwire   | **C5** — volume pot (**3** wires) Front Panel ↔ Preamp (**outstanding**) · LED **GRN** + **BLU** **done** — **V7/V8** pins **2/7** (`[LED wires.png](../photos/LED%20wires.png)`)                                                      |
| **18 AWG** hardwire   | **C6** — RCA **centers** from Back Panel → common preamp input                                                                                                                                                                         |
| **18 AWG** hardwire   | **C4** — finish preamp ↔ 8-pin grid path if not done in Part 4                                                                                                                                                                         |
| Mount                 | Attach Preamp Board to base — **[Q1](#q1-mount-order-on-the-base)**                                                                                                                                                                    |

#### Bias trim cold preset (Bourns 3296)

All four dividers: lug **A** (top pin on the pot body) → **−B**, lug **B** → **GND**, **pin 2** = wiper → **C4** → EL34 grid. **Left channel (LFT):** **RV2** and **RV3** on the solder side (chassis underside). **Right channel (RT):** **RV2′** and **RV3′** are the **mirror** half of the PCB — same **A/B/wiper** wiring, but the pots sit **upside-down** vs **RV2/RV3** for access. That flip does **not** change the preset rule: **A** is still **−B**, and turning the screw **counterclockwise** still moves the wiper toward **A**.

**Procedure (each pot, tubes out, C2 live):**

1. Meter **DC V** between **wiper (pin 2 / C)** and **−B (A)**.
2. Turn the screw **CCW** until **0 V** (or minimum Ω wiper↔**A**).
3. On **RV2** (2026-07-21 bench check): **CW** raises wiper↔**A** resistance; **CCW** lowers it — use that on **RV3**, **RV2′**, and **RV3′** as well (same screw sense; mirror mount only changes which way the body faces, not CW vs CCW).

Detail: [`preamp-board.md`](../docs/preamp-board.md#bias-network-el34-fixed-bias).

**Independent tests (Part 5 gate):**

| Check           | Pass                                                                                                                                    |
| --------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| Rails at preamp | **C2** live — **+B1 / +B2 / −B1 / GND** at their silk pads (**noval tubes out**); heater WHT pair direct from PT                        |
| Bias network    | **−B1 reaches all four trim dividers**; pot → C4 pad → socket → TP1 mapping table filled (`[preamp-board.md](../docs/preamp-board.md)`) |
| **C5**          | Volume pot sweeps (when installed)                                                                                                      |
| **LED**         | **Done** — **BLU** at panel · **GRN**/**BLU** on **V7** or **V8** pins **2/7** (as-built)                                               |
| **C6**          | RCA **centers** continuous back panel → preamp input                                                                                    |
| **C4**          | Grid path continuous preamp → all four octal pin **5** circuits                                                                         |

---

### Part 6 — Power up

Full integration — tubes in, music out. **Tubes go in staged, not all at once.**

#### EL34 safety gate — pass before any EL34 goes in

A missing bias wire means plate runaway. With **C2 / C3 / C4** connected and **all tubes out**:

| Check        | Pass                                                                                                                                                    |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Bias present | **−40 to −54 V DC** at **all four** octal **pin 5** (grid) circuits — through C2 → preamp bias network → C4                                             |
| Pots pre-set | Re-check **RV2**, **RV3**, **RV2′**, **RV3′**: **wiper ↔ −B (A)** → **0 V** (**CCW** — see [Bias trim cold preset](#bias-trim-cold-preset-bourns-3296)) |
| Sense sanity | ~**1 Ω** from each octal **pin 8** to GND (through R17/R18) — required before trusting the 40 mV bias readings                                          |
| +B at CTs    | +B present at both OT center taps (from Part 4 gate, re-verify)                                                                                         |

#### Staged power-up

| Step             | Work                                                                                                                       |
| ---------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Preamp tubes     | Install 12AX7 ×2 + 12AT7 ×2 only; power on bulb limiter; verify heaters, rails, no smoke                                   |
| EL34s, channel 1 | Two EL34s (one channel) on the **bulb limiter**; set bias at TP1 (~**40 mV** across the 1 Ω sense per tube)                |
| EL34s, channel 2 | Repeat for the other channel                                                                                               |
| Full mains       | Off the limiter; connect speakers on **4 Ω** or **8 Ω** taps, all harnesses connected, RCA input                           |
| Bias final       | Re-set all four trims warm — trims are on the **preamp board solder side** (chassis underside access), measured at **TP1** |
| Signal           | Line in → both channels; check hum with shorted input                                                                      |

**Part 6 gate:** clean audio both channels.

---

### Q1: Mount order on the base

**Test order vs physical order:** Parts **1–6** below are **what to verify** at each stage. **Physical mounting** on this chassis does not always follow Part numbers — use the [physical sequence](#physical-assembly-sequence) when **C1–C3** reach and octal access conflict.

Why hardwired harnesses matter:

| Factor                        | Effect                                                                                                                                                     |
| ----------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **All harnesses hardwired**   | Once soldered, boards and panels cannot be reordered without cutting wire — dry-fit and label before final solder                                          |
| **Back Panel ↔ Transformers** | AC inlet and speaker posts need reach to **PT** / **OT** — panel often early                                                                               |
| **Wire length**               | Pigtails must be long enough for whichever mount order works — label before final solder                                                                   |
| **Transformer covers**        | Install **after PT is checked** and **before** the large-cap-board / **C1** alley is crowded; leave off if a cover blocks later **C3** dress               |
| **Large Cap Board**           | Usually **mounted first**, then **C1 / C2 / C3** soldered from the bottom — hard to remove once wired                                                      |
| **8-pin vs preamp**           | ~**90%** octal PTP **before** preamp is screwed down; **1 Ω** sense + pin **8 BLK** at cutouts after preamp (`[preamp-board.md](../docs/preamp-board.md)`) |

#### Physical assembly sequence

Recommended flow when **transformers** and **8-pin sockets** are already on the chassis (factory-style bottom access — `[assembled from bottom.png](../photos/assembled%20from%20bottom.png)`):

1. **PT checked** (AC secondaries on pairs); **OT cold DCR** on both units (`[OT.md](../docs/OT.md#bench-verification-both-ots--no-power-up-on-the-ot)`) — no OT “mains power-up.”
2. **Transformer covers** on (if screws clear — revisit if **C1** dress does not fit).
3. **Back panel** mounted — **WALL AC**, earth, **LEFT/RIGHT** speaker OT wires; **LEFT FEEDBACK** / **RIGHT FEEDBACK** / second **G** **BLK** can wait for preamp.
4. **8-pin — phase A (before Large Cap Board):** OT **Vn PIN 3/4**, **PT** heaters to pins **2/7**, **1 kΩ** stoppers, **C4** to pin **5**; **no** **+B LEFT/RIGHT** to board yet, **no** **GRN** to **TP1** yet.
5. **Large Cap Board** mounted (commit carefully) → solder **C1**, star **GND**, **C3** (**+B LEFT/RIGHT**, **TP1** GRN later), **C2** pigtails toward preamp.
6. **Part 3 gate** — variac/limiter, tubes out, log rails.
7. **8-pin — phase B:** finish **C3** (+B at OT **RED**, pin **8** **GRN** → **TP1**); pin **8** **BLK** toward preamp pads.
8. **Preamp** mounted → **C2**, **PREAMP HEAT**, **PT GND**, **1 Ω** sense parts + pin **8** tails, **C4**/**C6**; bias trim cold preset.
9. **Front panel** last — **C5** (volume pot); LED **done**.
10. **Part 6** — staged tubes and bias.

**Front** and **back** panels are loosely coupled to board order; **back** early is fine if post clearance passes.

Dry-fit the **Large Cap Board** and **Preamp Board** screw positions before final **C1–C3** solder. Record what worked in `[docs/chassis.md](../docs/chassis.md)`.

#### Legacy trial sequence (logical reach only)

Superseded for this build by [physical assembly sequence](#physical-assembly-sequence) above — kept as a short checklist:

1. Transformers on base (Part 1)
2. Back Panel (Part 2)
3. 8-pin phase A → Large Cap Board mount + solder (Parts 4A + 3)
4. Preamp (Part 5) after 8-pin phase B
5. Front panel last

---

### Parts vs parts (quick reference)

| Parts arriving | Unblocks                                                                             |
| -------------- | ------------------------------------------------------------------------------------ |
| **T2.5A fuse** | Part 2 AC path (fuse holder **in place** — `[parts-list.md](../docs/parts-list.md)`) |
| Tubes          | Part 6 (on hand — install at Part 6)                                                 |

**18 AWG**, heat-shrink, harness hardware, large cap board, preamp metal-film, IEC inlet, RCA shorting cap ×4, and bench tools: **on hand** — see `[parts-list.md](../docs/parts-list.md)`.

**Bench-tool gaps:** discharge resistor and bulb limiter / variac are **on hand** per `[parts-list.md](../docs/parts-list.md)`.

Full parts inventory: `[docs/parts-list.md](../docs/parts-list.md)`.

---

### Open issues to close during rebuild

| ID                                                                             | Close during         |
| ------------------------------------------------------------------------------ | -------------------- |
| **T-2** second-unit confirm (map decoded on unit 1 — `[OT.md](../docs/OT.md)`) | Do-now list / Part 1 |
| **OI-7** small ceramic caps on preamp board (meter + log pad location)         | Do-now list / Part 5 |

Closed recently: **OI-8** superseded — **R17/R18** **1 Ω** sense parts **replace** at rebuild (`[tubes.md](../docs/tubes.md#el34-cathode-sense-pdf-r17--r18)`) · **T-2 unit 1** (DCR matrix — `[OT.md](../docs/OT.md)`) · **C3 redefinition** and full rail-delivery map (`[8-pin-chassis.md](../docs/8-pin-chassis.md)`, `[large-cap-board.md](../docs/large-cap-board.md)`) · **C2 map** and bias-trim confirmation (`[preamp-board.md](../docs/preamp-board.md)`).

Full history: `[archive/open-issues.md](../archive/open-issues.md)`.

---
