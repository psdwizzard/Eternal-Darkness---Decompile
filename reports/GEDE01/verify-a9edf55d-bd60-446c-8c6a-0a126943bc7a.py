"""Assignment-local verification; run from eternal-darkness-decomp after Ninja."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ASSIGNMENT = "a9edf55d-bd60-446c-8c6a-0a126943bc7a"
REPORTS = Path("reports/GEDE01")
EXPECTED_SHA1 = "ea24b6af954876ce072562ff39cdb4c81d32be1f"


def run(command):
    result = subprocess.run(command, capture_output=True, text=True)
    record = dict(command=command, exit_code=result.returncode,
                  stdout=result.stdout, stderr=result.stderr)
    assert result.returncode == 0, record
    return record


def elf_text(path):
    blob = Path(path).read_bytes()
    assert blob[:6] == b"\x7fELF\x01\x02", "Expected ELF32 big-endian"
    header = struct.unpack_from(">HHIIIIIHHHHHH", blob, 16)
    sections = [struct.unpack_from(">IIIIIIIIII", blob, header[5] + i * header[10])
                for i in range(header[11])]
    names_section = sections[header[12]]
    names = blob[names_section[4]:names_section[4] + names_section[5]]

    def string(data, offset):
        return data[offset:data.index(b"\0", offset)].decode()

    text_index = next(i for i, section in enumerate(sections)
                      if string(names, section[0]) == ".text")
    text_section = sections[text_index]
    code = blob[text_section[4]:text_section[4] + text_section[5]]
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symbols = sections[section[6]]
        strings_section = sections[symbols[6]]
        strings = blob[strings_section[4]:strings_section[4] + strings_section[5]]
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", blob, offset)
            symbol = struct.unpack_from(">IIIBBH", blob,
                                        symbols[4] + (info >> 8) * symbols[9])
            relocations.append(dict(offset=address, type=info & 255,
                                    symbol=string(strings, symbol[0]), addend=addend))
    return dict(path="eternal-darkness-decomp/" + path,
                text_size=len(code), text_sha256=hashlib.sha256(code).hexdigest(),
                relocations=relocations), code


measurements = {}
for mode, options in (("canonical", []), ("relocation_strict", ["-c", "functionRelocDiffs=all"])):
    record = run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u",
                  "main/game/game_fn_801E3020", "fn_801E3020", *options,
                  "-o", "-", "--format", "json"])
    raw = json.loads(record.pop("stdout"))
    for side in ("left", "right"):
        symbol = next(s for s in raw[side]["symbols"] if s["name"] == "fn_801E3020")
        assert int(symbol["size"]) == 728
        assert all(i.get("diff_kind", "DIFF_NONE") == "DIFF_NONE"
                   for i in symbol["instructions"])
    symbol = next(s for s in raw["left"]["symbols"] if s["name"] == "fn_801E3020")
    assert symbol["match_percent"] == 100
    record["raw_objdiff"] = raw
    measurements[mode] = record

target, target_code = elf_text("build/GEDE01/obj/game/game_fn_801E3020.o")
candidate, candidate_code = elf_text("build/GEDE01/src/game/game_fn_801E3020.o")
assert target_code == candidate_code
assert target["relocations"] == candidate["relocations"]
assert len(target["relocations"]) == 28
dol = Path("build/GEDE01/main.dol").read_bytes()
assert hashlib.sha1(dol).hexdigest() == EXPECTED_SHA1
assert dol == Path("orig/GEDE01/sys/main.dol").read_bytes()
assert "build/GEDE01/main.dol: OK" in (REPORTS / f"build-{ASSIGNMENT}.log").read_text()

verification = dict(
    version=1, assignment_id=ASSIGNMENT, target="fn_801E3020", compiler="GC/1.3",
    compiler_policy_changed=False, canonical_match_percent=100,
    relocation_strict_match_percent=100, measurements=measurements,
    elf_comparison=dict(target=target, candidate=candidate, bytes_equal=True,
                        relocation_offsets_types_targets_addends_equal=True),
    relocation_note="28 ELF RELA entries agree exactly. Objdiff additionally resolves the lwz displacement to lbl_802FC5BC+12, producing 29 relocation-bearing instructions.",
    dol_sha1=run(["sha1sum", "build/GEDE01/main.dol"]), retail_dol_bytes_equal=True,
    legal_audit=run(["python3", "tools/legal_audit.py"]),
    source_sha256=hashlib.sha256(Path("src/game/game_fn_801E3020.c").read_bytes()).hexdigest(),
    configure_command=dict(command="python3 configure.py", exit_code=0),
    build_command=dict(command=".tools/bin/ninja -j2", exit_code=0),
    build_log_note="Compiler CRLF line endings normalized to LF; output text otherwise preserved.",
    configure_log=f"eternal-darkness-decomp/reports/GEDE01/configure-{ASSIGNMENT}.log",
    build_log=f"eternal-darkness-decomp/reports/GEDE01/build-{ASSIGNMENT}.log",
    experiments=f"eternal-darkness-decomp/reports/GEDE01/experiments-{ASSIGNMENT}.json",
    diagnosis="Explicit ObjectState subobject and PositionWords aggregate assignment reproduce retail address formation and copy scheduling. Removing a spurious third fn_801E8328 argument, restoring a mutable global declaration, and grouping the discriminator with its KindInfo input recover the exact final load schedule and register allocation. The callee source independently supports its two-word signature. No compiler or gate changes.",
)
(REPORTS / f"objdiff-{ASSIGNMENT}.json").write_text(json.dumps(verification, indent=2) + "\n")
print(json.dumps(dict(canonical=100, relocation_strict=100, text_bytes=728,
                     elf_relocations=28, dol_sha1=EXPECTED_SHA1,
                     legal_audit=verification["legal_audit"]["stdout"]), indent=2))
