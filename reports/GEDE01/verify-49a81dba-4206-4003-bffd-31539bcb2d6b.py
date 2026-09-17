"""Assignment-local verification; run from eternal-darkness-decomp."""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

ASSIGNMENT = "49a81dba-4206-4003-bffd-31539bcb2d6b"
REPORTS = Path("reports/GEDE01")
TARGET = "fn_800D607C"
UNIT = "main/game/game_fn_800D607C"
PREFIX = "eternal-darkness-decomp/"
EXPECTED_DOL = "ea24b6af954876ce072562ff39cdb4c81d32be1f"


def run(command):
    result = subprocess.run(command, text=True, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE, check=True)
    return {"command": command, "exit_code": result.returncode,
            "stdout": result.stdout, "stderr": result.stderr}


def text_section(path):
    data = path.read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02", "Expected ELF32 big-endian"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    shoff, entsize, count, stridx = header[6], header[11], header[12], header[13]
    sections = [struct.unpack_from(">10I", data, shoff + i * entsize)
                for i in range(count)]
    strings = sections[stridx]
    names = data[strings[4]:strings[4] + strings[5]]
    for section in sections:
        name = names[section[0]:].split(b"\0", 1)[0]
        if name == b".text":
            return data[section[4]:section[4] + section[5]]
    raise AssertionError("Missing .text")


def relocations(output):
    pattern = re.compile(
        r"^([0-9a-f]{8})\s+[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]+)"
        r"\s+(\S+)\s+([+-])\s+([0-9a-f]+)$", re.MULTILINE)
    return [{"offset": int(offset, 16), "type": kind,
             "target_symbol_value": int(value, 16), "target_name": name,
             "addend": int(addend, 16) * (-1 if sign == "-" else 1)}
            for offset, kind, value, name, sign, addend in pattern.findall(output)]


evidence = {
    "version": 1, "assignment_id": ASSIGNMENT, "target": TARGET,
    "command_cwd": "eternal-darkness-decomp",
    "hypothesis": "The ninth outgoing argument was misidentified: the existing callee "
                  "has eight parameters. Preserve the stack+8 store as a volatile local "
                  "copy, and use six independent one-word aggregates for noncontiguous "
                  "initializer/chosen values. No compiler setting changes.",
    "commands": [], "objdiff": {},
}
for mode, config in (("canonical", []),
                     ("relocation_name_address", ["-c", "functionRelocDiffs=name_address"]),
                     ("relocation_all", ["-c", "functionRelocDiffs=all"])):
    output = REPORTS / f"objdiff-{ASSIGNMENT}-{mode}.raw.json"
    command = ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", UNIT,
               TARGET, *config, "-o", str(output), "--format", "json"]
    evidence["commands"].append(run(command))
    result = json.loads(output.read_text())
    left = next(s for s in result["left"]["symbols"] if s["name"] == TARGET)
    right = next(s for s in result["right"]["symbols"] if s["name"] == TARGET)
    assert left["match_percent"] == 100.0
    assert int(left["size"]) == int(right["size"]) == 328
    evidence["objdiff"][mode] = {
        "raw_file": PREFIX + str(output), "match_percent": left["match_percent"],
        "target_size": left["size"], "generated_size": right["size"],
    }

objects = {"retail": Path("build/GEDE01/obj/game/game_fn_800D607C.o"),
           "generated": Path("build/GEDE01/src/game/game_fn_800D607C.o")}
evidence["elf_relocations"] = {}
texts = {}
for side, path in objects.items():
    raw = run(["readelf", "-rW", str(path)])
    symbols = run(["readelf", "-sW", str(path)])
    normalized = relocations(raw["stdout"])
    assert len(normalized) == 13
    evidence["elf_relocations"][side] = {
        "raw_readelf_relocations": raw, "raw_readelf_symbols": symbols,
        "normalized": normalized,
    }
    texts[side] = text_section(path)
assert evidence["elf_relocations"]["retail"]["normalized"] == evidence["elf_relocations"]["generated"]["normalized"]
assert texts["retail"] == texts["generated"]
assert len(texts["retail"]) == 328
evidence["text_bytes"] = {
    "equal": True, "size": 328,
    "sha256": {side: hashlib.sha256(data).hexdigest() for side, data in texts.items()},
    "relocation_offsets_types_resolved_names_values_and_explicit_addends_equal": True,
}
evidence["commands"].append(run(["build/tools/objdiff-cli", "--version"]))
evidence["commands"].append(run([".tools/bin/ninja", "-t", "commands",
                                  "build/GEDE01/src/game/game_fn_800D607C.o"]))
evidence["commands"].append(run(["python3", "tools/legal_audit.py"]))
dol_result = run(["sha1sum", "build/GEDE01/main.dol"])
assert dol_result["stdout"].split()[0] == EXPECTED_DOL
evidence["commands"].append(dol_result)
build_log = REPORTS / f"build-{ASSIGNMENT}.log"
assert "build/GEDE01/main.dol: OK" in build_log.read_text()
evidence["full_build_log"] = PREFIX + str(build_log)
evidence["full_build_commands"] = [{"command": ["python3", "configure.py"], "exit_code": 0},
                                   {"command": [".tools/bin/ninja", "-j2"], "exit_code": 0}]
evidence["build_log_line_endings"] = "CRLF normalized to LF; captured combined stdout/stderr otherwise unchanged."
evidence["split_validation"] = {"path": PREFIX + "config/GEDE01/splits.txt",
                                "unit": "game/game_fn_800D607C.c",
                                "start": "0x800D607C", "end": "0x800D61C4", "unchanged": True}
evidence["experiment_evidence"] = PREFIX + str(REPORTS / f"experiments-{ASSIGNMENT}.json")
evidence["preexisting_workspace_change"] = "CLAUDE.md was already modified on arrival; left untouched and excluded from commit under assignment file scope."
output = REPORTS / f"objdiff-{ASSIGNMENT}.json"
output.write_text(json.dumps(evidence, indent=2) + "\n")
envelope = {
    "version": 1, "assignment_id": ASSIGNMENT, "attempt": 5,
    "base_commit": "6016d3f4c0c792274df45f10e96285a940371077",
    "target": TARGET, "status": "matched", "evidence": [PREFIX + str(output)],
    "divergence": "",
}
(REPORTS / f"durable-{ASSIGNMENT}.json").write_text(json.dumps(envelope, indent=2) + "\n")
print(json.dumps({"canonical": 100.0, "relocation_strict": 100.0,
                  "text_bytes_equal": True, "relocations_equal": 13,
                  "dol_sha1": EXPECTED_DOL, "status": "matched"}))
