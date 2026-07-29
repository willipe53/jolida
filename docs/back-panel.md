# Back Panel

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-1 · 2026-07-12  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

Rear panel: **AC inlet + fuse**, **speaker binding posts** (G / 4 Ω / 8 Ω per channel), and **four RCA inputs**. Binding posts and RCA jacks are **insulated from the panel** — the painted aluminum back panel is **not** a signal return conductor. Photos: [`../photos/back panel.png`](../photos/back%20panel.png) · [`../photos/speaker_posts.png`](../photos/speaker_posts.png) · [`../photos/back panel new.png`](../photos/back%20panel%20new.png) · [`../photos/assembled from bottom.png`](../photos/assembled%20from%20bottom.png).

## Components (rebuild parts)

| Item          | Part                                  | Notes                                                                  |
| ------------- | ------------------------------------- | ---------------------------------------------------------------------- |
| AC inlet      | **Schurter 6100.3300** (IEC C14)      | Replaces original                                                      |
| Fuse holder   | **P-H155** panel holder               | In the **HOT** leg, before the **power switch**                        |
| Fuse          | **T2.5A / 250 V slo-blow, 5×20 mm**   | ~200 W @ 115 V ≈ 1.7 A load                                            |
| Speaker posts | Binding posts ×6 (Cliff CL2160 class) | **Insulated** from panel; trim rear threads ≤ ~10 mm for chassis depth |
| RCA jacks     | 4× (reuse or replace)                 | All four paralleled at preamp — no selector switch                     |
| RCA caps      | 4× shorting caps (3D-print or buy)    | For unused inputs — see [Unused RCA jacks](#unused-rca-jacks)          |

---

## Mains AC — two nets (do not merge)

This amp has **two different “AC” paths**. Only the first is **115 V mains** from the wall.

| Net               | Voltage                          | Path                                                                                   |
| ----------------- | -------------------------------- | -------------------------------------------------------------------------------------- |
| **115 V primary** | Mains                            | IEC → fuse → **power switch** → **PT** primary (**RED1+RED2** / **ORG1+ORG2**)         |
| **PT HV**         | ~300 V AC (magnetically coupled) | **PT** **RED+BLK** coil pair → Large Cap Board **AC IN** → **VD3–VD6** bridge (**C1**) |

Large Cap Board silk **AC IN** is **not** the IEC inlet. It is the **high-voltage secondary** from the PT. With the **switch off**, the primary is dead and the HV winding delivers nothing — you do **not** switch **AC IN** separately for normal on/off.

### 115 V path (IEC → fuse → switch → PT primary)

Front-panel **power switch** (both poles) sits **after the fuse** and **before** the PT primary splices:

```text
IEC HOT ──► fuse ──► switch pole A ──► WHT (WALL AC) ──► splice ──► PT RED1 + RED2   (115 V primary hot)
IEC NEUTRAL ──► switch pole B ──► BLK (WALL AC) ──► splice ──► PT ORG1 + ORG2       (115 V primary neutral)
IEC EARTH (GRN/YEL) ──► chassis star   (unswitched — see [`chassis.md`](chassis.md))
```

**Switch outputs go to the PT primary only** — **not** to Large Cap Board **AC IN**. Dress **WHT/BLK** on the harness; at the PT body meter **RED1/RED2** and **ORG1/ORG2** ([`PT.md`](PT.md#primary-strap-115-v)).

Detail: [`front-panel.md`](front-panel.md#mains-power-switch) · factory PDF **T2** primary vs secondary (secondary → bridge = **PT HV** net above).

### PT HV path (PT → Large Cap Board — not mains)

```text
PT RED + BLK (tags 21 / 11 at HV stub) ──► Large Cap Board AC IN ──► bridge ──► +B rails
```

Label **PT HV** ([`labels.md`](labels.md)). **C1** only — see [`large-cap-board.md`](large-cap-board.md#c1--pt--this-board-18-awg-twisted-pairs).

---

## AC wiring (18 AWG hardwire)

| Path                                | Detail                                                                                               |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- |
| Inlet **HOT** → fuse → switch → PT  | **WHT** (**WALL AC**) after fuse/switch → splice **RED1 + RED2** at PT — [`PT.md`](PT.md)            |
| Inlet **NEUTRAL** → switch → PT     | **BLK** (**WALL AC**) → splice **ORG1 + ORG2** at PT (tag **23**). **Never** bond neutral to chassis |
| Inlet **EARTH** (GRN/YEL) → chassis | Shortest / thickest / most secure wire in the amp → **star stud** — see [`chassis.md`](chassis.md)   |

Mains dress is **WHT/BLK** on the extension (**WALL AC** label); coil colors at the PT remain **RED** / **ORG** for meter ID ([`PT.md`](PT.md#dcr-coil-leads-only--for-id)). **Do not** land **WALL AC** on Large Cap Board **AC IN**.

---

## Signal ground at the rear panel

Binding posts and RCA shells are **insulated** from the panel — every return is a **wire**. On this chassis, **rear-panel audio returns consolidate on the Large Cap Board GND pour**, not on extra pads on the preamp ([`hand_schematic.png`](../photos/hand_schematic.png) — tags **1**, **18**, **11**, **6** **BLK** and **16** **BLU** at that pour; RCA shields were **not** tagged at disassembly).

### Star topology (avoid ground loops)

Use **one** panel-side reference, then **one** path to the chassis star:

```text
Rear panel (insulated posts / RCAs)
  speaker G signal BLK (tags 1, 11) ──┐
  RCA shell bus (rebuild — see below) ─┼──► Large Cap Board GND pour (big copper pour)
  tag 18 BLK (as-drawn harness) ───────┘         │
                                                 ├── C2 tag-6 BLK ──► Preamp GND pad
  PT tag-9 BLK ─────────────────────────────────► Preamp GND pour (direct)
                                                 │
  Heavy BLK ───────────────────────────────────► chassis star (with IEC earth)
```

- **Do not** also run RCA shields to the **preamp** if speaker **G** returns already go to the **Large Cap Board** — that duplicates the reference and invites hum loops. Shields and **G** signal **BLK** legs share the **Large Cap Board pour** only.
- The preamp stays on **PT GND** + **C2** **6 BLK** (same 0 V node as the large-cap-board pour when **C2** is connected).
- **Tag 11** is reused elsewhere (**PT HV** return **11 BLK** on **C1**) — identify by **color + path**, not tag alone ([`../README.md`](../README.md)).

| Node                                               | Rebuild landing                                                                                                                                                                             |
| -------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Speaker **G** signal **BLK** (second wire at post) | Large Cap Board **GND** pour — disassembly tags **1** (LFT **G**), **11** (RT **G**) on [`hand_schematic.png`](../photos/hand_schematic.png)                                                |
| RCA **shells** (×4, tied at harness)               | **Same Large Cap Board GND pour** as above — **18 AWG** or **22 AWG** **BLK** bus; **not** on **C6** (centers only). Buzz shells → pour; preamp sees **GND** only via **C2** tag **6 BLK**. |
| **16 BLU** at pour (hand drawing)                  | **Verify at rebuild** — tag **16** is also PT secondary in other notes; confirm net before soldering ([`large-cap-board.md`](large-cap-board.md#panel--harness-gnd-pour))                   |

Factory PDF **GND** at speaker **0 / G** is the OT common **and** circuit reference — electrically the same net as the pour once wired, even though the physical landing is the **large cap board**, not the binding post itself.

---

## Speaker posts (OT secondaries + NFB, 18 AWG hardwire)

Binding posts are **insulated from the panel** — only the wires below carry current, not the aluminum back plate.

Channel is fixed by the disassembly stub tags ([`OT.md`](OT.md)).

**4 Ω** posts: **one** wire only — OT tap (**LEFT 4Ω** / **RIGHT 4Ω**) to the post.

**G** and **8 Ω** posts: **two** wires spliced at each binding post (tee). One wire is always from the **OT**; the other is a **preamp hardwire** (not **C6**, not Molex).

### **G** (common) — OT wire + signal ground

| Leg at post | Label / dress                               | Goes to                                                                                                                                |
| ----------- | ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| **1**       | **LEFT COM** / **RIGHT COM** (OT secondary) | That channel’s OT **BLK** common → speaker **G** post (return for the load)                                                            |
| **2**       | Second **BLK** (often thinner at splice)    | Large Cap Board **GND** pour (tags **1** / **11** on [`hand_schematic.png`](../photos/hand_schematic.png)) — not a separate preamp pad |

The second **BLK** is **not** another OT lead. It is the circuit **GND** reference for that speaker **G** node (factory PDF **GND** at **0 / G**). Same pour receives RCA **shell** bus and **C2** tag **6 BLK** → preamp ([`chassis.md`](chassis.md)).

Detail, buzz tests: [`preamp-board.md`](preamp-board.md#speaker-g-ground-tie) · photo [`assembled from bottom.png`](../photos/assembled%20from%20bottom.png).

### **8 Ω** — OT wire + negative feedback (NFB)

| Leg at post | Label / dress                                              | Goes to                                                                       |
| ----------- | ---------------------------------------------------------- | ----------------------------------------------------------------------------- |
| **1**       | **LEFT 8Ω** / **RIGHT 8Ω** (OT secondary)                  | That channel’s OT **8 Ω** tap → speaker **8 Ω** post (load tap when strapped) |
| **2**       | **LEFT FEEDBACK** / **RIGHT FEEDBACK** ( **PRP** as-built) | **Preamp board** **LFN** / **RFN** — global NFB from the **8 Ω** post sample  |

NFB path (hardwire only):

| Channel | **8 Ω** post tag | Lands on preamp                                                                               |
| ------- | ---------------- | --------------------------------------------------------------------------------------------- |
| **LFT** | **19**           | **R5′** (27 kΩ, silk **R5′**) in parallel with **\*C2** (20 pF) → **V1(A)** cathode **pin 3** |
| **RT**  | **13**           | **R5** (27 kΩ) in parallel with **\*C2** → **V5(A)** cathode **pin 3**                        |

The **LEFT FEEDBACK** / **RIGHT FEEDBACK** wire does **not** go to **GND**, **C6**, or the large cap board. **Do not omit it** — gain and distortion change without NFB.

Detail, buzz tests: [`preamp-board.md`](preamp-board.md#global-negative-feedback-nfb) · photo [`speaker_posts.png`](../photos/speaker_posts.png).

### Tags, labels, as-built splice colors

Per factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)): the **8 Ω** node tees to NFB; the **G** node tees OT return and circuit **GND**. Panel-end insulation may not match coil color — trust continuity from the OT stub / P-touch label.

| Post        | Tag | P-touch (OT wire) | Coil or net (authoritative)       | As-built color (may differ after splices) |
| ----------- | --- | ----------------- | --------------------------------- | ----------------------------------------- |
| **LFT G**   | 1   | **LEFT COM**      | **BLK** (heavier → OT)            | BLK                                       |
| **LFT G**   | 1   | —                 | → Large Cap Board **GND** pour    | BLK (thinner; tag **1**)                  |
| **LFT 4 Ω** | 15  | **LEFT 4Ω**       | **BLU**                           | BLK                                       |
| **LFT 8 Ω** | 19  | **LEFT 8Ω**       | **BRN**                           | BLU at splice                             |
| **LFT 8 Ω** | 19  | —                 | → preamp **LFN** (**R5′ ∥ \*C2**) | **PRP** · label **LEFT FEEDBACK**         |
| **RT G**    | 11  | **RIGHT COM**     | **BLK** (heavier → OT)            | BRN at splice                             |
| **RT G**    | 11  | —                 | → Large Cap Board **GND** pour    | BLK (thinner; tag **11**)                 |
| **RT 4 Ω**  | 17  | **RIGHT 4Ω**      | **BLU**                           | BLU (confirm at splice)                   |
| **RT 8 Ω**  | 13  | **RIGHT 8Ω**      | **BRN**                           | RED at splice                             |
| **RT 8 Ω**  | 13  | —                 | → preamp **RFN** (**R5 ∥ \*C2**)  | **PRP** · label **RIGHT FEEDBACK**        |

Splice colors in the table may differ from coil colors — trust the OT stub and P-touch label, not panel-end insulation alone.

---

## Harness C6 — Back Panel ↔ Preamp Board (Micro-Fit 3.0, 4-pin, this doc owns it)

**One plug + one receptacle, 22 AWG.** Factory had four RCA inputs and a selector; this rebuild **parallels all four** to one preamp input (no switch).

| Pin | Back Panel end   | Preamp end                                        |
| --- | ---------------- | ------------------------------------------------- |
| 1   | RCA **1** center | Pins 1–4 tie to the **common preamp**             |
| 2   | RCA **2** center | **input net** at the Preamp Board                 |
| 3   | RCA **3** center | receptacle ([`preamp-board.md`](preamp-board.md)) |
| 4   | RCA **4** center |                                                   |

**RCA shells** → **Large Cap Board GND pour** (with speaker **G** signal **BLK** bus) — [Signal ground](#signal-ground-at-the-rear-panel). **C6** = **centers** only.

### Unused RCA jacks

Paralleled inputs mean any **unconnected** jack acts as an antenna into the preamp. Handle each unused jack one of these ways:

| Option                             | Effect                                                                                 |
| ---------------------------------- | -------------------------------------------------------------------------------------- |
| **3D-printed shorting cap** (best) | Center pin shorted to shell → antenna dead; recommended for jacks left empty long-term |
| **Do not crimp** the C6 pin        | Center wire absent → antenna disconnected from preamp (jack floats, but harmless)      |
| Dust cap only                      | Cosmetic; antenna still lives if the C6 pin is populated                               |

### C6 worksheet (fill at bench)

| Pin | Function   | Jack (label at bench) | Color | ☐ Crimped | ☐ Metered |
| --- | ---------- | --------------------- | ----- | --------- | --------- |
| 1   | RCA center |                       |       | ☐         | ☐         |
| 2   | RCA center |                       |       | ☐         | ☐         |
| 3   | RCA center |                       |       | ☐         | ☐         |
| 4   | RCA center |                       |       | ☐         | ☐         |

Label each pin with the jack name (AUX / CD / TAPE / TUNER — assign at bench to match panel silk). Unplug **C6** to separate the Back Panel from the Preamp Board for mount-order dry-fit ([`../README.md`](../README.md) Q1).

---

## Bench tests (Part 2 gate)

| Check                 | Pass                                                                                                                                               |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| **PT** primary cold Ω | No short to chassis before full power wiring                                                                                                       |
| Speaker posts         | Insulated posts; OT on **G / 4 Ω / 8 Ω**; **G** signal **BLK** + RCA **shells** → **Large Cap Board GND pour**; **LEFT/RIGHT FEEDBACK** on **8 Ω** |
| Earth bond            | IEC earth lug to chassis star — low Ω, bare metal-to-metal                                                                                         |
| Clearance             | No binding post hits a transformer when the panel is seated                                                                                        |

---

## Related

- [`chassis.md`](chassis.md) — star ground, safety earth
- [`OT.md`](OT.md) — secondary tap colors
- [`PT.md`](PT.md) — primary strap
- [`preamp-board.md`](preamp-board.md) — C6 preamp end
- [`../README.md`](../README.md) — Part 2 build order

## Changelog

| Date       | Change                                                                                                                     |
| ---------- | -------------------------------------------------------------------------------------------------------------------------- |
| 2026-07-12 | Created from CONNECTORS.md C6 + README Part 2 back-panel work                                                              |
| 2026-07-20 | **WALL AC** label on mains **WHT/BLK**; PT harness in [`PT.md`](PT.md) / [`labels.md`](labels.md)                          |
| 2026-07-20 | Speaker OT wires: **LEFT/RIGHT COM/4Ω/8Ω** — [`labels.md`](labels.md)                                                      |
| 2026-07-18 | 8 Ω dual-wire (OT **BRN** + **PRP** NFB); photo + PDF cross-ref                                                            |
| 2026-07-21 | Mains path: fuse → **power switch** → PT primary only; **AC IN** = **PT HV** (not IEC)                                     |
| 2026-07-22 | Panel returns → **Large Cap Board GND pour** (hand sch **1/6/11/18** **BLK**, **16** **BLU** verify); RCA shells same pour |
