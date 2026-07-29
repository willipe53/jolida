# Block diagram — wiring overview

> **ARCHIVED 2026-07-12** — superseded by the per-component docs in [`../docs/`](../docs/). The C3 edge shown here (rails to the 8-pin chassis) is **known-wrong**; C3 is 2× +B feeds to the OT center taps + 4× pin-8 bias sense wires ([`8-pin-chassis.md`](../docs/8-pin-chassis.md)).

ASCII map derived from [`INTERCONNECTS.md`](INTERCONNECTS.md) — one labeled line per non-empty matrix cell. Pinouts and checklists: [`CONNECTORS.md`](CONNECTORS.md); build order: [`README.md`](../README.md).

## Legend

| Symbol      | Meaning                                                                |
| ----------- | ---------------------------------------------------------------------- |
| `──`        | Hardwire (18 AWG or heavy — see label)                                 |
| Molex boxes | Micro-Fit 3.0 (**C4** = Molex 1 · **C5** = Molex 2 · **C6** = Molex 3) |

Channel tags: **LFT** OT stubs **1 / 15 / 19** · **RT** stubs **11 / 17 / 13** ([`OT.md`](../docs/OT.md)).

---

## Blocks and links

```text
                    ┌──────────────┐
                    │ Front Panel  │
                    └──────┬───────┘
                           │ Volume pot ×3 → plug · LED DK BLU → holder
                           ▼
                    ┌──────────────┐
                    │   Molex 2    │
                    └──────┬───────┘
                           │ Volume pot ×3 → receptacle · LED GRN (noval pin)
                           ▼
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│  Back Panel  │───►│   Molex 3    │───►│ Preamp Board │◄── C2 +B1 · +B2 · GND ─── Large Cap Board
└───┬─────┬────┘    └──────────────┘    └───┬──────────┘
    │     │         RCA centers →          │ RCA input net → receptacle
    │     │         plug pins 1–4          │
    │     │                                │ Grids ×4 → receptacle
    │     │                                ▼
    │     │                         ┌──────────────┐
    │     │                         │   Molex 1    │
    │     │                         └──────┬───────┘
    │     │                                │ Grids ×4 → plug
    │     │                                ▼
    │     │ Spkr G·4Ω·8Ω (heavy)    ┌──────────────┐
    ▼     │                         │  8-Pin     │◄── C3 +B · +B1 · +B2 · −B1 · GND
┌─────────┐│ Spkr G·4Ω·8Ω (heavy)   │  Chassis   │
│ Left OT ││                         └─────┬──────┘
└────┬────┘│                               │ Primary ×5 (RT channel)
     │ Primary ×5 (RED YEL ORG WHT BRN · plates · UL · +B CT)
     └──────────────────────────────► 8-Pin Chassis ◄────────────────────────── Primary ×5 (RT)
                                      ▲                    ▲
                                   Left OT              Right OT

┌─────────┐
│   PT    │──── C1 HV AC RED/BLK · 50 V aux BLU/BLU · GND ────► Large Cap Board
└────┬────┘
     │ 115 V AC H/N · IEC earth → chassis star ◄── Back Panel
     ├── Heater BRN/BRN · YEL/YEL (direct) ────────────────► 8-Pin Chassis
     └── Heater WHT/WHT · tag-9 GND BLK (direct) ──────────► Preamp Board
```

---

## Link index

Same edges as [`INTERCONNECTS.md`](INTERCONNECTS.md) (upper triangle).

| From            | To              | Label                                                                    |
| --------------- | --------------- | ------------------------------------------------------------------------ |
| Back Panel      | Left OT         | Spkr **G · 4 Ω · 8 Ω** (heavy)                                           |
| Back Panel      | PT              | **115 V AC** H/N · **IEC earth** → chassis star                          |
| Back Panel      | Right OT        | Spkr **G · 4 Ω · 8 Ω** (heavy)                                           |
| Back Panel      | Molex 3         | RCA centers → plug pins 1–4                                              |
| Front Panel     | Molex 2         | Volume pot ×3 → plug · LED **DK BLU** → holder                           |
| Left OT         | 8-Pin Chassis   | Primary **×5** (**RED YEL ORG WHT BRN**) → plates p3 · UL p4 · **+B** CT |
| PT              | Large Cap Board | **C1** — HV AC **RED/BLK** · 50 V aux **BLU/BLU** · GND                  |
| PT              | 8-Pin Chassis   | Heater **BRN/BRN** · **YEL/YEL** (direct)                                |
| PT              | Preamp Board    | Heater **WHT/WHT** · **tag-9 GND** **BLK** (direct)                      |
| Right OT        | 8-Pin Chassis   | Primary **×5** (same roles, RT channel)                                  |
| Large Cap Board | 8-Pin Chassis   | **C3** — **+B · +B1 · +B2 · −B1 · GND** (GRN @ TP1)                      |
| Large Cap Board | Preamp Board    | **C2** — **+B1 · +B2 · GND**                                             |
| 8-Pin Chassis   | Molex 1         | Grids ×4 → plug                                                          |
| Preamp Board    | Molex 1         | Grids ×4 → receptacle                                                    |
| Preamp Board    | Molex 2         | Volume pot ×3 → receptacle · LED **GRN** (noval pin)                     |
| Preamp Board    | Molex 3         | RCA input net → receptacle                                               |

**Not shown** (same-block / PTP only): OT **+B** center tap ↔ **C3 +B** at 8-Pin PTP · bias trim **V3/V4/V7/V8** · EL34 cathodes / 1 Ω sense · grid stoppers.

---

## See also

- [`INTERCONNECTS.md`](INTERCONNECTS.md) — full matrix (source for this diagram)
- [`CONNECTORS.md`](CONNECTORS.md) — C1–C6 pinouts, worksheets
- [`README.md`](../README.md) — phased rebuild plan
- [`PT.md`](../docs/PT.md) · [`OT.md`](../docs/OT.md) — transformer coil ID
- [`large-cap-board.md`](../docs/large-cap-board.md) — rail names and TP1 / C3 map
