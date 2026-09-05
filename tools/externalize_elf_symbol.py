#!/usr/bin/env python3
"""Verify and externalize a defined symbol in a big-endian ELF32 object."""

import re
import struct
import sys
from pathlib import Path

require_whole_section = False
required_section_symbols = None
args = [sys.argv[0]]
for arg in sys.argv[1:]:
    if arg == "--require-whole-section":
        require_whole_section = True
    elif arg.startswith("--require-section-symbols="):
        if required_section_symbols is not None:
            raise SystemExit("--require-section-symbols may be specified only once")
        required_section_symbols = arg.split("=", 1)[1].split(",")
        if not all(required_section_symbols) or len(set(required_section_symbols)) != len(
            required_section_symbols
        ):
            raise SystemExit("--require-section-symbols needs unique symbol names")
    else:
        args.append(arg)
if require_whole_section and required_section_symbols is not None:
    raise SystemExit(
        "--require-whole-section and --require-section-symbols are mutually exclusive"
    )
if len(args) not in (3, 5):
    raise SystemExit(
        f"usage: {sys.argv[0]} OBJECT LOCAL_SYMBOL [RETAIL_SYMBOL RETAIL_DOL] "
        "[--require-whole-section | --require-section-symbols=SYMBOL,...]"
    )
path = Path(args[1])
target = args[2]
retail_target = args[3] if len(args) == 5 else None
retail_dol = Path(args[4]) if retail_target else None
data = bytearray(path.read_bytes())

if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit(f"{path}: expected a big-endian ELF32 object")

section_offset = struct.unpack_from(">I", data, 0x20)[0]
section_size = struct.unpack_from(">H", data, 0x2E)[0]
section_count = struct.unpack_from(">H", data, 0x30)[0]


def has_relocations(section_index, symbol_value, symbol_size):
    """Return whether a relocation applies within this symbol's value."""
    for index in range(section_count):
        header = section_offset + index * section_size
        section_type = struct.unpack_from(">I", data, header + 4)[0]
        target_index = struct.unpack_from(">I", data, header + 0x1C)[0]
        if section_type not in (4, 9) or target_index != section_index:  # RELA/REL
            continue
        relocation_offset = struct.unpack_from(">I", data, header + 0x10)[0]
        relocation_size = struct.unpack_from(">I", data, header + 0x14)[0]
        entry_size = struct.unpack_from(">I", data, header + 0x24)[0]
        if entry_size == 0:
            entry_size = 12 if section_type == 4 else 8
        for relocation in range(
            relocation_offset, relocation_offset + relocation_size, entry_size
        ):
            offset = struct.unpack_from(">I", data, relocation)[0]
            if symbol_value <= offset < symbol_value + symbol_size:
                return True
    return False

