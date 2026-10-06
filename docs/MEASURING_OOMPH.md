# Measuring oomph

Force for the DAC input solenoids, at the gap the plunger will have once it is mounted. Holding force with the plunger already seated is the easiest point in the stroke and is the wrong number to use.

A finger pushes back with a few newtons and stops the plunger short of the end of the stroke. A front-panel button is usually under 3 N (about 300 g) and moves a fraction of a millimeter.

## Button force

Set a kitchen scale on the bench and press the DAC button with a pencil eraser on the scale. The reading at the click is the required force, in grams.

## Solenoid force

Measure the coil resistance with the coil unpowered. Current at a given voltage is `I = V / R`.

Fix the solenoid at the same gap it will have in the housing, pointed at the scale, and pulse it. The scale reading is the available force at that gap.

At one fixed gap, force tracks current squared until the iron saturates:

```text
F_new / F_now ≈ (V_new / V_now)²
```

A coil that manages 150 g at 5 V is in the neighborhood of 600 g at 10 V, at that same gap. Past saturation the curve flattens and more voltage mostly makes heat.

If the label says 12 V and the rail is 5 V, the force ratio is `(5/12)²`, about one sixth of the force at the labeled voltage.

## What changes the force

**Gap.** Force collapses as the plunger starts farther out, and it rises sharply in the last couple of millimeters. Mount the solenoid so the button is touched near the end of the stroke, with the plunger square on the button cap.

**Voltage.** This is the electrical control, and only for the length of the pulse. The coil supply can move without touching the D1 Mini. Keep the pulse near a tenth of a second. Average heat is `V² / R` times the fraction of time the coil is on, which for a tap every few seconds is small even above the printed voltage. The limit is the energy in that one pulse. Twice the labeled voltage for a tenth of a second is a normal intermittent overdrive. The 1000 µF capacitor has to be rated above the coil-supply voltage.

**Pulse-width modulation.** If the tap is too strong, PWM during that tenth of a second reduces force, again roughly with the square of the duty. Lengthening the pulse does not add force once the plunger has finished moving. It only heats the coil.
