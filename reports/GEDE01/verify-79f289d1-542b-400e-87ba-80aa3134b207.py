"""Assignment-local raw ELF verification; run from eternal-darkness-decomp."""
import hashlib
import json
import struct
from pathlib import Path


def read_function(path):
    blob = Path(path).read_bytes()
    assert blob[:6] == b"\x7fELF\x01\x02", "Expected big-endian ELF32"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
    sections = [struct.unpack_from(">IIIIIIIIII", blob, header[6] + i * header[11])
                for i in range(header[12])]

    def data(index):
        section = sections[index]
        return blob[section[4]:section[4] + section[5]]

    def name(table, offset):
        return table[offset:table.index(b"\0", offset)].decode()

    symtab = next(i for i, section in enumerate(sections) if section[1] == 2)
    symbols = []
    for offset in range(0, sections[symtab][5], 16):
        n, value, size, info, other, section = struct.unpack_from(
            ">IIIBBH", data(symtab), offset)
        symbols.append((name(data(sections[symtab][6]), n), value, size, section))
    function = next(s for s in symbols if s[0] == "fn_800C7E40")
    relocations = []
    for index, section in enumerate(sections):
        if section[1] != 4 or section[7] != function[3]:
            continue
        assert section[6] == symtab
        for offset in range(0, section[5], 12):
            address, info, addend = struct.unpack_from(">IIi", data(index), offset)
            if function[1] <= address < function[1] + function[2]:
                relocations.append({"offset": address - function[1],
                                    "type": info & 255,
                                    "target": symbols[info >> 8][0],
                                    "addend": addend})
    return (data(function[3])[function[1]:function[1] + function[2]], relocations)


target, target_relocs = read_function("build/GEDE01/obj/game/game_fn_800C7E40.o")
base, base_relocs = read_function("build/GEDE01/src/game/game_fn_800C7E40.o")
measurement = {
    "target_bytes": len(target), "base_bytes": len(base),
    "raw_text_equal": target == base,
    "target_text_sha256": hashlib.sha256(target).hexdigest(),
    "base_text_sha256": hashlib.sha256(base).hexdigest(),
    "exact_instructions": sum(target[i:i+4] == base[i:i+4]
                              for i in range(0, len(target), 4)),
    "relocations_equal_including_offsets_types_targets_addends": target_relocs == base_relocs,
    "target_relocations": target_relocs, "base_relocations": base_relocs,
}
print(json.dumps(measurement, indent=2))
assert len(target) == len(base) == 680
assert target == base
assert len(target_relocs) == len(base_relocs) == 43
assert target_relocs == base_relocs
