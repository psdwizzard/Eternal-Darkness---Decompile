"""Reproduce assignment evidence; run from eternal-darkness-decomp/."""
import hashlib
import json
from pathlib import Path
import re
import shlex
import subprocess

AID = "0d0abf5c-66be-4095-ae47-800eaf1c7541"
REPORTS = Path("reports/GEDE01")
TARGET = "build/GEDE01/obj/game/game_fn_801F8748.o"
CANDIDATE = "build/GEDE01/src/game/game_fn_801F8748.o"
SOURCE = Path("src/game/game_fn_801F8748.c")
EXPECTED = "ea24b6af954876ce072562ff39cdb4c81d32be1f"


with (REPORTS / f"verification-{AID}.log").open("w") as log:
    def run(args):
        log.write("$ " + shlex.join(args) + "\n")
        log.flush()
        result = subprocess.run(args, text=True, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT)
        log.write(result.stdout)
        log.write(f"EXIT {result.returncode}\n")
        log.flush()
        result.check_returncode()
        return result.stdout

    run(["python3", "configure.py"])
    run([".tools/bin/ninja", "-j2"])
    run([".tools/bin/ninja", "-t", "commands", CANDIDATE])
    run(["build/tools/objdiff-cli", "-V"])
    canonical = REPORTS / f"objdiff-canonical-{AID}.json"
    strict = REPORTS / f"objdiff-{AID}.json"
    run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u",
         "main/game/game_fn_801F8748", "--format", "json-pretty",
         "-o", str(canonical)])
    run(["build/tools/objdiff-cli", "diff", "-1", TARGET, "-2", CANDIDATE,
         "-c", "function_reloc_diffs=all", "--format", "json-pretty",
         "-o", str(strict)])
    for name, path in [("canonical", canonical), ("relocation-strict", strict)]:
        diff = json.loads(path.read_text())
        log.write(json.dumps({"comparison": name,
                              "retail": diff["left"]["sections"][0],
                              "candidate": diff["right"]["sections"][0]}) + "\n")

    relocations = []
    for obj in [TARGET, CANDIDATE]:
        output = run(["build/binutils/powerpc-eabi-readelf", "-rW", obj])
        entries = []
        for line in output.splitlines():
            fields = line.split()
            if len(fields) >= 7 and fields[2].startswith("R_PPC_"):
                entries.append({"offset": fields[0], "type": fields[2],
                                "target": fields[4], "addend": " ".join(fields[5:])})
        relocations.append(entries)
    identity = lambda entries: [(e["type"], e["target"], e["addend"]) for e in entries]
    log.write(json.dumps({"relocation_counts": list(map(len, relocations)),
                          "ordered_types_targets_addends_equal":
                          identity(relocations[0]) == identity(relocations[1]),
                          "relocation_offsets_equal":
                          relocations[0] == relocations[1]}) + "\n")

    # Preserve measured memory-access metadata, not a callee disassembly dump.
    for start, stop, mode in [(0x802114E0, 0x80211584, "psq_st"),
                              (0x80211710, 0x80211764, "psq_l")]:
        cmd = ["build/binutils/powerpc-eabi-objdump", "-d", "-M", "gekko",
               f"--start-address={start:#x}", f"--stop-address={stop:#x}",
               "build/GEDE01/main.elf"]
        result = subprocess.run(cmd, text=True, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, check=True)
        accesses = [(int(offset), 4 if width == "1" else 8)
                    for offset, width in re.findall(
                        mode + r"\s+f\d+,(\d+)\(r3\),([01]),0", result.stdout)]
        covered = {byte for offset, size in accesses for byte in range(offset, offset + size)}
        assert covered == set(range(48)), accesses
        log.write("$ " + shlex.join(cmd) + " | extract r3 paired-single access offsets/widths\n")
        log.write(json.dumps({"callee": f"fn_{start:08X}",
                              "accesses_offset_width": accesses,
                              "covered_bytes": len(covered),
                              "required_extent": max(covered) + 1}) + "\nEXIT 0\n")

    run(["sha1sum", "build/GEDE01/main.dol"])
    assert hashlib.sha1(Path("build/GEDE01/main.dol").read_bytes()).hexdigest() == EXPECTED
    run(["sha256sum", str(SOURCE), TARGET, CANDIDATE])
    run(["python3", "tools/legal_audit.py"])
    run(["git", "diff", "--check"])
    assert not re.search(r"\b(?:asm|__asm|__asm__)\b", SOURCE.read_text())
    log.write("Source check: independent C translation unit; no assembly.\n")
