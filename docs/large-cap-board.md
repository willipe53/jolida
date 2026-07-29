# Large Cap Board

**Unit:** Jolida SJ202A / JD202  
**Photos:** [`large cap board top desoldered.png`](../photos/large%20cap%20board%20top%20desoldered.png) · [`large cap board bottom desoldered.png`](../photos/large%20cap%20board%20bottom%20desoldered.png) · [`large cap board side.png`](../photos/large%20cap%20board%20side.png)

Vertical PCB for **HT/bias rectification, the large filter caps, and rail distribution** (**C1** in, **C2** to preamp, **C3** / **TP1** to the output end). Not mains switching, not the PT, and not heaters — older notes and photos may still say “power board.”

Converts PT AC → DC rails. All harness wires here are **18 AWG hardwire** except the four **GRN** TP1 sense lines (**22 AWG OK**). Identity = **color + tag**, never tag number alone (several numbers are reused).

Historical observation notes: [`../archive/large-cap-board-as-built-notes.md`](../archive/large-cap-board-as-built-notes.md).

---

## Stuffing BOM

All parts below **in place** on the board (2026-07-20).

| Ref          | Value              | Status   | Notes                                       |
| ------------ | ------------------ | -------- | ------------------------------------------- |
| **VD3–VD6**  | **1N5408** ×4      | in place | HT bridge around **AC IN**                  |
| **VD7**      | **1N4007**         | in place | Bias rectifier                              |
| **C8, C9**   | **470 µF / 450 V** | in place | Top HT pair (series; midpoint → GND)        |
| **C5, C6**   | **180 µF / 450 V** | in place | +B2 / +B1 filters                           |
| **C7**       | **470 µF / 50 V**  | in place | Aux rail — **not** the top pair             |
| **C10, C11** | **220 µF / 160 V** | in place | Bias filters                                |
| **R23, R24** | **68 kΩ / 3 W**    | in place | Bleeders between C8/C9 (replaced old ~62 k) |
| **R21**      | **100 kΩ / 3 W**   | in place | Dropper +B1 → +B2                           |
| **R22**      | **3.3 kΩ / 5 W**   | in place | Do **not** disturb                          |
| **R25**      | **2.2 kΩ / 3 W**   | in place | Bias dropper −B → −B1                       |

**Bridge order** (left→right at AC IN): **VD6 · VD4 · AC IN · VD5 · VD3**.

### Physical order (bottom → top of board)

Bias end at bottom → HT end at top: **VD7 → R25 → C11 → C10 → −B → C5 → +B2 → C6 → R21 → TP1 → VD3–VD6 / AC IN / 70V IN → C8 → R23/R24 → C9 (+B)**.

**+B1** has no silk on this face — tap after **R22**, leaves as **15 RED**.

---

## Rails (what leaves the board)

| Silk / net | Nominal | Leaves as                                                                                                                 |
| ---------- | ------- | ------------------------------------------------------------------------------------------------------------------------- |
| **+B**     | ~+425 V | **2× RED** (tags **13**, **23**) → OT center taps (**C3**)                                                                |
| **+B1**    | ~+370 V | **15 RED** → preamp (**C2**)                                                                                              |
| **+B2**    | ~+220 V | **7 YEL** → preamp (**C2**)                                                                                               |
| **−B1**    | ~−54 V  | **9 BLU** → preamp **−B** (**C2**)                                                                                        |
| **GND**    | 0 V     | **6 BLK** → preamp (**C2**) + heavy BLK → chassis star · **panel harness returns** land on board **GND pour** (see below) |

**Not on this board:** heaters (direct PT → tubes). **PT tag-9 GND** runs **direct PT → preamp pour** (not through this board).

### Panel + harness GND pour

Large copper **GND pour** on this PCB is the **consolidation point** for rear-panel audio returns and on-board filter returns. Owner hand map ([`hand_schematic.png`](../photos/hand_schematic.png)) tagged at this pour:

