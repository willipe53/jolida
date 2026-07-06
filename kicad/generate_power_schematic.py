#!/usr/bin/env python3
"""Generate KiCad 10 power-board schematic for Jolida SJ202A."""

import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECT = "jolida"
ROOT_UUID = "a1b2c3d4-e5f6-7890-abcd-ef1234567890"


def uid():
    return str(uuid.uuid4())


def q(s):
    return f'"{s}"'


def sym(ref, lib_id, value, x, y, rot=0, extra=None):
    extra = extra or {}
    pins = {"Device:C": 2, "Device:R": 2, "Device:D": 2, "Connector:Conn_01x02": 2, "power:GND": 1}
    pin_uuids = "\n".join(
        f'\t\t(pin {q(str(i))}\n\t\t\t(uuid {q(uid())})\n\t\t)' for i in range(1, pins[lib_id] + 1)
    )
    props = [
        f'\t\t(property "Reference" {q(ref)}\n\t\t\t(at {x} {y - 2.54} 0)\n\t\t\t(effects (font (size 1.27 1.27)))\n\t\t)',
        f'\t\t(property "Value" {q(value)}\n\t\t\t(at {x} {y + 2.54} 0)\n\t\t\t(effects (font (size 1.27 1.27)))\n\t\t)',
        f'\t\t(property "Footprint" ""\n\t\t\t(at {x} {y} 0)\n\t\t\t(effects (font (size 1.27 1.27)) hide)\n\t\t)',
        f'\t\t(property "Datasheet" "~"\n\t\t\t(at {x} {y} 0)\n\t\t\t(effects (font (size 1.27 1.27)) hide)\n\t\t)',
        f'\t\t(property "Description" ""\n\t\t\t(at {x} {y} 0)\n\t\t\t(effects (font (size 1.27 1.27)) hide)\n\t\t)',
    ]
    for k, v in extra.items():
        props.append(
            f'\t\t(property {q(k)} {q(v)}\n\t\t\t(at {x} {y} 0)\n\t\t\t(effects (font (size 1.27 1.27)))\n\t\t)'
        )
    return f"""\t(symbol
\t\t(lib_id {q(lib_id)})
\t\t(at {x} {y} {rot})
\t\t(unit 1)
\t\t(exclude_from_sim no)
\t\t(in_bom yes)
\t\t(on_board yes)
\t\t(dnp no)
\t\t(uuid {q(uid())})
{chr(10).join(props)}
{pin_uuids}
\t\t(instances
\t\t\t(project {q(PROJECT)}
\t\t\t\t(path {q(f"/{ROOT_UUID}")}
\t\t\t\t\t(reference {q(ref)})
\t\t\t\t\t(unit 1)
\t\t\t\t)
\t\t\t)
\t\t)
\t)"""


def wire(x1, y1, x2, y2):
    return f"""\t(wire
\t\t(pts
\t\t\t(xy {x1} {y1}) (xy {x2} {y2})
\t\t)
\t\t(stroke
\t\t\t(width 0)
\t\t\t(type solid)
\t\t)
\t\t(uuid {q(uid())})
\t)"""


def glabel(net, x, y, rot=0):
    return f"""\t(label {q(net)}
\t\t(at {x} {y} {rot})
\t\t(effects
\t\t\t(font (size 1.27 1.27))
\t\t\t(justify left bottom)
\t\t)
\t\t(uuid {q(uid())})
\t)"""


def note(text, x, y):
    return f"""\t(text {q(text)}
\t\t(exclude_from_sim no)
\t\t(at {x} {y} 0)
\t\t(effects
\t\t\t(font (size 1.27 1.27))
\t\t\t(justify left top)
\t\t)
\t\t(uuid {q(uid())})
\t)"""


