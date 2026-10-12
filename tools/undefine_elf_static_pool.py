#!/usr/bin/env python3
"""Externalize one completely owned, zero-filled static pool; fail before mutation.

Usage: undefine_elf_static_pool.py OBJECT EXACT_LINKER_SYMBOL SYMBOLS_FILE
Both NOBITS and zero PROGBITS pools require an explicit retail object extent.
Relocations applied inside removed data, or references to any other pool
symbol, are forbidden. Direct references to the exact externalized symbol
retain their relocation and addend.
"""
import re
import struct
import sys
from pathlib import Path


def externalize(data, target, symbols):
    data = bytearray(data)

    def require(ok, message):
        if not ok:
            raise ValueError(message)

    def bounds(offset, size):
        require(0 <= offset <= len(data) and 0 <= size <= len(data) - offset,
                'truncated or out-of-bounds ELF range')

    def unpack(fmt, offset):
        bounds(offset, struct.calcsize(fmt))
        return struct.unpack_from(fmt, data, offset)

    require(len(data) >= 52 and data[:7] == b'\x7fELF\x01\x02\x01', 'expected big-endian ELF32')
    require(unpack('>H', 16)[0] == 1 and unpack('>H', 18)[0] == 20, 'expected relocatable PowerPC object')
    require(unpack('>H',40)[0]==52 and unpack('>I',28)[0]==0 and unpack('>H',44)[0]==0, 'unsupported ELF header or program-header metadata')
    shoff = unpack('>I', 32)[0]
    entsize, count, names_index = unpack('>HHH', 46)
    require(entsize == 40 and count > 0 and names_index < count, 'invalid section table')
    bounds(shoff, entsize * count)
    sections = [unpack('>10I', shoff + i * entsize) for i in range(count)]
    for s in sections:
        if s[1] != 8:
            bounds(s[4], s[5])
    ranges=[(0,52,'ELF header'),(shoff,shoff+entsize*count,'section headers')]
    ranges += [(s[4],s[4]+s[5],f'section {i}') for i,s in enumerate(sections) if s[1] not in (0,8) and s[5]]
    ranges.sort()
    require(all(a[1]<=b[0] for a,b in zip(ranges,ranges[1:])), 'overlapping ELF section or metadata storage')
    tables = [i for i, s in enumerate(sections) if s[1] == 2]
    require(len(tables) == 1, 'expected one symbol table')
    symindex = tables[0]
    table = sections[symindex]
    require(table[9] == 16 and table[5] % 16 == 0 and table[6] < count, 'invalid symbol table')
    strings = sections[table[6]]
    require(strings[1] == 3, 'invalid symbol string table')

    def name(index):
        require(index < strings[5], 'symbol name outside string table')
        start = strings[4] + index
        end = data.find(b'\0', start, strings[4] + strings[5])
        require(end >= start, 'unterminated symbol name')
        return bytes(data[start:end]).decode('ascii')

    entries = [unpack('>IIIBBH', table[4] + i * 16) for i in range(table[5] // 16)]
    require(0 < table[7] <= len(entries) and all((entry[3] >> 4 == 0) == (i < table[7]) for i, entry in enumerate(entries)), 'invalid local/global symbol ordering')
    require(all(section[6] != symindex or section[1] in (4, 9) for section in sections), 'unsupported symbol-indexed section')
    hits = [i for i, entry in enumerate(entries) if name(entry[0]) == target]
    require(len(hits) == 1, 'expected one exact linker symbol')
    hit = hits[0]
    _, value, size, info, other, pool = entries[hit]
    require(0 < pool < count and value == 0 and info & 15 in (0, 1) and info >> 4 in (0, 1) and other == 0,
            'pool symbol must be a visible object at section start')
    section = sections[pool]
    require(section[1] in (1, 8) and section[5] > 0 and not section[2] & 4,
            'pool must be non-executable PROGBITS or NOBITS')
    require(size <= section[5], 'pool symbol exceeds section bounds')
    mapping_pattern = re.compile(
        r'^([^\s=]+)\s*=\s*(\.[\w.]+):0x([0-9A-Fa-f]+)\s*;([^\n]*)$', re.M
    )
    mappings = mapping_pattern.findall(symbols)
    # dtk gives bare local retail names an address-qualified linker name.
    # Normalize only explicit locals; the address still must match exactly,
    # and duplicate names/overlapping ownership remain rejected below.
    mappings = [
        (f'{name}_{int(address, 16):08X}' if re.search(r'\bscope:local\b', attributes)
         and not re.fullmatch(r'.*_[0-9A-Fa-f]{8}', name) else name,
         section_name, address, attributes)
        for name, section_name, address, attributes in mappings
    ]
    targets = [record for record in mappings if record[0] == target]
    require(len(targets) == 1, 'expected one exact retail mapping')
    _, retail_section, address, attributes = targets[0]
    address_value = int(address, 16)

    def mapping_extent(record):
        symbol_name, section_name, symbol_address, symbol_attributes = record
        extent = re.search(r'\bsize:(0x[0-9A-Fa-f]+|[0-9]+)\b', symbol_attributes)
        require(section_name in ('.bss', '.sbss') and re.search(r'\btype:object\b', symbol_attributes) and extent,
                'expected sized retail zero-storage object')
        start = int(symbol_address, 16)
        name_address = re.fullmatch(r'.*_([0-9A-Fa-f]{8})', symbol_name)
        require(not re.search(r'\bscope:local\b', symbol_attributes) or name_address,
                'local retail symbol must use a NAME_ADDRESS linker name')
        require(not name_address or int(name_address.group(1), 16) == start,
                'NAME_ADDRESS linker name does not match retail symbol address')
        return start, int(extent[1], 0)

    mapping_extent(targets[0])
    limit = address_value + section[5]
    require(limit <= 0x100000000, 'retail pool range overflows address space')
    intervals = []
    for record in mappings:
        start = int(record[2], 16)
        if start >= limit:
            continue
        extent = re.search(r'\bsize:(0x[0-9A-Fa-f]+|[0-9]+)\b', record[3])
        if extent is None:
            require(record[1] != retail_section,
                    'cannot establish retail object extent')
            continue
        end = start + int(extent[1], 0)
        if end <= address_value:
            continue
        require(record[1] == retail_section, 'overlapping retail sections')
        start, extent = mapping_extent(record)
        intervals.append((start, start + extent))
    cursor = address_value
    for start, end in sorted(intervals):
        require(start == cursor and cursor < end <= 0x100000000,
                'retail mappings overlap or do not exactly cover the full pool')
        cursor = end
    require(cursor >= limit, 'retail mappings do not cover the full pool')
    if section[1] == 1:
        require(not any(data[section[4]:section[4] + section[5]]), 'PROGBITS pool is not all zero')
    local_objects = [(0, size)] if size else []
    for i, entry in enumerate(entries):
        if entry[5] != pool or i == hit:
            continue
        if entry[1] == 0 and entry[2] == 0 and entry[3] == 3:
            continue
        # MWCC anchors may be zero-sized or own the first object in a pool.
        # Their unreferenced local objects must partition the remaining bytes.
        # Only the aggregate anchor can remain a relocation target below.
        require(entry[3] == 1 and entry[4] == 0
                and entry[2] > 0 and entry[1] + entry[2] <= section[5],
                'removed section has another symbol owner')
        local_objects.append((entry[1], entry[1] + entry[2]))
    if local_objects:
        cursor = 0
        for start, end in sorted(local_objects):
            require(start == cursor or (cursor < start < cursor + 8 and start % 8 == 0
                    and not any(data[section[4] + cursor:section[4] + start])),
                    'local aggregate owners overlap or leave a gap')
            cursor = end
        require(cursor == section[5], 'local aggregate owners do not cover full pool')
    for reloc in sections:
        if reloc[1] not in (4, 9):
            continue
        expected = 12 if reloc[1] == 4 else 8
        require(reloc[9] == expected and reloc[5] % expected == 0 and reloc[6] == symindex and 0 < reloc[7] < count,
                'invalid relocation table')
        require(reloc[7] != pool, 'relocation section targets removed pool')
        for off in range(reloc[4], reloc[4] + reloc[5], expected):
            where, reference = unpack('>II', off)
            index = reference >> 8
            # PowerPC ELF relocation storage widths; unsupported encodings fail closed.
            widths = {0: 0, 1: 4, 2: 4, 3: 2, 4: 2, 5: 2, 6: 2, 7: 4, 8: 4, 9: 4, 10: 4, 11: 4, 12: 4, 13: 4, 26: 4, 32: 2, 109: 4}
            kind = reference & 255
            require(kind in widths and index < len(entries) and where <= sections[reloc[7]][5] - widths[kind], 'invalid relocation reference or complete range')
            require(entries[index][5] != pool or index == hit,
                    'incoming relocation references a different pool symbol')
    # All checks completed. Never change the caller's bytes on rejection.
    rewritten = list(entries)
    rewritten[hit] = (entries[hit][0], 0, 0, 16, 0, 0)
    # The unreferenced local owners disappear with the validated pool. Keep
    # their metadata inside the now-empty section for ELF readers/objdiff.
    for i, entry in enumerate(entries):
        if i != hit and entry[5] == pool:
            rewritten[i] = (entry[0], 0, 0, entry[3], entry[4], pool)
    order = [i for i, entry in enumerate(rewritten) if entry[3] >> 4 == 0] + [i for i, entry in enumerate(rewritten) if entry[3] >> 4 != 0]
    indices = {old: new for new, old in enumerate(order)}
    for new, old in enumerate(order):
        struct.pack_into('>IIIBBH', data, table[4] + new * 16, *rewritten[old])
    table_fields = list(table)
    table_fields[7] = sum(entry[3] >> 4 == 0 for entry in rewritten)
    struct.pack_into('>10I', data, shoff + symindex * 40, *table_fields)
    for reloc in sections:
        if reloc[1] in (4, 9):
            for off in range(reloc[4], reloc[4] + reloc[5], reloc[9]):
                reference = unpack('>I', off + 4)[0]
                struct.pack_into('>I', data, off + 4, (indices[reference >> 8] << 8) | (reference & 255))
    fields = list(section)
    fields[5] = 0
    struct.pack_into('>10I', data, shoff + pool * 40, *fields)
    return bytes(data)


def main():
    if len(sys.argv) != 4:
        raise SystemExit('usage: undefine_elf_static_pool.py OBJECT SYMBOL SYMBOLS_FILE')
    file = Path(sys.argv[1])
    try:
        result = externalize(file.read_bytes(), sys.argv[2], Path(sys.argv[3]).read_text())
    except (ValueError, UnicodeError, struct.error) as error:
        raise SystemExit(f'{file}: {error}')
    file.write_bytes(result)
    print(f'{file}: {sys.argv[2]} undefined; validated pool emptied')


if __name__ == '__main__':
    main()
