# Open Issues

Questions we still need to **answer on the bench** for **this chassis**. Each item says what the part is, what we already know, what to measure, and why it matters.

**Trust order:** this amp’s photos and parts > [`gemini-restoration-notes.md`](gemini-restoration-notes.md) > factory PDF ([`Jolida-JD202A-int-sch.pdf`](../docs/Jolida-JD202A-int-sch.pdf)). See [`SOURCES.md`](../docs/SOURCES.md).

When you close an item, record the measurement in the worksheet or board doc and change **Status** to **Closed**.

---

## OI-1 — EL34 grid stopper resistors — Closed

**Status:** Closed · 2026-07-06 · rebuild with **1 kΩ** (match factory PDF)

**What this is:** Each **EL34** power tube has a **control grid** — the pin that receives audio from the preamp. A **small resistor in series** between the preamp wire and that grid pin is a **grid stopper** (factory parts **R13** and **R16**, one per channel).

**Resolution:** [`8 pin 4.png`](../photos/8%20pin%204.png) close-up shows the blue-body **1 kΩ** resistor soldered from the preamp signal wire to **pin 5** of the octal socket (control grid). Key at ~6 o'clock, pin 5 at ~1 o'clock (bottom view, clockwise from key). Matches factory PDF **R13** / **R16**. All four sockets carry the same **1 kΩ** stopper per [`assembled from bottom.png`](../photos/assembled%20from%20bottom.png).

**Supersedes:** Earlier docs said **pin 4** — that would be the screen (UL tap) and would break push-pull operation. **Correct pin is 5** (control grid). Also supersedes earlier **6.8 kΩ** read.

**Rebuild:** Install **1 kΩ** grid stoppers on all four sockets, **pin 5**.

**EL34 pinout reference (bottom view, clockwise from key):**

| Pin   | Function                             |
| ----- | ------------------------------------ |
| 1     | IS (internal shield)                 |
| 2     | Heater                               |
| 3     | Anode (plate) — OT primary           |
| 4     | Screen (g₂) — OT **UL tap**          |
| **5** | **Control grid (g₁) — 1 kΩ stopper** |
| 6     | NC                                   |
| 7     | Heater                               |
| 8     | Cathode + g₃ — **Vx-TP** / 1 Ω R     |

---

## OI-2 — Large Cap Board big resistors (R21–R24) — Closed

**Status:** Closed · 2026-07-06

**What this is:** Resistors on the large cap board that drop and bleed the **B+ filter stack** (**R21–R24** on the factory PDF).

| Part         | Factory PDF      | This chassis                      | Notes                                                                     |
| ------------ | ---------------- | --------------------------------- | ------------------------------------------------------------------------- |
| **R21**      | 100 kΩ / 2 W     | **100 kΩ**                        | Owner confirmed                                                           |
| **R22**      | 3.3 kΩ / 5 W     | **White ceramic on board** (kept) | Assume PDF **3.3 kΩ** unless meter says otherwise                         |
| **R23, R24** | 68 kΩ / 2 W each | **~62 kΩ** each (original)        | Desoldered parts meter **60–65 kΩ**; bands **blue – red – orange – gold** |

**Band reading note:** Listed one way the colors run **gold, orange, red, blue** along the body. For the code, read from the **other** end: **blue (6) · red (2) · orange (×1k) · gold (±5 %)** → **62 kΩ**, which matches the meter. PDF **68 kΩ** is **blue · grey · orange · gold**.

**Rebuild:** **100 kΩ** R21 · **3.3 kΩ / 5 W** ceramic R22 · **68 kΩ / 3 W** R23 and R24 (**on order** — PDF **68 kΩ / 2 W**; **3 W** upgrade OK). Do **not** reinstall the original **~62 kΩ** parts.

**Supersedes:** Old **27 Ω / 10 W** silk read · disputed photo band reads · **47 kΩ** guess · **62 kΩ** rebuild default.

**Still at power-up:** confirm rail **voltages** match [`large-cap-board.md`](../docs/large-cap-board.md) (names closed — **OI-3**).

---

## OI-6 — TP1 test pads / C3 harness origin — Closed

**Status:** Closed · 2026-07-06

**What this is:** Five **small test pads** (**TP1**) near the **AC IN** bridge on the Large Cap Board. Silk reads **V4, V3, GND, V3, V4** (bottom→top). These are **not** tube sockets and **not** the bias-trim pots **V3/V4/V7/V8** under the chassis — they are the **Large Cap Board end of C3** (factory breakout + rebuild solder points).

**Resolution:**

