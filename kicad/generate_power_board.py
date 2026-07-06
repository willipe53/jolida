#!/usr/bin/env python3
"""Generate a first-pass KiCad PCB for the Jolida power board (placement RE).

Output: jolida.kicad_pcb — board outline + footprint positions from flat_power.png.
Copper routing is NOT included (reverse-engineering pass 1).
"""

import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parent
OUT = ROOT / "jolida.kicad_pcb"

# Approximate board size (mm) — refine with calipers vs flat_power.png
BOARD_W = 38.0
BOARD_H = 175.0
ORIGIN_X = 10.0
ORIGIN_Y = 10.0

# Component centers (x_mm, y_mm) bottom → top per docs/power-board.md / flat_power.png
# x relative to board center column; y measured from board bottom edge upward
CX = ORIGIN_X + BOARD_W / 2

def y_from_bottom(mm_from_bottom: float) -> float:
    return ORIGIN_Y + BOARD_H - mm_from_bottom


PLACEMENT = [
    ("VD7", "axial", CX, y_from_bottom(8)),
    ("R25", "axial", CX, y_from_bottom(18)),
    ("C11", "elec_sm", CX - 4, y_from_bottom(28)),
    ("C10", "elec_sm", CX + 4, y_from_bottom(28)),
    ("-B", "pad1", CX + 12, y_from_bottom(38)),
    ("C5", "elec_lg", CX, y_from_bottom(50)),
    ("C6", "elec_lg", CX, y_from_bottom(68)),
    ("R21", "power_ww", CX + 10, y_from_bottom(82)),
    ("TP1_V4b", "tp", CX - 10, y_from_bottom(88)),
    ("TP1_V3b", "tp", CX - 10, y_from_bottom(92)),
    ("TP1_GND", "tp", CX - 10, y_from_bottom(96)),
    ("TP1_V3t", "tp", CX - 10, y_from_bottom(100)),
    ("TP1_V4t", "tp", CX - 10, y_from_bottom(104)),
    ("VD6", "axial", CX - 8, y_from_bottom(118)),
    ("VD4", "axial", CX - 3, y_from_bottom(118)),
    ("VD5", "axial", CX + 3, y_from_bottom(118)),
    ("VD3", "axial", CX + 8, y_from_bottom(118)),
    ("AC_IN1", "pad1", CX - 2, y_from_bottom(125)),
    ("AC_IN2", "pad1", CX + 2, y_from_bottom(125)),
    ("C8", "elec_lg", CX - 6, y_from_bottom(142)),
    ("R23", "axial", CX, y_from_bottom(150)),
    ("R24", "axial", CX, y_from_bottom(154)),
    ("C9", "elec_lg", CX + 6, y_from_bottom(142)),
]

MOUNT_HOLES = [
    (ORIGIN_X + 5, ORIGIN_Y + 5),
    (ORIGIN_X + BOARD_W - 5, ORIGIN_Y + 5),
    (ORIGIN_X + 5, ORIGIN_Y + BOARD_H - 5),
    (ORIGIN_X + BOARD_W - 5, ORIGIN_Y + BOARD_H - 5),
]


def uid():
    return str(uuid.uuid4())


def q(s):
    return f'"{s}"'


def fp_axial(ref, x, y, rot=0):
    pitch = 5.08
    return f"""\t(footprint "RE:Axial_2pin"
\t\t(layer "F.Cu")
\t\t(at {x} {y} {rot})
\t\t(uuid {q(uid())})
\t\t(property "Reference" {q(ref)}
\t\t\t(at 0 -3.5 {rot})
\t\t\t(layer "F.SilkS")
\t\t\t(uuid {q(uid())})
\t\t\t(effects (font (size 1 1) (thickness 0.15)))
\t\t)
\t\t(property "Value" {q(ref)}
\t\t\t(at 0 3.5 {rot})
\t\t\t(layer "F.Fab")
\t\t\t(uuid {q(uid())})
\t\t\t(effects (font (size 1 1) (thickness 0.15)))
\t\t)
\t\t(pad "1" thru_hole circle
\t\t\t(at {-pitch/2} 0)
\t\t\t(size 1.8 1.8) (drill 1.0)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t\t(pad "2" thru_hole circle
\t\t\t(at {pitch/2} 0)
\t\t\t(size 1.8 1.8) (drill 1.0)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t)"""


def fp_elec(ref, x, y, size=6.0, drill=1.2):
    return f"""\t(footprint "RE:Elec_2pin"
\t\t(layer "F.Cu")
\t\t(at {x} {y})
\t\t(uuid {q(uid())})
\t\t(property "Reference" {q(ref)}
\t\t\t(at 0 {-size - 2})
\t\t\t(layer "F.SilkS")
\t\t\t(uuid {q(uid())})
\t\t\t(effects (font (size 1 1) (thickness 0.15)))
\t\t)
\t\t(pad "1" thru_hole rect
\t\t\t(at {-size/2} 0)
\t\t\t(size {size} {size*0.6}) (drill {drill})
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t\t(pad "2" thru_hole oval
\t\t\t(at {size/2} 0)
\t\t\t(size {size*0.8} {size*0.5}) (drill {drill})
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t)"""


