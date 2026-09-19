"""Reproduce this assignment's build, byte, relocation and legal checks.
Run from eternal-darkness-decomp with python3 reports/GEDE01/verify-<assignment>.py.
"""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

AID = "f38c5465-1d9a-4ee1-b3bf-b03e4050f953"
REPORTS = Path("reports/GEDE01")
EXPECTED_DOL = "ea24b6af954876ce072562ff39cdb4c81d32be1f"
result = {"version": 1, "assignment_id": AID, "target": "fn_80135510", "commands": []}


def run(cmd):
    proc = subprocess.run(cmd, text=True, capture_output=True)
    row = {"command": cmd, "exit_code": proc.returncode,
           "stdout": proc.stdout, "stderr": proc.stderr}
    result["commands"].append(row)
    assert proc.returncode == 0, row
    return proc.stdout


def text_section(path):
    data = path.read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    offset = struct.unpack_from(">I", data, 32)[0]
    size, count, name_index = struct.unpack_from(">HHH", data, 46)
    sections = [struct.unpack_from(">10I", data, offset + i * size) for i in range(count)]
    names = sections[name_index]
    strings = data[names[4]:names[4] + names[5]]
    for section in sections:
        name = strings[section[0]:].split(b"\0", 1)[0]
        if name == b".text":
            return data[section[4]:section[4] + section[5]]
    raise AssertionError("No .text section")


run(["python3", "configure.py"])
run([".tools/bin/ninja", "-j2"])
result["effective_compiler_commands"] = run([
    ".tools/bin/ninja", "-t", "commands", "build/GEDE01/src/game/game_fn_80135510.o"
]).splitlines()[-1:]
for mode, extra in [("canonical", []), ("relocation-strict", ["-c", "function_reloc_diffs=name_address"])]:
    output = REPORTS / f"objdiff-{AID}-{mode}.json"
    run(["build/tools/objdiff-cli", "-L", "error", "diff", "-p", ".", "-u",
         "main/game/game_fn_80135510", "fn_80135510", "-o", str(output),
         "--format", "json-pretty"] + extra)
    data = json.loads(output.read_text())
    symbols = [next(s for s in data[side]["symbols"] if s["name"] == "fn_80135510")
               for side in ["left", "right"]]
    result[mode] = {"raw_evidence": "eternal-darkness-decomp/" + str(output),
                    "target_size": int(symbols[0]["size"]),
                    "base_size": int(symbols[1]["size"]),
                    "target_instruction_count": len(symbols[0]["instructions"]),
                    "base_instruction_count": len(symbols[1]["instructions"]),
                    "target_match_percent": symbols[0]["match_percent"],
                    "base_match_percent": symbols[1]["match_percent"]}
    assert all(s["match_percent"] == 100 for s in symbols)
    assert all(int(s["size"]) == 568 for s in symbols)
    if mode == "relocation-strict":
        tuples = []
        for symbol in symbols:
            rows = []
            for wrapped in symbol["instructions"]:
                instruction = wrapped.get("instruction", {})
                relocation = instruction.get("relocation")
                if relocation is not None:
                    rows.append([int(instruction.get("address", 0)), relocation.get("type"),
                                 relocation.get("type_name"), instruction["formatted"],
                                 int(relocation.get("addend", 0))])
            tuples.append(rows)
        result["objdiff_relocation_annotations"] = {
            "target_count": len(tuples[0]), "base_count": len(tuples[1]),
            "equal": tuples[0] == tuples[1],
            "note": "Includes 24 inferred annotations in addition to 46 ELF relocations."
        }
        assert tuples[0] == tuples[1]

blobs, relocations = [], []
for side in ["obj", "src"]:
    obj = Path(f"build/GEDE01/{side}/game/game_fn_80135510.o")
    blobs.append(text_section(obj))
    raw = run(["build/binutils/powerpc-eabi-readelf", "-rW", str(obj)])
    rows = []
    for line in raw.splitlines():
        match = re.match(r"^([0-9a-f]{8})\s+([0-9a-f]{8})\s+(R_\S+)\s+([0-9a-f]+)\s+(\S+)\s+([+-])\s+([0-9a-f]+)$", line.strip())
        if match:
            offset, info, kind, value, target, sign, addend = match.groups()
            rows.append({"offset": int(offset, 16), "type": int(info, 16) & 255,
                         "type_name": kind, "target": target, "target_value": int(value, 16),
                         "addend": int(addend, 16) * (-1 if sign == "-" else 1)})
    relocations.append(rows)
result["elf_relocations"] = {"target": relocations[0], "base": relocations[1],
                             "equal": relocations[0] == relocations[1]}
assert len(relocations[0]) == len(relocations[1]) == 46
assert relocations[0] == relocations[1]
result["raw_text_bytes"] = {
    "target_size": len(blobs[0]), "base_size": len(blobs[1]), "equal": blobs[0] == blobs[1],
    "target_sha256": hashlib.sha256(blobs[0]).hexdigest(),
    "base_sha256": hashlib.sha256(blobs[1]).hexdigest(),
    "mismatching_byte_offsets": [i for i, (a, b) in enumerate(zip(*blobs)) if a != b]
}
assert len(blobs[0]) == len(blobs[1]) == 568
assert blobs[0] == blobs[1]
raw_hash = run(["sha1sum", "build/GEDE01/main.dol"])
result["dol"] = {"expected_sha1": EXPECTED_DOL, "raw_sha1sum": raw_hash,
                 "verified": raw_hash.split()[0] == EXPECTED_DOL}
assert result["dol"]["verified"]
result["legal_audit"] = run(["python3", "tools/legal_audit.py"])
source = Path("src/game/game_fn_80135510.c").read_bytes()
result["source_sha256"] = hashlib.sha256(source).hexdigest()
result["hypothesis"] = (
    "Retail's register copy is produced by strength reduction of array indices. "
    "Taking &lbl_8064CF88[record_index], then incrementing record_index in a separate "
    "statement before the call, retains the two required induction registers. "
    "Using postincrement in the array subscript collapses them."
)
result["trial_evidence"] = f"eternal-darkness-decomp/reports/GEDE01/trials-{AID}.json"
(REPORTS / f"objdiff-{AID}.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({"canonical": result["canonical"], "relocation_strict": result["relocation-strict"],
                  "elf_relocations": len(relocations[0]), "raw_text_bytes_equal": True,
                  "dol": result["dol"], "legal_audit": result["legal_audit"]}, indent=2))
