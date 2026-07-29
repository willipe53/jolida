# Power Transformer (PT)

**Unit:** Jolida SJ202A / JD202 · factory type **LM-9908P-A** class  
**Photos:** [`pt.png`](../photos/pt.png) · [`transformers.png`](../photos/transformers.png)

All PT leads are **18 AWG**, hardwired (no Molex). Keep twisted pairs twisted end-to-end. Identity = **coil color + continuity**, not tag number alone (tag **21** is reused — see below).

**Harness extensions (2026-07-20):** new **18 AWG** pigtails soldered at the cut stubs; heat-shrink every joint. **Insulation dress** below is what you run in the chassis — coil colors at the PT body are unchanged for DCR ID.

**P-touch labels applied (2026-07-20):** **WALL AC**, **PT HV**, **70V IN**, **PT GND**, **PREAMP HEAT**, **V3/V4 HEAT** (**BLK/WHT**, coil **BRN/BRN**), **V7/V8 HEAT** (**YEL/YEL**). Detail: [`labels.md`](labels.md).

---

## Wire map

One **5.8 mm** sleeve over both legs of a twisted pair is OK if it fits ([`labels.md`](labels.md)).

| At PT coil            | Winding             | Tag(s)                  | Harness dress (extension) | P-touch label   | Goes to                                                                  |
| --------------------- | ------------------- | ----------------------- | ------------------------- | --------------- | ------------------------------------------------------------------------ |
| **RED1 + RED2**       | Primary hot (115 V) | **21**                  | **WHT**                   | **WALL AC**     | AC inlet **HOT** (fuse in this leg) — [`back-panel.md`](back-panel.md)   |
| **ORG1 + ORG2**       | Primary neutral     | **23**                  | **BLK**                   | **WALL AC**     | AC inlet **NEUTRAL** (same label on **WHT/BLK** run)                     |
| **RED + BLK**         | HV ~300 V AC        | **21** RED / **11** BLK | **RED + BLK** (same)      | **PT HV**       | Large Cap Board **AC IN** → bridge VD3–VD6 (**C1**)                      |
| **BLU + BLU**         | 50 V aux            | **17** / **19**         | **BLU + BLU** (same)      | **70V IN**      | Large Cap Board **70V IN** (**C1**) → bias **−B** on large cap board     |
| **BLK** (label **0**) | Ground reference    | **9**                   | **BLK** (same)            | **PT GND**      | Preamp board **GND** pour (bottom-left) — **not** Large Cap Board        |
| **WHT + WHT**         | Heater 6.3 V        | **5**                   | **WHT + WHT** (same)      | **PREAMP HEAT** | Preamp board heaters (bottom-left edge)                                  |
| **BRN + BRN**         | Heater 6.3 V        | —                       | **BLK + WHT** twisted     | **V3/V4 HEAT**  | **V3**, **V4** — pins **2 / 7** ([`8-pin-chassis.md`](8-pin-chassis.md)) |
| **YEL + YEL**         | Heater 6.3 V        | —                       | **YEL + YEL** (same)      | **V7/V8 HEAT**  | **V7**, **V8** — pins **2 / 7**                                          |

**C1** = only the HV pair + 50 V aux pair → Large Cap Board. Heaters, tag-9 GND, and mains primary are **not** C1.

**Do not** confuse harness **BLK/WHT** (**V3/V4 HEAT**, PT coil **BRN/BRN**) with OT primary **WHT** (UL screen on a different wire).

### Primary strap (115 V)

Mains is switched on the **front panel** (after the rear-panel **fuse**), then hardwired to the PT — not to the Large Cap Board **AC IN** ([`back-panel.md`](back-panel.md#mains-ac--two-nets-do-not-merge)).

```text
IEC HOT  ──fuse──► switch ──► WHT  ──► splice ──► RED1 + RED2  (at PT)   label: WALL AC
IEC NEUTRAL ────► switch ──► BLK  ──► splice ──► ORG1 + ORG2  (at PT)   label: WALL AC
```

Do **not** tie RED to ORG across halves. Do **not** series the two 115 V windings.

### Tag 21 collision

Same tag number, two different nets:

| Tag **21** stub | Coil lead     | Destination           |
| --------------- | ------------- | --------------------- |
| HV secondary    | **RED** (HV)  | Large Cap Board AC IN |
| Primary harness | **RED1/RED2** | AC inlet hot          |

### Heater rules

- Three **separate** windings (3 A each). **Do not parallel** the two EL34 windings (coil **BRN/BRN** vs **YEL/YEL**) unless you first meter **0 V AC** between the hot legs — wrong phase shorts the winding.
- EL34 heater pairs have **no coil tags** — use **coil color at the PT** + your **V3/V4** / **V7/V8** labels on the harness.

---

## Coil label (as read)

```text
0  300V  240V     300 mA     ← use 300 V + 0; 240 V tap capped (unused)
   50V   0        100 mA
   6.3V  0        3 A        ← WHT/WHT (left)
   6.3V  6.3V     3 A / 3 A  ← **V3/V4 HEAT** BLK/WHT (coil BRN) · **V7/V8 HEAT** YEL/YEL
   115V
   115V                      ← parallel for 115 V mains
```

---

## DCR (coil leads only — for ID)

| Pair            | DCR   | Winding                              |
| --------------- | ----- | ------------------------------------ |
| RED ↔ BLK (HV)  | 25 Ω  | HV 300 V ↔ 0                         |
| BLU ↔ BLU       | 15 Ω  | 50 V aux                             |
| BLU ↔ tag-9 BLK | OL    | GND is separate                      |
| WHT ↔ WHT       | 2.5 Ω | Preamp heater                        |
| BRN ↔ BRN       | 2.2 Ω | **V3/V4 HEAT** (harness **BLK/WHT**) |
| YEL ↔ YEL       | 2.2 Ω | **V7/V8 HEAT**                       |
| RED1 ↔ ORG1     | ~5 Ω  | Primary half A                       |
| RED2 ↔ ORG2     | ~5 Ω  | Primary half B                       |
| RED1 ↔ ORG2     | OL    | Halves isolated                      |

---

## Related

- [`large-cap-board.md`](large-cap-board.md) — **C1** landings; what HV / 50 V become after the board
- [`preamp-board.md`](preamp-board.md) — **PREAMP HEAT** (**WHT/WHT**) + **PT GND** (tag **9**)
- [`8-pin-chassis.md`](8-pin-chassis.md) — **V3/V4 HEAT** / **V7/V8 HEAT** pairs
- [`labels.md`](labels.md) — P-touch queue
- [`back-panel.md`](back-panel.md) — AC inlet / primary
- [`OT.md`](OT.md) — output transformers (separate units)
- [`../archive/wire-tags.md`](../archive/wire-tags.md) — full tag index
- [`../archive/TRANSFORMERS.md`](../archive/TRANSFORMERS.md) — older long-form notes
