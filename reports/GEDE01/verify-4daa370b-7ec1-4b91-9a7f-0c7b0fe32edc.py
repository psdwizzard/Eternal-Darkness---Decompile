"""Assignment verification; run from eternal-darkness-decomp."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ASSIGNMENT = "4daa370b-7ec1-4b91-9a7f-0c7b0fe32edc"
PREFIX = Path("reports/GEDE01")
log = {"assignment_id": ASSIGNMENT, "cwd": "eternal-darkness-decomp", "commands": []}

def run(args):
    result = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log["commands"].append({"argv": args, "exit": result.returncode, "raw_output": result.stdout})
    (PREFIX / ("verification-" + ASSIGNMENT + ".json")).write_text(json.dumps(log, indent=2) + "\n")
    print("$ " + " ".join(args), flush=True)
    print(result.stdout[-2500:], flush=True)
    result.check_returncode()
    return result.stdout

def elf_measurement(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    offset = struct.unpack_from(">I", data, 32)[0]
    entsize, count, names_index = struct.unpack_from(">HHH", data, 46)
    sections = [struct.unpack_from(">10I", data, offset + i * entsize) for i in range(count)]
    def payload(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, at):
        return table[at:table.index(b"\0", at)].decode()
    names = payload(sections[names_index])
    text = next(s for s in sections if string(names, s[0]) == ".text")
    rel = next(s for s in sections if string(names, s[0]) == ".rela.text")
    symtab = sections[rel[6]]
    strings = payload(sections[symtab[6]])
    relocations = []
    for at in range(rel[4], rel[4] + rel[5], rel[9]):
        address, info, addend = struct.unpack_from(">IIi", data, at)
        symbol = struct.unpack_from(">IIIBBH", data, symtab[4] + (info >> 8) * symtab[9])
        relocations.append({"offset": hex(address), "type": info & 255, "target": string(strings, symbol[0]), "addend": addend})
    return payload(text), relocations

run(["python3", "configure.py"])
run([".tools/bin/ninja", "-j2"])
for label, options in [("canonical", []), ("strict", ["-c", "function_reloc_diffs=name_address"])]:
    name = ("objdiff-" if label == "strict" else "canonical-objdiff-") + ASSIGNMENT + ".json"
    path = PREFIX / name
    run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_801A69F0", "-o", str(path), "--format", "json-pretty"] + options + ["fn_801A69F0"])
    diff = json.loads(path.read_text())
    target = next(s for s in diff["left"]["symbols"] if s["name"] == "fn_801A69F0")
    assert target["match_percent"] == 100.0
    log[label] = {"match_percent": target["match_percent"], "bytes": target["size"], "instructions": len(target["instructions"])}
objects = ["build/GEDE01/obj/game/game_fn_801A69F0.o", "build/GEDE01/src/game/game_fn_801A69F0.o"]
measurements = []
for obj in objects:
    run(["readelf", "-r", obj])
    measurements.append(elf_measurement(obj))
assert measurements[0] == measurements[1], "Text bytes or relocation offset/type/target/addend mismatch"
log["elf"] = {"text_bytes_equal": True, "text_size": len(measurements[0][0]), "text_sha256": hashlib.sha256(measurements[0][0]).hexdigest(), "relocations_equal": True, "relocations": measurements[0][1]}
run(["sha1sum", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"])
for path in ["build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"]:
    assert hashlib.sha1(Path(path).read_bytes()).hexdigest() == "ea24b6af954876ce072562ff39cdb4c81d32be1f"
run(["cmp", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"])
run(["python3", "tools/legal_audit.py"])
run(["git", "diff", "--check"])
run(["git", "diff", "--", "configure.py", "src/game/game_fn_801A69F0.c", "config/GEDE01/splits.txt"])
log["source_sha256"] = hashlib.sha256(Path("src/game/game_fn_801A69F0.c").read_bytes()).hexdigest()
log["passed"] = True
(PREFIX / ("verification-" + ASSIGNMENT + ".json")).write_text(json.dumps(log, indent=2) + "\n")
print(json.dumps({k:v for k,v in log.items() if k != "commands"}, indent=2))
