# Interconnect matrix

> **ARCHIVED 2026-07-12** — superseded by the per-component docs in [`../docs/`](../docs/); each doc lists its own end of every harness. Some cells reflect the pre-redefinition C3 (rails) and are **known-wrong**.

Upper triangle only — cell **(row, column)** lists signals between those two blocks. Diagonal and lower triangle are blank.

If two blocks meet **only** through a Molex, fill the **block ↔ Molex** cells — not the block ↔ block cell (e.g. Back Panel → **Molex 3** → Preamp Board, not Back Panel → Preamp Board direct).

**Molex IDs** (this rebuild — three Micro-Fit harnesses):

| ID          | Harness | Between (via Molex)          |
| ----------- | ------- | ---------------------------- |
| **Molex 1** | **C4**  | Preamp Board ↔ 8-Pin Chassis |
| **Molex 2** | **C5**  | Front Panel ↔ Preamp Board   |
| **Molex 3** | **C6**  | Back Panel ↔ Preamp Board    |

Hardwire harness names **C1–C3** appear in cells where they apply. Detail: [`CONNECTORS.md`](CONNECTORS.md).

---

## Matrix

|                     | Back Panel | Front Panel | Left OT                        | PT                                              | Right OT                       | Large Cap Board                                         | 8-Pin Chassis                                                            | Preamp Board                                        | Molex 1               | Molex 2                                              | Molex 3                     |
| ------------------- | ---------- | ----------- | ------------------------------ | ----------------------------------------------- | ------------------------------ | ------------------------------------------------------- | ------------------------------------------------------------------------ | --------------------------------------------------- | --------------------- | ---------------------------------------------------- | --------------------------- |
| **Back Panel**      |            |             | Spkr **G · 4 Ω · 8 Ω** (heavy) | **115 V AC** H/N · **IEC earth** → chassis star | Spkr **G · 4 Ω · 8 Ω** (heavy) |                                                         |                                                                          |                                                     |                       |                                                      | RCA centers → plug pins 1–4 |
| **Front Panel**     |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     |                       | Volume pot ×3 → plug · LED **DK BLU** → holder       |                             |
| **Left OT**         |            |             |                                |                                                 |                                |                                                         | Primary **×5** (**RED YEL ORG WHT BRN**) → plates p3 · UL p4 · **+B** CT |                                                     |                       |                                                      |                             |
| **PT**              |            |             |                                |                                                 |                                | **C1** — HV AC **RED/BLK** · 50 V aux **BLU/BLU** · GND | Heater **BRN/BRN** · **YEL/YEL** (direct)                                | Heater **WHT/WHT** · **tag-9 GND** **BLK** (direct) |                       |                                                      |                             |
| **Right OT**        |            |             |                                |                                                 |                                |                                                         | Primary **×5** (same roles, RT channel)                                  |                                                     |                       |                                                      |                             |
| **Large Cap Board** |            |             |                                |                                                 |                                |                                                         | **C3** — **+B · +B1 · +B2 · −B1 · GND** (GRN @ TP1)                      | **C2** — **+B1 · +B2 · GND**                        |                       |                                                      |                             |
| **8-Pin Chassis**   |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     | Grids ×4 → plug       |                                                      |                             |
| **Preamp Board**    |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     | Grids ×4 → receptacle | Volume pot ×3 → receptacle · LED **GRN** (noval pin) | RCA input net → receptacle  |
| **Molex 1**         |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     |                       |                                                      |                             |
| **Molex 2**         |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     |                       |                                                      |                             |
| **Molex 3**         |            |             |                                |                                                 |                                |                                                         |                                                                          |                                                     |                       |                                                      |                             |

**Not shown** (same-block / PTP only): OT **+B** center tap ↔ **C3 +B** at 8-Pin PTP · bias trim **V3/V4/V7/V8** · EL34 cathodes / 1 Ω sense · grid stoppers.
