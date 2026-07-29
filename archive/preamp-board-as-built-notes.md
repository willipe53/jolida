<!-- Archived snapshot of docs/preamp-board.md before reconnect-sheet cleanup (2026-07-15). Historical observation / tagging notes. Live rebuild sheet: docs/preamp-board.md. -->

# ARCHIVE — preamp-board-as-built-notes

**Do not use this file to rebuild.** See [`../docs/preamp-board.md`](../docs/preamp-board.md) for the live reconnect sheet.

---

**Unit:** Jolida SJ202A / JD202 (serial 2021-siah)  
**Rev:** as-built-0 · 2026-07-12 (first pass — many values still **Low** / meter TBD)  
**Authority:** [`SOURCES.md`](SOURCES.md) — empirical first

## Critical: silk ≠ factory PDF

This board’s **silkscreen designators** (e.g. **R13**, **RV2**) are **not** guaranteed to match factory PDF refs of the same name. Example: PCB silk **R13 / R13′** labels the large **white ceramic** parts on the left edge; PDF **R13** is a **1 kΩ** EL34 grid stopper on the **8-pin chassis**. Treat PDF as topology only until each silk is buzzed and metered.

## Confidence scale

| Conf.    | Meaning                                                                                         |
| -------- | ----------------------------------------------------------------------------------------------- |
| **High** | Silk readable in photo **and** body/value confirmed, or role confirmed by continuity / OI close |
| **Med**  | Silk or type clear; value from band read / PDF guess — needs meter                              |
| **Low**  | Location or role inferred; conflicting evidence; or PDF-only                                    |

When confidence is **Med** or **Low**, prefer a bench measurement over ordering parts from the PDF alone.

## Files

| File                                                                                                                 | Purpose                                        |
| -------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------- |
| [`../photos/preamp board top.png`](../photos/preamp%20board%20top.png)                                               | Component side — silk + tubes                  |
| [`../photos/preamp board top center.png`](../photos/preamp%20board%20top%20center.png)                               | Close-up silk (**R**, **RV**, **J**, **L IN**) |
| [`../photos/preamp board top center pre desolder.png`](../photos/preamp%20board%20top%20center%20pre%20desolder.png) | Close-up before full strip                     |
| [`../photos/preamp board top before desolder.png`](../photos/preamp%20board%20top%20before%20desolder.png)           | Earlier top / wire tags                        |
| [`../photos/preamp board bottom.png`](../photos/preamp%20board%20bottom.png)                                         | Solder side — film caps, trim pots, ceramics   |
| [`../photos/preamp board top desoldered.png`](../photos/preamp%20board%20top%20desoldered.png)                       | Component side after desolder — bare traces    |
| [`../archive/open-issues.md`](../archive/open-issues.md)                                                             | **OI-7** ceramics · **OI-8** (closed)          |
| [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf)                                                             | Secondary topology (PDF V1/V2 region)          |

---

## Function

Horizontal PCB with **four 9-pin (noval) sockets** (12AX7 ×2, 12AT7 ×2) and **four clearance holes** for EL34s that mount on the **8-pin chassis** (not on this board). Dual channel — silk often uses primes (**R14′**, **V1′**).

| Silk / label        | Role (best guess)                                 | Conf. |
| ------------------- | ------------------------------------------------- | ----- |
| Noval sockets       | **12AX7A** input + **12AT7** driver (×2 channels) | High  |
| **V3 / V4** cutouts | Clearance for EL34s on chassis (PTP)              | High  |
| **L IN** / **GND**  | Line input from **C6** / volume path              | High  |
| **−B** / **B−**     | Bias supply entry (**9 BLU**, C2) → bias network  | High  |
| **GND** pour        | Preamp ground → chassis star (**PT tag-9 BLK**)   | High  |

