#!/usr/bin/env python3
"""Reproduce this assignment's byte, relocation, objdiff, and DOL checks."""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[2]
ASSIGNMENT = "97dc05b3-2167-4840-ab54-b8ef823283a3"
OUT = Path("reports/GEDE01")
TARGET = "fn_80063E64"
EXPECTED_DOL = "ea24b6af954876ce072562ff39cdb4c81d32be1f"
transcript = []


def run(args, output=None):
    result = subprocess.run(args, cwd=ROOT, text=True, capture_output=True)
    transcript.append({"command": args, "exit_status": result.returncode,
                       "stdout": result.stdout, "stderr": result.stderr})
    if output:
        (ROOT / OUT / f"{output}-{ASSIGNMENT}.log").write_text(result.stdout)
    result.check_returncode()
    return result.stdout


def text_section(path):
    data = (ROOT / path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    offset = struct.unpack_from(">I", data, 32)[0]
    stride, count, strings = struct.unpack_from(">HHH", data, 46)
    headers = [struct.unpack_from(">10I", data, offset + i * stride)
               for i in range(count)]
    table = headers[strings]
    names = data[table[4]:table[4] + table[5]]
    for header in headers:
        if names[header[0]:].split(b"\0")[0] == b".text":
            return data[header[4]:header[4] + header[5]]
    raise AssertionError("Missing .text")


def relocation_rows(raw):
    pattern = (r"^([0-9a-f]+)\s+[0-9a-f]+\s+(R_PPC_\w+)\s+"
               r"([0-9a-f]+)\s+(\S+)\s+([+-])\s+([0-9a-f]+)$")
    return [(int(offset, 16), kind, int(value, 16), name,
             int(addend, 16) * (-1 if sign == "-" else 1))
            for offset, kind, value, name, sign, addend
            in re.findall(pattern, raw, re.M)]


scores = {}
for mode in ("canonical", "strict"):
    output = OUT / f"{mode}-{ASSIGNMENT}.json"
    command = ["build/tools/objdiff-cli", "diff", "-p", ".", "-u",
               "main/game/game_fn_80063E64", TARGET, "-o", str(output),
               "--format", "json"]
    if mode == "strict":
        command += ["-c", "function_reloc_diffs=name_address"]
    run(command)
    diff = json.loads((ROOT / output).read_text())
    scores[mode] = {}
    for side in ("left", "right"):
        symbol = next(s for s in diff[side]["symbols"] if s["name"] == TARGET)
        scores[mode][side] = {"size": int(symbol["size"]),
                              "instructions": len(symbol["instructions"]),
                              "match_percent": symbol["match_percent"]}
        assert scores[mode][side] == {"size": 3284, "instructions": 821,
                                     "match_percent": 100.0}

run(["python3", "tools/fndiff.py", "game/game_fn_80063E64.c", TARGET], "fndiff")
objects = {"retail": "build/GEDE01/obj/game/game_fn_80063E64.o",
           "generated": "build/GEDE01/src/game/game_fn_80063E64.o"}
relocations = {}
text = {}
for side, path in objects.items():
    raw = run(["build/binutils/powerpc-eabi-readelf", "-rW", path],
              side + "-relocations")
    relocations[side] = relocation_rows(raw)
    text[side] = text_section(path)
assert len(relocations["retail"]) == 184
assert relocations["retail"] == relocations["generated"]
assert len(text["retail"]) == 3284 and text["retail"] == text["generated"]

dol = run(["sha1sum", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"])
assert all(line.split()[0] == EXPECTED_DOL for line in dol.splitlines())
assert len(dol.splitlines()) == 2
run(["cmp", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"])
run(["python3", "tools/legal_audit.py"])
run(["git", "diff", "--check"])
assert "# game/game_fn_80063E64.c: game (linked True)" in (ROOT / "build.ninja").read_text()

result = {"scores": scores, "relocations_per_side": 184,
          "relocation_offset_type_symbol_value_target_addend_equal": True,
          "text_bytes_equal": True,
          "text_sha256": hashlib.sha256(text["retail"]).hexdigest(),
          "dol_sha1": EXPECTED_DOL, "dol_bytes_equal": True,
          "source_sha256": hashlib.sha256((ROOT / "src/game/game_fn_80063E64.c").read_bytes()).hexdigest(),
          "compiler_sha256": hashlib.sha256((ROOT / "compilers/GC/1.3/mwcceppc.exe").read_bytes()).hexdigest(),
          "source_linked": True, "raw_commands": transcript}
(ROOT / OUT / f"verification-{ASSIGNMENT}.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({key: value for key, value in result.items() if key != "raw_commands"}, indent=2))
