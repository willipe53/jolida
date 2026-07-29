# Output Transformers (OT)

**Unit:** Jolida SJ202A / JD202 · factory type **LM-9914U** (PDF **T1**)  
**Photos:** [`ot-1.png`](../photos/ot-1.png) · [`ot-2.png`](../photos/ot-2.png) · [`ot-3.png`](../photos/ot-3.png) · [`ot-4.png`](../photos/ot-4.png)

Two identical units (one per channel). All leads **hardwired** — no Molex. **BRN appears on both sides** — two different wires. Trust **coil color**, not panel-end color after splices. EL34 designators **V3/V4** (LFT) and **V7/V8** (RT): [`tubes.md`](tubes.md).

**Bench ID only:** if coil colors are missing, meter the bare OT — [`../archive/ot-bench-notes.md`](../archive/ot-bench-notes.md) (DCR matrix). That table does **not** tell you where to solder; this doc does.

---

## Bench verification (both OTs — no “power-up” on the OT)

An OT has **no safe standalone mains test**. You do **not** apply wall voltage to OT primaries or secondaries by themselves. Validation is **cold Ω** now; **hot** checks wait until **Part 3/4** (+B at **+B LEFT** / **+B RIGHT** through the Large Cap Board, tubes out).

**Power off, unplugged.** One OT at a time, no boards or sockets wired to the leads. Probe the **applied P-touch labels** on the harness ([`labels.md`](labels.md)) — dress insulation may not match factory coil color (e.g. no brown on **LEFT 8Ω** / **RIGHT 8Ω** or on **V4 PIN 3** / **V8 PIN 3**).

**LFT OT** (labels **+B LEFT**, **V3 PIN 3/4**, **V4 PIN 3/4**, **LEFT COM**, **LEFT 4Ω**, **LEFT 8Ω**):

| Step | Meter                                                                            | Pass                                          |
| ---- | -------------------------------------------------------------------------------- | --------------------------------------------- |
| 1    | **+B LEFT** ↔ **V3 PIN 3** and **+B LEFT** ↔ **V4 PIN 3**                        | ~**53 Ω** each (CT to each plate half)        |
| 2    | **V3 PIN 3** ↔ **V3 PIN 4**; **V4 PIN 3** ↔ **V4 PIN 4**                         | ~**36 Ω** each (twisted pairs — do not split) |
| 3    | **V3 PIN 3** ↔ **V4 PIN 3**                                                      | ~**103 Ω** (full primary)                     |
| 4    | Any **+B LEFT** or **V3/V4 PIN 3/4** ↔ **LEFT COM**, **LEFT 4Ω**, or **LEFT 8Ω** | **OL** (primary–secondary isolation)          |

**RT OT** ( **+B RIGHT**, **V7 PIN 3/4**, **V8 PIN 3/4**, **RIGHT COM**, **RIGHT 4Ω**, **RIGHT 8Ω**): same Ω pattern — swap names in step 1–4. Compare both units (README **T-2**). Reference matrix at bare coil: [`ot-bench-notes`](../archive/ot-bench-notes.md).

Optional: confirm **LFT** vs **RT** stub tags **1/15/19** vs **11/17/13** at the transformer body before panel terminations.

**After Large Cap Board is live (Part 3 gate, tubes out):** confirm **+B DC** at **+B LEFT** and **+B RIGHT**. That proves the **C3** feed and CT connection — not audio performance (that needs tubes and load).

---

## How to connect (one OT = one channel)

Each OT has **five primary** leads → **8-pin chassis** + **+B** from the Large Cap Board, and **three secondary** leads → **back-panel** speaker posts (plus **panel-side tees** on **G** and **8 Ω** only — not extra OT wires).

**Rebuild primary landing (2026-07-20):** twist **ORG+YEL** to one socket, **BRN+WHT** to the other — never split a pair. Same assignment both channels:

| Tube   | Channel | OT primary pair (pins **3** / **4**) |
| ------ | ------- | ------------------------------------ |
| **V3** | LFT     | **ORG** + **YEL**                    |
| **V4** | LFT     | **BRN** + **WHT**                    |
| **V7** | RT      | **ORG** + **YEL**                    |
| **V8** | RT      | **BRN** + **WHT**                    |

