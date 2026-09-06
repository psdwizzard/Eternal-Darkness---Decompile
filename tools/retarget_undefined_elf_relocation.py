#!/usr/bin/env python3
"""Retarget one relocation between adjacent undefined ELF symbols."""

import os
import re
import struct
import sys
from pathlib import Path


if len(sys.argv) != 9:
    raise SystemExit(
        "usage: retarget_undefined_elf_relocation.py OBJECT FROM_SYMBOL "
        "FROM_ADDEND TO_SYMBOL TO_ADDRESS TO_ADDEND RELOCATION_TYPE SYMBOLS_FILE"
    )

path = Path(sys.argv[1])
from_name = sys.argv[2]
from_addend = int(sys.argv[3], 0)
to_name = sys.argv[4]
to_address = int(sys.argv[5], 0)
to_addend = int(sys.argv[6], 0)
relocation_types = {"R_PPC_EMB_SDA21": 109}
relocation_name = sys.argv[7]
symbols_path = Path(sys.argv[8])
if relocation_name not in relocation_types:
    raise SystemExit(f"unsupported relocation type {relocation_name!r}")
relocation_type = relocation_types[relocation_name]


def configured_symbol(name: str) -> int:
    pattern = re.compile(
        rf"^{re.escape(name)}\s*=\s*[^:;]+:(0x[0-9A-Fa-f]+)\s*;",
        re.MULTILINE,
    )
    matches = pattern.findall(symbols_path.read_text())
    if len(matches) != 1:
        raise SystemExit(
            f"{symbols_path}: expected one definition of {name!r}, found {len(matches)}"
        )
    return int(matches[0], 16)


if configured_symbol(from_name) + from_addend != to_address + to_addend:
    raise SystemExit("source and destination symbol expressions resolve to different addresses")

original_stat = path.stat()
data = bytearray(path.read_bytes())
if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit(f"{path}: expected a big-endian ELF32 object")

section_offset = struct.unpack_from(">I", data, 0x20)[0]
section_size = struct.unpack_from(">H", data, 0x2E)[0]
section_count = struct.unpack_from(">H", data, 0x30)[0]

symtab_header = None
for index in range(section_count):
    header = section_offset + index * section_size
    if struct.unpack_from(">I", data, header + 4)[0] == 2:
        if symtab_header is not None:
            raise SystemExit(f"{path}: expected one symbol table")
        symtab_header = header
if symtab_header is None:
    raise SystemExit(f"{path}: symbol table not found")

symbol_offset = struct.unpack_from(">I", data, symtab_header + 0x10)[0]
symbol_table_size = struct.unpack_from(">I", data, symtab_header + 0x14)[0]
string_index = struct.unpack_from(">I", data, symtab_header + 0x18)[0]
entry_size = struct.unpack_from(">I", data, symtab_header + 0x24)[0]
string_header = section_offset + string_index * section_size
string_offset = struct.unpack_from(">I", data, string_header + 0x10)[0]

symbols = {}
for symbol_index, entry in enumerate(
    range(symbol_offset, symbol_offset + symbol_table_size, entry_size)
):
    name_offset = struct.unpack_from(">I", data, entry)[0]
    name_start = string_offset + name_offset
    name_end = data.index(0, name_start)
    name = data[name_start:name_end].decode("ascii")
    if name in (from_name, to_name):
        if name in symbols:
            raise SystemExit(f"{path}: duplicate symbol {name!r}")
        symbols[name] = (symbol_index, entry)

if set(symbols) != {from_name, to_name}:
    raise SystemExit(f"{path}: required symbols {from_name!r} and {to_name!r} not found")

from_entry = symbols[from_name][1]
from_value, from_size = struct.unpack_from(">II", data, from_entry + 4)
from_section = struct.unpack_from(">H", data, from_entry + 0x0E)[0]
if from_value != 0 or from_size != 0 or from_section != 0:
    raise SystemExit(f"{path}: {from_name} must be an undefined zero-valued symbol")

to_entry = symbols[to_name][1]
to_value, to_size = struct.unpack_from(">II", data, to_entry + 4)
to_section = struct.unpack_from(">H", data, to_entry + 0x0E)[0]
if to_value != 0 or to_size != 0 or to_section >= section_count:
    raise SystemExit(f"{path}: {to_name} must be a zero-valued symbol")

from_index = symbols[from_name][0]
to_index = symbols[to_name][0]
source_matches = 0
destination_matches = 0
for index in range(section_count):
    header = section_offset + index * section_size
    if struct.unpack_from(">I", data, header + 4)[0] != 4:
        continue
    relocation_offset = struct.unpack_from(">I", data, header + 0x10)[0]
    relocation_size = struct.unpack_from(">I", data, header + 0x14)[0]
    relocation_entry_size = struct.unpack_from(">I", data, header + 0x24)[0] or 12
    for relocation in range(
        relocation_offset, relocation_offset + relocation_size, relocation_entry_size
    ):
        info = struct.unpack_from(">I", data, relocation + 4)[0]
        addend = struct.unpack_from(">i", data, relocation + 8)[0]
        if info >> 8 == from_index and info & 0xFF == relocation_type and addend == from_addend:
            struct.pack_into(">I", data, relocation + 4, (to_index << 8) | relocation_type)
            struct.pack_into(">i", data, relocation + 8, to_addend)
            source_matches += 1
        elif info >> 8 == to_index and info & 0xFF == relocation_type and addend == to_addend:
            destination_matches += 1

if (source_matches, destination_matches) not in ((1, 0), (0, 1)):
    raise SystemExit(
        f"{path}: expected exactly one pre- or post-retarget {relocation_name} "
        f"relocation, found source={source_matches} destination={destination_matches}"
    )

# The objcopy-added marker exists only to allocate a symbol-table entry. Make
# it an undefined reference after the exact relocation has been retargeted.
if to_section != 0:
    struct.pack_into(">H", data, to_entry + 0x0E, 0)
if source_matches == 1 or to_section != 0:
    path.write_bytes(data)
    os.utime(path, ns=(original_stat.st_atime_ns, original_stat.st_mtime_ns))
