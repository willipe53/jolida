# Preamp Board

**Unit:** Jolida SJ202A / JD202  
**Photos:** [`preamp board top.png`](../photos/preamp%20board%20top.png) · [`preamp board top center.png`](../photos/preamp%20board%20top%20center.png) · [`preamp board bottom.png`](../photos/preamp%20board%20bottom.png) · [`preamp board top desoldered.png`](../photos/preamp%20board%20top%20desoldered.png)

Four noval sockets (12AX7 ×2, 12AT7 ×2) + EL34 clearance holes (sockets on [`8-pin-chassis.md`](8-pin-chassis.md)). Tube designators **V1–V8**: [`tubes.md`](tubes.md). Dual channel — primes (**′**) = second channel.

**Silk ≠ PDF.** PCB designators do **not** match factory PDF refs of the same name. Example: PCB silk **R13** = EL34 **pin 5** grid landing (**C4** net); silk **R16** = pins **1**+**8** / **1 Ω** cathode sense — PDF **R13** / **R16** are the **1 kΩ** grid stopper **bodies** on the **8-pin chassis**. Stuff by the tables below, not by shopping the PDF.

Historical observation notes: [`../archive/preamp-board-as-built-notes.md`](../archive/preamp-board-as-built-notes.md).

---

## Rebuild convention — PCB parts on top