LIB = """
\t(lib_symbols
\t\t(symbol "Device:C"
\t\t\t(pin_numbers hide)
\t\t\t(pin_names (offset 0.254))
\t\t\t(exclude_from_sim no)
\t\t\t(in_bom yes)
\t\t\t(on_board yes)
\t\t\t(property "Reference" "C"
\t\t\t\t(at 0.635 2.54 0)
\t\t\t\t(effects (font (size 1.27 1.27)) (justify left))
\t\t\t)
\t\t\t(property "Value" "C"
\t\t\t\t(at 0.635 -2.54 0)
\t\t\t\t(effects (font (size 1.27 1.27)) (justify left))
\t\t\t)
\t\t\t(property "Footprint" ""
\t\t\t\t(at 0.9652 -3.81 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Datasheet" "~"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Description" "Capacitor"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(symbol "C_0_1"
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy -2.032 -0.762) (xy 2.032 -0.762))
\t\t\t\t\t(stroke (width 0.508) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy -2.032 0.762) (xy 2.032 0.762))
\t\t\t\t\t(stroke (width 0.508) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t)
\t\t\t(symbol "C_1_1"
\t\t\t\t(pin passive line
\t\t\t\t\t(at 0 3.81 270)
\t\t\t\t\t(length 2.794)
\t\t\t\t\t(name "~" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "1" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t\t(pin passive line
\t\t\t\t\t(at 0 -3.81 90)
\t\t\t\t\t(length 2.794)
\t\t\t\t\t(name "~" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "2" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t)
\t\t\t(embedded_fonts no)
\t\t)
\t\t(symbol "Device:R"
\t\t\t(pin_numbers hide)
\t\t\t(pin_names (offset 0))
\t\t\t(exclude_from_sim no)
\t\t\t(in_bom yes)
\t\t\t(on_board yes)
\t\t\t(property "Reference" "R"
\t\t\t\t(at 2.032 0 90)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Value" "R"
\t\t\t\t(at 0 0 90)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Footprint" ""
\t\t\t\t(at -1.778 0 90)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Datasheet" "~"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Description" "Resistor"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(symbol "R_0_1"
\t\t\t\t(rectangle
\t\t\t\t\t(start -1.016 -2.54)
\t\t\t\t\t(end 1.016 2.54)
\t\t\t\t\t(stroke (width 0.254) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t)
\t\t\t(symbol "R_1_1"
\t\t\t\t(pin passive line
\t\t\t\t\t(at 0 3.81 270)
\t\t\t\t\t(length 1.27)
\t\t\t\t\t(name "~" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "1" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t\t(pin passive line
\t\t\t\t\t(at 0 -3.81 90)
\t\t\t\t\t(length 1.27)
\t\t\t\t\t(name "~" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "2" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t)
\t\t\t(embedded_fonts no)
\t\t)
\t\t(symbol "Device:D"
\t\t\t(pin_numbers hide)
\t\t\t(pin_names (offset 1.016))
\t\t\t(exclude_from_sim no)
\t\t\t(in_bom yes)
\t\t\t(on_board yes)
\t\t\t(property "Reference" "D"
\t\t\t\t(at 0 2.54 0)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Value" "D"
\t\t\t\t(at 0 -2.54 0)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Footprint" ""
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Datasheet" "~"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Description" "Diode"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(symbol "D_0_1"
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy -1.27 1.27) (xy -1.27 -1.27))
\t\t\t\t\t(stroke (width 0.254) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy 1.27 0) (xy -1.27 0))
\t\t\t\t\t(stroke (width 0) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy 1.27 1.27) (xy 1.27 -1.27) (xy -1.27 0) (xy 1.27 1.27))
\t\t\t\t\t(stroke (width 0.254) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t)
\t\t\t(symbol "D_1_1"
\t\t\t\t(pin passive line
\t\t\t\t\t(at -3.81 0 0)
\t\t\t\t\t(length 2.54)
\t\t\t\t\t(name "K" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "1" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t\t(pin passive line
\t\t\t\t\t(at 3.81 0 180)
\t\t\t\t\t(length 2.54)
\t\t\t\t\t(name "A" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "2" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t)
\t\t\t(embedded_fonts no)
\t\t)
\t\t(symbol "Connector:Conn_01x02"
\t\t\t(pin_names
\t\t\t\t(offset 1.016)
\t\t\t\t(hide yes)
\t\t\t)
\t\t\t(exclude_from_sim no)
\t\t\t(in_bom yes)
\t\t\t(on_board yes)
\t\t\t(property "Reference" "J"
\t\t\t\t(at 0 2.54 0)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Value" "Conn_01x02"
\t\t\t\t(at 0 -5.08 0)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Footprint" ""
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Datasheet" "~"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Description" "2-pin connector"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(symbol "Conn_01x02_1_1"
\t\t\t\t(rectangle
\t\t\t\t\t(start -1.27 -2.413)
\t\t\t\t\t(end 1.27 2.413)
\t\t\t\t\t(stroke (width 0.254) (type default))
\t\t\t\t\t(fill (type background))
\t\t\t\t)
\t\t\t\t(pin passive line
\t\t\t\t\t(at -5.08 1.27 0)
\t\t\t\t\t(length 3.81)
\t\t\t\t\t(name "Pin_1" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "1" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t\t(pin passive line
\t\t\t\t\t(at -5.08 -1.27 0)
\t\t\t\t\t(length 3.81)
\t\t\t\t\t(name "Pin_2" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "2" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t)
\t\t\t(embedded_fonts no)
\t\t)
\t\t(symbol "power:GND"
\t\t\t(power)
\t\t\t(pin_names (offset 0))
\t\t\t(exclude_from_sim no)
\t\t\t(in_bom yes)
\t\t\t(on_board yes)
\t\t\t(property "Reference" "#PWR"
\t\t\t\t(at 0 -6.35 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Value" "GND"
\t\t\t\t(at 0 -3.81 0)
\t\t\t\t(effects (font (size 1.27 1.27)))
\t\t\t)
\t\t\t(property "Footprint" ""
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Datasheet" ""
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(property "Description" "Ground"
\t\t\t\t(at 0 0 0)
\t\t\t\t(effects (font (size 1.27 1.27)) hide)
\t\t\t)
\t\t\t(symbol "GND_0_1"
\t\t\t\t(polyline
\t\t\t\t\t(pts (xy 0 0) (xy 0 -1.27) (xy 1.27 -1.27) (xy 0 -2.54) (xy -1.27 -1.27) (xy 0 -1.27))
\t\t\t\t\t(stroke (width 0) (type default))
\t\t\t\t\t(fill (type none))
\t\t\t\t)
\t\t\t)
\t\t\t(symbol "GND_1_1"
\t\t\t\t(pin power_in line
\t\t\t\t\t(at 0 0 270)
\t\t\t\t\t(length 0)
\t\t\t\t\thide
\t\t\t\t\t(name "GND" (effects (font (size 1.27 1.27))))
\t\t\t\t\t(number "1" (effects (font (size 1.27 1.27))))
\t\t\t\t)
\t\t\t)
\t\t\t(embedded_fonts no)
\t\t)
\t)
"""

