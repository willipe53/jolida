<!-- Archived snapshot of docs/large-cap-board.md before reconnect-sheet cleanup (2026-07-15). Historical observation / tagging notes. Live rebuild sheet: docs/large-cap-board.md. -->

# ARCHIVE — large-cap-board-as-built-notes

**Do not use this file to rebuild.** See [`../docs/large-cap-board.md`](../docs/large-cap-board.md) for the live reconnect sheet.

---

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-05  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

## Files

| File                                                                                                         | Purpose                                                                  |
| ------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------ |
| [`../photos/large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png)       | **Primary PCB layout** — desoldered board, silk + old tag labels visible |
| [`../photos/large cap board bottom desoldered.png`](../photos/large%20cap%20board%20bottom%20desoldered.png) | Solder side, desoldered                                                  |
| [`../photos/large cap board top 2.png`](../photos/large%20cap%20board%20top%202.png)                         | Alternate top view (populated)                                           |
| [`../photos/large cap board side.png`](../photos/large%20cap%20board%20side.png)                             | Side view (cap bodies)                                                   |
| [`../archive/large-cap-board.png`](../archive/large-cap-board.png)                                           | Visual schematic (archived)                                              |
| [`../archive/large-cap-board.svg`](../archive/large-cap-board.svg)                                           | Same diagram as SVG (archived)                                           |
| [`../archive/kicad/jolida.kicad_sch`](../archive/kicad/jolida.kicad_sch)                                     | KiCad schematic (archived; open `jolida.kicad_pro`)                      |
| [`../archive/kicad/jolida.kicad_pcb`](../archive/kicad/jolida.kicad_pcb)                                     | KiCad board layout (archived; placement pass 1)                          |
| [`../archive/open-issues.md`](../archive/open-issues.md)                                                     | C10/C11 verification (OI-2 closed)                                       |

Regenerate KiCad files (archived generators):

```bash
python3 archive/kicad/generate_power_schematic.py
python3 archive/kicad/generate_large_cap_board.py
```

---

## Function

Vertical PCB mounted in chassis. Converts transformer AC into:

| Net (PCB silk) | PDF net        | Nominal (PDF, idle) | Role                                      | Leaves the board as                                        |
| -------------- | -------------- | ------------------- | ----------------------------------------- | ---------------------------------------------------------- |
| **+B**         | **+B**         | ~+425 V             | Main HT after C8/C9                       | **2× RED** (tags **13**, **23**) → OT center taps (**C3**) |
| **+B1**        | **+B1**        | ~+370 V             | Screens / driver supply                   | **15 RED** → preamp (**C2**)                               |
| **+B2**        | **+B2**        | ~+220 V             | Preamp supply                             | **7 YEL** → preamp (**C2**)                                |
| **−B**         | **−B**         | ~−72 V              | Bias raw (on board)                       | —                                                          |
| **−B1**        | **−B1**        | ~−54 V              | Bias filtered → preamp bias network       | **9 BLU** → preamp (**C2**)                                |
| **70V IN**     | PT 50 V aux in | AC from **T2**      | Aux winding input (**VD7** / **C7** path) | in: **PT BLU/BLU** tags **17/19** ([`PT.md`](PT.md))       |

Transformer **T2** is off-board (LM-9908P-A class). This sheet ends at the wire harness.

**Tag-reuse warning:** numbers **23 / 21 / 19 / 17** appear at this board **twice** — on the red/blue power wires above **and** on the four **GRN** TP1 sense wires (different wires, same numbers). Identity = **color + number**, never number alone.

---

## As-built BOM (this chassis)

| Ref          | Value              | Status                                                                                                          |
| ------------ | ------------------ | --------------------------------------------------------------------------------------------------------------- |
| **VD3–VD6**  | 1N5408 (bridge)    | **Confirmed** silk [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) |
| **C8**       | 470 µF / 450 V     | **Top cap** (pair with C9) · Chemi-Con · confirmed                                                              |
| **C9**       | 470 µF / 450 V     | **Top cap** (pair with C8) · Chemi-Con · confirmed                                                              |
| **R23, R24** | **68 kΩ / 3 W**    | **On order** ×2 · PDF **68 kΩ / 2 W** · original **~62 kΩ** (60–65 kΩ meter, blue–red–orange–gold)              |
| **R21**      | **100 kΩ / 2 W**   | Wirewound · **brown–black–yellow–gold** · tag **21** nearby                                                     |
| **R22**      | **3.3 kΩ / 5 W**   | **White ceramic on board** (kept) — PDF value; meter optional                                                   |
| **C6**       | **180 µF / 450 V** | **Cap body verified**                                                                                           |
| **C5**       | **180 µF / 450 V** | **Cap body verified**                                                                                           |
| **C7**       | 470 µF / 50 V      | PDF / side photo only — **not** the top pair (those are **C8/C9**)                                              |
| **VD7**      | 1N4007             | PCB silk                                                                                                        |
| **C11**      | 220 µF / 160 V     | PDF · verify (green cap TBD)                                                                                    |
| **R25**      | 2.2 kΩ / 2 W       | On order · PDF match                                                                                            |
| **C10**      | 220 µF / 160 V     | PCB silk · verify value                                                                                         |

### Observed, position TBD

| Value             | Notes                                                             |
| ----------------- | ----------------------------------------------------------------- |
| 220 µF / 200 V ×2 | `large cap board side.png` top — not confirmed on desoldered silk |

---

## PCB layout (physical bottom → top)

From [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) — board held vertically, reading **bottom edge up** (bias end → HT end):

| Order | Ref / label  | Notes                                                                                                                                                  |
| ----- | ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 1     | **VD7**      | Bias diode, bottom                                                                                                                                     |
| 2     | **R25**      |                                                                                                                                                        |
| 3     | **C11**      |                                                                                                                                                        |
| 4     | **C10**      |                                                                                                                                                        |
| 5     | **−B**       | Owner silk **−B** (OI-3)                                                                                                                               |
| 6     | **C5**       | Small “5” near **+B2** silk                                                                                                                            |
| 7     | **+B2**      | Owner silk **+B2** (OI-3)                                                                                                                              |
| 8     | **C6**       |                                                                                                                                                        |
| 9     | **R21**      | **Silk confirmed** · white wirewound (`RX27-1-5` class)                                                                                                |
| 10    | **TP1**      | **Bias test-point header** — five isolated pads, silk **V4, V3, GND, V3, V4** bottom→top; center **GND**; **GRN** sense wires from EL34 pin 8 (**C3**) |
| 11    | **VD3–VD6**  | **Confirmed** bridge around **AC IN** · owner silk **70V IN** at PT aux input (OI-3)                                                                   |
| 12    | **C8**       | Top of HT stack — **not C7**                                                                                                                           |
| 13    | **R23, R24** | Between C8 and C9                                                                                                                                      |
| 14    | **C9**       | Top · owner silk **+B** (OI-3)                                                                                                                         |

**Bridge positions** (left→right around AC IN): **VD6 · VD4 · AC IN · VD5 · VD3**.

**Top cap pair = C8 + C9** (series HT filter). **C7** is a separate PDF aux rail — not these two.

**PCB silk (OI-3):** **+B**, **+B2**, **−B**, **70V IN** on desoldered board. **+B1** has no silk on this face — tap after **R22**, leaves as **15 RED** (C2).

**TP1 (bias test points, redefined 2026-07-12):** the five TP1 pads are **isolated test points** — no other connectivity on this board. Each outer pad receives a **GRN sense wire from one EL34's pin 8** (factory **Vx-TP**, [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)); center pad = **GND**. Purpose: measure each tube's bias (~40 mV across the 1 Ω cathode sense) with a meter at this board instead of flipping the chassis. Silk names the tube — at rebuild, wire each socket's pin 8 to its named pad; the old GRN tag numbers (**23/17/21/19**) are historical. Harness detail: [`8-pin-chassis.md`](8-pin-chassis.md).

## Harnesses at this board

Every wire in and out, from photo labels on [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) (2026-07-12):

| Wire (color + tag)       | Direction | Net / function                       | Harness | Other end                                                  |
| ------------------------ | --------- | ------------------------------------ | ------- | ---------------------------------------------------------- |
| **21 RED**               | in        | PT HV ~300 V AC → **AC IN** / bridge | **C1**  | PT-L1 ([`PT.md`](PT.md))                                   |
| **11 BLK**               | in        | PT HV return (0 V) → **AC IN**       | **C1**  | PT-L2                                                      |
| **17 BLU**               | in        | PT 50 V aux → **70V IN**             | **C1**  | PT-L3                                                      |
| **19 BLU**               | in        | PT 50 V aux → **70V IN**             | **C1**  | PT-L4                                                      |
| **13 RED**               | out       | **+B** (from top 470 µF cap +)       | **C3**  | One OT center tap ([`8-pin-chassis.md`](8-pin-chassis.md)) |
| **23 RED**               | out       | **+B** (same node)                   | **C3**  | Other OT center tap                                        |
| **15 RED**               | out       | **+B1**                              | **C2**  | Preamp **+B1** pad ([`preamp-board.md`](preamp-board.md))  |
| **7 YEL**                | out       | **+B2** (leaves near 180 µF C5/C6)   | **C2**  | Preamp **+B2** pad                                         |
| **9 BLU**                | out       | **−B / −B1** (bias)                  | **C2**  | Preamp **−B** pad (bias network)                           |
| **6 BLK**                | out       | **GND**                              | **C2**  | Preamp **GND** pad                                         |
| **GRN ×4** (23/17/21/19) | in        | EL34 pin-8 bias sense → **TP1**      | **C3**  | Octal sockets, pin 8                                       |
| Heavy BLK                | out       | Board **GND** pour → chassis star    | —       | Star stud ([`chassis.md`](chassis.md))                     |

**Not through this board:** heaters (all three 6.3 V pairs run **direct from the PT** to the preamp board and octal sockets) and the PT tag-9 **BLK** ground (direct PT → preamp pour).

### C1 — PT ↔ Large Cap Board (hardwire, this doc owns it)

Four 18 AWG solder joints (the mains-primary and safety-earth wiring belongs to the [Back Panel](back-panel.md)):

| Wire | Function     | Tag | Color | ☐ Soldered | ☐ Metered |
| ---- | ------------ | --- | ----- | ---------- | --------- |
| 1    | PT HV        | 21  | RED   | ☐          | ☐         |
| 2    | PT HV return | 11  | BLK   | ☐          | ☐         |
| 3    | PT 50 V aux  | 17  | BLU   | ☐          | ☐         |
| 4    | PT 50 V aux  | 19  | BLU   | ☐          | ☐         |

Keep the HV pair and the aux pair twisted through splices. To bench-test the Large Cap Board alone, C1 is the only harness that must be live.

Full tag index: [`../archive/wire-tags.md`](../archive/wire-tags.md). Most original wires removed.

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

See [`../archive/schematic-comparison.md`](../archive/schematic-comparison.md). Key: **180 µF** not **220 µF** at C5/C6; **R21–R24** confirmed (OI-2 closed).

---

## Next steps

- [x] **R21** **100 kΩ** (OI-2)
- [x] **R22** ceramic on board (OI-2)
- [ ] **R23, R24** **68 kΩ / 3 W** ×2 on order (install when arrived; original **~62 kΩ** — do not reuse)
- [x] **TP1** redefined — isolated bias test points; pad↔tag order moot (wire pin 8 to named pad)
- [x] Harness fully mapped — all in/out wires identified (2026-07-12)
- [ ] Read green bias caps (C10/C11) before reinstall
- [ ] Assign KiCad footprints from desoldered pad patterns
- [ ] Wire KiCad `large-cap-board.kicad_sch` nets (run generator, connect in KiCad)