```text
                    Large Cap Board +B pour (C3 RED, tags 13 / 23)
                              │
PRIMARY (5)                   ▼
  RED ───────────── OT center tap (same wire, or splice at OT stub)

  ORG ── pin 3 ── V3 (LFT)     YEL ── pin 4 ── V3
  BRN ── pin 3 ── V4 (LFT)     WHT ── pin 4 ── V4

  ORG ── pin 3 ── V7 (RT)     YEL ── pin 4 ── V7
  BRN ── pin 3 ── V8 (RT)     WHT ── pin 4 ── V8

SECONDARY (3) → back panel
  BLK ── speaker G post (+ second BLK from post → preamp GND — see back-panel)
  BLU ── speaker 4 Ω post
  BRN ── speaker 8 Ω post (+ PRP NFB from post → preamp — not from OT coil)
```

Detail: [`8-pin-chassis.md`](8-pin-chassis.md) · [`back-panel.md`](back-panel.md) · [`large-cap-board.md`](large-cap-board.md) (**C3**).

---

## Primary — coil color → tube → pin

Ultralinear push-pull. **ORG+YEL** and **BRN+WHT** are the only valid pairs ([`8-pin-chassis.md`](8-pin-chassis.md)).

| Coil color | Lands on  | Tube           | EL34 pin                                            |
| ---------- | --------- | -------------- | --------------------------------------------------- |
| **RED**    | **+B CT** | —              | **C3** **RED** → OT **RED** stub (not a socket pin) |
| **ORG**    | Plate     | **V3**, **V7** | **3**                                               |
| **YEL**    | UL screen | **V3**, **V7** | **4** (twist with **ORG**)                          |
| **BRN**    | Plate     | **V4**, **V8** | **3**                                               |
| **WHT**    | UL screen | **V4**, **V8** | **4** (twist with **BRN**)                          |

| Channel | **C3** +B feed tag | P-touch label | Tubes on this OT |
| ------- | ------------------ | ------------- | ---------------- |
| **LFT** | **13** RED         | **+B LEFT**   | **V3** + **V4**  |
| **RT**  | **23** RED         | **+B RIGHT**  | **V7** + **V8**  |

**+B wiring:** both tags are **18 AWG RED** from the **same Large Cap Board +B pour** (~425 V at the top cap stack) — two wires, one node ([`large-cap-board.md`](large-cap-board.md)). **Board end:** solder each at **+B**. **OT end:** join to that channel’s **RED** center-tap lead. That is a straight high-voltage run — **not** a socket pin, **not** the **TP1** bias header (those five pads are **GRN** pin-8 sense only). Swapping tag **13** vs **23** between channels is electrically fine if each OT stays matched to its sockets and speaker posts.

Labels: [`labels.md`](labels.md) — **+B LEFT/RIGHT**, **V3–V8 PIN 3/4**, **LEFT/RIGHT COM/4Ω/8Ω** ( **LEFT** = LFT channel, **RIGHT** = RT).

---

## Secondary — coil color → signal → destination

| Coil color | Signal name | P-touch (OT coil)            | OT lead connects to                  | Also at panel (not from OT coil)                                                                               |
| ---------- | ----------- | ---------------------------- | ------------------------------------ | -------------------------------------------------------------------------------------------------------------- |
| **BLK**    | **0 / G**   | **LEFT COM** / **RIGHT COM** | Speaker **G** post — heavier **BLK** | Second **BLK** **G** post → preamp **GND** pour (unlabeled batch)                                              |
| **BLU**    | **4 Ω**     | **LEFT 4Ω** / **RIGHT 4Ω**   | Speaker **4 Ω** post — one wire only | —                                                                                                              |
| **BRN**    | **8 Ω**     | **LEFT 8Ω** / **RIGHT 8Ω**   | Speaker **8 Ω** post — one wire only | **LEFT FEEDBACK** / **RIGHT FEEDBACK** from **8 Ω** post → preamp **LFN** / **RFN** ([`labels.md`](labels.md)) |

Speaker straps between **G** and either **4 Ω** or **8 Ω**. **G** signal **BLK** and RCA **shells** → **Large Cap Board GND pour**; preamp reference via **C2** + **PT GND** ([`chassis.md`](chassis.md)).

**Dress:** do not twist secondary **BLK / BLU / BRN** together — three separate taps. Loose harness or cable tie to the back panel is enough.

---

## Channel assignment (LFT vs RT)

Parts are interchangeable. Match original stub tags at reassembly:

| Channel | Secondary tags         | Panel posts             |
| ------- | ---------------------- | ----------------------- |
| **LFT** | **1**, **15**, **19**  | **G**, **4 Ω**, **8 Ω** |
| **RT**  | **11**, **17**, **13** | **G**, **4 Ω**, **8 Ω** |

