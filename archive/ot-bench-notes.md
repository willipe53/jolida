# OT — bench identification (DCR matrix)

**Archived bench data** — use when the coil colors are wrong or missing and you need to **identify** leads on a bare OT. For **where to solder**, use [`../docs/OT.md`](../docs/OT.md).

**Unit:** LM-9914U class · **T-2 closed** 2026-07-12 · measured on OT unit 1.

---

## How to read the matrix

Meter **Ω between lead pairs** on one OT (no tubes, no boards connected). Symmetry tells you roles:

| Reading                                        | Meaning                                               |
| ---------------------------------------------- | ----------------------------------------------------- |
| **ORG↔BRN ≈ 103 Ω**                            | Full primary winding — plates at the ends             |
| **RED↔ORG** and **RED↔BRN ≈ 53 Ω** (symmetric) | **RED** = **+B center tap**                           |
| **RED↔YEL** and **RED↔WHT ≈ 21 Ω**             | **YEL** / **WHT** = **UL screen taps** (~40% from CT) |
| **ORG↔YEL**, **BRN↔WHT** (mid values)          | Same-half pairs — do not split across sockets         |

Once colors are confirmed, wire per [`../docs/OT.md`](../docs/OT.md) — not from this table alone.

---

## DCR matrix (primary — unit 1, Ω)

|         | ORG | YEL | WHT | BRN |
| ------- | --- | --- | --- | --- |
| **RED** | 53  | 21  | 21  | 53  |
| **ORG** | —   | 36  | 71  | 103 |
| **YEL** | —   | —   | 39  | 73  |
| **WHT** | —   | —   | —   | 36  |

Confirm the same pattern on unit 2 before final solder.

---

## Related

- [`../docs/OT.md`](../docs/OT.md) — connection map (rebuild)
- [`../docs/8-pin-chassis.md`](../docs/8-pin-chassis.md) — primary landings at EL34 sockets
- [`TRANSFORMERS.md`](TRANSFORMERS.md) — index
