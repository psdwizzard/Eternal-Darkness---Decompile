"""Run from eternal-darkness-decomp; compare raw ELF text and relocation records."""
import hashlib
import json
import struct
from pathlib import Path


def inspect(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    sections = [struct.unpack_from(">IIIIIIIIII", data, header[6] + i * header[11])
                for i in range(header[12])]

    def contents(section):
        return data[section[4]:section[4] + section[5]]

    def string(table, offset):
        return table[offset:].split(b"\0", 1)[0].decode()

    names = contents(sections[header[13]])
    text_index = next(i for i, s in enumerate(sections)
                      if string(names, s[0]) == ".text")
    text = contents(sections[text_index])
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symbols = sections[section[6]]
        strings = contents(sections[symbols[6]])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", data, offset)
            symbol = struct.unpack_from(">IIIBBH", data,
                                        symbols[4] + (info >> 8) * symbols[9])
            relocations.append({
                "offset": address, "type": info & 255,
                "target": string(strings, symbol[0]),
                "target_value": symbol[1], "addend": addend,
            })
    return text, {
        "path": path, "text_size": len(text),
        "text_sha256": hashlib.sha256(text).hexdigest(),
        "relocation_count": len(relocations), "relocations": relocations,
    }


left_bytes, left = inspect("build/GEDE01/obj/game/game_fn_800539D8.o")
right_bytes, right = inspect("build/GEDE01/src/game/game_fn_800539D8.o")
result = {
    "text_bytes_equal": left_bytes == right_bytes,
    "relocation_records_equal": left["relocations"] == right["relocations"],
    "left": left, "right": right,
}
print(json.dumps(result, indent=2))
assert result["text_bytes_equal"]
assert result["relocation_records_equal"]
