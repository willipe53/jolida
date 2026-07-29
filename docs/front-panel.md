# Front Panel

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-12  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

Front panel carries the **volume pot**, the **power LED**, and the **mains power switch**. The factory input-selector position is **not used** in this rebuild — all four RCAs are paralleled at the preamp via **C6** ([`back-panel.md`](back-panel.md)).

Photos: [`../photos/LED wires.png`](../photos/LED%20wires.png), [`../photos/assembled amp.png`](../photos/assembled%20amp.png).

## Mains power switch

**Switches 115 V primary only** — both IEC legs after the rear-panel fuse:

| Switch end | From               | To (switch on)                                 |
| ---------- | ------------------ | ---------------------------------------------- |
| Pole **A** | Fuse / IEC **HOT** | **WHT** run → PT **RED1 + RED2** (**WALL AC**) |
| Pole **B** | IEC **NEUTRAL**    | **BLK** run → PT **ORG1 + ORG2** (**WALL AC**) |

**Not** wired to Large Cap Board **AC IN** — that pad pair is **PT HV** (~300 V AC from the transformer secondary), downstream of the primary. See [`back-panel.md`](back-panel.md#mains-ac--two-nets-do-not-merge) and [`large-cap-board.md`](large-cap-board.md#c1--pt--this-board-18-awg-twisted-pairs).

**Earth** (GRN/YEL) bypasses the switch to the chassis star ([`chassis.md`](chassis.md)).

The **power LED** is a separate hardwire ([below](#power-led--original-wiring-not-on-c5)) — not the mains switch itself.

## Harness C5 — Front Panel ↔ Preamp Board (Micro-Fit 3.0, 6-pin housing, 3 used — this doc owns it)

**One plug + one receptacle, 22 AWG.** The kit has no 5-pin housing, so C5 uses a **6-pin housing with three positions populated** — volume pot only.

| Pin | Function   |
| --- | ---------- |
| 1–3 | Volume pot |
| 4–6 | **empty**  |

The volume bundle carried disassembly tag **23** (GRN + RED) — the *volume* tag 23, distinct from the other tag-23 wires at the PT and Large Cap Board (identity = color + number, never number alone).

### C5 worksheet (fill at crimp)

| Pin | Function | Pot lug | Color | ☐ Crimped | ☐ Metered |
| --- | -------- | ------- | ----- | --------- | --------- |
| 1   | Volume   |         |       | ☐         | ☐         |
| 2   | Volume   |         |       | ☐         | ☐         |
| 3   | Volume   |         |       | ☐         | ☐         |
| 4–6 | empty    | —       | —     | —         | —         |

Unplug **C5** to lift the Front Panel for pot service.

---

## Power LED — original wiring (not on C5)

The power LED does **not** terminate at a Molex on the preamp board. Photo evidence ([`LED wires.png`](../photos/LED%20wires.png)):

| Wire (at disassembly) | Factory color           | Preamp end                                                          | Front panel end            |
| --------------------- | ----------------------- | ------------------------------------------------------------------- | -------------------------- |
| LED return / drive    | **GRN**                 | **Soldered to a noval (9-pin) socket pin** on the preamp board      | —                          |
| LED other leg         | **DK BLU** (light blue) | — (series resistor / limit network is on the board near the socket) | **Front-panel LED holder** |

The LED pair had **no numeric tag** at disassembly.

**Rebuild:**

1. **GRN** — replicate factory: buzz the wire to its noval socket pin on the bare preamp board (a "Do now" item — see [`../README.md`](../README.md)), then solder to the same pin. Likely heater-related or +B2-derived — confirm against the factory PDF before power-up.
2. **DK BLU** — hardwire to the front-panel LED holder; polarity matters — test with a bench supply or 9 V battery + series 1 kΩ before tube power.
3. **Do not** put the LED legs on C5 unless you deliberately redesign the harness; the original preamp-board solder point is the reference.

**Front panel service:** unplug **C5** (volume) and disconnect the **DK BLU** lead at the LED holder; **GRN** stays on the preamp board.

---

## Bench tests (Part 5/6 gate)

| Check  | Pass                                                                         |
| ------ | ---------------------------------------------------------------------------- |
| **C5** | Volume pot sweeps smoothly end to end; no crackle on the meter               |
| LED    | **DK BLU** polarity verified at the holder; **GRN** on the correct noval pin |

---

## Related

- [`preamp-board.md`](preamp-board.md) — C5 preamp end, LED GRN pin
- [`back-panel.md`](back-panel.md) — C6 RCA inputs (selector not used)
- [`../README.md`](../README.md) — Part 5 build order

## Changelog

| Date       | Change                                                                           |
| ---------- | -------------------------------------------------------------------------------- |
| 2026-07-21 | **Mains power switch** — 115 V to PT primary only; not Large Cap Board **AC IN** |