def fp_power_ww(ref, x, y):
    return f"""\t(footprint "RE:PowerWW_2pin"
\t\t(layer "F.Cu")
\t\t(at {x} {y} 90)
\t\t(uuid {q(uid())})
\t\t(property "Reference" {q(ref)}
\t\t\t(at 0 -6)
\t\t\t(layer "F.SilkS")
\t\t\t(uuid {q(uid())})
\t\t\t(effects (font (size 1 1) (thickness 0.15)))
\t\t)
\t\t(pad "1" thru_hole oval
\t\t\t(at 0 -5)
\t\t\t(size 3.5 2.5) (drill 1.2)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t\t(pad "2" thru_hole oval
\t\t\t(at 0 5)
\t\t\t(size 3.5 2.5) (drill 1.2)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t)"""


def fp_tp(ref, x, y):
    return f"""\t(footprint "RE:TestPoint"
\t\t(layer "F.Cu")
\t\t(at {x} {y})
\t\t(uuid {q(uid())})
\t\t(property "Reference" {q(ref)}
\t\t\t(at 0 -2.5)
\t\t\t(layer "F.SilkS")
\t\t\t(uuid {q(uid())})
\t\t\t(effects (font (size 0.8 0.8) (thickness 0.12)))
\t\t)
\t\t(pad "1" thru_hole circle
\t\t\t(at 0 0)
\t\t\t(size 2.0 2.0) (drill 1.0)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t)"""


def fp_mount(x, y):
    return f"""\t(footprint "RE:Mount_3mm"
\t\t(layer "F.Cu")
\t\t(at {x} {y})
\t\t(uuid {q(uid())})
\t\t(pad "" thru_hole circle
\t\t\t(at 0 0)
\t\t\t(size 6.0 6.0) (drill 3.2)
\t\t\t(layers "*.Cu" "*.Mask")
\t\t\t(uuid {q(uid())})
\t\t)
\t)"""


def make_footprint(ref, kind, x, y):
    if kind == "axial":
        return fp_axial(ref, x, y)
    if kind == "elec_sm":
        return fp_elec(ref, x, y, size=5.0, drill=1.0)
    if kind == "elec_lg":
        return fp_elec(ref, x, y, size=8.0, drill=1.4)
    if kind == "power_ww":
        return fp_power_ww(ref, x, y)
    if kind == "tp":
        return fp_tp(ref, x, y)
    if kind == "pad1":
        return fp_tp(ref, x, y)
    return fp_axial(ref, x, y)


x0, y0 = ORIGIN_X, ORIGIN_Y
x1, y1 = ORIGIN_X + BOARD_W, ORIGIN_Y + BOARD_H

footprints = [make_footprint(ref, kind, x, y) for ref, kind, x, y in PLACEMENT]
footprints += [fp_mount(x, y) for x, y in MOUNT_HOLES]

outline = f"""\t(gr_rect
\t\t(start {x0} {y0}) (end {x1} {y1})
\t\t(stroke (width 0.1) (type default))
\t\t(fill none)
\t\t(layer "Edge.Cuts")
\t\t(uuid {q(uid())})
\t)
\t(gr_text "Jolida power board RE pass 1 - placement from flat_power.png"
\t\t(at {x0 + 2} {y0 + 3} 0)
\t\t(layer "Cmts.User")
\t\t(uuid {q(uid())})
\t\t(effects (font (size 1.2 1.2) (thickness 0.15)))
\t)
\t(gr_text "Copper not routed. Measure board and run generate_power_board.py to refine."
\t\t(at {x0 + 2} {y0 + 6} 0)
\t\t(layer "Cmts.User")
\t\t(uuid {q(uid())})
\t\t(effects (font (size 1 1) (thickness 0.12)))
\t)"""

content = f"""(kicad_pcb
\t(version 20241229)
\t(generator "generate_power_board.py")
\t(generator_version "1.0")
\t(general
\t\t(thickness 1.6)
\t\t(legacy_teardrops no)
\t)
\t(paper "A4")
\t(title_block
\t\t(title "Jolida Power Board")
\t\t(date "2026-07-05")
\t\t(rev "pcb-re-1")
\t\t(company "jolida RE project")
\t\t(comment 1 "Placement from photos/flat_power.png")
\t\t(comment 2 "Unrouted - reverse engineering")
\t)
\t(layers
\t\t(0 "F.Cu" signal)
\t\t(2 "B.Cu" signal)
\t\t(5 "F.SilkS" user "F.Silkscreen")
\t\t(1 "F.Mask" user)
\t\t(3 "B.Mask" user)
\t\t(17 "Dwgs.User" user "User.Drawings")
\t\t(19 "Cmts.User" user "User.Comments")
\t\t(25 "Edge.Cuts" user)
\t\t(31 "F.CrtYd" user "F.Courtyard")
\t)
\t(setup
\t\t(pad_to_mask_clearance 0)
\t\t(allow_soldermask_bridges_in_footprints no)
\t\t(grid_origin {ORIGIN_X} {ORIGIN_Y})
\t)
{outline}

{chr(10).join(footprints)}

\t(embedded_fonts no)
)
"""

OUT.write_text(content)
print(f"Wrote {OUT}")