Rails into this board via [**C2**](#harness-c2--large-cap-board--preamp-board-hardwire-this-doc-owns-it): **+B1**, **+B2**, **−B1** (bias), **GND**. Heater **WHT/WHT** (tag **5**) and **PT-L5 GND** arrive **direct from the PT**.

---

## Silk inventory (component side)

Observed labels on [`preamp board top.png`](../photos/preamp%20board%20top.png) / center close-ups:

| Silk                      | What it marks                             | Conf.                                |
| ------------------------- | ----------------------------------------- | ------------------------------------ |
| **R1–R15** (+ primes)     | Blue axial resistors                      | High (label); **Med/Low** (value)    |
| **R13 / R13′**            | **White ceramic** blocks, left edge       | High (silk + body)                   |
| **C2, C3, C4, C6**        | Cap footprints (some empty)               | High (silk); **Low** (stuffed value) |
| **RV2, RV3**              | 3-pin pot footprints (often empty on top) | High (silk); **Low** (PDF map)       |
| **J1–J9**                 | Wire jumpers / links                      | High                                 |
| **V1′, V3, V4**           | Tube / cutout labels                      | High                                 |
| **L IN**, **GND**, **−B** | Pad legends                               | High                                 |

---

## As-built BOM (this chassis)

### Tubes / sockets

| Silk / location       | Observed                     | PDF hint                  | Conf. | Notes                                                              |
| --------------------- | ---------------------------- | ------------------------- | ----- | ------------------------------------------------------------------ |
| Noval ×4              | White ceramic 9-pin sockets  | V1/V5 12AX7 · V2/V6 12AT7 | High  | Which socket is AX7 vs AT7 — **Med** (trace heaters / plate loads) |
| **V3 / V4** (cutouts) | Large holes, no octal on PCB | EL34 clearance            | High  | Sockets on **8-pin chassis**                                       |

### White ceramic power resistors (left edge) — OI-8 closed

**Closed 2026-07-12 (owner decision):** all four white ceramics were **left soldered in place**, so the circuit is as-factory and no identification or ordering is needed. Documented under the factory PDF designators: **R17 / R18** (×2 channels) — the **1 Ω cathode-sense resistors**, one per EL34, consistent with their placement at the four EL34 clearance cutouts. Each EL34's cathode (pin 8) returns to GND through one of these; bias is read as ~**40 mV** across it (via the pin-8 sense wires at Large Cap Board **TP1** — [`8-pin-chassis.md`](8-pin-chassis.md)).

| Silk                      | Part (factory PDF)                   | Status                        | Conf.                |
| ------------------------- | ------------------------------------ | ----------------------------- | -------------------- |
| **R13 / R13′** + 2 primed | **R17 / R18** ×2 — 1 Ω cathode sense | **In place — do not disturb** | High (owner closure) |

Sanity check before trusting the 40 mV bias reading at Part 6: meter ~**1 Ω** from each octal pin 8 to GND.

### Blue axial resistors — silk → value map (closed 2026-07-12)

**Method:** band reads on [`preamp board top.png`](../photos/preamp%20board%20top.png) / center close-ups, cross-checked against the [metered pile](parts-list.md#desoldered-resistor-pile--metered-inventory-2026-07-12) and PDF **roles** (not PDF designators — silk ≠PDF). Primes (′) match the unprimed channel.

| PCB silk       | Value (install)           | Evidence                                                                | PDF role (name differs)    | Conf.            |
| -------------- | ------------------------- | ----------------------------------------------------------------------- | -------------------------- | ---------------- |
| **R1 / R1′**   | **100 kΩ**                | 5-band brn-blk-blk-org-brn on board                                     | plate / bias-string 100 kΩ | High             |
| **R2 / R2′**   | **10 kΩ**                 | 5-band brn-blk-blk-red-brn on board                                     | **R51**-class 10 kΩ        | High             |
| **R3 / R3′**   | **470 Ω**                 | yel-vio-**brn**-gold on board (black was a misread); pile metered 460 Ω | PDF **R3**                 | High             |
| **R4 / R4′**   | **1.6 MΩ**                | grid-leak position; pile metered **1.6 M** (PDF draws 1 M)              | PDF **R4** (value delta)   | High (meter)     |
| **R5 / R5′**   | **27 kΩ** (~26 k metered) | red-vio-org at silk **R5**; 2 of the six ~26 k pieces                   | PDF **R5**                 | High             |
| **R6 / R6′**   | **15 kΩ**                 | pile matched pair; PDF **R6** role (3 W bodies)                         | PDF **R6**                 | Med              |
| **R7 / R7′**   | **22 kΩ**                 | red-red-org on solder side; pile ×2                                     | PDF **R7** (driver plate)  | Med              |
| **R8 / R8′**   | **24 kΩ**                 | pile ×2; PDF **R8** role                                                | PDF **R8** (driver plate)  | Med              |
| **R9 / R9′**   | **100 kΩ**                | brn-blk-yel-gold at silk **R9**                                         | PDF 100 kΩ family          | High             |
| **R10 / R10′** | **27 kΩ** (~26 k)         | bias −B side; **metered**                                               | bias divider               | **High** (meter) |
| **R11 / R11′** | **27 kΩ** (~26 k)         | bias −B side; **metered**                                               | bias divider               | **High** (meter) |
| **R12 / R12′** | **100 kΩ**                | brn-blk-yel-gold at silk **R12**                                        | PDF 100 kΩ family          | High             |
| **R14 / R14′** | **12 kΩ**                 | bias GND side; **metered**                                              | bias divider               | **High** (meter) |
| **R15 / R15′** | **12 kΩ**                 | bias GND side; **metered**                                              | bias divider               | **High** (meter) |

**R13 / R13′** = white ceramics left in place (**R17/R18** 1 Ω cathode sense) — not blue axials.

#### What this teaches

1. **Silk names are not PDF names.** PCB **R1 = 100 kΩ** while PDF **R1 = 1 kΩ**. PCB **R2 = 10 kΩ** while PDF **R2 = 1 kΩ**. Putting “PDF R1” into silk pad R1 would be wrong.
2. **The values still appear in the PDF BOM** under **other** refs. Same product family, **remapped silk**, not a different circuit.
3. **Do not shop the PDF by designator for this board.** Use the table above.
4. **R6 / R7 / R8** are **Med** — values from the pile + PDF role; some sit on the solder side. Confirm body bands when stuffing if a piece is ambiguous.
5. Extra **10 kΩ ×2** in the pile (the pair that still carried the **C51** discs) are the PDF **R51 ∥ C51** network — not a second silk-R2; pad sites logged under OI-7.

**Desoldered pile metered (2026-07-12):** full inventory in [`parts-list.md`](parts-list.md#desoldered-resistor-pile--metered-inventory-2026-07-12).

### Capacitors

| Location / silk     | Observed                                         | PDF hint                           | Conf.        | Notes                                                                                                                                                           |
| ------------------- | ------------------------------------------------ | ---------------------------------- | ------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Large green film ×N | Dark green rectangular film, solder / top side   | **C3/C4** 0.22 µF / 630 V coupling | Med          | Confirm marking (**224** / **224J**)                                                                                                                            |
| Blue film (CBB)     | Blue rectangular, **CBB 400V** visible on bottom | **C1** 0.47 µF / 400 V (**474J**)  | Med          | Matches Gemini note class                                                                                                                                       |
| Small electrolytics | Silver cans near novals                          | Cathode / local bypass             | **Low**      | Read µF / V on body                                                                                                                                             |
| **C3** silk (empty) | Footprint empty on center close-up               | —                                  | High (empty) | May be optional / desoldered                                                                                                                                    |
| Disc ceramics ×4    | Orange/tan discs; 2 still in corners (bottom)    | **\*C2** 20 pF · **\*C51** 100 pF  | Med          | **OI-7 half closed** — off-board pair rides the two 10 kΩ resistors = **R51 ∥ C51** (×2 channels); corner pair (presumed \*C2) still on board — meter + pad log |

### Potentiometers / trims — EL34 bias trims (confirmed)

**Confirmed by trace reads on the bare board (2026-07-12):** the four trims (silk **RV2 / RV2′ / RV3 / RV3′**, mounted for solder-side / chassis-underside access) are the **per-EL34 bias adjusters** — see [Bias network](#bias-network-el34-fixed-bias) below.

| Silk / location             | Function                     | Conf. | Notes                                         |
| --------------------------- | ---------------------------- | ----- | --------------------------------------------- |
| **RV2 / RV2′ / RV3 / RV3′** | EL34 bias trim, one per tube | High  | Divider element −B ↔ GND; wiper = grid output |

## Bias network (EL34 fixed bias)

The EL34 fixed-bias network lives **on this board**, not on the chassis. Traced on the bare board (2026-07-12) — four identical dividers, one per EL34. Values metered on the desoldered parts (2026-07-12):

```text
−B ──~26 kΩ (R10/R11 family)── [pot ~22 kΩ] ──12 kΩ (R14/R15 family)── GND
                                    │
                                  wiper → grid output → C4 → EL34 pin 5
```

| Pot      | Ground-side resistor (12 kΩ) | −B-side resistor (~26 kΩ) | Wiper output → EL34 |
| -------- | ---------------------------- | ------------------------- | ------------------- |
| **RV2**  | **R14**                      | **R10** (adjacent silk)   | map at Part 5       |
| **RV2′** | **R14′**                     | R10/R11 family            | map at Part 5       |
| **RV3**  | **R15**                      | **R11** (photo read)      | map at Part 5       |
| **RV3′** | **R15′**                     | R10/R11 family            | map at Part 5       |

- **R10 / R11 family**: bands **red-violet-orange** (27 kΩ nominal), **metered ~26 kΩ** — within 5% of nominal. **R14 / R15 family**: **brown-red-orange**, **metered 12 kΩ**. The desoldered pile holds **six** ~26k pieces and **four** 12k: four 26k + all four 12k complete the bias dividers; the remaining **two ~26k are silk R5 / R5′** (PDF R5 signal path).
- Fixed resistors on **both ends** of each element bound the adjustment range (hottest and coldest limits).
- **Coldest (safest) = wiper toward the −B end.** Pre-set all four there before first EL34 power-up.
- **Range math:** 26k + 22k + 12k = 60k string. On **−72 V** (raw −B) the wiper spans ≈ **−14 to −41 V** — correct EL34 territory. On −54 V it would top out at −31 V (too shallow), so the dividers almost certainly hang on the **~−72 V node** — verify the actual rail at the R10/R11 tops before tubes go in.
- The wiper output reaches the EL34 grid through the **C4** harness ([`8-pin-chassis.md`](8-pin-chassis.md)) — which is why C4 wires ride at bias DC.
- Bias is *measured* at Large Cap Board **TP1** (pin-8 sense lines, 40 mV across the 1 Ω R17/R18).

**Fill at Part 5** (only pot → tube mapping remains — trace each wiper to its C4 exit pad):

| Pot      | C4 exit pad | EL34 socket | TP1 pad | R-values metered (expect ~26k / 12k) |
| -------- | ----------- | ----------- | ------- | ------------------------------------ |
| **RV2**  |             |             |         |                                      |
| **RV2′** |             |             |         |                                      |
| **RV3**  |             |             |         |                                      |
| **RV3′** |             |             |         |                                      |

### Jumpers / pads

| Silk                      | Observed           | Conf. |
| ------------------------- | ------------------ | ----- |
| **J1–J9**                 | Wire links stuffed | High  |
| **L IN**, **GND**, **−B** | Pad legends        | High  |

---

## PCB layout (component side — top → bottom of photos)

Orientation: board long axis vertical in photos; **noval sockets on the right**; **white ceramics on the left**; **EL34 cutouts** left-of-center.

| Zone (photo top → bottom) | What’s there                                                                     | Conf. |
| ------------------------- | -------------------------------------------------------------------------------- | ----- |
| Top edge                  | Film caps · wire bundle · **WHT** heaters near bottom of board in other views    | Med   |
| Upper noval + cutout      | Socket · **R\*** cluster · white ceramic **R13** family                          | High  |
| Mid board                 | **J4–J9** · **L IN** / **GND** / **−B** · tag **23** GRN/RED (volume / LED area) | High  |
| Lower novals + cutouts    | Second channel mirror · more **R\*** · ceramics                                  | High  |
| Bottom edge               | **WHT/WHT** heater pair · more film caps                                         | High  |

Solder side ([`preamp board bottom.png`](../photos/preamp%20board%20bottom.png)): film caps, four silver trims, bottom-side blue resistors, ceramic discs, tag **23** GRN/RED.

---

## Harness C2 — Large Cap Board ↔ Preamp Board (hardwire, this doc owns it)

Fully mapped from photo reads on [`preamp board top center pre desolder.png`](../photos/preamp%20board%20top%20center%20pre%20desolder.png) (2026-07-12). Exactly **four wires**, each landing on its matching silk pad:

| Wire       | Net                         | Preamp silk pad | ☐ Soldered | ☐ Metered |
| ---------- | --------------------------- | --------------- | ---------- | --------- |
| **15 RED** | **+B1** (~370 V)            | **+B1**         | ☐          | ☐         |
| **7 YEL**  | **+B2** (~220 V)            | **+B2**         | ☐          | ☐         |
| **9 BLU**  | **−B / −B1** (bias, ~−54 V) | **−B**          | ☐          | ☐         |
| **6 BLK**  | **GND**                     | **GND**         | ☐          | ☐         |

- **C2 carries bias**: the preamp tubes are cathode-biased, but the **EL34 fixed-bias network lives on this board** ([Bias network](#bias-network-el34-fixed-bias)) — −B1 arrives here and reaches the EL34 grids via **C4**.
- **No heaters on C2** — the WHT/WHT pair (tag 5) runs **direct from the PT** to this board's bottom-left edge.
- To bench-test the Large Cap Board alone, unsolder C2 once at this end.

## Other harness pads (preamp end)

| Tag / color    | Net                  | Conf. | Notes                                                                                   |
| -------------- | -------------------- | ----- | --------------------------------------------------------------------------------------- |
| **5** WHT×2    | Heater 6.3 V         | High  | PT → preamp **direct** ([`PT.md`](PT.md))                                               |
| **9** BLK      | Preamp **GND** pour  | High  | PT-L5 → chassis star; **not** the same wire as 9 BLU (tag reuse)                        |
| **23** GRN+RED | Volume pot bundle    | High  | → **C5** ([`front-panel.md`](front-panel.md)); *volume* tag 23, distinct from other 23s |
| LED **GRN**    | Noval socket pin     | Med   | Power LED return — buzz exact pin on bare board ([`front-panel.md`](front-panel.md))    |
| C4 grids ×4    | EL34 grid outputs    | High  | Bias DC + audio → [`8-pin-chassis.md`](8-pin-chassis.md)                                |
| **L IN** / GND | RCA common input net | High  | ← **C6** pins 1–4 tied ([`back-panel.md`](back-panel.md))                               |

---

## PDF reference BOM (topology only — do not build blindly)

One channel (PDF); right channel repeats. Defaults 0.5 W unless noted.

| PDF ref   | PDF value               | Likely on this PCB?                        | Conf. |
| --------- | ----------------------- | ------------------------------------------ | ----- |
| V1        | 12AX7A                  | Yes (noval)                                | High  |
| V2        | 12AT7                   | Yes (noval)                                | High  |
| R2        | 1 kΩ                    | Maybe                                      | Low   |
| R3        | 470 Ω                   | Maybe                                      | Low   |
| R4        | 1 MΩ                    | Maybe                                      | Low   |
| R5        | 27 kΩ (\*)              | Maybe + ceramic                            | Low   |
| R6        | 15 kΩ / 3 W             | Maybe                                      | Low   |
| R7        | 22 kΩ / 2 W             | Maybe (driver plate load)                  | Low   |
| R8        | 24 kΩ / 2 W             | Maybe (driver plate load)                  | Low   |
| R51       | 10 kΩ                   | Maybe                                      | Low   |
| \*C2      | 20 pF / 100 V           | **OI-7**                                   | Low   |
| \*C51     | 100 pF / 1 kV           | **OI-7**                                   | Low   |
| C1        | 0.47 µF / 400 V         | Blue CBB class                             | Med   |
| C3, C4    | 0.22 µF / 630 V         | Green film class                           | Med   |
| R17 / R18 | 1 Ω / 5 W cathode sense | **Yes** — the white ceramics (OI-8 closed) | High  |
| RV2 / RV3 | 22 kΩ bias trim         | **Yes** — the four trims (confirmed)       | High  |

---

## Bench worksheet (fill at Part 5)

Resistor silk → value is in the [map above](#blue-axial-resistors--silk--value-map-closed-2026-07-12). Use this sheet for caps / remaining buzz-outs only.

| Silk / item             | Meter Ω / µF | Body marking | Notes                 | Conf. after | Initials |
| ----------------------- | ------------ | ------------ | --------------------- | ----------- | -------- |
| Green film #1           |              |              | C3/C4?                |             |          |
| Blue CBB                |              |              | C1?                   |             |          |
| Ceramic disc (corner)   |              |              | \*C2 / \*C51          |             |          |
| Bias trims RV2/RV3 (+′) |              |              | pot → C4 → EL34 / TP1 |             |          |

---

## Next steps

- [x] **OI-8:** closed — white ceramics = **R17/R18** (1 Ω cathode sense), left in place
- [x] Bias trims confirmed — four dividers −B ↔ GND, wiper → grid (2026-07-12)
- [x] **−B** silk pad net confirmed — bias entry from C2 (**9 BLU**)
- [ ] **OI-7:** half closed — off-board pair = **C51** on the 10k R51s; meter the two corner discs (presumed \*C2) + log four pad sites
- [x] Meter every blue **R\*** — desoldered pile value-identified 2026-07-12 ([`parts-list.md`](parts-list.md#desoldered-resistor-pile--metered-inventory-2026-07-12))
- [x] Map metered values → silk pads — [table above](#blue-axial-resistors--silk--value-map-closed-2026-07-12) (2026-07-12); R6/R7/R8 Med only
- [ ] Read film-cap bodies (**224** / **474** / voltage)
- [ ] Buzz **which noval** is 12AX7 vs 12AT7 (plate-load / pinout)
- [ ] Buzz LED **GRN** wire to its noval pin
- [ ] Map each bias pot → C4 exit pad → EL34 socket → TP1 pad
- [ ] Build KiCad `preamp.kicad_sch` only after silk↔PDF map stabilizes

---

## Related

- [`large-cap-board.md`](large-cap-board.md) — C2 source (rails **+B1 / +B2 / −B1** into this board)
- [`8-pin-chassis.md`](8-pin-chassis.md) — **C4** grids, pin-8 sense, TP1
- [`front-panel.md`](front-panel.md) — **C5** volume, LED wiring
- [`back-panel.md`](back-panel.md) — **C6** RCA inputs
- [`../archive/open-issues.md`](../archive/open-issues.md) — OI-7 (open), OI-8 (closed)
- [`../archive/schematic-comparison.md`](../archive/schematic-comparison.md) — PDF deltas
