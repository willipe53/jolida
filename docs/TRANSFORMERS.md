# Transformers (PT and OT)

Index for the three transformers in this chassis. Detail lives in dedicated docs:

| Doc              | Unit                                                                       |
| ---------------- | -------------------------------------------------------------------------- |
| [`PT.md`](PT.md) | **Power Transformer** — center; mains, HV, 50 V aux, heaters               |
| [`OT.md`](OT.md) | **Output Transformers** — two identical units; EL34 plates + speaker posts |

---

## Overview

| Unit                                 | Role                              | Location          | Photos                                                                                      |
| ------------------------------------ | --------------------------------- | ----------------- | ------------------------------------------------------------------------------------------- |
| **PT** (Power Transformer)           | Mains + secondaries → Power Board | Center            | [`pt.png`](../photos/pt.png), [`transformers.png`](../photos/transformers.png) (large unit) |
| **OT** (Output Transformer) — unit 1 | EL34 PP, channel **TBD** (L or R) | Either side of PT | [`ot-1.png`](../photos/ot-1.png), [`ot-2.png`](../photos/ot-2.png)                          |
| **OT** (Output Transformer) — unit 2 | EL34 PP, other channel            | Either side of PT | [`ot-3.png`](../photos/ot-3.png), [`ot-4.png`](../photos/ot-4.png)                          |

Factory types (secondary reference only): PT **LM-9908P-A** class; OT **LM-9914U** class — [`schematic-comparison.md`](schematic-comparison.md).

---

## Chassis is fully disassembled

There are **no live endpoints** to buzz (no binding posts, sockets, or boards wired up). Identification now comes from:

1. **[`PT.md`](PT.md) / [`OT.md`](OT.md) + photos** — lead colors at the coil vs after splice  
2. **[`wire-tags.md`](wire-tags.md)** — numbered tags on **cut harness stubs** (same number = same wire)  
3. **[`hand-schematic-notes.md`](hand-schematic-notes.md)** — where each tag went *before* disassembly  
4. **Meter on the transformer only** — resistance **between leads on the same unit** (worksheets in PT/OT docs)  
5. **At reassembly** — wire one channel, verify, then mirror for the other OT  

Left vs right OT assignment is by **disassembly tags** on speaker stubs (**LFT** **1/15/19**, **RT** **11/17/13**) — see [`OT.md`](OT.md) and [`hand_schematic.png`](../photos/hand_schematic.png).

---

## Related documents

- [`wire-tags.md`](wire-tags.md) — tag index
- [`hand-schematic-notes.md`](hand-schematic-notes.md) — harness map and splice log
- [`CONNECTORS.md`](CONNECTORS.md) — **C1** PT → Power Board; OT primaries hardwired on 8-pin chassis
- [`photos/transformers.png`](../photos/transformers.png) — PT + OT together for scale

---

## Changelog

| Date       | Change                                                                           |
| ---------- | -------------------------------------------------------------------------------- |
| 2026-07-06 | Initial inventory from transformer photos                                        |
| 2026-07-06 | Disassembled chassis: transformer-only ID, tag stubs, defer L/R to reassembly    |
| 2026-07-06 | Rename A/B/C → **PT** / **OT**; photos `pt.png`, `ot-1`…`ot-4.png`               |
| 2026-07-06 | Split detail into [`PT.md`](PT.md) and [`OT.md`](OT.md); this file is index only |
