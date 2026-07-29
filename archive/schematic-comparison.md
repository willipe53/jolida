# Factory PDF vs this unit (delta log)

**Read [`SOURCES.md`](../docs/SOURCES.md) first.** This file logs where the randomly sourced PDF disagrees with **this chassis**. It does not elevate the PDF to primary authority.

Reference PDF: [`Jolida-JD202A-int-sch.pdf`](../docs/Jolida-JD202A-int-sch.pdf) (JD202A.s01, 2002-04-19) — source: [audiocircuit.dk/jolida](https://audiocircuit.dk/jolida/)

Primary evidence: [`gemini-restoration-notes.md`](gemini-restoration-notes.md), [`../photos/`](../photos/), bench measurements.

---

## When to use the PDF

| Use PDF for…                               | Do **not** use PDF for…                                         |
| ------------------------------------------ | --------------------------------------------------------------- |
| Likely signal path (Mullard-style UL EL34) | Cap values on this unit                                         |
| Tube type hints (12AX7 / 12AT7 / EL34)     | Resistor values without verifying                               |
| Rail names (+B, +B1, +B2, −B)              | Wire colors or harness routing                                  |
| **8 Ω NFB** path (**R5 ∥ C2** → **12AX7**) | Assuming **PRP** = OT tap (it is a **second** wire at the post) |
| “Does this topology make sense?”           | Claiming SJ202A = exact 2002 BOM                                |

---

## Board mapping (topology — PDF still useful here)

| Your board      | PDF region                              | KiCad sheet (planned)       |
| --------------- | --------------------------------------- | --------------------------- |
| Large Cap Board | T2 secondaries → VD3–7, C5–C11          | `large-cap-board.kicad_sch` |
| Preamp board    | S2, RW1, V1/V2 (×2 channels on one PCB) | `preamp.kicad_sch`          |
| 8-pin / chassis | V3/V4 EL34 PTP, T1, bias                | `output_chassis.kicad_sch`  |
| Harnesses       | (poorly represented on PDF)             | `interconnect.kicad_sch`    |

---

## Where PDF and unit agree (low controversy)

- Tube lineup: EL34 ×4, 12AX7 ×2, 12AT7 ×2; UL push-pull; bias **~40 mV**
- Global NFB: **8 Ω** speaker post → **R5 (27 kΩ) ∥ C2 (20 pF)** → **12AX7** cathode (per channel)
- Speaker **G**: OT **0** tap **and** circuit **GND** at the same binding post (second **BLK** → preamp pour)
- Film caps: **474J 400V** (0.47 µF), **CBB22 220n** (0.22 µF) — keep
- Large Cap Board exists as vertical PCB with bridge + multi-stage filters
- Six speaker taps, four RCA inputs, volume + selector
- PT type LM-9908P-A class; OT LM-9914U class

---

## Known deltas (PDF → this unit)

| Topic         | PDF                                            | This unit (empirical)                                              | Action                                                                                             |
| ------------- | ---------------------------------------------- | ------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------- |
| C5/C6         | 220 µF / 450 V                                 | **180 µF / 450 V**                                                 | Install 180 µF; KiCad notes as-built                                                               |
| C5/C6 voltage | 450 V                                          | Some **200 V** bodies seen                                         | Gemini: OK; optional upgrade on recap                                                              |
| C8/C9         | 470 µF / 400 V                                 | **470 µF / 450 V** top pair on flat_power                          | OK                                                                                                 |
| C7            | 470 µF / 50 V                                  | PDF aux rail — separate from **C8/C9**                             | Side photo                                                                                         |
| R23/R24       | 68 kΩ / 2 W bleeders                           | Original **~62 kΩ** · rebuild **68 kΩ / 3 W** (on order)           | Install **68 kΩ / 3 W**                                                                            |
| R21–R22       | per PDF                                        | **100 kΩ** · ceramic **R22** on board                              | OI-2 closed                                                                                        |
| EL34 grid R   | 1 kΩ                                           | **1 kΩ** all four sockets (assembled bottom photo)                 | **Closed** (OI-1)                                                                                  |
| Global NFB    | **8 Ω** post → **R5 ∥ C2** → **12AX7** cathode | **PRP** from tags **13/19** posts; **R5/R5′** + **\*C2** on preamp | Documented [`back-panel.md`](../docs/back-panel.md) · [`preamp-board.md`](../docs/preamp-board.md) |
| PCB silk      | +B, +B1, +B2, −B                               | **+B**, **+B2**, **−B**, **70V IN**; **+B1** unlabeled on face     | OI-3 closed                                                                                        |
| Model         | JD202A.s01                                     | Sticker **SJ202A**, panel **JD202**                                | Informational                                                                                      |

---

## Open issues

See [`../archive/open-issues.md`](../archive/open-issues.md) for OI-1 … OI-8 (plain-language bench checklist; archived).

---

## PDF BOM (reference only — do not build blindly)

| Ref     | PDF value               | As-built note                                                  |
| ------- | ----------------------- | -------------------------------------------------------------- |
| C8/C9   | 470 µF / 400 V (series) | 470 µF / 450 V observed                                        |
| C6      | 220 µF / 450 V          | **180 µF / 450 V**                                             |
| C5      | 220 µF / 450 V          | **180 µF / 450 V**                                             |
| C11/C10 | 220 µF / 160 V          | Confirm on green caps                                          |
| C7      | 470 µF / 50 V           | PDF aux rail — **not** the top pair (**C8/C9**)                |
| R21     | 100K / 2 W              | **100 kΩ** confirmed                                           |
| R22     | 3.3K / 5 W              | **Ceramic on board** — PDF value                               |
| R23/R24 | 68K / 2 W               | Rebuild **68 kΩ / 3 W** on order · original **~62 kΩ** metered |
| R25     | 2.2K / 2 W              | On order                                                       |
| VD3–6   | 1N5408                  | **Confirmed** silk                                             |
| VD7     | 1N4007                  | Silk on flat_power                                             |

---

## Other notes

- EL34 sockets: chassis PTP; preamp PCB holes are clearance only.
- Chassis hardware upgrades (posts, inlet, fuse) are mechanical — not on PDF.
- Wire tags: check aid only; most original wires removed.
