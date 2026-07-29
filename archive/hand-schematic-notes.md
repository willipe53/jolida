# Hand Schematic Notes

Source: [`photos/hand_schematic.png`](../photos/hand_schematic.png)

Hand-drawn wiring map made during disassembly. Numbered tags were applied when wires were cut. Red-ink entries document additional cuts and color changes at splices.

---

## Layout (top → bottom)

| Region                          | Physical counterpart                                           |
| ------------------------------- | -------------------------------------------------------------- |
| Top strip (LFT / AC / RT / RCA) | Rear panel: speaker terminals, AC inlet, RCA inputs → selector |
| Center block                    | Power transformer                                              |
| V3 / V4 / TP1 detail            | Bias trim pots (underside access: V3, V4, V7, V8)              |
| Horizontal board with caps      | Large Cap Board (AC/DC, +B rails)                              |
| Middle chassis area             | Octal (8-pin) EL34 point-to-point wiring                       |
| Bottom large board              | Preamp board (4× noval sockets + 4× octal holes)               |
| Bottom edge                     | Volume pot (GRN / RED, tag 23)                                 |

```mermaid
flowchart TB
    RP[Rear panel]
    PT[Power transformer]
    PWR[Large Cap Board]
    OCT[Octal socket wiring]
    PRE[Preamp board]
    VOL[Volume pot]
    RP --> PT
    PT --> PWR
    PT --> OCT
    PWR --> PRE
    OCT --> PRE
    PRE --> VOL
```

---

## Notation conventions

### Wire tags

- A **number** on the drawing = white tag on the physical wire at the cut point.
- Two ends with the same number belong together.
- Tags are disassembly IDs, not factory designators.

### Color labels

- **Single color** (e.g. `BLK`, `BLU`) = current wire insulation color.
- **Two colors** on one tag in red-ink splice notes (e.g. `BRN` replaced `PRP`) = **re-termination** during disassembly — **not** a twisted pair.
- **8 Ω posts (tags 13, 19):** factory has **two wires** — **BRN** (OT) **and** **PRP** (NFB to preamp **R5 / \*C2**). See [`../docs/back-panel.md`](../docs/back-panel.md).
- **G posts (tags 1, 11):** **two BLK wires** — OT common **and** signal **GND** to preamp pour (PDF **GND** at speaker **0**).
- **Red ink** = new splices or re-terminations after additional cuts (see list below).

---

## New splices (red ink, upper left)

| Tag | New color | Path                     | Notes                                                                                 |
| --- | --------- | ------------------------ | ------------------------------------------------------------------------------------- |
| 23  | RED       | **PT** → large cap board | Was BLK at PT bottom bundle                                                           |
| 21  | RED       | **PT** tap               | Was ORG at PT left tap                                                                |
| 19  | BLU       | **OT** → LFT 8 Ω         | Was BRN (originally PRP→BRN) at speaker path                                          |
| 17  | BLU       | **OT** → RT 4 Ω          | Was YEL at OT secondary (not PT tap)                                                  |
| 11  | BRN       | **OT** → RT G            | Was BLK at RT common                                                                  |
| 15  | BLK       | **OT** → LFT 4 Ω         | Was BLU at LFT 4 Ω                                                                    |
| 13  | RED       | **OT** → RT 8 Ω          | Was BRN (originally PRP→BRN); **separate** from tag 13 RED on PT→large-cap-board path |

Verify each splice with continuity before reassembly.

---

## Rear panel — speaker terminals (**OT** secondaries)

Channel assignment from the top strip of [`hand_schematic.png`](../photos/hand_schematic.png):

| Channel | Tags on OT stubs       |
| ------- | ---------------------- |
| **LFT** | **1**, **15**, **19**  |
| **RT**  | **11**, **17**, **13** |

| Terminal | Tag | Color | Notes                                         |
| -------- | --- | ----- | --------------------------------------------- |
| LFT 8 Ω  | 19  | BRN   | OT 8 Ω coil tap; panel splice may read BLU    |
| LFT 8 Ω  | 19  | PRP   | **NFB** → preamp **R5′ ∥ \*C2** (second wire) |
| LFT 4 Ω  | 15  | BLU   | New splice → BLK                              |
| LFT G    | 1   | BLK   | OT common (heavier)                           |
| LFT G    | 1   | BLK   | Signal **GND** → preamp pour (thinner)        |
| RT G     | 11  | BLK   | OT common (heavier; splice may read BRN)      |
| RT G     | 11  | BLK   | Signal **GND** → preamp pour (thinner)        |
| RT 4 Ω   | 17  | BLU   | New splice → BLU (confirm at splice)          |
| RT 8 Ω   | 13  | BRN   | OT 8 Ω coil tap; panel splice may read RED    |
| RT 8 Ω   | 13  | PRP   | **NFB** → preamp **R5 ∥ \*C2** (second wire)  |

---

## Power transformer harness (**PT** → Large Cap Board / heaters)

| Tag | Color (as drawn) | Destination / notes                                                 |
| --- | ---------------- | ------------------------------------------------------------------- |
| 23  | BLK → RED        | PT bottom → large cap board; new splice                             |
| —   | WHT ×2           | Heater — **preamp board** (tag **5×2** at coil)                     |
| —   | BRN ×2           | Heater — **2× EL34 (channel A)** (no coil tag; hand-sch "10×2")     |
| —   | YEL ×2           | Heater — **2× EL34 (channel B)** (no coil tag; hand-sch "1×2")      |
| 16  | BLU              | PT secondary                                                        |
| 14  | BLK              | PT secondary                                                        |
| 21  | ORG → RED        | PT tap; new splice                                                  |
| 4   | RED              | PT tap                                                              |
| 3   | B                | PT tap (right)                                                      |
| 13  | RED              | PT → large cap board (red ink, new splice) — **not** RT 8 Ω speaker |
| 15  | B                | PT tap (left) — **not** LFT 4 Ω speaker                             |
| 17  | YEL              | PT tap — **not** RT 4 Ω speaker                                     |

