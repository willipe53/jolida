# Wire Tag Reference

Tags are numbered labels applied when wires were cut during disassembly. Same number = same wire (both ends).

**Color notation:** `PRP → BRN` means the wire was purple, replaced with brown. This is **not** a twisted pair.

**PT vs OT:** **Power Transformer (PT)** feeds the Power Board (HV, heaters, aux). **Output Transformer (OT)** secondaries go to the rear-panel speaker posts. The hand schematic groups them near the center block — several tags were mislabeled **PT** on early notes when they are **OT** speaker leads.

Source: [`photos/hand_schematic.png`](../photos/hand_schematic.png), board photos, bench notes.

Status: **In progress** — verify with continuity before reassembly.

## PT coil — bench confirmed (2026-07-06)

Tags below are on **PT leads** at the coil (see [`PT.md`](PT.md)). Hand-schematic rows for the same tag numbers may refer to **different cuts** — buzz stub → coil lead.

| Tag | PT lead    | Winding                                                                                         |
| --- | ---------- | ----------------------------------------------------------------------------------------------- |
| 11  | BLK        | HV 0 V                                                                                          |
| 21  | RED        | **PT-L1** → Power Board **AC IN**; **PT-R5a/b** → **AC inlet** (duplicate tag — separate stubs) |
| 17  | BLU        | 50 V aux                                                                                        |
| 19  | BLU        | 50 V aux                                                                                        |
| 9   | BLK        | **PT-L5** → Preamp board **GND** ([`preamp board top.png`](../photos/preamp%20board%20top.png)) |
| 5   | WHT (pair) | 6.3 V heater                                                                                    |
| 23  | ORG→BLK    | Merged primary returns (**PT-R6a/b**) — ORG at coil                                             |

Right-side **BRN/BRN** and **YEL/YEL** heater pairs: **no** tags at coil.

---

## Tag index

| Tag | Current color | Replaced from | From                                   | To                         | Notes                                                                                                                            |
| --- | ------------- | ------------- | -------------------------------------- | -------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| 1   | BLK           | —             | **OT**                                 | LFT G (common)             | Speaker common, left                                                                                                             |
| 3   | B             | —             | **PT**                                 | —                          | PT tap, right side                                                                                                               |
| 4   | RED           | —             | **PT**                                 | Octal area                 | PT tap; also labeled in chassis section                                                                                          |
| 5   | WHT           | —             | —                                      | Preamp board (×2)          | Left edge of preamp board                                                                                                        |
| 6   | BLK           | —             | Power board / preamp                   | Preamp octal row           |                                                                                                                                  |
| 7   | BLK           | —             | Power board                            | Preamp (YEL nearby)        | Left bundle into power board                                                                                                     |
| 7   | YEL           | —             | —                                      | Preamp internal            | Same tag number — confirm if same wire                                                                                           |
| 9   | BLK           | —             | **PT** (label **0**)                   | Preamp board **GND**       | Bottom-left ground pour between white ceramics — [`preamp board top.png`](../photos/preamp%20board%20top.png); **not** trim pots |
| 9   | BLU           | —             | Power board                            | —                          | **Different wire** — duplicate tag number; verify at bench                                                                       |
| 9   | DK BLU        | —             | Octal area / preamp                    | —                          | **Different wire** — duplicate tag number                                                                                        |
| 10  | BRN           | —             | **PT**                                 | —                          | ×2 heater pair (10×2)                                                                                                            |
| 11  | BRN           | BLK           | **OT**                                 | RT G (common)              | New splice: was BLK → now BRN; stub also at power board — verify                                                                 |
| 13  | RED           | BRN (was PRP) | **PT** / power board                   | Power board / preamp       | PT-side harness; **not** RT 8 Ω speaker — new splice; 13 RED crossed out in one location on drawing                              |
| 13  | BRN           | PRP           | **OT**                                 | RT 8 Ω / preamp            | Speaker path; original purple wire replaced with brown                                                                           |
| 14  | BLK           | —             | **PT**                                 | —                          | PT secondary                                                                                                                     |
| 15  | BLK           | BLU           | **OT**                                 | LFT 4 Ω                    | New splice: was BLU → now BLK                                                                                                    |
| 15  | RED           | —             | Power board / preamp                   | —                          | Separate appearance — not LFT 4 Ω speaker                                                                                        |
| 16  | BLU           | —             | **PT** / power board                   | —                          | PT secondary                                                                                                                     |
| 17  | BLU           | YEL           | **OT**                                 | RT 4 Ω                     | New splice: was YEL → now BLU                                                                                                    |
| 18  | BLK           | —             | Power board                            | —                          | Right side                                                                                                                       |
| 19  | BLU           | BRN (was PRP) | **OT**                                 | LFT 8 Ω                    | New splice; was purple → brown → blue; also drawn near power board GRN bundle / bias                                             |
| 21  | RED           | ORG           | **PT** / power board GRN bundle / bias | **PT**                     | New splice: was ORG → now RED                                                                                                    |
| 23  | RED           | BLK           | **PT** / power board / volume          | PT bottom, GRN bundle, VOL | **Verify:** multiple appearances — one wire or separate?                                                                         |
| 23  | GRN           | —             | Volume pot                             | Preamp                     | GRN 23 VOL                                                                                                                       |
| 23  | RED           | —             | Volume pot                             | Preamp                     | RED 23 VOL                                                                                                                       |

