# Document authority & methodology

How we decide what this amp **is**, and what to trust when sources disagree.

---

## Priority order (highest first)

| Priority | Source                                                                                                                      | Role                                                                                                                                              |
| -------- | --------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| **1**    | **Physical unit**                                                                                                           | Cap markings, meter readings, photos, desoldered PCB silk, transformer label, hand schematic                                                      |
| **2**    | **[`gemini-restoration-notes.md`](gemini-restoration-notes.md)**                                                            | Empirical chassis breakdown: measurements, part IDs, Mouser cart tied to *this* unit — **high-confidence working document**                       |
| **3**    | **[`photos/`](../photos/)** + **[`hand-schematic-notes.md`](hand-schematic-notes.md)** + **[`wire-tags.md`](wire-tags.md)** | Disassembly record; wire tags for checking work (most harnesses removed)                                                                          |
| **4**    | **[`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)**                                                                | **Randomly sourced** factory drawing (audiocircuit.dk). Useful for **topology hints** and **naming** — **not** authoritative BOM for this chassis |
| **5**    | **KiCad sheets (planned)**                                                                                                  | Synthesized from 1–3; PDF used only where it agrees or fills gaps                                                                                 |

**Rule:** When PDF and bench disagree, **bench wins**. Log deltas in [`open-issues.md`](open-issues.md) and [`schematic-comparison.md`](schematic-comparison.md).

---

## Why the PDF is secondary

- Downloaded from an enthusiast archive — provenance and revision unknown.
- Titled **JD202A.s01** (2002); unit sticker **SJ202A** / panel **JD202** — same product line, many factory running changes.
- Already diverges from **this** unit on at least:
  - **C5/C6:** PDF **220 µF** → as-built **180 µF / 450 V** (owner read cap body)
  - **C5/C6 voltage class:** PDF **450 V** → some installed caps **200 V** (Gemini accepted for service)
  - **R21–R24:** **100 kΩ** · **3.3 kΩ** ceramic R22 · **68 kΩ / 3 W** bleeders on order (original **~62 kΩ**)
  - **Rail names:** PCB silk **+B**, **+B2**, **−B**, **70V IN** (OI-3)
  - **Grid stoppers:** PDF **1 kΩ** — confirmed **1 kΩ** on all four sockets ([`assembled from bottom.png`](../photos/assembled%20from%20bottom.png))

The PDF is a **cross-check**, not the spec we build to.

---

## Gemini conversation — why it ranks high

The Tube Amp chat was not generic advice. It was driven by:

- Photos and measurements from **your** chassis (panel cutouts, depth limits, fuse length)
- Identification of **Cliff CL2160** posts, **474J** film caps, cap values on power board
- Mouser cart review against **actual** recap needs

That makes [`gemini-restoration-notes.md`](gemini-restoration-notes.md) the best consolidated **empirical** record until we publish a formal as-built BOM and KiCad.

---

## Building per-board schematics (planned)

Each KiCad sheet derives from **physical evidence first**:

| Sheet               | Primary inputs                                                                  | PDF use                                                |
| ------------------- | ------------------------------------------------------------------------------- | ------------------------------------------------------ |
| **Power board**     | Desoldered PCB photos, cap markings, silk (**+B**, **+B2**, **−B**, **70V IN**) | Rectifier topology, rail names — verify against traces |
| **Preamp board**    | Populated/desoldered PCB, film cap markings, V1/V1′/V2/V2′ silk                 | Stage topology only                                    |
| **8-pin / chassis** | Octal socket photos, OT wiring, hand schematic                                  | EL34/UL hookup hints                                   |
| **Interconnect**    | Hand schematic, wire tags                                                       | Loose reference only                                   |

---

## Related files

| File                                                         | Purpose                                 |
| ------------------------------------------------------------ | --------------------------------------- |
| [`gemini-restoration-notes.md`](gemini-restoration-notes.md) | Empirical restoration & parts (primary) |
| [`schematic-comparison.md`](schematic-comparison.md)         | PDF vs unit delta log                   |
| [`open-issues.md`](open-issues.md)                           | Unresolved bench items                  |
| [`hand-schematic-notes.md`](hand-schematic-notes.md)         | Disassembly wiring map                  |
