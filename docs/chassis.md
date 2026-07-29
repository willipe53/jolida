# Chassis — grounding and assembly

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-12  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

The chassis itself is a component: it carries the **star ground**, the **safety earth bond**, and constrains the **mount order** of every other assembly.

## Grounding — chassis star point

All circuit grounds meet at **one chassis stud** — the **star**. On this unit it sits center-frame, just right of the **TP1** test-point header, in the shadow between the Large Cap Board and the filter-cap bank ([`../photos/assembled from bottom.png`](../photos/assembled%20from%20bottom.png)).

### Two kinds of "ground" (do not confuse)

| Kind                       | Job                                           | Path                                                                |
| -------------------------- | --------------------------------------------- | ------------------------------------------------------------------- |
| **Safety earth** (GRN/YEL) | Fault current → mains earth (protects you)    | IEC inlet earth pin → **chassis stud**, short / thick / most secure |
| **Signal / circuit GND**   | 0 V reference for audio + DC (protects sound) | **One** reference tree — see below                                  |

**AC mains:** only the **earth** prong touches the chassis. **HOT** → fuse → PT primary; **NEUTRAL** → PT primary. **Never** bond neutral to the chassis.

### Reference tree (this chassis — avoid loops)

Rear panel hardware is **insulated** from the aluminum sheet — returns are **wired**, not through the panel.

```text
                    chassis star
                         ▲
              heavy BLK  │  IEC GRN/YEL (safety)
                         │
              Large Cap Board GND pour ◄── tags 1, 11, 18 BLK (hand sch)
                         │            ◄── RCA shell bus (rebuild)
                         │            ◄── tag 6 BLK out as C2 → preamp GND
                         │
              Preamp GND pour ◄── PT tag-9 BLK (direct)
                         │      ◄── C2 tag-6 BLK (from large cap board only)
```

- **Consolidate** speaker **G** signal **BLK** legs and RCA **shields** on the **Large Cap Board pour** — not separate runs to the preamp ([`back-panel.md`](back-panel.md#signal-ground-at-the-rear-panel), [`large-cap-board.md`](large-cap-board.md#panel--harness-gnd-pour)).
- **Preamp** has few ground pads; it sees circuit **GND** through **PT GND** + **C2** **6 BLK**, not a second shield path.
- OT **LEFT COM** / **RIGHT COM** stay on the **G** posts only (load return) — do not also tie OT commons to the pour unless factory did (they go to **G** post tee).

### What lands on the star (this chassis)

| Lug at star             | Path                                                                  | Confidence                    |
| ----------------------- | --------------------------------------------------------------------- | ----------------------------- |
| **Large Cap Board GND** | Heavy **BLK** from board **GND pour**                                 | High (owner recall + photos)  |
| **IEC safety earth**    | GRN/YEL from AC inlet                                                 | **Verify on rebuild**         |
| **Preamp / panel**      | Indirect — via large-cap-board pour + **C2** **6 BLK** and **PT GND** | Hand schematic + rebuild plan |

**Not the star:** individual RCA shells or speaker posts (insulated) — wire to **large-cap-board pour** first.

### How they were joined (as-built)

The grounds appeared to **all arrive at the star together**: leads wound/twisted together, crimped into a single **ring terminal**, then the whole joint **soldered over**. Practical to replicate, but note the trade-off:

- **Pro:** one solid mechanical/electrical tie; nothing floats.
- **Con:** it is a **daisy-tie**, not true independent star legs — the board and speaker returns share the last bit of that ring. For this amp it evidently worked; if hum shows up at power-up, separate the legs so each ground arrives at the stud on its own before combining.

### Rebuild checklist

- [ ] **IEC earth (GRN/YEL)** on the star stud — shortest, thickest, tightened hard; serrated/star washer; **bare metal-to-metal** (no paint/powder-coat under the lug).
- [ ] Confirm **PT / OT frames** have continuity to chassis through their mounting bolts (coated feet can leave a frame floating — add a star washer or bonding strap).
- [ ] Speaker **G** posts: **two BLK** each — OT common **and** signal **BLK** → **Large Cap Board GND pour** ([`back-panel.md`](back-panel.md))
- [ ] RCA **shells**: one bus → **Large Cap Board GND pour** (not preamp, not panel metal)
- [ ] **C2** **6 BLK** connected — preamp **GND** referenced from large-cap-board pour
- [ ] Large Cap Board pour → chassis **star** (heavy **BLK**)
- [ ] If replicating the wound-ring-then-solder joint, still bring **IEC earth as its own lug** — do not bury safety earth inside a soldered bundle where a cold joint could isolate it.

---

## Mount order (Q1)

Physical mounting constraints (transformer covers, **8-pin before Large Cap Board**, solder board in place) are documented in [`../README.md`](../README.md#physical-assembly-sequence). Summary:

| Factor                        | Effect                                                                                   |
| ----------------------------- | ---------------------------------------------------------------------------------------- |
| **C1–C3 are hardwired**       | Once soldered, boards cannot be reordered without cutting wire                           |
| **C4 / C5 / C6 are Molex**    | Preamp ↔ 8-pin, Front Panel ↔ Preamp, Back Panel ↔ Preamp unplug for fit checks          |
| **Back Panel ↔ Transformers** | AC inlet and speaker posts need reach to PT / OT — panel often mounts early              |
| **Wire length**               | Pigtails must be long enough for whichever mount order works — label before final solder |

Dry-fitting the bare boards costs nothing and can be done **now**, while waiting on parts.

---

## Related

- [`back-panel.md`](back-panel.md) — IEC inlet, earth wire origin, panel GND bus
- [`large-cap-board.md`](large-cap-board.md) · [`preamp-board.md`](preamp-board.md) — board ground pours
- [`OT.md`](OT.md) — secondary common
- [`../photos/hand_schematic.png`](../photos/hand_schematic.png) — tags **1 / 6 / 11 / 18 / 16** at pour
- [`../README.md`](../README.md) — build order, Q1

## Changelog

| Date       | Change                                                                                                      |
| ---------- | ----------------------------------------------------------------------------------------------------------- |
| 2026-07-22 | Ground tree: panel returns → **Large Cap Board pour**; preamp via **C2** + **PT GND**; RCA shells same pour |
| 2026-07-21 | Link README **physical assembly sequence** (covers, 8-pin phase A/B, board solder-in-place)                 |
| 2026-07-12 | Created from CONNECTORS.md grounding section + README Q1                                                    |
| 2026-07-18 | **G** post dual **BLK** (OT + signal); PDF **GND** at speaker **0**                                         |
