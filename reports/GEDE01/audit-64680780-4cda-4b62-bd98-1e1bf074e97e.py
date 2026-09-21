"""Assignment-specific raw ELF audit. Run from eternal-darkness-decomp."""
import hashlib
import json
from pathlib import Path
import struct


def read_function(path):
    blob = Path(path).read_bytes()
    assert blob[:6] == b"\x7fELF\x01\x02"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
    sections = [
        struct.unpack_from(">IIIIIIIIII", blob, header[6] + i * header[11])
        for i in range(header[12])
    ]

    def data(section):
        return blob[section[4]:section[4] + section[5]]

    tables = {}
    for index, section in enumerate(sections):
        if section[1] != 2:
            continue
        strings = data(sections[section[6]])
        tables[index] = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            name, value, size, info, other, shndx = struct.unpack_from(
                ">IIIBBH", blob, offset
            )
            tables[index].append({
                "name": strings[name:strings.index(b"\0", name)].decode(),
                "value": value, "size": size, "section": shndx,
            })
    symbol = next(
        symbol for table in tables.values() for symbol in table
        if symbol["name"] == "fn_8019FAB8"
    )
    start, size = symbol["value"], symbol["size"]
    code = data(sections[symbol["section"]])[start:start + size]
    relocations = []
    for section in sections:
        if section[1] not in (4, 9) or section[7] != symbol["section"]:
            continue
        assert section[1] == 4, "Require explicit RELA addends"
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", blob, offset)
            target = tables[section[6]][info >> 8]
            if start <= address < start + size:
                relocations.append({
                    "offset": address - start, "type": info & 255,
                    "target": target["name"], "target_value": target["value"],
                    "addend": addend,
                })
    return {
        "path": "eternal-darkness-decomp/" + path, "size": len(code),
        "code_sha256": hashlib.sha256(code).hexdigest(),
        "relocations": relocations,
    }, code


retail, retail_code = read_function("build/GEDE01/obj/game/game_fn_8019FAB8.o")
compiled, compiled_code = read_function("build/GEDE01/src/game/game_fn_8019FAB8.o")
result = {
    "method": "ELF32 symbol-byte and SHT_RELA comparison with explicit signed addends",
    "retail": retail, "compiled": compiled,
    "raw_code_bytes_equal": retail_code == compiled_code,
    "relocation_records_equal": retail["relocations"] == compiled["relocations"],
}
print(json.dumps(result, indent=2))
assert result["raw_code_bytes_equal"] and len(retail_code) == 508
assert result["relocation_records_equal"] and len(retail["relocations"]) == 16
