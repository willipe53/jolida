# jolida

A **Jolida SJ202A / JD202** integrated tube amp — EL34 ×4, 12AX7 ×2, 12AT7 ×2 — stripped, rebuilt, and documented as-built. This repo is the notes from that rebuild, and the story of the system around it.

Jolida JD202A with tubes lit

---

## Speakers first

The amp was coming back. The speakers were not.

I had owned a pair of **Acoustic Energy AE 209s** — big, bulky, and dry in a clinical way that never matched the warmth of the Jolida. When we left the burbs I let them go. The new room needed something smaller that still sounded like music next to tubes. I landed on **DALI Opticon 1 MK2**.

They looked fine on the floor, but they needed short stands that tipped them up a bit.

Ear-line math wanted something steep. In Fusion, **~7.5°** looked right. The shelf matched the Opticon footprint; rubber feet for the floor. The first print design ballooned to about **seventeen hours**. Adaptive cubic infill around **5%** cut that to roughly **eight**. Then came **1 mm Filaflex** mats for the shelf — square edges, no brim, hairspray on the bed for a clean release.

With the Opticons on their wedges, the Jolida that would drive them deserved the same attention.

---

## Where the amp came from

I bought it in the late 1990s from **Andy Singer** at **Sound by Singer** on 16th Street next door to Coffee Shop and across the street from Blue Water Grille.

In the city apartment it was the daily stereo. TV ran through one input. Music through others, but in the burbs it became more of a conversation piece. Sometimes it worked a party with a **Sonos Connect** piping into an input. Then it fell into disuse.

One day I opened the bottom, looked around, and wondered what a full strip-and-rebuild with new high-quality parts would feel like.

---

## Opening the patient

Chassis underside before rebuild

The underside was dense factory point-to-point, with some visible low-quality parts. I decided to desolder it clean and rebuild with physical documentation along with whatever schematics I could find on the internet.

Amp parts laid out on the bench

Boards, transformers, panels — the scale of the teardown was the first honest look at what I had bought twenty-odd years earlier.

---

## Mapping without a trustworthy map

Hand schematic from disassembly

My disassembly sketch left a lot to be desired. I found a factory drawing online — `[docs/Jolida-JD202A-int-sch.pdf](docs/Jolida-JD202A-int-sch.pdf)` — and treated it as topology only. Tags, photos, and continuity got the last word.

Complexity showed up early and often. Silkscreen names did not match PDF designators — **R13** and **R16** on the preamp board meant something different than the schematic’s grid-stopper and cathode-sense story. Wire-tag numbers were reused (by me) across harnesses. The hand map, the PDF, and the board had to be cross-checked until they stopped disagreeing.

---

## Resistor archaeology

Desoldered resistor pile

Every desoldered resistor went through the meter. Color bands are sometimes hard to discern, but I got through it.

For the large-cap board I chose **pink flameproof metal-oxide** parts where heat and fault behavior matter. For the preamp signal path, **blue metal film** — quieter, tighter matching.

---

## The big cans

Green factory caps beside larger orange replacements

Purchased the best quality caps I could find that still fit the size constraints of the chassis. On the preamp, the factory green coupling chicklets became **Sprague Orange Drop 716P** film — fancy looking but huge.

---

## Transformers and wire

Transformer leads dressed and labeled

I passed on the thick Amazon PVC that meets an “18 AWG” claim by wrapping the copper in a garden hose, instead getting some really expensive **18 AWG PTFE** stranded tinned copper — thin jacket, **600 V**, heater pairs twisted tight, insulation that does not melt back under the iron.

Labels for future-me went on with a **Brother P-touch** and **HSe** heat-shrink. **PREAMP HEAT**, **V3/V4 HEAT**, **V7/V8 HEAT**, **+B LEFT**, **+B RIGHT**, pin labels on the OT primaries — permanent tags near the nodes that matter.

---

## Back panel

Assembled back panel

Hardware had to fit **existing** holes. New IEC inlet, a fuse holder shallow enough for the panel, binding posts that take spades without looking like toy plastic. RCA shells land on the large-cap board **GND pour** with the speaker **G** returns. Safety earth goes to a chassis **star**. Inputs are paralleled — no selector switch on this rebuild.

I replaced the broken gold-tone feet with aluminum isolators that match the brushed chassis better than the old jewelry did.

---

## Preamp board

Assembled preamp board

Four novals, bias trims on the solder side for underside access, NFB corners with the little discs. **Bourns 3296** multiturn pots (~**22 kΩ**) replaced the old trims — smooth bias work without sudden jumps.

Some of the hardest hours were small parts. A **10 kΩ / 100 pF** network looked parallel on a fuzzy schematic read and series in the desoldered pile. The photos and the board won: **R51 + C51 in series** on the **12AX7** sockets, part of an **SRPP** front end with mirrored triode halves on **V1** versus **V5**. The pilot LED, schematic-wise, hangs off the preamp heaters; as-built it lives on **V7/V8** pins **2** and **7**. Also I thought a blue LED would look better than the green one that came with the amp, but it sat weird so had to be hot-glued in place.

Cold bias preset and warm trim at the **TP1** pads are how you keep EL34s alive — wiper to the −B end before tubes go in, then ~**40 mV** per cathode sense once they are hot. From under the chassis the screw sense felt backwards from the docs until the meter said otherwise. Detail lives in `[docs/preamp-board.md](docs/preamp-board.md)` and `[docs/tubes.md](docs/tubes.md)`.

