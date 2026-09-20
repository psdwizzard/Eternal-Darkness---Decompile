"""Verify the retained function and preserve raw tool output."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
ID = "5baa94f5-30a9-4fe4-b2e0-70c9b3517411"
REPORT = ROOT / "reports/GEDE01"
records = []
for command in [
    ["sha1sum", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"],
    ["build/binutils/powerpc-eabi-readelf", "-rW", "build/GEDE01/obj/game/game_fn_801C3E2C.o"],
    ["build/binutils/powerpc-eabi-readelf", "-rW", "build/GEDE01/src/game/game_fn_801C3E2C.o"],
    ["python3", "tools/legal_audit.py"],
]:
    result = subprocess.run(command, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    records.append({"command": command, "exit_code": result.returncode, "output": result.stdout})
    assert result.returncode == 0, result.stdout
assert hashlib.sha1((ROOT / "build/GEDE01/main.dol").read_bytes()).hexdigest() == "ea24b6af954876ce072562ff39cdb4c81d32be1f"
def text_section(path):
    data = path.read_bytes()
    offset = struct.unpack_from(">I", data, 32)[0]
    size, count, names = struct.unpack_from(">HHH", data, 46)
    headers = [struct.unpack_from(">10I", data, offset + i * size) for i in range(count)]
    h = headers[names]
    strings = data[h[4]:h[4]+h[5]]
    for h in headers:
        if strings[h[0]:].split(b"\0", 1)[0] == b".text":
            return data[h[4]:h[4]+h[5]]
    raise AssertionError("No text section")
a = text_section(ROOT / "build/GEDE01/obj/game/game_fn_801C3E2C.o")
b = text_section(ROOT / "build/GEDE01/src/game/game_fn_801C3E2C.o")
relocations = {}
for side, record in zip(["left", "right"], records[1:3]):
    relocs = []
    active = False
    for line in record["output"].splitlines():
        if line.startswith("Relocation section"):
            active = "'.rela.text'" in line
        fields = line.split()
        if active and len(fields) >= 7 and fields[2].startswith("R_PPC_"):
            relocs.append({"offset": int(fields[0], 16), "type": fields[2], "target": fields[4], "addend": int(fields[6], 16) * (-1 if fields[5] == "-" else 1)})
    relocations[side] = relocs
shapes = {side: [{k:v for k,v in r.items() if k != "offset"} for r in relocs] for side, relocs in relocations.items()}
assert shapes["left"] == shapes["right"]
assert len(relocations["left"]) == 17
summary = {"raw_commands": records, "text_sizes": [len(a), len(b)], "raw_text_bytes_equal": a == b, "raw_text_differing_byte_offsets": [i for i in range(min(len(a),len(b))) if a[i] != b[i]], "text_relocations": relocations, "relocation_types_targets_addends_equal": True, "relocation_offsets_equal": relocations["left"] == relocations["right"]}
(REPORT / f"verification-{ID}.json").write_text(json.dumps(summary, indent=2) + "\n")
print(json.dumps({"text_sizes": summary["text_sizes"], "relocation_shapes_equal": True, "raw_bytes_equal": a == b}))
