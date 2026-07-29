# Parts list

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah) · inventory refresh **2026-07-20**

Single flat list of every part in the rebuild, sorted by board/assembly. **Status** meanings:

- **on hand** — have it (original reused or new part received)
- **on order** — purchased, awaiting arrival
- **mounted** — new part received and soldered onto the board
- **in place** — never desoldered; do not disturb
- **verify** — value or identity is low-confidence; meter/read at bench before install (see the board doc)

| Reference             | Board / assembly | Type                                             | Status                                                                                         |
| --------------------- | ---------------- | ------------------------------------------------ | ---------------------------------------------------------------------------------------------- |
| VD3–VD6               | Large Cap Board  | 1N5408 rectifier (HT bridge)                     | in place                                                                                       |
| VD7                   | Large Cap Board  | 1N4007 rectifier (bias supply)                   | in place                                                                                       |
| C5, C6                | Large Cap Board  | 180 µF / 450 V electrolytic                      | in place                                                                                       |
| C7                    | Large Cap Board  | 470 µF / 50 V electrolytic                       | in place                                                                                       |
| C8, C9                | Large Cap Board  | 470 µF / 450 V electrolytic (top pair)           | in place                                                                                       |
| C10, C11              | Large Cap Board  | 220 µF / 160 V electrolytic (green, bias)        | in place                                                                                       |
| R21                   | Large Cap Board  | 100 kΩ / 2 W wirewound                           | in place                                                                                       |
| R22                   | Large Cap Board  | 3.3 kΩ / 5 W white ceramic                       | in place                                                                                       |
| R23, R24              | Large Cap Board  | 68 kΩ / 3 W bleeder                              | in place (replaced original ~62 kΩ)                                                            |
| R25                   | Large Cap Board  | 2.2 kΩ / 2 W                                     | in place                                                                                       |
| R1 / R1′              | Preamp Board     | **100 kΩ** metal-film (plate / string)           | in place                                                                                       |
| R2 / R2′              | Preamp Board     | **10 kΩ** metal-film (signal)                    | in place                                                                                       |
| R3 / R3′              | Preamp Board     | **470 Ω** metal-film                             | in place                                                                                       |
| R4 / R4′              | Preamp Board     | **1 MΩ** metal-film (grid leak)                  | in place                                                                                       |
| R5 / R5′              | Preamp Board     | **27 kΩ** metal-film (global NFB)                | in place                                                                                       |
| R6 / R6′              | Preamp Board     | **15 kΩ** metal-film (plate load)                | in place                                                                                       |
| R7 / R7′              | Preamp Board     | **22 kΩ** metal-film (driver plate)              | in place                                                                                       |
| R8 / R8′              | Preamp Board     | **24 kΩ** metal-film (driver plate)              | in place                                                                                       |
| R9 / R9′              | Preamp Board     | **100 kΩ** metal-film                            | in place                                                                                       |
| R10 / R10′            | Preamp Board     | **27 kΩ** metal-film (bias −B)                   | in place                                                                                       |
| R11 / R11′            | Preamp Board     | **27 kΩ** metal-film (bias −B)                   | in place                                                                                       |
| R12 / R12′            | Preamp Board     | **100 kΩ** metal-film                            | in place                                                                                       |
| R14 / R14′            | Preamp Board     | **12 kΩ** metal-film (bias GND)                  | in place                                                                                       |
| R15 / R15′            | Preamp Board     | **12 kΩ** metal-film (bias GND)                  | in place                                                                                       |
| R17 / R18 (×4)        | Preamp Board     | **1 Ω / 5 W** cathode sense (PDF; pad **R16**)   | **on hand** — **replace** all four; map [`tubes.md`](tubes.md#el34-cathode-sense-pdf-r17--r18) |
| RV2, RV2′, RV3, RV3′  | Preamp Board     | **Bourns 3296** EL34 bias trim (~22 kΩ, PDF)     | in place                                                                                       |
| C1 (PDF)              | Preamp Board     | **0.47 µF / 400 V** film (blue CBB)              | in place — factory blues **left in place**; [`tubes.md`](tubes.md#preamp-c1-pdf)               |
| C3, C4 (PDF)          | Preamp Board     | **0.22 µF / 630 V** Orange Drop **716P** × **4** | in place — replaced factory green film                                                         |
| \*C2 (PDF)            | Preamp Board     | Disc ceramic **20 pF** (NFB, **R5**)             | on board — corner pair (OI-7)                                                                  |
| **\*C51** (PDF)       | **V1**, **V5**   | Disc ceramic **100 pF** in series with **R51**   | **on hand** (desoldered set) — [`tubes.md`](tubes.md#parts-soldered-at-socket-pins)            |
| Noval sockets ×4      | Preamp Board     | 9-pin ceramic socket                             | on hand (reuse)                                                                                |
| V1, V5                | Preamp Board     | 12AX7A tube                                      | on hand — [`tubes.md`](tubes.md) **V1** LFT · **V5** RT                                        |
| V2, V6                | Preamp Board     | 12AT7 tube                                       | on hand — [`tubes.md`](tubes.md) **V2** LFT · **V6** RT                                        |
| Octal sockets ×4      | 8-Pin Chassis    | 8-pin socket (chassis mount)                     | on hand (reuse)                                                                                |
| Grid stoppers ×4      | 8-Pin Chassis    | 1 kΩ at EL34 **pin 5**                           | on hand (OI-1) — [socket-pin parts](#socket-pin-parts)                                         |
| V3, V4, V7, V8        | 8-Pin Chassis    | EL34 power tube                                  | on hand — [`tubes.md`](tubes.md)                                                               |
| PT                    | Chassis          | Power transformer LM-9908P-A class               | on hand — **18 AWG** extensions + labels applied ([`PT.md`](PT.md), [`labels.md`](labels.md))  |
| OT ×2                 | Chassis          | Output transformer LM-9914U                      | on hand                                                                                        |
| AC inlet              | Back Panel       | Schurter 6100.3300 IEC C14                       | on hand                                                                                        |
| Fuse holder           | Back Panel       | P-H155 panel mount, 5×20                         | in place                                                                                       |
| Fuse                  | Back Panel       | T2.5A / 250 V slo-blow 5×20                      | on order                                                                                       |
| Speaker posts ×6      | Back Panel       | Binding post (Cliff CL2160 class)                | in place                                                                                       |
| RCA jacks ×4          | Back Panel       | RCA panel jack                                   | on hand (reuse)                                                                                |
| RCA shorting cap ×4   | Back Panel       | 3D-printed shorting cap (one design, four jacks) | in place                                                                                       |
| Volume pot            | Front Panel      | Replacement volume pot (new)                     | on hand                                                                                        |
| Power LED + holder    | Front Panel      | Original LED (GRN / DK BLU leads)                | on hand — verify polarity + noval pin                                                          |
| C4 housing pair       | Harness          | Molex Micro-Fit 3.0, 4-pin plug + receptacle     | on hand (kit)                                                                                  |
| C5 housing pair       | Harness          | Molex Micro-Fit 3.0, 6-pin (3 used)              | on hand (kit)                                                                                  |
| C6 housing pair       | Harness          | Molex Micro-Fit 3.0, 4-pin plug + receptacle     | on hand (kit)                                                                                  |
| Micro-Fit terminals   | Harness          | Crimp terminals, 22 AWG                          | on hand (kit)                                                                                  |
| Hookup wire, 18 AWG   | Harness          | 600 V rated, for C1/C2/C3 + AC + speakers        | on hand                                                                                        |
| Hookup wire, 22 AWG   | Harness          | For Molex harnesses + sense lines                | on hand                                                                                        |
| Heat-shrink           | Harness          | Assorted, for splices and lead dress             | on hand                                                                                        |
| Discharge resistor    | Bench tool       | 10 kΩ / 5 W with clip leads                      | on hand                                                                                        |
| Bulb limiter / variac | Bench tool       | Series-lamp rig or variac for first power-up     | on hand                                                                                        |

Detail and worksheets per board: [`large-cap-board.md`](large-cap-board.md) · [`preamp-board.md`](preamp-board.md) · [`8-pin-chassis.md`](8-pin-chassis.md) · [`back-panel.md`](back-panel.md) · [`front-panel.md`](front-panel.md) · [`PT.md`](PT.md) · [`OT.md`](OT.md) · socket-pin map [`tubes.md`](tubes.md#parts-soldered-at-socket-pins).

## Socket-pin parts

Resistors (and paired disc caps) **soldered at tube socket pins** — **not** on preamp PCB silk. PDF refs may differ from PCB silk (see [`preamp-board.md`](preamp-board.md)). Per-tube pin map: [`tubes.md`](tubes.md#parts-soldered-at-socket-pins).

| PDF ref           | Tube(s)        | Socket         | Pin (mount)                       | Value     | Cap (series)     | Qty | Status                   | Notes                                                                                                   |
| ----------------- | -------------- | -------------- | --------------------------------- | --------- | ---------------- | --- | ------------------------ | ------------------------------------------------------------------------------------------------------- |
| **R13** (PDF)     | **V3–V8**      | Octal          | **5**                             | **1 kΩ**  | —                | 4   | on hand                  | Grid stopper body at socket; preamp landing pad **R13** / **R13′** ← **C4**                             |
| **R51**           | **V1**, **V5** | Noval          | **V1: 6 ↔ 8** · **V5: 1 ↔ 3**     | **10 kΩ** | **\*C51** 100 pF | 2   | on hand (desoldered set) | **In series** with **\*C51**, SRPP plate→cathode — [`tubes.md`](tubes.md#parts-soldered-at-socket-pins) |
| **\*C51**         | **V1**, **V5** | (with **R51**) | —                                 | —         | **100 pF**       | 2   | on hand (desoldered set) | Series chain with **R51**; reuse OK                                                                     |
| **RF1** / **RF2** | **V1**, **V5** | Noval          | **V1: 4 → GND** · **V5: 9 → GND** | **1 kΩ**  | —                | 2   | on hand (desoldered set) | 6.3 V heater reference — one per heater **leg** — [`tubes.md`](tubes.md#parts-soldered-at-socket-pins)  |

**PCB (replace, not socket-pin):** **R17 / R18** ×4 cathode sense — [`tubes.md`](tubes.md#el34-cathode-sense-pdf-r17--r18). **C1** blue film — **in place** ([`tubes.md`](tubes.md#preamp-c1-pdf)).

---

## Metal-film stock (2026-07-20)

Bench kit (nominal values): **470 Ω**, **2.2 kΩ**, **10 kΩ**, **12 kΩ**, **15 kΩ**, **22 kΩ**, **24 kΩ**, **27 kΩ**, **47 kΩ**, **68 kΩ**, **100 kΩ**, **220 kΩ**, **1 MΩ**.

| Needed for preamp install | Qty (both channels)                                       | In stock? |
| ------------------------- | --------------------------------------------------------- | --------- |
| **470 Ω** (R3)            | 2 (**R3 / R3′** in place)                                 | yes       |
| **1 MΩ** (R4)             | 2 (**R4 / R4′** in place)                                 | yes       |
| **10 kΩ** (R2, R51)       | 4 (**R2 / R2′** in place; **R51** ×2 at sockets — reuse)  | yes       |
| **12 kΩ** (R14, R15)      | 4 (all in place)                                          | yes       |
| **15 kΩ** (R6)            | 2 (**R6 / R6′** in place)                                 | yes       |
| **22 kΩ** (R7)            | 2 (**R7 / R7′** in place)                                 | yes       |
| **24 kΩ** (R8)            | 2 (**R8 / R8′** in place)                                 | yes       |
| **27 kΩ** (R5, R10, R11)  | 6 (**R5 / R5′**, **R10 / R10′**, **R11 / R11′** in place) | yes       |
| **100 kΩ** (R1, R9, R12)  | 6 (all in place)                                          | yes       |

**Not used on preamp silk (spares in kit):** **47 kΩ**, **220 kΩ**. **2.2 kΩ** / **68 kΩ** were large-cap-board only — already **in place** on [`large-cap-board.md`](large-cap-board.md). **1 kΩ** grid stoppers: reuse desoldered blues on 8-pin chassis (not in the metal-film kit list).

**Still on order** (everything else in the table below that remains **on order**): **T2.5A fuse** only.

## Desoldered resistor pile — metered inventory (2026-07-12)

Every desoldered resistor identified by DMM (photo: [`resistors.png`](../photos/resistors.png)). Owner band reads corrected where the meter disagreed (blue/black and blue/violet confusions on blue bodies).

**Count reconciliation (closed 2026-07-12):** 36 pieces = **4 large cap board** (R21, R23, R24, R25) + **4 grid stoppers** (8-pin chassis) + **28 preamp** (silk R1–R12, R14, R15 × 2 channels; **R16** / **R16′** = the in-place white **1 Ω** ceramics). Channel-symmetry check passes: every preamp bucket is even; the only odd counts (5× 100k, 1× 2.2k) are exactly the odd large-cap-board parts (R21, R25). No unexplained pieces, no missing values.

**Silk → value map (closed 2026-07-12):** see [`preamp-board.md`](preamp-board.md#blue-axial-resistors--silk--value-map-closed-2026-07-12). High-confidence on R1–R5, R9–R12, R14–R15; R6/R7/R8 Med (pile + PDF role).

| Value      | Qty | Bands (nominal)        | Role / destination                                                                            |
| ---------- | --- | ---------------------- | --------------------------------------------------------------------------------------------- |
| **100 kΩ** | 5   | brn-blk-yel            | Silk **R1, R9, R12** × channels (preamp) + power **R21**; new 3 W parts cover any wattage gap |
| **~26 kΩ** | 6   | red-vio-org (27k nom)  | Silk **R10/R11** ×2 (bias) + silk **R5/R5′** (signal)                                         |
| **12 kΩ**  | 4   | brn-red-org            | Silk **R14/R15** family (bias GND side)                                                       |
| **10 kΩ**  | 4   | brn-blk-org            | Silk **R2/R2′** + **R51** ×2 (**in series** with **\*C51** at V1/V5 sockets)                  |
| **1 kΩ**   | 4–6 | brn-blk-red            | Grid stoppers ×4 on 8-pin chassis + **RF1/RF2** heater refs (V1 pin 4 / V5 pin 9 → GND)       |
| **1.6 MΩ** | 2   | brn-blu-grn            | Silk **R4/R4′** grid leaks — PDF R4 draws 1 M; as-built 1.6 M                                 |
| **470 Ω**  | 2   | metered 460 Ω, matched | Silk **R3/R3′**                                                                               |
| **62 kΩ**  | 2   | blu-red-org            | Old large-cap-board **R23/R24** bleeders — retired; **68 kΩ / 3 W** replacements installed    |
| **22 kΩ**  | 2   | red-red-org            | Silk **R7/R7′** (PDF R7 driver plate)                                                         |
| **24 kΩ**  | 2   | red-yel-org            | Silk **R8/R8′** (PDF R8 driver plate)                                                         |
| **15 kΩ**  | 2   | brn-grn-org            | Silk **R6/R6′** (PDF R6)                                                                      |
| **2.2 kΩ** | 1   | red-red-red            | Large Cap Board **R25** original — **2.2 kΩ** replacement **in place** on board               |
