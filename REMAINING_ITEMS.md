# Remaining items

Active checklist for finishing the Jolida SJ202A / JD202 rebuild. The full step-by-step rebuild plan (Parts 1–6, prep, mount order) is preserved in [`README.md`](README.md).

Pinouts, harness maps, and component detail: [`docs/`](docs/) — start with [`docs/tubes.md`](docs/tubes.md) and [`docs/parts-list.md`](docs/parts-list.md).

---

## Safety — discharge check

Repeat before any work on the Large Cap Board or 8-pin chassis, and whenever the amp has been powered:

| Task                                        | Success criteria                                                                                                                                                                                         |
| ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Safety — discharge check** on all HV caps | Meter each cap terminal → GND reads **≤ 5 V DC**. If any cap reads > 10 V, short across a **10 kΩ / 5 W** resistor for 30 s and re-check. See [Cap-discharge procedure](#cap-discharge-procedure) below. |

---

## Cap-discharge procedure

Repeat **every time** the amp has been powered, before touching any wire on the Large Cap Board or 8-pin chassis:

1. Unplug mains. Wait 60 s.
2. With one hand behind your back, meter **DC voltage** across each big cap (**C5**, **C6**, **C8**, **C9**) — probe (+) to cap (+), probe (−) to cap (−) or chassis GND.
3. If any cap reads > 25 V, discharge via **10 kΩ / 5 W resistor** clipped across the terminals for 30 s (do **not** short with a screwdriver — that spot-welds the cap and pits the plates).
4. Re-meter until all caps read ≤ 5 V. Only then start work.
5. Verify **bleeder time constant** — with **68 kΩ ∥ 68 kΩ = 34 kΩ** across **C8 + C9** series (≈ 235 µF equivalent), τ ≈ 8 s. Powered-off caps should drop from ~425 V to ~5 V in **~30 s** (about 4τ). If discharge takes minutes, **R23 or R24 is open** — do not proceed.

---

## Bias trim cold preset (Bourns 3296)

**C2** live, **all tubes out** — repeat before installing EL34s in [Part 6](#part-6--power-up).

All four dividers: lug **A** (top pin on the pot body) → **−B**, lug **B** → **GND**, **pin 2** = wiper → **C4** → EL34 grid. **Left channel (LFT):** **RV2** and **RV3** on the solder side (chassis underside). **Right channel (RT):** **RV2′** and **RV3′** are the **mirror** half of the PCB — same **A/B/wiper** wiring, but the pots sit **upside-down** vs **RV2/RV3** for access. That flip does **not** change the preset rule: **A** is still **−B**, and turning the screw **counterclockwise** still moves the wiper toward **A**.

**Procedure (each pot, tubes out, C2 live):**

1. Meter **DC V** between **wiper (pin 2 / C)** and **−B (A)**.
2. Turn the screw **CCW** until **0 V** (or minimum Ω wiper↔**A**).
3. On **RV2** (2026-07-21 bench check): **CW** raises wiper↔**A** resistance; **CCW** lowers it — use that on **RV3**, **RV2′**, and **RV3′** as well (same screw sense; mirror mount only changes which way the body faces, not CW vs CCW).

Detail: [`docs/preamp-board.md`](docs/preamp-board.md#bias-network-el34-fixed-bias).

---

## Part 6 — Power up

Full integration — tubes in, music out. **Tubes go in staged, not all at once.**

### EL34 safety gate — pass before any EL34 goes in

A missing bias wire means plate runaway. With **C2 / C3 / C4** connected and **all tubes out**:

| Check        | Pass                                                                                                                                                    |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Bias present | **−40 to −54 V DC** at **all four** octal **pin 5** (grid) circuits — through C2 → preamp bias network → C4                                             |
| Pots pre-set | Re-check **RV2**, **RV3**, **RV2′**, **RV3′**: **wiper ↔ −B (A)** → **0 V** (**CCW** — see [Bias trim cold preset](#bias-trim-cold-preset-bourns-3296)) |
| Sense sanity | ~**1 Ω** from each octal **pin 8** to GND (through R17/R18) — required before trusting the 40 mV bias readings                                          |
| +B at CTs    | +B present at both OT center taps (re-verify)                                                                                                           |

### Staged power-up

| Step             | Work                                                                                                                       |
| ---------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Preamp tubes     | Install 12AX7 ×2 + 12AT7 ×2 only; power on bulb limiter; verify heaters, rails, no smoke                                   |
| EL34s, channel 1 | Two EL34s (one channel) on the **bulb limiter**; set bias at TP1 (~**40 mV** across the 1 Ω sense per tube)                |
| EL34s, channel 2 | Repeat for the other channel                                                                                               |
| Full mains       | Off the limiter; connect speakers on **4 Ω** or **8 Ω** taps, all harnesses connected, RCA input                           |
| Bias final       | Re-set all four trims warm — trims are on the **preamp board solder side** (chassis underside access), measured at **TP1** |
| Signal           | Line in → both channels; check hum with shorted input                                                                      |

**Part 6 gate:** clean audio both channels.