| Item                | Detail                                                                                                                                                                                                   |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Center pad**      | **GND** (owner confirmed)                                                                                                                                                                                |
| **Outer four pads** | **Green** wire each, tags **23**, **17**, **21**, **19** (one tag per pad)                                                                                                                               |
| **Tag → net**       | **23** = **+B** · **21** = **+B1** · **19** = **+B2** · **17** = **−B1** / bias ([`large-cap-board.md`](../docs/large-cap-board.md))                                                                     |
| **Pad ↔ tag order** | **Not recorded** — silk **V4, V3, GND, V3, V4** bottom→top; buzz each TP1 pad to its tag stub at rebuild                                                                                                 |
| **C3 destination**  | **8-pin Chassis** · EL34 **pin 8** — factory **Vx-TP** on [`Jolida-JD202A-int-sch.pdf`](../docs/Jolida-JD202A-int-sch.pdf) / [`_sch-page-1.png`](_sch-page-1.png) (supersedes earlier **pin 1** misread) |

**Factory PDF:** **V3-TP**, **V4-TP**, **V7-TP**, **V8-TP** sit on **pin 8** of each EL34 — bias test nodes (~**40 mV** target across **R17/R18** 1 Ω). Large Cap Board **TP1** silk **V3/V4** matches those designators (left channel; right channel **V7/V8** via harness). **Grids** are **pin 5** + **1 kΩ** stoppers (**OI-1**); **screens** (UL tap from OT) are **pin 4**.

**Rebuild:** Solder **C3** at these **TP1** pads (or adjacent pad equivalents after recap). Label both ends: net + tag (e.g. `+B / tag 23`).

**Why it mattered:** Maps **C3** for Part 3 — which Large Cap Board rail goes to which chassis wire.

---

## OI-3 — Large Cap Board voltage names — Closed

**Status:** Closed · 2026-07-06 · meter **voltages** at Part 3 first power-up (tubes out)

**What this is:** **Silkscreen names** for rails on the Large Cap Board PCB.

**Resolution (owner read, desoldered board):**

| PCB silk (this board)    | PDF / circuit net  | Nominal (PDF, idle)         | Harness tag (if wired)                    |
| ------------------------ | ------------------ | --------------------------- | ----------------------------------------- |
| **+B**                   | **+B**             | ~**+425 V**                 | **23**                                    |
| **+B2**                  | **+B2**            | ~**+220 V**                 | **19**                                    |
| **−B**                   | **−B**             | ~**−72 V** (raw bias)       | — (bias stack on board)                   |
| **70V IN**               | PT **50 V aux** in | AC from **T2** 50 V winding | **PT BLU/BLU** ([`PT.md`](../docs/PT.md)) |
| *(no silk on this face)* | **+B1**            | ~**+370 V**                 | **21**                                    |

**Notes:**

- PCB silk matches the **factory PDF** (**+B**, **+B2**, **−B**) — not the earlier doc alias **+B3** for the highest rail.
- **+B1** (~370 V) is the tap after **R22** in the filter stack — present in the circuit and on harness tag **21**, but **not** in the four silks you listed (may be unlabeled on this board face or only on stickers).
- **70V IN** is the **PT auxiliary winding** input (PDF **50 V** class; **BLU/BLU** at transformer). Feeds **VD7** / **C7** / bias raw **−B** path — not a DC output rail.
- **−B1** (~−54 V, filtered bias) is downstream of **−B** on the board (**C10/R25**); harness tag **17** is the **−B1 / bias** feed toward the chassis (**C3**).

**At first power-up:** Variac/limiter, tubes out — log **+B**, **+B1**, **+B2**, **−B**, **−B1** vs PDF targets in [`large-cap-board.md`](../docs/large-cap-board.md).

**Supersedes:** Earlier read **+B1 / +B2 / +B3** on [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) — **+B3** was a doc label for PDF **+B**; use **+B** per PCB silk.

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

## OI-7 — Small ceramic caps on preamp board — Open

**Status:** Open · 2026-07-06 · needs meter reading + pad location log at rebuild

**What this is:** Four **small ceramic disc caps** live on the **preamp board**. Two are still installed in board corners (visible on [`preamp board bottom.png`](../photos/preamp%20board%20bottom.png) as small orange / tan discs). The other two **came off when the resistors they were piggybacked across were desoldered** — i.e. they were installed in **parallel with a resistor's leads** and got pulled with the resistor.

**Candidate factory PDF designators** (both marked **`*`** on the schematic = *select at test* / optional anti-parasitic caps, one per channel = 4 total):

