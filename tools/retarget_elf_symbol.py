#!/usr/bin/env python3
"""Point every relocation against one local symbol at another symbol.

MWCC sometimes addresses a pooled static both through the pool symbol
(`...bss.0`) and through the static's own name when the static sits at the
start of the pool.  Both symbols have the same section and value, so the
relocations can be moved onto one of them before the pool is externalized.

usage: retarget_elf_symbol.py OBJECT FROM TO
"""
import struct
import sys
from pathlib import Path

if len(sys.argv) != 4:
    raise SystemExit("usage: retarget_elf_symbol.py OBJECT FROM TO")
path = Path(sys.argv[1])
src_name, dst_name = sys.argv[2], sys.argv[3]
data = bytearray(path.read_bytes())
if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit(f"{path}: not a big-endian ELF32 object")
(e_shoff, _, _, _, _, e_shentsize, e_shnum, e_shstrndx) = struct.unpack(">IIHHHHHH", data[32:52])
sections = [struct.unpack(">IIIIIIIIII", data[e_shoff + i * e_shentsize:e_shoff + (i + 1) * e_shentsize]) for i in range(e_shnum)]
SHT_SYMTAB, SHT_RELA = 2, 4
symtab_index = next((i for i, s in enumerate(sections) if s[1] == SHT_SYMTAB), None)
if symtab_index is None:
    raise SystemExit(f"{path}: no symbol table")
symtab = sections[symtab_index]
strtab = sections[symtab[6]]
sym_off, sym_size, sym_ent = symtab[4], symtab[5], symtab[9]
str_off = strtab[4]

def name_at(index):
    end = data.index(b"\0", str_off + index)
    return data[str_off + index:end].decode("ascii")

found = {}
for i in range(sym_size // sym_ent):
    off = sym_off + i * sym_ent
    st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack(">IIIBBH", data[off:off + sym_ent])
    name = name_at(st_name)
    if name in (src_name, dst_name):
        found[name] = (i, st_value, st_shndx)
if src_name not in found or dst_name not in found:
    raise SystemExit(f"{path}: need both symbols, found {sorted(found)}")
(src_idx, src_value, src_shndx), (dst_idx, dst_value, dst_shndx) = found[src_name], found[dst_name]
if src_shndx != dst_shndx or src_value != dst_value:
    raise SystemExit(f"{path}: {src_name!r} and {dst_name!r} are not the same address")
count = 0
for s in sections:
    if s[1] != SHT_RELA or s[6] != symtab_index:
        continue
    off, size, ent = s[4], s[5], s[9]
    for i in range(size // ent):
        r_off = off + i * ent
        r_offset, r_info, r_addend = struct.unpack(">IIi", data[r_off:r_off + 12])
        if (r_info >> 8) == src_idx:
            r_info = (dst_idx << 8) | (r_info & 0xFF)
            struct.pack_into(">IIi", data, r_off, r_offset, r_info, r_addend)
            count += 1
path.write_bytes(bytes(data))
print(f"{path}: {count} relocation(s) moved from {src_name} to {dst_name}")