PT label (see `photos/transformers.png`): 260V/300V 300mA, 50V 100mA, 6.3V 3.5A ×2, 115V ×2.

Speaker tags **1, 11, 13, 15, 17, 19** at the rear panel are **OT** secondaries — see section above, not this table.

---

## Large Cap Board GND pour (hand drawing)

On [`hand_schematic.png`](../photos/hand_schematic.png), the large **GND pour** by the horizontal **Large Cap Board** outline is annotated with disassembly tags:

| Tag    | Color   | Notes                                                                     |
| ------ | ------- | ------------------------------------------------------------------------- |
| **1**  | **BLK** | LFT **G** post signal return (second wire at post)                        |
| **11** | **BLK** | RT **G** post signal return — **not** PT **C1** HV **11 BLK** (tag reuse) |
| **18** | **BLK** | Harness to pour (right edge of board sketch)                              |
| **6**  | **BLK** | **C2 GND** — out to preamp **GND** pad                                    |
| **16** | **BLU** | Drawn to pour — verify net at rebuild (also PT secondary in PT table)     |

**RCA shells** were not tagged at disassembly; rebuild plan: shell bus → **same pour** ([`../docs/back-panel.md`](../docs/back-panel.md)). Preamp stays on **PT GND** + **C2** **6 BLK** only.

---

## Large Cap Board connections

| Tag            | Color      | Notes                                       |
| -------------- | ---------- | ------------------------------------------- |
| 9              | BLU        | Left bundle in                              |
| 7              | BLK        | Left bundle in                              |
| 23, 21, 19, 17 | GRN bundle | From PT/splice area (red-marked on drawing) |
| 18             | BLK        | Right side                                  |
| 11             | BLK        | Right side                                  |
| 15             | RED        | Right side                                  |
| 6              | BLK        | Right side                                  |
| 16             | BLU        | Right side                                  |

Cross-reference numbered stickers on [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) and [`large cap board bottom desoldered.png`](../photos/large%20cap%20board%20bottom%20desoldered.png).

Silkscreen rails (OI-3): **+B**, **+B2**, **−B**, **70V IN**; **+B1** on harness tag **21** only.

---

## Bias trim area (V3 / V4 / TP1)

Red-ink tags **19, 21, 17, 23** at octal socket detail — same four **GRN** **C3** wires from Large Cap Board **TP1** (OI-6 closed). Underside bias-trim pots: **V3, V4, V7, V8**.

---

## Chassis — octal (8-pin) EL34 wiring

Four red-circled tags **23, 21, 17, 19** at octal socket positions — **C3** **GRN** from Large Cap Board **TP1** (OI-6). Factory **Vx-TP** = EL34 **pin 8** ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)).

Other labels in this region: 4 RED, 13 RED (crossed out on drawing), 15 RED, 7 YEL, 9 DK BLU, RED 3, BLK 3.

Photos: [`8 pin 3.png`](../photos/8%20pin%203.png), [`8 pin 4.png`](../photos/8%20pin%204.png).

---

## Preamp board (bottom of drawing)

| Location        | Tag | Color        |                                                                                                   |
| --------------- | --- | ------------ | ------------------------------------------------------------------------------------------------- |
| Octal row       | 9   | BLK / DK BLU |                                                                                                   |
| Octal row       | 6   | BLK          |                                                                                                   |
| Noval / OT path | 19  | PRP          | **NFB** from LFT **8 Ω** post → **R5′ ∥ \*C2**                                                    |
| Noval / OT path | 13  | PRP          | **NFB** from RT **8 Ω** post → **R5 ∥ \*C2**                                                      |
| Internal        | 15  | RED          |                                                                                                   |
| Internal        | 7   | YEL          |                                                                                                   |
| Left edge       | 5   | WHT ×2       |                                                                                                   |
| Volume pot      | 23  | GRN + RED    |                                                                                                   |
| Power LED       | —   | GRN + DK BLU | **GRN** → noval socket pin · **BLU** → front panel ([`LED wires.png`](../photos/LED%20wires.png)) |

Four large circles = octal (8-pin); four small × circles = noval (9-pin). Small **×** marks on the drawing = LED indicators.

**Open question:** Tag 23 appears at PT (BLK/RED), large cap board (GRN bundle), and volume pot (GRN/RED). Confirm with continuity whether these are one continuous wire or separate cuts sharing a number.

---

## Open items

See [`../archive/open-issues.md`](../archive/open-issues.md) for schematic cross-check items (grid stoppers, power resistor, 180 µF placement).

Wire-tag / harness items:

- [ ] Resolve tag 23 — single net or multiple wires?
- [ ] Meaning of **13 RED** crossed out on drawing
- [ ] **RED 3 / BLK 3** labels in octal area
- [ ] RCA selector → preamp input wiring (not yet tagged)
- [ ] Map PT colored taps to schematic HV/heater/primary nets

---

## Related docs

- [`schematic-comparison.md`](../archive/schematic-comparison.md) — factory PDF vs photos
- [`../archive/open-issues.md`](../archive/open-issues.md) — OI-1 … OI-5 tracker
- [`wire-tags.md`](../archive/wire-tags.md) — tag lookup table
- [`gemini-restoration-notes.md`](../archive/gemini-restoration-notes.md) — parts and recap planning
- [`../photos/`](../photos/) — board and chassis photos
