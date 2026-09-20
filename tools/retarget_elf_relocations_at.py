#!/usr/bin/env python3
"""Retarget specific relocations by text offset onto another local symbol.

The pool-externalize flow sometimes needs one call site to reference a
different retail label than every other site sharing the same compiler-local
constant (for example two retail sdata2 copies of the same double). The
symbol+addend form of retarget_elf_relocation.py cannot split those sites;
this tool retargets by exact .text offset instead.
"""

import struct
import sys
from pathlib import Path

if len(sys.argv) < 5:
    raise SystemExit(
        "usage: retarget_elf_relocations_at.py OBJECT SYMBOL TO_SYMBOL OFFSET [OFFSET...] [keep]"
    )

path = Path(sys.argv[1])
from_name = sys.argv[2]
to_name = sys.argv[3]
args = sys.argv[4:]
keep_target = args and args[-1] == "keep"
if keep_target:
    args = args[:-1]
offsets = {int(x, 0) for x in args}

data = bytearray(path.read_bytes())

if data[:6] != b"\x7fELF\x01\x02":
    raise SystemExit("not a big-endian ELF32 object")

e_shoff, = struct.unpack(">I", data[0x20:0x24])
e_shentsize, e_shnum, e_shstrndx = struct.unpack(">HHH", data[0x2E:0x34])


def sh(i):
    base = e_shoff + i * e_shentsize
    name, typ, flags, addr, off, size, link, info, align, entsize = struct.unpack(
        ">IIIIIIIIII", data[base:base + 40]
    )
    return dict(name=name, typ=typ, off=off, size=size, link=link, entsize=entsize)


shstr = sh(e_shstrndx)


def cstr(table_off, name_off):
    end = data.index(b"\x00", table_off + name_off)
    return data[table_off + name_off:end].decode("ascii")


def shname(i):
    return cstr(shstr["off"], sh(i)["name"])


# locate the target symbol in the symtab
symtabs = [i for i in range(e_shnum) if shname(i) == ".symtab"]
if not symtabs:
    raise SystemExit("no .symtab")
symtab = sh(symtabs[0])
strtab = sh(symtab["link"])
to_index = None
from_index = None
count = symtab["size"] // 16
for i in range(count):
    entry = symtab["off"] + i * 16
    name_off, = struct.unpack(">I", data[entry:entry + 4])
    name = cstr(strtab["off"], name_off)
    if name == to_name:
        to_index = i
    elif name == from_name:
        from_index = i
if to_index is None:
    raise SystemExit(f"symbol {to_name!r} not found")
if from_index is None:
    raise SystemExit(f"symbol {from_name!r} not found")

# patch matching .rela.text entries
changed = 0
for i in range(e_shnum):
    sec = sh(i)
    if sec["typ"] != 4 or shname(sec["link"]) != ".symtab":  # SHT_RELA
        continue
    for j in range(sec["size"] // 12):
        entry = sec["off"] + j * 12
        r_offset, r_info, r_addend = struct.unpack(">IIi", data[entry:entry + 12])
        sym = r_info >> 8
        if sym == from_index and r_offset in offsets:
            data[entry + 4:entry + 8] = struct.pack(">I", (to_index << 8) | (r_info & 0xFF))
            changed += 1

if changed != len(offsets):
    raise SystemExit(f"expected {len(offsets)} relocations, patched {changed}")

# Unless the caller keeps it defined, the target symbol becomes an undefined
# reference, matching the pool-externalize flow where it was only added to
# receive these relocations.
if not keep_target:
    to_entry = symtab["off"] + to_index * 16
    struct.pack_into(">II", data, to_entry + 4, 0, 0)
    struct.pack_into(">H", data, to_entry + 0x0E, 0)

path.write_bytes(data)
print(f"retargeted {changed} relocations {from_name} -> {to_name}")
