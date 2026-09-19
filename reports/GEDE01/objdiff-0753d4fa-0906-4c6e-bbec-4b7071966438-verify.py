"""Run from eternal-darkness-decomp; independently audit this function's ELF relocations."""
import hashlib
import json
import struct
from pathlib import Path


def inspect(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02", "expected big-endian ELF32"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    shoff, shentsize, shnum, shstrndx = header[6], header[11], header[12], header[13]
    sections = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]

    def contents(section):
        return data[section[4]:section[4] + section[5]]

    def string(table, offset):
        return table[offset:table.index(b"\0", offset)].decode()

    names = contents(sections[shstrndx])
    text_index = next(i for i, s in enumerate(sections) if string(names, s[0]) == ".text")
    code = contents(sections[text_index])
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symbols = sections[section[6]]
        strings = contents(sections[symbols[6]])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", data, offset)
            symbol = struct.unpack_from(">IIIBBH", data, symbols[4] + (info >> 8) * symbols[9])
            relocations.append({"offset": address, "type": info & 255,
                                "target": string(strings, symbol[0]), "addend": addend})
    return {"path": path, "text_size": len(code), "text_sha256": hashlib.sha256(code).hexdigest(),
            "relocations": sorted(relocations, key=lambda r: r["offset"])}, code


retail, retail_code = inspect("build/GEDE01/obj/game/game_fn_80153FD0.o")
generated, generated_code = inspect("build/GEDE01/src/game/game_fn_80153FD0.o")
result = {"retail": retail, "generated": generated,
          "text_bytes_equal": retail_code == generated_code,
          "relocations_equal_including_offsets_types_targets_addends": retail["relocations"] == generated["relocations"]}
print(json.dumps(result, indent=2))
assert result["text_bytes_equal"]
assert result["relocations_equal_including_offsets_types_targets_addends"]
