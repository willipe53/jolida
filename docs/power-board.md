# Power Board Schematic

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-05  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

## Files

| File                                                                           | Purpose                                                 |
| ------------------------------------------------------------------------------ | ------------------------------------------------------- |
| [`power-board.png`](power-board.png)                                           | **Primary visual** — preview in Cursor or any viewer    |
| [`power-board.svg`](power-board.svg)                                           | Same diagram as SVG (browser / Inkscape)                |
| [`../kicad/jolida.kicad_sch`](../kicad/jolida.kicad_sch)                       | KiCad schematic (open `jolida.kicad_pro`)               |
| [`../kicad/jolida.kicad_pcb`](../kicad/jolida.kicad_pcb)                       | KiCad **board layout** (placement pass 1, unrouted)     |
| [`power-board-pcb.png`](power-board-pcb.png)                                   | PCB top preview (no KiCad needed)                       |
| [`../photos/flat_power.png`](../photos/flat_power.png)                         | **Primary PCB layout** — desoldered board, silk visible |
| [`../photos/desoldered power top.png`](../photos/desoldered%20power%20top.png) | Alternate top view                                      |
| [`open-issues.md`](open-issues.md)                                             | C10/C11 verification (OI-2 closed)                      |

Regenerate KiCad files:

```bash
python3 kicad/generate_power_schematic.py
python3 kicad/generate_power_board.py
```

**View the board in KiCad:** open `kicad/jolida.kicad_pro`, then click the **PCB Editor** tab (or open `jolida.kicad_pcb` directly). Pass 1 is **footprint placement only** — no copper traces yet.

**View without KiCad:** open [`power-board-pcb.png`](power-board-pcb.png).

---

## Function

Vertical PCB mounted in chassis. Converts transformer AC into:

| Net (PCB silk) | PDF net        | Nominal (PDF, idle) | Role                                      | Harness tag                       |
| -------------- | -------------- | ------------------- | ----------------------------------------- | --------------------------------- |
| **+B**         | **+B**         | ~+425 V             | Main HT after C8/C9                       | **23**                            |
| **+B1**        | **+B1**        | ~+370 V             | Screens / driver supply                   | **21**                            |
| **+B2**        | **+B2**        | ~+220 V             | Preamp supply                             | **19**                            |
| **−B**         | **−B**         | ~−72 V              | Bias raw (on board)                       | —                                 |
| **−B1**        | **−B1**        | ~−54 V              | Bias filtered → chassis                   | **17**                            |
| **70V IN**     | PT 50 V aux in | AC from **T2**      | Aux winding input (**VD7** / **C7** path) | **PT BLU/BLU** ([`PT.md`](PT.md)) |

Transformer **T2** is off-board (LM-9908P-A class). This sheet ends at wire harness connectors.

---

## As-built BOM (this chassis)

| Ref          | Value              | Status                                                                                             |
| ------------ | ------------------ | -------------------------------------------------------------------------------------------------- |
| **VD3–VD6**  | 1N5408 (bridge)    | **Confirmed** silk [`flat_power.png`](../photos/flat_power.png)                                    |
| **C8**       | 470 µF / 450 V     | **Top cap** (pair with C9) · Chemi-Con · confirmed                                                 |
| **C9**       | 470 µF / 450 V     | **Top cap** (pair with C8) · Chemi-Con · confirmed                                                 |
| **R23, R24** | **68 kΩ / 3 W**    | **On order** ×2 · PDF **68 kΩ / 2 W** · original **~62 kΩ** (60–65 kΩ meter, blue–red–orange–gold) |
| **R21**      | **100 kΩ / 2 W**   | Wirewound · **brown–black–yellow–gold** · tag **21** nearby                                        |
| **R22**      | **3.3 kΩ / 5 W**   | **White ceramic on board** (kept) — PDF value; meter optional                                      |
| **C6**       | **180 µF / 450 V** | **Cap body verified**                                                                              |
| **C5**       | **180 µF / 450 V** | **Cap body verified**                                                                              |
| **C7**       | 470 µF / 50 V      | PDF / side photo only — **not** the top pair (those are **C8/C9**)                                 |
| **VD7**      | 1N4007             | PCB silk                                                                                           |
| **C11**      | 220 µF / 160 V     | PDF · verify (green cap TBD)                                                                       |
| **R25**      | 2.2 kΩ / 2 W       | On order · PDF match                                                                               |
| **C10**      | 220 µF / 160 V     | PCB silk · verify value                                                                            |

### Observed, position TBD

| Value             | Notes                                                         |
| ----------------- | ------------------------------------------------------------- |
| 220 µF / 200 V ×2 | `power board side.png` top — not confirmed on desoldered silk |

---

