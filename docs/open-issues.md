# Open Issues

Questions we still need to **answer on the bench** for **this chassis**. Each item says what the part is, what we already know, what to measure, and why it matters.

**Trust order:** this amp’s photos and parts > [`gemini-restoration-notes.md`](gemini-restoration-notes.md) > factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)). See [`SOURCES.md`](SOURCES.md).

When you close an item, record the measurement in the worksheet or board doc and change **Status** to **Closed**.

---

## OI-1 — EL34 grid stopper resistors — Closed

**Status:** Closed · 2026-07-06 · rebuild with **1 kΩ** (match factory PDF)

**What this is:** Each **EL34** power tube has a **control grid** — the pin that receives audio from the preamp. A **small resistor in series** between the preamp wire and that grid pin is a **grid stopper** (factory parts **R13** and **R16**, one per channel).

**Resolution:** [`assembled from bottom.png`](../photos/assembled%20from%20bottom.png) shows **four identical** resistors soldered between the preamp board and **pin 4** of each octal socket. All read **1 kΩ** (brown-black-black-brown-brown, 5-band **1 %**). Matches factory PDF — **no 6.8 kΩ** on this chassis.

**Supersedes:** Earlier read of **6.8 kΩ** on [`another 8 pin.png`](../photos/another%208%20pin.png) — likely a different part or misread; trust the assembled bottom view.

**Rebuild:** Install **1 kΩ** grid stoppers on all four sockets.

---

## OI-2 — Power board big resistors (R21–R24) — Closed

**Status:** Closed · 2026-07-06

**What this is:** Resistors on the power board that drop and bleed the **B+ filter stack** (**R21–R24** on the factory PDF).

| Part         | Factory PDF      | This chassis                      | Notes                                                                     |
| ------------ | ---------------- | --------------------------------- | ------------------------------------------------------------------------- |
| **R21**      | 100 kΩ / 2 W     | **100 kΩ**                        | Owner confirmed                                                           |
| **R22**      | 3.3 kΩ / 5 W     | **White ceramic on board** (kept) | Assume PDF **3.3 kΩ** unless meter says otherwise                         |
| **R23, R24** | 68 kΩ / 2 W each | **~62 kΩ** each (original)        | Desoldered parts meter **60–65 kΩ**; bands **blue – red – orange – gold** |

**Band reading note:** Listed one way the colors run **gold, orange, red, blue** along the body. For the code, read from the **other** end: **blue (6) · red (2) · orange (×1k) · gold (±5 %)** → **62 kΩ**, which matches the meter. PDF **68 kΩ** is **blue · grey · orange · gold**.

**Rebuild:** **100 kΩ** R21 · **3.3 kΩ / 5 W** ceramic R22 · **68 kΩ / 3 W** R23 and R24 (**on order** — PDF **68 kΩ / 2 W**; **3 W** upgrade OK). Do **not** reinstall the original **~62 kΩ** parts.

**Supersedes:** Old **27 Ω / 10 W** silk read · disputed photo band reads · **47 kΩ** guess · **62 kΩ** rebuild default.

**Still at power-up:** confirm rail **voltages** match [`power-board.md`](power-board.md) (names closed — **OI-3**).

---

## OI-6 — TP1 test pads / C3 harness origin — Closed

**Status:** Closed · 2026-07-06

**What this is:** Five **small test pads** (**TP1**) near the **AC IN** bridge on the Power Board. Silk reads **V4, V3, GND, V3, V4** (bottom→top). These are **not** tube sockets and **not** the bias-trim pots **V3/V4/V7/V8** under the chassis — they are the **Power Board end of C3** (factory breakout + rebuild solder points).

**Resolution:**

| Item                | Detail                                                                                                                                                                                           |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Center pad**      | **GND** (owner confirmed)                                                                                                                                                                        |
| **Outer four pads** | **Green** wire each, tags **23**, **17**, **21**, **19** (one tag per pad)                                                                                                                       |
| **Tag → net**       | **23** = **+B** · **21** = **+B1** · **19** = **+B2** · **17** = **−B1** / bias ([`power-board.md`](power-board.md))                                                                             |
| **Pad ↔ tag order** | **Not recorded** — silk **V4, V3, GND, V3, V4** bottom→top; buzz each TP1 pad to its tag stub at rebuild                                                                                         |
| **C3 destination**  | **8-pin Chassis** · EL34 **pin 8** — factory **Vx-TP** on [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) / [`_sch-page-1.png`](_sch-page-1.png) (supersedes earlier **pin 1** misread) |