for section_index in range(section_count):
    header = section_offset + section_index * section_size
    section_type = struct.unpack_from(">I", data, header + 4)[0]
    if section_type != 2:  # SHT_SYMTAB
        continue

    symbol_offset = struct.unpack_from(">I", data, header + 0x10)[0]
    symbol_table_size = struct.unpack_from(">I", data, header + 0x14)[0]
    string_index = struct.unpack_from(">I", data, header + 0x18)[0]
    entry_size = struct.unpack_from(">I", data, header + 0x24)[0]
    string_header = section_offset + string_index * section_size
    string_offset = struct.unpack_from(">I", data, string_header + 0x10)[0]

    for entry in range(symbol_offset, symbol_offset + symbol_table_size, entry_size):
        name_offset = struct.unpack_from(">I", data, entry)[0]
        name_start = string_offset + name_offset
        name_end = data.index(0, name_start)
        if data[name_start:name_end].decode("ascii") == target:
            symbol_value, symbol_size = struct.unpack_from(">II", data, entry + 4)
            symbol_section = struct.unpack_from(">H", data, entry + 0x0E)[0]
            if retail_target or require_whole_section or required_section_symbols:
                if symbol_size == 0 or symbol_section == 0 or symbol_section >= section_count:
                    raise SystemExit(f"{path}: {target} has no file-backed value")
                section_header = section_offset + symbol_section * section_size
                value_section_type = struct.unpack_from(">I", data, section_header + 4)[0]
                value_section_offset = struct.unpack_from(">I", data, section_header + 0x10)[0]
                value_section_size = struct.unpack_from(">I", data, section_header + 0x14)[0]
                if value_section_type == 8 or symbol_value + symbol_size > value_section_size:
                    raise SystemExit(f"{path}: {target} has no complete file-backed value")
                if require_whole_section and (
                    symbol_value != 0 or symbol_size != value_section_size
                ):
                    raise SystemExit(
                        f"{path}: refusing whole-section removal: {target} covers "
                        f"[0x{symbol_value:X}, 0x{symbol_value + symbol_size:X}), "
                        f"section size is 0x{value_section_size:X}"
                    )
                if required_section_symbols is not None:
                    required = set(required_section_symbols)
                    ranges = []
                    defined_section_symbols = set()
                    for candidate in range(
                        symbol_offset, symbol_offset + symbol_table_size, entry_size
                    ):
                        candidate_name_offset = struct.unpack_from(">I", data, candidate)[0]
                        candidate_name_start = string_offset + candidate_name_offset
                        candidate_name_end = data.index(0, candidate_name_start)
                        candidate_name = data[
                            candidate_name_start:candidate_name_end
                        ].decode("ascii")
                        candidate_value, candidate_size = struct.unpack_from(
                            ">II", data, candidate + 4
                        )
                        candidate_section = struct.unpack_from(
                            ">H", data, candidate + 0x0E
                        )[0]
                        if candidate_section == symbol_section and candidate_size != 0:
                            defined_section_symbols.add(candidate_name)
                        if candidate_name not in required:
                            continue
                        if candidate_section != symbol_section or candidate_size == 0:
                            raise SystemExit(
                                f"{path}: {candidate_name} is not a nonempty symbol "
                                f"in {target}'s section"
                            )
                        ranges.append(
                            (candidate_value, candidate_value + candidate_size, candidate_name)
                        )
                    found = {name for _, _, name in ranges}
                    if found != required:
                        missing = ", ".join(sorted(required - found))
                        raise SystemExit(f"{path}: required section symbols not found: {missing}")
                    unexpected = defined_section_symbols - required
                    if unexpected:
                        names = ", ".join(sorted(unexpected))
                        raise SystemExit(
                            f"{path}: unlisted symbols in removed section: {names}"
                        )
                    cursor = 0
                    for start, end, name in sorted(ranges):
                        if start < cursor or end <= start:
                            raise SystemExit(
                                f"{path}: {name} overlaps another required symbol"
                            )
                        padding = data[
                            value_section_offset + cursor:value_section_offset + start
                        ]
                        if any(padding):
                            raise SystemExit(
                                f"{path}: nonzero unverified section bytes from "
                                f"0x{cursor:X} to 0x{start:X}"
                            )
                        cursor = end
                    padding = data[
                        value_section_offset + cursor:
                        value_section_offset + value_section_size
                    ]
                    if any(padding):
                        raise SystemExit(
                            f"{path}: nonzero unverified section bytes from "
                            f"0x{cursor:X} to 0x{value_section_size:X}"
                        )
            if retail_target:
                address_match = re.fullmatch(r".*_([0-9A-Fa-f]{8})", retail_target)
                if not address_match:
                    raise SystemExit(f"invalid addressed retail symbol {retail_target!r}")
                # Relocation-backed aggregates contain unresolved placeholders,
                # so their raw bytes are not comparable before link.
                if not has_relocations(symbol_section, symbol_value, symbol_size):
                    value_offset = value_section_offset + symbol_value
                    local_value = data[value_offset:value_offset + symbol_size]
                    address = int(address_match.group(1), 16)
                    dol = retail_dol.read_bytes()
                    segments = [(0x00, 0x48, 0x90, 7), (0x1C, 0x64, 0xAC, 11)]
                    for off_base, addr_base, size_base, count in segments:
                        for i in range(count):
                            file_off = struct.unpack_from(">I", dol, off_base + 4 * i)[0]
                            start = struct.unpack_from(">I", dol, addr_base + 4 * i)[0]
                            size = struct.unpack_from(">I", dol, size_base + 4 * i)[0]
                            if start <= address and address + symbol_size <= start + size:
                                retail_value = dol[file_off + address - start:file_off + address - start + symbol_size]
                                break
                        else:
                            continue
                        break
                    else:
                        raise SystemExit(f"{retail_dol}: address 0x{address:08X} is not in a file-backed segment")
                    if local_value != retail_value:
                        raise SystemExit(
                            f"{path}: {target} value {local_value.hex()} does not match "
                            f"{retail_target} at 0x{address:08X}: {retail_value.hex()}"
                        )
            struct.pack_into(">H", data, entry + 0x0E, 0)  # SHN_UNDEF
            path.write_bytes(data)
            raise SystemExit(0)

raise SystemExit(f"{path}: symbol {target!r} not found")
