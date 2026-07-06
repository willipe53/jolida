# Jolida JD202A — Restoration Notes (empirical / primary)

**Authority:** This document is the **high-confidence** record of parts and decisions derived from **empirical breakdown of this chassis** (photos, measurements, cap markings, cart review). It outranks the randomly sourced factory PDF — see [`SOURCES.md`](SOURCES.md).

Source chat: [Gemini "Tube Amp"](https://gemini.google.com/app/3faab7701e105442) (July 2026)

Formal KiCad/BOM will be synthesized from this + [`../photos/`](../photos/) + [`hand-schematic-notes.md`](hand-schematic-notes.md). Use [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) only as a secondary cross-check.

---

## Project scope

Restoration/recap of a **Jolida JD202A** integrated tube amplifier:

- Replace drift-prone and aged electrolytic capacitors and resistors
- Upgrade rear-panel chassis hardware (AC inlet, fuse, speaker terminals)
- Preserve existing panel cutouts and hole layout
- Work within very tight internal clearance behind the rear panel

Tube complement (factory spec): 4× EL34/6CA7, 2× 12AX7, 2× 12AT7. Ultra-linear Class AB1, ~40 W/ch @ 8 Ω.

---

## Mechanical constraints (critical)

These drove most hardware selection decisions:

| Area                                 | Constraint                                                                          |
| ------------------------------------ | ----------------------------------------------------------------------------------- |
| Speaker terminal internal protrusion | ~**10 mm** max inside panel before hitting transformer/components                   |
| Panel thickness                      | 6 mm total, **counterset to 3 mm** around terminal holes — helps swallow post shank |
| AC inlet cutout                      | **20 × 28 mm** socket hole; **40 mm** screw-center spacing                          |
| Fuse holder total length             | ~**30 mm** cap-to-solder-tab (cap on); standard Schurter/Littelfuse bodies too deep |
| Speaker connections                  | **Spade lugs only** — bananas not required                                          |
| Terminal layout                      | **Six individual holes** (not a barrier strip): L/R × (Common, 4 Ω, 8 Ω)            |

Rejected approaches:

- Combined IEC + EMI filter modules (e.g. Delta 03GEEG3E-R) — too deep (~40–45 mm)
- Standard deep Schurter fuse holders — exceed 30 mm total length
- Plastic or industrial-looking binding posts (Amplified Parts blocks, Pomona, Abbatron, Keystone)
- Barrier terminal strips — wrong aesthetic/layout (need individual holes)

---

## Chassis hardware decisions

### AC power inlet (Mouser — ordered/planned)

| Field  | Value                                                                 |
| ------ | --------------------------------------------------------------------- |
| Mfr    | Schurter **6100.3300**                                                |
| Mouser | **488-6100.3300**                                                     |
| Notes  | IEC C14, screw mount 40 mm spacing, shallow ~23 mm depth behind panel |

### Fuse holder (Amplified Parts — not Mouser)

Standard Mouser Schurter/Littelfuse holders too long for this chassis.

| Field | Value                                                                       |
| ----- | --------------------------------------------------------------------------- |
| SKU   | Amplified Parts **P-H155** (Radiohm/Belton style)                           |
| Notes | Low-profile 5×20 mm bayonet cap; ~29–30 mm total length; 12.7 mm panel hole |

### Speaker binding posts (non-Mouser)

Chose premium **machined brass/copper posts** (CMC-style, side-loading slot for spade/bare wire) from photo review in Gemini chat — not the eBay Cliff-style replacements or industrial Mouser options.

Install notes:

- Discard **all** old Cliff CL2160 hardware (plastic collars, spindles, nuts, washers)
- New posts are self-contained with their own isolation washers (inside + outside)
- Mount from outside, torque inner hex nut, **trim excess rear thread** (Dremel/hacksaw) to stay under 10 mm internal clearance
- Solder transformer tap wires to trimmed stub or solder tab

Old posts identified as **Cliff CL2160** binding posts.

### RCA input jacks (suggested — order status unclear)

From early Gemini recommendations (Amplified Parts):

| Channel           | SKU            | Qty |
| ----------------- | -------------- | --- |
| Right (red band)  | **P-COAX-32X** | 2   |
| Left (white band) | **P-COAX-33X** | 2   |

Use teflon/plastic shoulder washers so barrel never touches chassis metal (hum/ground loop).

---

## Mouser cart review (`Cart_Jul05_1110AM.xls`)

Gemini flagged these items before checkout:

### Confirmed good

| Part                | Mouser P/N          | Qty | Purpose                                                           |
| ------------------- | ------------------- | --- | ----------------------------------------------------------------- |
| Schurter 6100.3300  | 488-6100.3300       | —   | AC inlet                                                          |
| TDK B43231B5187M000 | 871-B43231B5187M000 | 4   | 180 µF / 450 V snap-in (replaces backordered B43231**C**5187M000) |
| PNP300JR-73-2K2     | —                   | —   | 2.2 kΩ, 3 W wirewound (R25)                                       |
| RSF3WSJR-73-68K     | 603-RSF3WSJR-73-68K | 2   | 68 kΩ, 3 W metal oxide (R23, R24 bleeders)                        |

### Action required before submit

| Issue               | Line   | Part                                                        | Problem                        | Recommended fix                                                       |
| ------------------- | ------ | ----------------------------------------------------------- | ------------------------------ | --------------------------------------------------------------------- |
| Wrong bleeder value | —      | **RSF3WSJR-73-47K** (if still in cart)                      | R23/R24 are **68 kΩ** bleeders | Drop **47 kΩ** · order **603-RSF3WSJR-73-68K** ×2 (**3 W**)           |
| Overpriced cap      | 14     | TDK **B43508B5477M000** ×2                                  | ~$25.95 each ($51.90 total)    | Replace with Nichicon LGG or LLS 470 µF / 450 V snap-in (~$8–10 each) |
| Duplicate 22 kΩ     | 6 & 12 | **603-RSF3WMJT-73-22K** ×10 AND **603-RSF3WSJB-FKK22K** ×10 | Two lines for same value       | Drop one line if unintentional duplicate                              |

### Capacitor alternatives discussed (180 µF / 450 V)

If TDK pricing/stock issues persist:

| Mfr              | Part                   | Notes                         |
| ---------------- | ---------------------- | ----------------------------- |
| United Chemi-Con | **EKMM451VSN181MQ35S** | 105 °C, ~$5.50–6.50           |
| Nichicon         | **LGG2W181MELZ35**     | 105 °C ultra-long life, ~$6–7 |

Both use 10 mm snap-in lead spacing; slightly slimmer cans than original 35 mm TDK — verify vertical headroom.

---

## Keep vs replace

### Replace

- Aluminum **electrolytic** capacitors (dry out, leak, drift)
- Carbon/metal-film resistors showing drift (e.g. 47 kΩ called out)
- Rear-panel hardware (AC inlet, fuse holder, speaker posts)
- Cliff CL2160 binding posts

### Keep (unless upgrading for sound)

- Blue **474J CBB 400V** capacitors — metallized **polypropylene film** (0.47 µF, 400 V)
  - CBB = Chinese PP film designation; 474J = 0.47 µF ±5%
  - Do not dry out; very stable unless physically damaged
  - Optional "cap rolling" upgrade only if pursuing boutique voicing (Solen, Mundorf, WIMA, etc.)

---

## Desoldering Cliff CL2160 binding posts

These brass posts are massive heat sinks. Do not treat like a small component.

### Tools

- Solder station **400–420 °C** (750–800 °F) — not a 25 W pencil
- **Wide chisel tip**
- Liquid rosin flux + fresh solder (thermal bridge)
- Heavy-gauge desoldering braid

### Procedure

1. **Mechanical first:** Back off hex nut (FCR7880SA7) a few turns before desoldering transformer wire
2. **Flood joint:** Flux + generous fresh solder on brass stud with chisel tip
3. **Unhook wire quickly:** Under ~5 s contact — heat travels up and melts nylon shoulder washers
4. **Wick remaining solder** from threads
5. **Remove locknut and washers**, push spindle out from front (0508.1701.52)
6. **Extract plastic shoulder collars** — tap/wiggle from inside; interlocking front/back halves

Discard all old tower parts. New machined posts install fresh.

---

## PCB cleaning after desoldering

1. **99% isopropyl alcohol** (not 70% rubbing alcohol) + short stiff nylon brush
2. **Blot while wet** with lint-free wipe or shop towel — do not air-dry (flux resmears)
3. For baked-on flux: **MG Chemicals 4140** or **Chemtronics Flux-Off**, soak 30 s, scrub, blot

---

## As-built power board (empirical — this unit)

From cap bodies, photos, and bench. PDF values shown only where they differ.

| Position    | As-built (confirmed / observed) | PDF (JD202A.s01)        | Notes                              |
| ----------- | ------------------------------- | ----------------------- | ---------------------------------- |
| Top pair    | **470 µF / 450 V** (Chemi-Con)  | C8/C9: 470 µF / 400 V   | Same role; voltage rating OK       |
| Middle pair | **180 µF / 450 V**              | C5/C6: 220 µF / 450 V   | **Owner read cap body 2026-07-05** |
| Other HV    | **220 µF / 200 V** (observed)   | 220 µF / 450 V          | Gemini: 200 V OK for service       |
| Bottom pair | **470 µF / 50 V** (KME)         | C7: 470 µF / 50 V       | Match                              |
| Bias caps   | Green electolytics (TBD)        | C10/C11: 220 µF / 160 V | Read before reinstall              |
| R23/R24     | **~62 kΩ / 2 W** (original)     | 68K / 2 W bleeders      | Rebuild **68 kΩ / 3 W** on order   |

---

## Reference schematic (secondary)

Factory drawing: [`Jolida-JD202A-int-sch.pdf`](Jolida-JD202A-int-sch.pdf) — [audiocircuit.dk/jolida](https://audiocircuit.dk/jolida/)

**Not authoritative for this chassis.** Use for topology hints; defer to table above and photos when values differ. See [`schematic-comparison.md`](schematic-comparison.md).

---

## Next steps (project)

- [x] Photos of board, chassis, component markings → [`../photos/`](../photos/)
- [x] KiCad power board schematic (first pass) → [`docs/power-board.svg`](docs/power-board.svg), [`kicad/power.kicad_sch`](../kicad/power.kicad_sch)
- [ ] Extend as-built BOM (preamp board, chassis)
- [ ] KiCad per-board schematics (preamp, 8-pin chassis)
- [ ] Resolve open issues → [`open-issues.md`](open-issues.md)