---

## Tubes

New tube complement

Front row silk reads **V2 · V1 · V5 · V6**; rear **V3 · V4 · V8 · V7**. Center novals are the **12AX7** gain stages; outer novals the **12AT7** drivers; the four octals are the push-pull output.

EL34 in the V7 position

New glass for the rebuild: **Shuguang Treasure 6CA7-Z** ×4 — Chinese 珍品 / Treasure series, the “dragon” look, EL34-family power tubes — and **Genalex Gold Lion ECC81** ×4, **Made in Russia**, for the small-signal sockets. Staged power-up on a bulb limiter first, then full mains and warm bias at **TP1**.

---

## Into the room

Streaming started with a used **Sonos Connect Gen 2**. Fine for getting audio into the amp; its DAC was the weak link. That chase ended on a **Denafrips Enyo** — R2R, coax in.

For interconnects I A/B’d a shiny blue **WireWorld Luna** against matte green **AudioQuest Emerald**. The Emeralds won; in addition to probably being better I am pretty sure these are the originals from Sound by Singer. The arrows on the jacket are the shield drain — toward the source, so noise has somewhere to go that is not the amp.

Speaker cable is absurdly thick stuff I almost certainly overpaid for at some point. Now it runs to the Opticons — spades into the new posts.

Volume pot on the front panel closes the signal path, but the high-quality audio pot I purchased was so big I had to cut away a small bit of chassis behind the front panel so it would fit.

The chain that plays is:

**Sonos Connect (coax) → Denafrips Enyo (Emeralds) → Jolida (Thicks) → DALI Opticon 1 MK2**.

Jolida on the sideboard with DALI Opticon, Denafrips Enyo, and Sonos Connect

Pin maps, BOM, and board notes live under `[docs/](docs/)`. The old Parts 1–6 checklist is archived at `[archive/rebuild-plan.md](archive/rebuild-plan.md)`.

---

## Documentation

Read `[docs/SOURCES.md](docs/SOURCES.md)` first — **physical unit and empirical bench notes outrank the sourced factory PDF.**

One document per **physical component**; each owns the pinout and harness worksheets for its end of the wire.

| Document                                                           | Role                                                                                                                                                            |
| ------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `[docs/SOURCES.md](docs/SOURCES.md)`                               | Authority order & methodology                                                                                                                                   |
| `[docs/tubes.md](docs/tubes.md)`                                   | **Tube designators V1–V8** — naming authority for all docs and future schematic                                                                                 |
| `[docs/large-cap-board.md](docs/large-cap-board.md)`               | **Large Cap Board** — BOM, layout, rails; owns **C1** (+ its end of C2/C3)                                                                                      |
| `[docs/preamp-board.md](docs/preamp-board.md)`                     | **Preamp Board** — silk / BOM / bias network; owns **C2**                                                                                                       |
| `[docs/8-pin-chassis.md](docs/8-pin-chassis.md)`                   | **8-Pin Chassis** — EL34 PTP wiring; owns **C3**, **C4**                                                                                                        |
| `[docs/back-panel.md](docs/back-panel.md)`                         | **Back Panel** — AC inlet, fuse, posts, RCAs; owns **C6**                                                                                                       |
| `[docs/front-panel.md](docs/front-panel.md)`                       | **Front Panel** — volume, LED; owns **C5**                                                                                                                      |
| `[docs/chassis.md](docs/chassis.md)`                               | **Chassis** — star ground, safety earth, mount order                                                                                                            |
| `[docs/PT.md](docs/PT.md)`                                         | **Power Transformer** — coil ID, DCR, harness                                                                                                                   |
| `[docs/OT.md](docs/OT.md)`                                         | **Output Transformers** — two units, primary color map, speaker paths                                                                                           |
| `[docs/parts-list.md](docs/parts-list.md)`                         | **Parts list** — every part, by board, with status                                                                                                              |
| `[docs/hand-schematic-notes.md](docs/hand-schematic-notes.md)`     | Disassembly wiring map                                                                                                                                          |
| `[docs/Jolida-JD202A-int-sch.pdf](docs/Jolida-JD202A-int-sch.pdf)` | Secondary — randomly sourced factory drawing                                                                                                                    |
| `[archive/rebuild-plan.md](archive/rebuild-plan.md)`               | Archived Parts 1–6 rebuild checklist (memorial)                                                                                                                 |
| `[photos/](photos/)`                                               | Board and chassis photos                                                                                                                                        |
| `[archive/](archive/)`                                             | Superseded docs — open-issues tracker, wire tags, gemini notes, PDF delta log, old interconnect docs (CONNECTORS / INTERCONNECTS / BLOCK_DIAGRAM), KiCad drafts |

**Wire-tag rule** (applies everywhere tags are mentioned): disassembly tag numbers were **reused** — e.g. 23/21/19/17 appear on PT power wires _and_ on the green TP1 sense wires; 9 is both BLU (−B) and BLK (PT ground). Identity = **color + number**, never number alone.

**Boards (for navigating the docs):** Large Cap Board (HT/bias filter, C1/C2/C3), Preamp board (four novals), 8-pin chassis (EL34 PTP). Planned output still includes per-board schematics (Fusion 360 → Eagle) with tube refs **V1–V8** per `[docs/tubes.md](docs/tubes.md)`, and the as-built BOM in `[docs/parts-list.md](docs/parts-list.md)`.