## PCB layout (physical bottom → top)

From [`flat_power.png`](../photos/flat_power.png) — board held vertically, reading **bottom edge up** (bias end → HT end):

| Order | Ref / label  | Notes                                                                                                                   |
| ----- | ------------ | ----------------------------------------------------------------------------------------------------------------------- |
| 1     | **VD7**      | Bias diode, bottom                                                                                                      |
| 2     | **R25**      |                                                                                                                         |
| 3     | **C11**      |                                                                                                                         |
| 4     | **C10**      |                                                                                                                         |
| 5     | **−B**       | Owner silk **−B** (OI-3)                                                                                                |
| 6     | **C5**       | Small “5” near **+B2** silk                                                                                             |
| 7     | **+B2**      | Owner silk **+B2** (OI-3)                                                                                               |
| 8     | **C6**       |                                                                                                                         |
| 9     | **R21**      | **Silk confirmed** · white wirewound (`RX27-1-5` class)                                                                 |
| 10    | **TP1**      | **C3** harness origin — silk **V4, V3, GND, V3, V4** bottom→top; **GRN** tags **23, 17, 21, 19**; center **GND** (OI-6) |
| 11    | **VD3–VD6**  | **Confirmed** bridge around **AC IN** · owner silk **70V IN** at PT aux input (OI-3)                                    |
| 12    | **C8**       | Top of HT stack — **not C7**                                                                                            |
| 13    | **R23, R24** | Between C8 and C9                                                                                                       |
| 14    | **C9**       | Top · owner silk **+B** (OI-3)                                                                                          |

**Bridge positions** (left→right around AC IN): **VD6 · VD4 · AC IN · VD5 · VD3**.

**Top cap pair = C8 + C9** (series HT filter). **C7** is a separate PDF aux rail — not these two.

**PCB silk (OI-3):** **+B**, **+B2**, **−B**, **70V IN** on desoldered board. **+B1** has no silk on this face — tap after **R22**, harness tag **21**.

**TP1 / C3:** Five pads = **Power Board solder end of C3**. Center = **GND**. Outer four = **GRN** tags **23 (+B)**, **17 (−B1/bias)**, **21 (+B1)**, **19 (+B2)** → **8-pin Chassis**. Factory **Vx-TP** = EL34 **pin 8** ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)); **TP1** silk **V3/V4** matches **V3-TP/V4-TP**. Grids = **pin 4** (**OI-1**). Full map: [`open-issues.md`](open-issues.md) **OI-6**.

## Harness (wire tags → nets)

| Tag | Net (PCB / PDF) | C3 / TP1                 |
| --- | --------------- | ------------------------ |
| 23  | **+B**          | **GRN** · TP1 pad (OI-6) |
| 21  | **+B1**         | **GRN** · TP1 pad (OI-6) |
| 19  | **+B2**         | **GRN** · TP1 pad (OI-6) |
| 17  | **−B1** / bias  | **GRN** · TP1 pad (OI-6) |
| 11  | GND             | TP1 center + elsewhere   |
| 15  | mid board       | —                        |
| 13  | **+B** area     | —                        |
| 7   | lower board     | —                        |
| 5   | bottom          | —                        |

Full tag list: [`wire-tags.md`](wire-tags.md). Most original wires removed.

---

## Circuit topology (text)

```text
T2 HV ──► AC IN ──► [VD3–VD6 bridge] ──► +B
                                        │
                    C8(470) ──┬── C9(470)  (series, midpoint → GND)
                              │
                         R23 ∥ R24 → GND
                              │
                             R22
                              │
                             +B1 ── C6(180µ) ── GND
                              │
                             R21
                              │
                             +B2 ── C5(180µ) ── GND

T2 50V ──► VD7 ──► -B ── C11 ── GND
                    │
                   R25
                    │
                   -B1 ── C10 ── GND

T2 (aux) ──► C7(470/50) ── +50V rail
```

---

## PDF cross-check deltas

See [`schematic-comparison.md`](schematic-comparison.md). Key: **180 µF** not **220 µF** at C5/C6; **R21–R24** confirmed (OI-2 closed).

---

## Next steps

- [x] **R21** **100 kΩ** (OI-2)
- [x] **R22** ceramic on board (OI-2)
- [ ] **R23, R24** **68 kΩ / 3 W** ×2 on order (install when arrived; original **~62 kΩ** — do not reuse)
- [x] **TP1 / C3** map documented (OI-6); pad↔tag order — buzz at rebuild
- [ ] Read green bias caps (C10/C11) before reinstall
- [ ] Assign KiCad footprints from desoldered pad patterns
- [ ] Wire KiCad `power.kicad_sch` nets (run generator, connect in KiCad)
