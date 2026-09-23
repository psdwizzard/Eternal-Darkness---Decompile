"""Extract the assigned function's ELF32 RELA targets and addends (no code bytes)."""
import json
import struct
from pathlib import Path
ID = "191bb0ce-611b-4781-b324-25ccdc13a9e0"

def extract(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    h = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    sections = [struct.unpack_from(">IIIIIIIIII", data, h[6] + i*h[11]) for i in range(h[12])]
    result = []
    for relsec in sections:
        if relsec[1] != 4:
            continue
        symsec = sections[relsec[6]]
        strsec = sections[symsec[6]]
        strings = data[strsec[4]:strsec[4]+strsec[5]]
        symbols = []
        for off in range(symsec[4], symsec[4]+symsec[5], symsec[9]):
            sym = struct.unpack_from(">IIIBBH", data, off)
            name = strings[sym[0]:].split(b"\0", 1)[0].decode()
            symbols.append((name, sym))
        functions = [s for name, s in symbols if name == "fn_80130720" and s[5] == relsec[7]]
        if not functions:
            continue
        function = functions[0]
        for off in range(relsec[4], relsec[4]+relsec[5], relsec[9]):
            address, info, addend = struct.unpack_from(">IIi", data, off)
            if function[1] <= address < function[1]+function[2]:
                name, symbol = symbols[info >> 8]
                result.append({"function_offset":address-function[1], "type":info&255,
                    "target":name,"target_address":symbol[1],"addend":addend})
    return result

unit = next(u for u in json.loads(Path("objdiff.json").read_text())["units"] if u["name"] == "main/game/game_fn_80130720")
target, generated = extract(unit["target_path"]), extract(unit["base_path"])
identity = lambda rows: [{k:v for k,v in row.items() if k != "function_offset"} for row in rows]
result = {"target_path":unit["target_path"],"generated_path":unit["base_path"],
    "target_relocations":target,"generated_relocations":generated,
    "target_names_addresses_types_addends_equal_in_order":identity(target)==identity(generated),
    "note":"Instruction offsets intentionally differ for this NonMatching candidate; this checks only relocation identities, not a byte match."}
Path("reports/GEDE01/relocations-"+ID+".json").write_text(json.dumps(result,indent=2)+"\n")
print(json.dumps({"target_relocation_count":len(target),"generated_relocation_count":len(generated),"identities_equal":identity(target)==identity(generated)}))
assert target and generated and identity(target)==identity(generated)