---

## By destination

### Rear panel — speaker terminals (from **OT** secondaries)

| Terminal | Tag | Color        | Replacement history |
| -------- | --- | ------------ | ------------------- |
| LFT 8 Ω  | 19  | BLU (splice) | PRP → BRN → BLU     |
| LFT 4 Ω  | 15  | BLK (splice) | BLU → BLK           |
| LFT G    | 1   | BLK          | —                   |
| RT G     | 11  | BRN (splice) | BLK → BRN           |
| RT 4 Ω   | 17  | BLU (splice) | YEL → BLU           |
| RT 8 Ω   | 13  | RED (splice) | PRP → BRN → RED     |

Channel is determined by stub tags (**LFT** **1/15/19**, **RT** **11/17/13**) — see [`OT.md`](OT.md).

### Power transformer (**PT** → Power Board / heaters)

| Tag  | Color   | Function (TBD)              |
| ---- | ------- | --------------------------- |
| 3    | B       | PT tap (right)              |
| 4    | RED     | PT tap → octal area         |
| 14   | BLK     | Secondary                   |
| 16   | BLU     | Secondary                   |
| 21   | ORG/RED | PT tap                      |
| 23   | BLK/RED | → power board / volume area |
| 1×2  | YEL     | Heater                      |
| 5×2  | WHT     | Heater                      |
| 10×2 | BRN     | Heater                      |

**Also drawn near PT** (likely duplicate tag numbers — verify at bench):

| Tag | Color | Drawing note     | Likely actual                    |
| --- | ----- | ---------------- | -------------------------------- |
| 13  | RED   | PT → power board | **PT** harness, not OT RT 8 Ω    |
| 15  | B     | PT tap (left)    | **PT** tap — not LFT 4 Ω speaker |
| 17  | YEL   | PT tap           | **PT** tap — not RT 4 Ω speaker  |

### Output transformer (**OT** secondaries → rear panel)

| Tag | Color   | Terminal |
| --- | ------- | -------- |
| 1   | BLK     | LFT G    |
| 11  | BLK/BRN | RT G     |
| 15  | BLU/BLK | LFT 4 Ω  |
| 17  | BLU/YEL | RT 4 Ω   |
| 19  | BRN/BLU | LFT 8 Ω  |
| 13  | BRN/RED | RT 8 Ω   |

### Power board