**This rebuild:** install all **R1–R15** metal-film parts on the **component side (top)** for readability. The factory often put **R6 / R7 / R8** (and some caps/trims) on the **solder side** — that was clearance / habit, not a requirement. **Bias trims (RV2–RV3)** stay on the **solder side** (chassis-underside access). **Socket-pin** parts (**R51**, grid stoppers) are **not** on the PCB — see [`parts-list.md`](parts-list.md#socket-pin-parts) and [`tubes.md`](tubes.md#parts-soldered-at-socket-pins).

---

## EL34 cathode sense (PDF **R17 / R18**)

**Replace** all four **1 Ω / 5 W** parts at rebuild — do not keep the factory white ceramics as “good enough.” Full tube map, silk naming, and wiring: [`tubes.md`](tubes.md#el34-cathode-sense-pdf-r17--r18).

Sanity check before **TP1** bias readings: ~**1 Ω** from each octal **pin 8** → **GND** (through the new sense resistor on this board).

---

## Installed (new metal film)

| PCB silk       | Install    | Status   | Role           |
| -------------- | ---------- | -------- | -------------- |
| **R1 / R1′**   | **100 kΩ** | in place | Plate / string |
| **R2 / R2′**   | **10 kΩ**  | in place | Signal         |
| **R3 / R3′**   | **470 Ω**  | in place |                |
| **R4 / R4′**   | **1 MΩ**   | in place | Grid leak      |
| **R5 / R5′**   | **27 kΩ**  | in place | Global NFB     |
| **R6 / R6′**   | **15 kΩ**  | in place | Plate load     |
| **R7 / R7′**   | **22 kΩ**  | in place | Driver plate   |
| **R8 / R8′**   | **24 kΩ**  | in place | Driver plate   |
| **R9 / R9′**   | **100 kΩ** | in place |                |
| **R10 / R10′** | **27 kΩ**  | in place | Bias −B side   |
| **R11 / R11′** | **27 kΩ**  | in place | Bias −B side   |
| **R12 / R12′** | **100 kΩ** | in place |                |
| **R14 / R14′** | **12 kΩ**  | in place | Bias GND side  |
| **R15 / R15′** | **12 kΩ**  | in place | Bias GND side  |

---

## Installed (bias trims)

| Silk                        | Part                         | Status   | Notes                                                                                                             |
| --------------------------- | ---------------------------- | -------- | ----------------------------------------------------------------------------------------------------------------- |
| **RV2 / RV2′ / RV3 / RV3′** | **Bourns 3296** (~22 kΩ PDF) | in place | **A** (top lug) → **−B**, **B** → GND, **pin 2** wiper; solder side — **RV2′/RV3′** mirror-mounted vs **RV2/RV3** |

---

## Installed (factory **C1** — blue film)

| Part (PDF) | Value               | Status   | Notes                                                                      |
| ---------- | ------------------- | -------- | -------------------------------------------------------------------------- |
| **C1**     | **0.47 µF / 400 V** | in place | Blue **CBB** caps **left in place** — [`tubes.md`](tubes.md#preamp-c1-pdf) |

---

## Installed (coupling film — PDF **C3** / **C4**)

| Part (PDF)                | Value                           | Status   | Notes                                       |
| ------------------------- | ------------------------------- | -------- | ------------------------------------------- |
| **C3**, **C4** (+ primes) | **0.22 µF / 600–630 V** × **4** | in place | **Orange Drop 716P** replaced factory green |

---

## Resistors to install (new metal film)

All **PCB silk R1–R15** are **in place** (see [Installed](#installed-new-metal-film)).

**PDF-only, socket-pin mount:** **R51 + \*C51 in series** ×2 (12AX7 plate→cathode: **V1 pins 6 ↔ 8**, **V5 pins 1 ↔ 3**) and **RF1 / RF2** heater refs (**1 kΩ**: **V1 pin 4 → GND**, **V5 pin 9 → GND**) — see [`tubes.md`](tubes.md#parts-soldered-at-socket-pins) · [`parts-list.md`](parts-list.md#socket-pin-parts). All four desoldered parts on hand; reuse OK.

---

## Capacitors to install

| Part        | Value                | Notes                                                    |
| ----------- | -------------------- | -------------------------------------------------------- |
| **\*C2** ×2 | **20 pF** (presumed) | NFB — in parallel with **R5 / R5′**; corner discs (OI-7) |

Factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)): preamp caps are **C1**, **C3/C4**, **\*C2**, and **\*C51** (with **R51**) only — no noval cathode-bypass electrolytics. All **µF-class electrolytics** are on the power supply (**C5–C11**). Archive “silver cans near novals” was **Low** confidence and matches **bias trim pots** on [`preamp board bottom.png`](../photos/preamp%20board%20bottom.png), not missing parts.

---

## Bias network (EL34 fixed bias)

Lives **on this board**. Four identical dividers:

```text
−B ── 27 kΩ (R10/R11) ── [RV ~22 kΩ] ── 12 kΩ (R14/R15) ── GND
                              │
                            wiper → C4 → EL34 pin 5
```

| Pot      | GND-side (12 kΩ) | −B-side (27 kΩ) | → EL34 (map at rebuild) |
| -------- | ---------------- | --------------- | ----------------------- |
| **RV2**  | **R14**          | **R10**         |                         |
| **RV2′** | **R14′**         | R10/R11 family  |                         |
| **RV3**  | **R15**          | **R11**         |                         |
| **RV3′** | **R15′**         | R10/R11 family  |                         |

- **Coldest (safest)** = wiper toward **−B** (lug **A**, top pin on the **3296** body). Pre-set all four before first EL34 power-up.
- **Mounting:** **RV2** / **RV3** (LFT) and **RV2′** / **RV3′** (RT) share the same **A → −B**, **B → GND**, **pin 2** wiper wiring. The primed pair is **mirror-flipped** on the solder side (body upside-down vs LFT) — **A** is still **−B**; screw **CCW** still moves the wiper toward **A**.
- **Cold preset (Part 5 / Part 6 gate):** **C2** live, **all tubes out.** Meter **DC V** between **wiper (pin 2 / C)** and **−B (A)**; turn **CCW** until **0 V** on **RV2**, **RV3**, **RV2′**, and **RV3′**. **Bench check on RV2 (2026-07-21):** **CCW** → lower Ω wiper↔**A**; **CW** → higher Ω.
- Measure running bias at Large Cap Board **TP1** (~40 mV across 1 Ω sense) after EL34s are in.
- Fill pot → C4 pad → socket → TP1 at Part 5 (still open).

---

## Line input (RCA + volume)

Factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)) topology per channel: RCA **center** → input selector → **RW1** (~**100 kΩ** volume) → **R1** (**1 kΩ** series) → **V1(B)** / **V5(B)** grid pin **7** ([`tubes.md`](tubes.md)). Right channel mirrors on the primed half of the PCB.

### This rebuild (harness)

| Path                            | Where it lands                                                                                                                              |
| ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| RCA **centers** ×4 (paralleled) | **C6** → **L IN** pad ([`back-panel.md`](back-panel.md)) — factory selector removed                                                         |
| **Volume pot** (PDF **RW1**)    | **C5** → front panel ([`front-panel.md`](front-panel.md)) — in series on the input net; buzz **L IN** ↔ pot ↔ **V1(B)** pin **7** at Part 5 |
| RCA **shells** (all four)       | **Hardwire** **BLK** shell bus → **Large Cap Board GND pour** (with speaker **G** signal **BLK**) — **not** preamp pad, **not** **C6**      |

Circuit **GND** for line input: RCA **centers** via **C6** → **L IN**; returns (shells + speaker **G** signal **BLK**) → **Large Cap Board GND pour**; preamp **GND** pad via **C2** **6 BLK** + **PT GND** only ([`chassis.md`](chassis.md)).

### PDF vs PCB silk (do not mix refs)

| PDF ref         | PDF value / role          | On this Jolida PCB                                                                                    |
| --------------- | ------------------------- | ----------------------------------------------------------------------------------------------------- |
| **RW1**         | ~**100 kΩ** volume        | Front-panel pot via **C5** (not a silk **RW1**)                                                       |
| **R1**          | **1 kΩ** input series     | **Not** silk **R1** — install **100 kΩ** at **R1 / R1′** (plate / B+ string)                          |
| (input network) | Often **470 Ω** near grid | Silk **R3 / R3′** = **470 Ω** (in place) — likely the input-grid / stopper class part, not PDF **R1** |

Putting PDF **R1** (**1 kΩ**) on silk pad **R1** would be wrong. See [`../archive/preamp-board-as-built-notes.md`](../archive/preamp-board-as-built-notes.md#critical-silk--factory-pdf).

---

## Global negative feedback (NFB)

Factory PDF ([`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)): each channel samples the **8 Ω** speaker binding post and returns that signal to the **12AX7** first-section cathode (**V1(A)** / **V5(A)**, pin **3**) through:

**PCB silk at the board corners:** **LFN** and **RFN** are the **hardwire landing pads** for global NFB from the rear panel — **L**eft / **R**ight **F**eedback **N**etwork (factory abbrev.). Solder the run from each **8 Ω** post here (not at **GND**). Dress **PRP** (as-built); label **LEFT FEEDBACK** / **RIGHT FEEDBACK** ([`labels.md`](labels.md)).

| Silk    | Channel | **8 Ω** post tag | P-touch label      | On-board parts (PDF)                     |
| ------- | ------- | ---------------- | ------------------ | ---------------------------------------- |
| **LFN** | **LFT** | **19**           | **LEFT FEEDBACK**  | **R5′** ∥ **\*C2** → **V1(A)** pin **3** |
| **RFN** | **RT**  | **13**           | **RIGHT FEEDBACK** | **R5** ∥ **\*C2** → **V5(A)** pin **3**  |

Photo: corner pads beside silk **R5 / R5′** and the small **\*C2** discs — [`preamp board top desoldered.png`](../photos/preamp%20board%20top%20desoldered.png).

```text
8 Ω post ── LEFT FEEDBACK / RIGHT FEEDBACK (PRP as-built) ── LFN / RFN ── R5 or R5′ (27 kΩ) ─┬── *C2 (20 pF) ── V1(A)/V5(A) cathode (pin 3)
                                                    └── (R5 and *C2 in parallel)
```

| Channel | 8 Ω post tag | NFB parts (PDF)    | Tube · section      |
| ------- | ------------ | ------------------ | ------------------- |
| **LFT** | **19**       | **R5′** ∥ **\*C2** | **V1(A)** pin **3** |
| **RT**  | **13**       | **R5** ∥ **\*C2**  | **V5(A)** pin **3** |

- **Hardwire only** — not on **C2**, **C4**, **C5**, or **C6**.
- **Do not confuse** with EL34 bias (**C4**) or pin-8 sense (**TP1** / **GRN**).
- Rebuild: **LEFT FEEDBACK** / **RIGHT FEEDBACK** from each **8 Ω** post to **LFN** / **RFN** ( **R5 / \*C2** junction). Buzz before power-up — NFB must **not** read as a dead short to **GND** or **+B**.

Photo: [`../photos/speaker_posts.png`](../photos/speaker_posts.png). Panel end: [`back-panel.md`](back-panel.md).

---

## Speaker **G** ground tie

Factory PDF: the speaker **0 / G** terminal is **both** the OT secondary common **and** the circuit **GND** node (ground symbol at the post).

| Channel | **G** post tag | OT wire                   | Signal-GND wire                                                                                            |
| ------- | -------------- | ------------------------- | ---------------------------------------------------------------------------------------------------------- |
| **LFT** | **1**          | **BLK** from OT (heavier) | **BLK** → **Large Cap Board GND pour** (tag **1** on [`hand_schematic.png`](../photos/hand_schematic.png)) |
| **RT**  | **11**         | **BLK** from OT (heavier) | **BLK** → **Large Cap Board GND pour** (tag **11** — not PT **C1** **11 BLK**)                             |

- Preamp **GND** pour: **PT tag-9 BLK** direct + **C2** **6 BLK** from the **same** large-cap-board pour — **not** extra speaker or RCA wires to the preamp ([`large-cap-board.md`](large-cap-board.md#panel--harness-gnd-pour)).
- **C6** = RCA **centers** only; shells → large-cap-board pour with the **G** signal **BLK** legs ([`back-panel.md`](back-panel.md#signal-ground-at-the-rear-panel)).
- Rebuild: restore **both** black wires at each **G** post. Buzz: OT **BLK** ↔ OT coil only; thinner **BLK** ↔ large-cap-board **GND** pour, **not** OT primary.

Photo: [`../photos/assembled from bottom.png`](../photos/assembled%20from%20bottom.png).

---

## Wire map

### C2 — Large Cap Board → this board (18 AWG)

| Wire | Tag    | Color   | Net              | Silk pad |
| ---- | ------ | ------- | ---------------- | -------- |
| 1    | **15** | **RED** | **+B1** (~370 V) | **+B1**  |
| 2    | **7**  | **YEL** | **+B2** (~220 V) | **+B2**  |
| 3    | **9**  | **BLU** | **−B1** (bias)   | **−B**   |
| 4    | **6**  | **BLK** | **GND**          | **GND**  |

No heaters on C2.

### Direct from PT (not C2)

| Wire    | Tag   | Color     | AWG        | Lands on                                                                                            |
| ------- | ----- | --------- | ---------- | --------------------------------------------------------------------------------------------------- |
| Heater  | **5** | **WHT×2** | 18 twisted | Board bottom-left heater pads — label **PREAMP HEAT**                                               |
| GND ref | **9** | **BLK**   | 18         | Preamp **GND** pour → chassis star — label **PT GND** (**PT-L5**; also tied at speaker **G** posts) |

Tag **9 BLK** ≠ tag **9 BLU** (C2 bias).

### Other harnesses (this board end)

| Harness     | AWG                                     | Function                                                                                    | Detail                                                                                   |
| ----------- | --------------------------------------- | ------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| **C4**      | 22 Micro-Fit 4-pin                      | Bias + audio → EL34 grids (pin 5)                                                           | [`8-pin-chassis.md`](8-pin-chassis.md)                                                   |
| **C5**      | 22 Micro-Fit 6-pin (3 used)             | Volume pot                                                                                  | [`front-panel.md`](front-panel.md)                                                       |
| **C6**      | 22 Micro-Fit 4-pin                      | RCA **centers** (×4 paralleled) → **L IN**                                                  | [`back-panel.md`](back-panel.md)                                                         |
| **RCA GND** | **18 AWG** or **22 AWG** **BLK** (typ.) | Jack **shells** → **Large Cap Board GND pour**                                              | Not on **C6**                                                                            |
| LED         | —                                       | **GRN** / **DK BLU**                                                                        | Hardwire — buzz GRN to noval pin before power-up                                         |
| **NFB**     | 18 AWG (typ.)                           | **LEFT FEEDBACK** / **RIGHT FEEDBACK** ( **PRP** ) from **8 Ω** posts (tags **19**, **13**) | → **LFN** / **RFN** — **R5 / R5′** ∥ **\*C2** — see [NFB](#global-negative-feedback-nfb) |
| **G tie**   | 18 AWG (typ.)                           | **BLK** ×2 from **G** posts (tags **1**, **11**)                                            | → **Large Cap Board GND pour** — see [Speaker G ground tie](#speaker-g-ground-tie)       |

---

## Still open

- [ ] Buzz **LEFT FEEDBACK** / **RIGHT FEEDBACK** from each **8 Ω** post → **LFN** / **RFN** → **R5 / R5′ ∥ \*C2** at the **input-triode cathode** (**V1 pin 3** / **V5 pin 8** — mirrored halves)
- [ ] Buzz each **G** post: OT **BLK** ↔ OT only; thinner **BLK** ↔ **Large Cap Board GND pour** (not OT primary)
- [ ] **OI-7:** meter corner discs (\*C2); **R51 + \*C51 series** pads confirmed (**V1 6↔8**, **V5 1↔3**) — remaining: verify the pours those pins ride to (B+ / V2 grid)
- [ ] Buzz LED **GRN** → noval pin
- [ ] Buzz RCA **shell** bus → **Large Cap Board GND pour** (not a second run to preamp **GND** pad)

---

## Related

- [`tubes.md`](tubes.md) — **V1–V8** designators, (A)/(B) sections, mirror pairs
- [`large-cap-board.md`](large-cap-board.md) · [`8-pin-chassis.md`](8-pin-chassis.md) · [`front-panel.md`](front-panel.md) · [`back-panel.md`](back-panel.md) · [`PT.md`](PT.md)
- [`parts-list.md`](parts-list.md) — stock / orders
- [`../archive/preamp-board-as-built-notes.md`](../archive/preamp-board-as-built-notes.md) — full observation history
- [`../archive/open-issues.md`](../archive/open-issues.md) — OI-7; **R17/R18** replace per [`tubes.md`](tubes.md#el34-cathode-sense-pdf-r17--r18)
