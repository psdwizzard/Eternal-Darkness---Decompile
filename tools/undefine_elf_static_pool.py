#!/usr/bin/env python3
"""Turn a unit's local static-data block into a reference to the retail symbol.

MWCC pools a translation unit's file-scope statics into one local `.bss`
symbol (`...bss.0`) and addresses every static as a displacement from it.
A per-function unit that declares those statics therefore matches retail's
code but carries its own copy of the block.  This makes the renamed symbol
undefined and empties the NOBITS section so the link resolves it to the
retail block instead.

usage: undefine_elf_static_pool.py OBJECT SYMBOL SYMBOLS_FILE

SYMBOL must already carry the retail name (objcopy --redefine-sym) and must
be defined in symbols.txt as a `.bss` object; the object's section holding it
must be NOBITS.
"""

import re
import struct
import sys
from pathlib import Path

if len(sys.argv) != 4:
    raise SystemExit("usage: undefine_elf_static_pool.py OBJECT SYMBOL SYMBOLS_FILE")

path = Path(sys.argv[1])
target = sys.argv[2]
symbols_path = Path(sys.argv[3])

configured = re.findall(rf"^{re.escape(target)}\s*=\s*\.bss:0x[0-9A-Fa-f]+\s*;", symbols_path.read_text(), re.MULTILINE)
if len(configured) != 1:
    raise SystemExit(f"{symbols_path}: expected one .bss definition of {target!r}, found {len(configured)}")

data = bytearray(path.read_bytes())
if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit(f"{path}: not a big-endian ELF32 object")
(e_shoff, _, _, _, _, e_shentsize, e_shnum, e_shstrndx) = struct.unpack(">IIHHHHHH", data[32:52])
sections = [struct.unpack(">IIIIIIIIII", data[e_shoff + i * e_shentsize:e_shoff + (i + 1) * e_shentsize]) for i in range(e_shnum)]
SHT_SYMTAB, SHT_NOBITS = 2, 8
symtab_index = next((i for i, s in enumerate(sections) if s[1] == SHT_SYMTAB), None)
if symtab_index is None:
    raise SystemExit(f"{path}: no symbol table")
symtab = sections[symtab_index]
strtab = sections[symtab[6]]
sym_off, sym_size, sym_ent = symtab[4], symtab[5], symtab[9]
str_off = strtab[4]


def name_at(index: int) -> str:
    end = data.index(b"\0", str_off + index)
    return data[str_off + index:end].decode("ascii")


hits = []
for i in range(sym_size // sym_ent):
    off = sym_off + i * sym_ent
    st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack(">IIIBBH", data[off:off + sym_ent])
    if name_at(st_name) == target:
        hits.append((i, off, st_value, st_shndx, st_info))
if len(hits) != 1:
    raise SystemExit(f"{path}: expected one symbol {target!r}, found {len(hits)}")
i, off, st_value, st_shndx, st_info = hits[0]
if st_shndx == 0 or st_shndx >= e_shnum or sections[st_shndx][1] != SHT_NOBITS:
    raise SystemExit(f"{path}: {target!r} is not defined in a NOBITS section")
if st_value != 0:
    raise SystemExit(f"{path}: {target!r} must sit at the start of its section (value {st_value:#x})")
# global, undefined, no type
struct.pack_into(">IIIBBH", data, off, struct.unpack(">I", data[off:off + 4])[0], 0, 0, (1 << 4) | 0, 0, 0)
# empty the pooled section so the link allocates nothing for it
sh_off = e_shoff + st_shndx * e_shentsize
fields = list(sections[st_shndx])
fields[5] = 0
struct.pack_into(">IIIIIIIIII", data, sh_off, *fields)
path.write_bytes(bytes(data))
print(f"{path}: {target} now undefined; section {st_shndx} emptied")
