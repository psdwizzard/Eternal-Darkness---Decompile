#!/usr/bin/env python3
"""Retarget one relocation within a split compiler-local ELF constant."""

import re
import struct
import sys
from pathlib import Path


if len(sys.argv) != 9:
    raise SystemExit(
        "usage: retarget_elf_relocation.py OBJECT LOCAL_SYMBOL LOCAL_ADDEND "
        "RETAIL_BASE RETAIL_SYMBOL SIZE RELOCATION_TYPE RETAIL_DOL"
    )

path = Path(sys.argv[1])
local_name = sys.argv[2]
local_addend = int(sys.argv[3], 0)
retail_base = sys.argv[4]
retail_name = sys.argv[5]
value_size = int(sys.argv[6], 0)
relocation_types = {"R_PPC_EMB_SDA21": 109}
relocation_name = sys.argv[7]
if relocation_name not in relocation_types:
    raise SystemExit(f"unsupported relocation type {relocation_name!r}")
relocation_type = relocation_types[relocation_name]
retail_dol = Path(sys.argv[8])
data = bytearray(path.read_bytes())

if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit(f"{path}: expected a big-endian ELF32 object")
if local_addend < 0 or value_size <= 0:
    raise SystemExit("local addend must be nonnegative and size must be positive")


def symbol_address(name: str) -> int:
    match = re.fullmatch(r".*_([0-9A-Fa-f]{8})", name)
    if match is None:
        raise SystemExit(f"invalid addressed retail symbol {name!r}")
    return int(match.group(1), 16)


base_address = symbol_address(retail_base)
retail_address = symbol_address(retail_name)
if retail_address - base_address != local_addend:
    raise SystemExit(
        f"{retail_name} is not {local_addend:#x} bytes after {retail_base}"
    )

section_offset = struct.unpack_from(">I", data, 0x20)[0]
section_size = struct.unpack_from(">H", data, 0x2E)[0]
section_count = struct.unpack_from(">H", data, 0x30)[0]

symtab_header = None
for index in range(section_count):
    header = section_offset + index * section_size
    if struct.unpack_from(">I", data, header + 4)[0] == 2:  # SHT_SYMTAB
        if symtab_header is not None:
            raise SystemExit(f"{path}: expected one symbol table")
        symtab_header = header
if symtab_header is None:
    raise SystemExit(f"{path}: symbol table not found")

symbol_offset = struct.unpack_from(">I", data, symtab_header + 0x10)[0]
symbol_size = struct.unpack_from(">I", data, symtab_header + 0x14)[0]
string_index = struct.unpack_from(">I", data, symtab_header + 0x18)[0]
symbol_entry_size = struct.unpack_from(">I", data, symtab_header + 0x24)[0]
string_header = section_offset + string_index * section_size
string_offset = struct.unpack_from(">I", data, string_header + 0x10)[0]

symbols = {}
for symbol_index, entry in enumerate(
    range(symbol_offset, symbol_offset + symbol_size, symbol_entry_size)
):
    name_offset = struct.unpack_from(">I", data, entry)[0]
    name_start = string_offset + name_offset
    name_end = data.index(0, name_start)
    name = data[name_start:name_end].decode("ascii")
    if name in (local_name, retail_name):
        if name in symbols:
            raise SystemExit(f"{path}: duplicate symbol {name!r}")
        symbols[name] = (symbol_index, entry)

if local_name not in symbols or retail_name not in symbols:
    raise SystemExit(f"{path}: required symbols {local_name!r} and {retail_name!r} not found")

local_index, local_entry = symbols[local_name]
retail_index, retail_entry = symbols[retail_name]
local_value, local_size = struct.unpack_from(">II", data, local_entry + 4)
local_section = struct.unpack_from(">H", data, local_entry + 0x0E)[0]
retail_value = struct.unpack_from(">I", data, retail_entry + 4)[0]
retail_section = struct.unpack_from(">H", data, retail_entry + 0x0E)[0]

if local_section == 0 or local_section >= section_count:
    raise SystemExit(f"{path}: {local_name} has no file-backed section")
if local_addend + value_size > local_size:
    raise SystemExit(f"{path}: requested value is outside {local_name}")
if retail_section != local_section or retail_value != local_value + local_addend:
    raise SystemExit(
        f"{path}: {retail_name} does not identify offset {local_addend:#x} "
        f"within {local_name}"
    )

value_header = section_offset + local_section * section_size
value_section_type = struct.unpack_from(">I", data, value_header + 4)[0]
value_section_offset = struct.unpack_from(">I", data, value_header + 0x10)[0]
value_section_size = struct.unpack_from(">I", data, value_header + 0x14)[0]
value_start = local_value + local_addend
if value_section_type == 8 or value_start + value_size > value_section_size:
    raise SystemExit(f"{path}: requested value has no complete file backing")

dol = retail_dol.read_bytes()
retail_value_bytes = None
segments = [(0x00, 0x48, 0x90, 7), (0x1C, 0x64, 0xAC, 11)]
for off_base, addr_base, size_base, count in segments:
    for index in range(count):
        file_offset = struct.unpack_from(">I", dol, off_base + 4 * index)[0]
        address = struct.unpack_from(">I", dol, addr_base + 4 * index)[0]
        size = struct.unpack_from(">I", dol, size_base + 4 * index)[0]
        if address <= retail_address and retail_address + value_size <= address + size:
            start = file_offset + retail_address - address
            retail_value_bytes = dol[start:start + value_size]
            break
    if retail_value_bytes is not None:
        break
if retail_value_bytes is None:
    raise SystemExit(f"{retail_dol}: address {retail_address:#x} is not file-backed")

local_value_bytes = data[
    value_section_offset + value_start:value_section_offset + value_start + value_size
]
if local_value_bytes != retail_value_bytes:
    raise SystemExit(
        f"{path}: value {local_value_bytes.hex()} does not match {retail_name} "
        f"at {retail_address:#x}: {retail_value_bytes.hex()}"
    )

matches = 0
for index in range(section_count):
    header = section_offset + index * section_size
    if struct.unpack_from(">I", data, header + 4)[0] != 4:  # SHT_RELA
        continue
    relocation_offset = struct.unpack_from(">I", data, header + 0x10)[0]
    relocation_size = struct.unpack_from(">I", data, header + 0x14)[0]
    relocation_entry_size = struct.unpack_from(">I", data, header + 0x24)[0] or 12
    for relocation in range(
        relocation_offset,
        relocation_offset + relocation_size,
        relocation_entry_size,
    ):
        info = struct.unpack_from(">I", data, relocation + 4)[0]
        addend = struct.unpack_from(">i", data, relocation + 8)[0]
        if (
            info >> 8 == local_index
            and (info & 0xFF) == relocation_type
            and addend == local_addend
        ):
            struct.pack_into(">I", data, relocation + 4, (retail_index << 8) | (info & 0xFF))
            struct.pack_into(">i", data, relocation + 8, 0)
            matches += 1

if matches != 1:
    raise SystemExit(
        f"{path}: expected one {relocation_name} relocation to "
        f"{local_name}+{local_addend:#x}, found {matches}"
    )

# The added symbol becomes an undefined reference after its bytes and relocation
# have been checked. The original local symbol is externalized separately.
struct.pack_into(">II", data, retail_entry + 4, 0, 0)
struct.pack_into(">H", data, retail_entry + 0x0E, 0)
path.write_bytes(data)