| Post        | Tag | Coil color | Signal    |
| ----------- | --- | ---------- | --------- |
| **LFT G**   | 1   | **BLK**    | OT common |
| **LFT 4 Ω** | 15  | **BLU**    | 4 Ω tap   |
| **LFT 8 Ω** | 19  | **BRN**    | 8 Ω tap   |
| **RT G**    | 11  | **BLK**    | OT common |
| **RT 4 Ω**  | 17  | **BLU**    | 4 Ω tap   |
| **RT 8 Ω**  | 13  | **BRN**    | 8 Ω tap   |

Panel-end insulation colors may differ after splices — use **tag + coil color** at the OT stub.

---

## Rebuild worksheet (☐ per OT)

### LFT OT (**V3** + **V4**, tag **13** +B)

| Coil | P-touch label | Tube / signal | Pin or destination       | ☐   |
| ---- | ------------- | ------------- | ------------------------ | --- |
| RED  | **+B LEFT**   | +B CT         | PWR **+B** → OT RED stub | ☐   |
| ORG  | **V3 PIN 3**  | **V3** plate  | **V3** pin **3**         | ☐   |
| YEL  | **V3 PIN 4**  | **V3** UL     | **V3** pin **4** (∥ ORG) | ☐   |
| BRN  | **V4 PIN 3**  | **V4** plate  | **V4** pin **3**         | ☐   |
| WHT  | **V4 PIN 4**  | **V4** UL     | **V4** pin **4** (∥ BRN) | ☐   |
| BLK  | **LEFT COM**  | G             | LFT speaker **G** post   | ☐   |
| BLU  | **LEFT 4Ω**   | 4 Ω           | LFT **4 Ω** post         | ☐   |
| BRN  | **LEFT 8Ω**   | 8 Ω           | LFT **8 Ω** post         | ☐   |

### RT OT (**V7** + **V8**, tag **23** +B)

| Coil | P-touch label | Tube / signal | Pin or destination       | ☐   |
| ---- | ------------- | ------------- | ------------------------ | --- |
| RED  | **+B RIGHT**  | +B CT         | PWR **+B** → OT RED stub | ☐   |
| ORG  | **V7 PIN 3**  | **V7** plate  | **V7** pin **3**         | ☐   |
| YEL  | **V7 PIN 4**  | **V7** UL     | **V7** pin **4** (∥ ORG) | ☐   |
| BRN  | **V8 PIN 3**  | **V8** plate  | **V8** pin **3**         | ☐   |
| WHT  | **V8 PIN 4**  | **V8** UL     | **V8** pin **4** (∥ BRN) | ☐   |
| BLK  | **RIGHT COM** | G             | RT speaker **G** post    | ☐   |
| BLU  | **RIGHT 4Ω**  | 4 Ω           | RT **4 Ω** post          | ☐   |
| BRN  | **RIGHT 8Ω**  | 8 Ω           | RT **8 Ω** post          | ☐   |

Panel tees (**G** → preamp **GND**, **8 Ω** → **PRP** NFB): [`back-panel.md`](back-panel.md).

---

## Related

- [`tubes.md`](tubes.md) — **V3/V4/V7/V8** designators, mirror vs push-pull pairs
- [`8-pin-chassis.md`](8-pin-chassis.md) — socket pin map, **C3**, heaters
- [`back-panel.md`](back-panel.md) — speaker posts, **G** / **8 Ω** tees
- [`large-cap-board.md`](large-cap-board.md) — **C3** +B feeds to OT **RED** CT
- [`preamp-board.md`](preamp-board.md) — NFB, **G** → pour
- [`PT.md`](PT.md) — power transformer (separate unit)
- [`labels.md`](labels.md) — heat-shrink label text
- [`../archive/ot-bench-notes.md`](../archive/ot-bench-notes.md) — DCR matrix (identify colors only)
- [`../archive/wire-tags.md`](../archive/wire-tags.md) — disassembly tag index
- [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) — factory **T1** pinout

## Changelog

| Date       | Change                                                                                                |
| ---------- | ----------------------------------------------------------------------------------------------------- |
| 2026-07-21 | Bench verification section — cold DCR; no standalone OT mains test                                    |
| 2026-07-20 | P-touch labels **+B LEFT/RIGHT**, **Vn PIN 3/4**, **LEFT/RIGHT COM/4Ω/8Ω** — [`labels.md`](labels.md) |
| 2026-07-20 | Primary landing by tube: **V3/V7** **ORG+YEL**, **V4/V8** **BRN+WHT**; worksheets per OT              |
| 2026-07-18 | Connection-first layout; DCR moved to archive; fixed secondary map; link [`tubes.md`](tubes.md)       |