| Disassembly tag | Color   | Likely function (verify continuity)                                                             |
| --------------- | ------- | ----------------------------------------------------------------------------------------------- |
| **1**           | **BLK** | LFT speaker **G** signal return (second **BLK** at post)                                        |
| **11**          | **BLK** | RT speaker **G** signal return — **not** PT **C1** **11 BLK** (same tag number, different wire) |
| **18**          | **BLK** | Harness return to pour (right edge on drawing)                                                  |
| **6**           | **BLK** | **C2 GND** — pour here → preamp **GND** pad                                                     |
| **16**          | **BLU** | Drawn to pour — **confirm** (tag **16** also used on PT secondary in other tables)              |

**Rebuild additions:** RCA **shell** bus → **same pour** (not documented at disassembly). **Do not** duplicate shields at the preamp — one reference via this pour + **C2** **6 BLK**.

Heavy **BLK** from pour → chassis **star** ([`chassis.md`](chassis.md)).

---

## Wire map

### C1 — PT → this board (18 AWG, twisted pairs)

**AC IN** here = **PT HV** (~300 V AC secondary) — **not** IEC mains. Mains → fuse → switch → PT primary only: [`back-panel.md`](back-panel.md#mains-ac--two-nets-do-not-merge).

| Wire      | Tag    | Color   | Pad / net  | Label (applied)   |
| --------- | ------ | ------- | ---------- | ----------------- |
| HV        | **21** | **RED** | **AC IN**  | **PT HV**         |
| HV return | **11** | **BLK** | **AC IN**  | **PT HV** (pair)  |
| 50 V aux  | **17** | **BLU** | **70V IN** | **70V IN**        |
| 50 V aux  | **19** | **BLU** | **70V IN** | **70V IN** (pair) |

Keep HV pair and aux pair twisted. PT harness: [`PT.md`](PT.md). Mains **WALL AC** (**WHT/BLK**) and EL34 **V3/V4 HEAT** do **not** land here.

### C2 — this board → preamp (18 AWG)

| Wire | Tag    | Color   | Net     | Preamp silk |
| ---- | ------ | ------- | ------- | ----------- |
| 1    | **15** | **RED** | **+B1** | **+B1**     |
| 2    | **7**  | **YEL** | **+B2** | **+B2**     |
| 3    | **9**  | **BLU** | **−B1** | **−B**      |
| 4    | **6**  | **BLK** | **GND** | **GND**     |

### C3 — this board ↔ 8-pin / OTs

| Wire     | Tag             | Color         | AWG   | Label (applied) | Function                             |
| -------- | --------------- | ------------- | ----- | --------------- | ------------------------------------ |
| +B feed  | **13**          | **RED**       | 18    | **+B LEFT**     | +B → LFT OT **RED** CT               |
| +B feed  | **23**          | **RED**       | 18    | **+B RIGHT**    | +B → RT OT **RED** CT                |
| Sense ×4 | **23/17/21/19** | **GRN**       | 22 OK | —               | EL34 **pin 8** → **TP1** (named pad) |
| GND      | —               | Heavy **BLK** | 18    | —               | Board pour → chassis star            |

### TP1

Five isolated pads, silk **V4 · V3 · GND · V3 · V4** (bottom→top). Wire each EL34 pin 8 to its named pad; center = GND. Bias read ≈ **40 mV** across the 1 Ω cathode sense on the preamp board. Detail: [`8-pin-chassis.md`](8-pin-chassis.md).

---

## Circuit (text)

```text
PT HV ──► AC IN ──► [VD3–VD6] ──► +B
                                  │
              C8(470) ──┬── C9(470)   (series, mid → GND)
                        │
                   R23 ∥ R24 → GND
                        │
                       R22
                        │
                       +B1 ── C6(180) ── GND
                        │
                       R21
                        │
                       +B2 ── C5(180) ── GND

PT 50V ──► VD7 ──► −B ── C11 ── GND
                    │
                   R25
                    │
                   −B1 ── C10 ── GND
```

---

## Related

- [`PT.md`](PT.md) · [`preamp-board.md`](preamp-board.md) · [`8-pin-chassis.md`](8-pin-chassis.md) · [`chassis.md`](chassis.md)
- [`../archive/schematic-comparison.md`](../archive/schematic-comparison.md) — PDF vs as-built deltas
- [`../archive/large-cap-board-as-built-notes.md`](../archive/large-cap-board-as-built-notes.md) — full observation history