components = [
    sym("J1", "Connector:Conn_01x02", "T2_HV_AC", 30, 40, extra={"Note": "from T2 HV winding"}),
    sym("VD6", "Device:D", "1N5408", 55, 40, extra={"PCB_pos": "bridge left"}),
    sym("VD4", "Device:D", "1N5408", 70, 40, extra={"PCB_pos": "bridge"}),
    sym("VD5", "Device:D", "1N5408", 85, 40, extra={"PCB_pos": "bridge"}),
    sym("VD3", "Device:D", "1N5408", 100, 40, extra={"PCB_pos": "bridge right"}),
    sym("C8", "Device:C", "470uF/450V", 130, 30, extra={"Note": "Chemi-Con as-built"}),
    sym("C9", "Device:C", "470uF/450V", 130, 55, extra={"Note": "Chemi-Con as-built"}),
    sym("R23", "Device:R", "27R/10W", 155, 30, extra={"Note": "as-built; PDF 68K"}),
    sym("R24", "Device:R", "27R/10W", 155, 55, extra={"Note": "as-built; PDF 68K"}),
    sym("R22", "Device:R", "3.3K/5W", 180, 42, extra={"Note": "PDF only; no silk on flat_power OI-2"}),
    sym("C6", "Device:C", "180uF/450V", 205, 30, extra={"Note": "verified cap body"}),
    sym("R21", "Device:R", "100K/2W", 230, 42, extra={"Note": "silk confirmed; white RX27; value OI-2"}),
    sym("C5", "Device:C", "180uF/450V", 255, 30, extra={"Note": "verified cap body"}),
    sym("C7", "Device:C", "470uF/50V", 255, 55, extra={"Note": "PDF aux rail; not C8/C9 top pair"}),
    sym("#PWR01", "power:GND", "GND", 130, 70),
    sym("J2", "Connector:Conn_01x02", "T2_BIAS_AC", 30, 95, extra={"Note": "T2 50V winding"}),
    sym("VD7", "Device:D", "1N4007", 55, 95),
    sym("C11", "Device:C", "220uF/160V", 80, 95, extra={"Note": "verify green cap"}),
    sym("R25", "Device:R", "2.2K/2W", 105, 95),
    sym("C10", "Device:C", "220uF/160V", 130, 95, extra={"Note": "PCB silk C10"}),
    sym("#PWR02", "power:GND", "GND", 80, 110),
    sym("J_B3", "Connector:Conn_01x02", "OUT_+B3", 180, 120, extra={"WireTag": "23", "Net": "+B3"}),
    sym("J_B1", "Connector:Conn_01x02", "OUT_+B1", 205, 120, extra={"WireTag": "21", "Net": "+B1"}),
    sym("J_B2", "Connector:Conn_01x02", "OUT_+B2", 230, 120, extra={"WireTag": "19", "Net": "+B2"}),
    sym("J_BN1", "Connector:Conn_01x02", "OUT_-B1", 255, 120, extra={"WireTag": "17", "Net": "-B1"}),
    sym("J_GND", "Connector:Conn_01x02", "OUT_GND", 280, 120, extra={"WireTag": "11", "Net": "GND"}),
]