| Tag | Color                           | Notes                       |
| --- | ------------------------------- | --------------------------- |
| 5   | — (sticker on desoldered board) |                             |
| 6   | BLK                             |                             |
| 7   | BLK                             |                             |
| 9   | BLU                             |                             |
| 11  | BLK                             |                             |
| 13  | — (sticker)                     |                             |
| 15  | RED / sticker                   |                             |
| 16  | BLU                             |                             |
| 17  | **GRN** **C3**                  | **−B1** / bias · TP1 (OI-6) |
| 18  | BLK                             |                             |
| 19  | **GRN** **C3**                  | **+B2** · TP1 (OI-6)        |
| 21  | **GRN** **C3**                  | **+B1** · TP1 (OI-6)        |
| 23  | **GRN** **C3**                  | **+B** · TP1 (OI-6)         |

### Bias trim (V3 / V4 / V7 / V8)

Red-ink tags at octal/bias detail: **19, 21, 17, 23** — **C3** **GRN** from Power Board **TP1** (OI-6)

### Preamp board

| Tag | Color         | Notes                                                          |
| --- | ------------- | -------------------------------------------------------------- |
| 5   | WHT ×2        | Left edge                                                      |
| 6   | BLK           | Octal row                                                      |
| 7   | YEL           | Internal                                                       |
| 9   | BLK           | **PT label 0** → GND pour bottom-left (between white ceramics) |
| 13  | BRN (was PRP) | Near 8 Ω label — verify not same as PT tag 9                   |
| 15  | RED           | Internal                                                       |
| 19  | BRN (was PRP) | Near 8 Ω label                                                 |
| 23  | GRN + RED     | Volume pot                                                     |

### Octal (8-pin) sockets — chassis

| Ref / label | Socket pin | Notes                                                                     |
| ----------- | ---------- | ------------------------------------------------------------------------- |
| **Vx-TP**   | **8**      | Bias test per factory PDF (**V3/V4/V7/V8-TP**); ~40 mV target             |
| Grid (C4)   | **4**      | **1 kΩ** stopper (**OI-1**)                                               |
| 12          | —          | RED · [`another 8 pin.png`](../photos/another%208%20pin.png)              |
| 13          | —          | GRN · noval area [`2 left 9 pins.png`](../photos/2%20left%209%20pins.png) |

---

## New splices summary (red ink)

| Tag | Was           | Now | Path                                              |
| --- | ------------- | --- | ------------------------------------------------- |
| 23  | BLK           | RED | **PT** → power board                              |
| 21  | ORG           | RED | **PT** tap                                        |
| 19  | BRN (was PRP) | BLU | **OT** → LFT 8 Ω                                  |
| 17  | YEL           | BLU | **OT** → RT 4 Ω                                   |
| 11  | BLK           | BRN | **OT** → RT G                                     |
| 15  | BLU           | BLK | **OT** → LFT 4 Ω                                  |
| 13  | BRN (was PRP) | RED | **OT** → RT 8 Ω (separate from tag 13 **PT** RED) |

---

## Wire color cheat sheet (graph paper notes)

From `photos/preamp board bottom.png`:

Red, Yellow, Blue, Brown, Purple, Dk Blu, Green, Black, White, Orange

---

## Tags not yet placed

| Item                                     | Status                          |
| ---------------------------------------- | ------------------------------- |
| RCA inputs → selector → preamp (LIN/RIN) | Not tagged on hand schematic    |
| Input selector switch                    | Not tagged                      |
| LED (GRN/BLU pair)                       | Labeled on photo, no number tag |
| AC inlet (hot/neutral/earth)             | Panel labels 1, 2 only          |

---

## Related

- [`hand-schematic-notes.md`](hand-schematic-notes.md) — full diagram interpretation
- [`PT.md`](PT.md) — power transformer lead colors and worksheet
- [`OT.md`](OT.md) — output transformer lead colors and worksheet
- [`TRANSFORMERS.md`](TRANSFORMERS.md) — index
- [`../photos/hand_schematic.png`](../photos/hand_schematic.png)
