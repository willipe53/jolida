#!/usr/bin/env python3
"""Reformat GFM markdown tables to MD060 aligned style."""

from __future__ import annotations

import re
import sys
from pathlib import Path


def parse_row(line: str) -> list[str] | None:
    stripped = line.rstrip("\n")
    if not stripped.lstrip().startswith("|"):
        return None
    stripped = stripped.strip()
    inner = stripped[1:]
    if inner.endswith("|"):
        inner = inner[:-1]
    return [cell.strip() for cell in inner.split("|")]


def is_separator_row(cells: list[str]) -> bool:
    for cell in cells:
        compact = re.sub(r"\s", "", cell)
        if not compact:
            continue
        if not re.fullmatch(r":?-+:?", compact):
            return False
    return True


def format_aligned_table(table_lines: list[str]) -> list[str]:
    rows = [parse_row(line) for line in table_lines]
    if any(row is None for row in rows):
        return table_lines
    if len(rows) < 2 or not is_separator_row(rows[1]):
        return table_lines

    ncols = max(len(row) for row in rows)
    for row in rows:
        while len(row) < ncols:
            row.append("")

    widths = [3] * ncols
    for index, row in enumerate(rows):
        if index == 1:
            continue
        for col, cell in enumerate(row):
            widths[col] = max(widths[col], len(cell))

    def format_row(row: list[str], *, delimiter: bool = False) -> str:
        cells: list[str] = []
        for col in range(ncols):
            if delimiter:
                content = "-" * widths[col]
            else:
                content = row[col]
            cells.append(f" {content.ljust(widths[col])} ")
        return "|" + "|".join(cells) + "|"

    return [format_row(row, delimiter=(index == 1)) for index, row in enumerate(rows)]


def format_markdown(text: str) -> str:
    lines = text.splitlines(keepends=True)
    output: list[str] = []
    index = 0

    while index < len(lines):
        line = lines[index]
        if parse_row(line) is None:
            output.append(line)
            index += 1
            continue

        start = index
        while index < len(lines) and parse_row(lines[index]) is not None:
            index += 1

        block = [lines[i].rstrip("\n") for i in range(start, index)]
        formatted = format_aligned_table(block)
        for formatted_line in formatted:
            output.append(formatted_line + "\n")

    return "".join(output)


def main(argv: list[str]) -> int:
    paths = [Path(arg) for arg in argv] if argv else sorted(Path("docs").glob("*.md"))
    paths.extend([Path("README.md")] if not argv else [])

    seen: set[Path] = set()
    for path in paths:
        path = path.resolve()
        if path in seen or not path.is_file():
            continue
        seen.add(path)

        original = path.read_text(encoding="utf-8")
        updated = format_markdown(original)
        if updated != original:
            path.write_text(updated, encoding="utf-8")
            print(path)

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
