"""Run from eternal-darkness-decomp; independently compare ELF text and RELA."""
import hashlib
import json
from pathlib import Path
import struct


def extract(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    sections = [struct.unpack_from(">IIIIIIIIII", data, header[6] + i * header[11])
                for i in range(header[12])]

    def contents(section):
        return data[section[4]:section[4] + section[5]]

    def name(table, offset):
        return table[offset:].split(b"\0", 1)[0].decode()

    names = contents(sections[header[13]])
    index = next(i for i, section in enumerate(sections)
                 if name(names, section[0]) == ".text")
    code = contents(sections[index])
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != index:
            continue
        symbols = sections[section[6]]
        strings = contents(sections[symbols[6]])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", data, offset)
            symbol = struct.unpack_from(">IIIBBH", data,
                                        symbols[4] + (info >> 8) * symbols[9])
            relocations.append([address, info & 255, name(strings, symbol[0]), addend])
    return code, {
        "path": "eternal-darkness-decomp/" + path,
        "text_size": len(code),
        "text_sha256": hashlib.sha256(code).hexdigest(),
        "relocations": sorted(relocations),
    }


target_code, target = extract("build/GEDE01/obj/game/game_fn_801DF060.o")
base_code, base = extract("build/GEDE01/src/game/game_fn_801DF060.o")
result = {
    "target": target,
    "base": base,
    "raw_text_equal": target_code == base_code,
    "relocation_offsets_types_target_names_addends_equal":
        target["relocations"] == base["relocations"],
    "dol_sha1": hashlib.sha1(Path("build/GEDE01/main.dol").read_bytes()).hexdigest(),
}
print(json.dumps(result, indent=2))
assert result["raw_text_equal"]
assert result["relocation_offsets_types_target_names_addends_equal"]
assert result["dol_sha1"] == "ea24b6af954876ce072562ff39cdb4c81d32be1f"