wires = [
    wire(35, 40, 50, 40),
    wire(110, 40, 120, 40),
    wire(120, 40, 120, 30),
    wire(120, 30, 125, 30),
    wire(120, 40, 120, 55),
    wire(120, 55, 125, 55),
    wire(135, 42, 150, 42),
    wire(135, 42, 135, 70),
    wire(135, 52, 150, 52),
    wire(135, 52, 135, 70),
    wire(120, 42, 175, 42),
    wire(185, 42, 200, 42),
    wire(200, 42, 200, 30),
    wire(200, 30, 205, 30),
    wire(200, 42, 225, 42),
    wire(235, 42, 250, 42),
    wire(250, 42, 250, 30),
    wire(250, 30, 255, 30),
    wire(250, 52, 255, 52),
    wire(35, 95, 50, 95),
    wire(60, 95, 75, 95),
    wire(85, 95, 100, 95),
    wire(110, 95, 125, 95),
    wire(85, 95, 85, 110),
    wire(185, 42, 185, 120),
    wire(210, 42, 210, 120),
    wire(235, 42, 235, 120),
    wire(260, 95, 260, 120),
    wire(135, 70, 280, 70),
    wire(280, 70, 280, 117),
]

labels = [
    glabel("+B3", 115, 38),
    glabel("+B1", 195, 40),
    glabel("+B2", 245, 40),
    glabel("-B", 62, 93),
    glabel("-B1", 112, 93),
    glabel("GND", 133, 68),
]

notes = [
    note("Jolida SJ202A / JD202 - Power Board (as-built)", 25, 10),
    note("Empirical BOM from photos + cap markings. PDF cross-check only.", 25, 15),
    note("PCB layout: photos/flat_power.png (bottom to top)", 25, 20),
    note("TP1: V4 V3 GND V3 V4 - probe points near bridge (OI-6)", 25, 25),
    note("See docs/power-board.md", 25, 30),
]

content = f"""(kicad_sch
\t(version 20250114)
\t(generator "eeschema")
\t(generator_version "9.0")
\t(uuid {q(ROOT_UUID)})
\t(paper "A3")
\t(title_block
\t\t(title "Jolida Power Board")
\t\t(date "2026-07-05")
\t\t(rev "as-built-1")
\t\t(company "jolida RE project")
\t\t(comment 1 "SJ202A / JD202 - empirical BOM")
\t\t(comment 2 "See docs/power-board.md")
\t)
{LIB}
{chr(10).join(components)}

{chr(10).join(wires)}

{chr(10).join(labels)}

{chr(10).join(notes)}

\t(sheet_instances
\t\t(path "/"
\t\t\t(page "1")
\t\t)
\t)
\t(embedded_fonts no)
)
"""

for name in ("jolida.kicad_sch", "power.kicad_sch"):
    path = ROOT / name
    path.write_text(content)
    print(f"Wrote {path}")