| PDF ref    | Value         | Typical placement                         | Function                                                     |
| ---------- | ------------- | ----------------------------------------- | ------------------------------------------------------------ |
| **`*C51`** | 100 pF / 1 kV | Across driver plate-load **R51** (10 kΩ)  | HF stability on 12AT7 driver anode (Miller / anti-parasitic) |
| **`*C2`**  | 20 pF / 100 V | Across / near driver stage **R5** (27 kΩ) | HF stability on driver signal path                           |

Both appear twice on the PDF (once per channel) — matches the observed count of **4**.

**Best guess (subject to meter):**

- **2 still on board (corners)** = the ones piggybacked across resistors that were **kept in place** (probably `*C51` × 2, since **R51** is a normal preamp resistor and did not need desoldering).
- **2 removed with a resistor** = the ones piggybacked across resistors that were **pulled** (probably `*C2` × 2, since **R5** or an equivalent was in the desolder set).

**What to measure at rebuild:**

1. Meter the 2 surviving caps (in circuit if the board is bare, or after gentle desolder) — capacitance range **10 pF – 200 pF**.
2. Note the **silk / pad location** for all 4 positions on [`preamp board bottom.png`](../photos/preamp%20board%20bottom.png) — mark which are stuffed and which are empty.
3. Cross-reference with the factory PDF to confirm PDF designator (`*C2` vs `*C51`).
4. Decide: reinstall per PDF (**100 pF / 1 kV** and **20 pF / 100 V**), or leave uninstalled (PDF marks them optional — modern build with clean layout may not need them).

**Why it matters:** These caps are anti-parasitic — they suppress HF oscillation on the driver stage. Missing them is usually fine on a well-laid-out amp, but if the rebuilt amp shows HF instability (fuzzy top end, ultrasonic ringing on scope), reinstall them before hunting other causes.

**Photo:** [`preamp board bottom.png`](../photos/preamp%20board%20bottom.png) — small orange / tan discs visible near the noval socket rings.

---

## OI-8 — Preamp-board white ceramic power resistors — Open

**Status:** Open · 2026-07-06 · one-meter reading closes this

**What this is:** Four **white ceramic power resistors** sit vertically along the **LEFT edge** of the preamp board, one near each of the four EL34 socket cutouts ([`preamp board top.png`](../photos/preamp%20board%20top.png)). Owner left them on the board during desolder.

**Two possibilities:**

| Hypothesis                                      | PDF ref                          | Expected meter | Body power                                           |
| ----------------------------------------------- | -------------------------------- | -------------- | ---------------------------------------------------- |
| **A. EL34 cathode current-sense (1 Ω)**         | **R17 / R18** (+ pair) 1 Ω / 5 W | **~1 Ω**       | 5 W ceramic overkill for 1 Ω but plausible           |
| **B. 12AT7 driver plate loads (22 kΩ / 24 kΩ)** | **R7 / R8** + pair, 2 – 3 W      | **~22–24 kΩ**  | 5 W ceramic matches the ~2.5 W dissipation at ~250 V |

Position (near EL34 sockets, on the preamp-board edge closest to the octal chassis) is topologically consistent with **either** — the cathode sense would be run from EL34 pin 8 through a short wire to the resistor and back to preamp GND; the driver plate loads would sit on the preamp side and be fed from **+B1**.

**What to measure at rebuild:**

- Meter one of the four in-circuit (or lifted). ~**1 Ω** → hypothesis A closes: they **are R17/R18** (kept on board like R22, no action). ~**22 kΩ** or ~**24 kΩ** → hypothesis B closes: they are driver plate loads, and **R17/R18** (1 Ω / 5 W) still need to be sourced separately and installed on the 8-pin chassis at each EL34 socket pin 8 → GND.

**Why it matters:**

- Under hypothesis A, the **Vx-TP** bias reading (~40 mV target) is taken across these ceramics — R17/R18 are the amp's built-in bias-measurement instrument. Also determines whether we need to order R17/R18.
- Under hypothesis B, R17/R18 are not yet accounted for anywhere and must be added to the parts list.

**Related:** OI-6 (Vx-TP / pin 8 destination), OI-1 (grid stoppers on pin 5), OI-2 (R22 white-ceramic-on-board precedent).

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
| 2026-07-06 | **OI-7** opened: 4 small ceramic caps on preamp board (candidates **`*C2`** 20 pF, **`*C51`** 100 pF per PDF)                  |
| 2026-07-06 | **OI-8** opened: 4 white ceramic power resistors on preamp board LEFT edge — meter to disambiguate R17/R18 vs R7/R8            |