**Factory PDF:** **V3-TP**, **V4-TP**, **V7-TP**, **V8-TP** sit on **pin 8** of each EL34 — bias test nodes (~**40 mV** target across **R17/R18** 1 Ω). Power-board **TP1** silk **V3/V4** matches those designators (left channel; right channel **V7/V8** via harness). **Grids** remain **pin 4** + **1 kΩ** stoppers (**OI-1**).

**Rebuild:** Solder **C3** at these **TP1** pads (or adjacent pad equivalents after recap). Label both ends: net + tag (e.g. `+B / tag 23`).

**Why it mattered:** Maps **C3** for Part 3 — which Power Board rail goes to which chassis wire.

---

## OI-3 — Power board voltage names — Closed

**Status:** Closed · 2026-07-06 · meter **voltages** at Part 3 first power-up (tubes out)

**What this is:** **Silkscreen names** for rails on the Power Board PCB.

**Resolution (owner read, desoldered board):**

| PCB silk (this board)    | PDF / circuit net  | Nominal (PDF, idle)         | Harness tag (if wired)            |
| ------------------------ | ------------------ | --------------------------- | --------------------------------- |
| **+B**                   | **+B**             | ~**+425 V**                 | **23**                            |
| **+B2**                  | **+B2**            | ~**+220 V**                 | **19**                            |
| **−B**                   | **−B**             | ~**−72 V** (raw bias)       | — (bias stack on board)           |
| **70V IN**               | PT **50 V aux** in | AC from **T2** 50 V winding | **PT BLU/BLU** ([`PT.md`](PT.md)) |
| *(no silk on this face)* | **+B1**            | ~**+370 V**                 | **21**                            |

**Notes:**

- PCB silk matches the **factory PDF** (**+B**, **+B2**, **−B**) — not the earlier doc alias **+B3** for the highest rail.
- **+B1** (~370 V) is the tap after **R22** in the filter stack — present in the circuit and on harness tag **21**, but **not** in the four silks you listed (may be unlabeled on this board face or only on stickers).
- **70V IN** is the **PT auxiliary winding** input (PDF **50 V** class; **BLU/BLU** at transformer). Feeds **VD7** / **C7** / bias raw **−B** path — not a DC output rail.
- **−B1** (~−54 V, filtered bias) is downstream of **−B** on the board (**C10/R25**); harness tag **17** is the **−B1 / bias** feed toward the chassis (**C3**).

**At first power-up:** Variac/limiter, tubes out — log **+B**, **+B1**, **+B2**, **−B**, **−B1** vs PDF targets in [`power-board.md`](power-board.md).

**Supersedes:** Earlier read **+B1 / +B2 / +B3** on [`desoldered power top.png`](../photos/desoldered%20power%20top.png) — **+B3** was a doc label for PDF **+B**; use **+B** per PCB silk.

---

## OI-4 — Main filter cap value (C5 / C6) — Closed

**Status:** Closed · install **180 µF / 450 V** (TDK B43231B on order)

**What this was:** Two main B+ filter electrolytics. PDF **220 µF / 450 V**; cap bodies read **180 µF / 450 V**.

**Resolution:** Rebuild with **180 µF / 450 V**. PDF delta logged in [`schematic-comparison.md`](schematic-comparison.md) only.

---

## OI-5 — Model names on the amp — Closed

**Status:** Closed · no action

| Where          | Name       |
| -------------- | ---------- |
| Factory PDF    | JD202A.s01 |
| Front panel    | JD202      |
| Bottom sticker | SJ202A     |

Use the PDF for **topology**, not exact BOM match to the sticker.

---

## Accepted notes (not blocking)

**220 µF caps marked 200 V on +B rails:** Some bodies show **200 V** vs PDF **450 V**. Owner accepted; optional **450 V** upgrade on recap. Not blocking.

---

## Changelog

| Date       | Change                                                                                                                         |
| ---------- | ------------------------------------------------------------------------------------------------------------------------------ |
| 2026-07-05 | OI-4 resolved: **180 µF / 450 V** on cap body                                                                                  |
| 2026-07-05 | OI-2 expanded from `flat_power.png`; OI-6 added (TP1)                                                                          |
| 2026-07-06 | Rewritten in plain language (what / know / measure / why)                                                                      |
| 2026-07-06 | **OI-1** closed: all four socket resistors **1 kΩ** per [`assembled from bottom.png`](../photos/assembled%20from%20bottom.png) |
| 2026-07-06 | **OI-6** closed: TP1 = **C3**; **GRN** tags **23/17/21/19**; center **GND**; → EL34 **pin 8** (**Vx-TP** per PDF)              |
| 2026-07-06 | **OI-3** closed: PCB silk **+B**, **+B2**, **−B**, **70V IN** (owner); **+B1** via tag **21** only                             |
