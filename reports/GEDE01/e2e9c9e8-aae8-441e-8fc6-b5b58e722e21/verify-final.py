"""Run from eternal-darkness-decomp; record final canonical verification."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

out = Path("reports/GEDE01/e2e9c9e8-aae8-441e-8fc6-b5b58e722e21")
strict = Path("reports/GEDE01/objdiff-e2e9c9e8-aae8-441e-8fc6-b5b58e722e21.json")
canonical = out / "final-canonical.raw.json"
commands = []
def run(cmd):
    result = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    commands.append(dict(command=cmd, exit_code=result.returncode, output=result.stdout))
    (out / "final-commands.json").write_text(json.dumps(commands, indent=2) + "\n")
    print("$ " + " ".join(cmd), flush=True)
    print(result.stdout[-3000:], flush=True)
    if result.returncode:
        raise RuntimeError("Command failed; see final-commands.json")

run(["python3", "configure.py"])
run([".tools/bin/ninja", "-j2"])
run([".tools/bin/ninja", "-j2", "-v", "build/GEDE01/src/game/game_fn_80171BB4.o"])
run(["build/tools/objdiff-cli", "--version"])
base = ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_80171BB4"]
run(base + ["-o", str(canonical)])
run(base + ["-c", "function_reloc_diffs=name_address", "-o", str(strict)])
objects = ["build/GEDE01/obj/game/game_fn_80171BB4.o", "build/GEDE01/src/game/game_fn_80171BB4.o"]
for obj in objects:
    run(["build/binutils/powerpc-eabi-readelf", "-rW", obj])
run(["sha1sum", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"])
run(["python3", "tools/legal_audit.py"])
run(["git", "diff", "--check"])

# Direct ELF32 big-endian comparison; symbol names/addends independently decoded.
def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02"
    shoff = struct.unpack_from(">I", data, 32)[0]
    shsize, count, names_index = struct.unpack_from(">HHH", data, 46)
    headers = [struct.unpack_from(">10I", data, shoff + i * shsize) for i in range(count)]
    def contents(i):
        h = headers[i]
        return data[h[4]:h[4]+h[5]]
    def cstr(table, offset):
        return table[offset:table.index(b"\0", offset)].decode()
    names = contents(names_index)
    indices = {cstr(names, h[0]): i for i, h in enumerate(headers)}
    text_index = indices[".text"]
    relocations = []
    for i, h in enumerate(headers):
        if h[1] != 4 or h[7] != text_index:
            continue
        symbols = contents(h[6])
        strings = contents(headers[h[6]][6])
        for offset in range(h[4], h[4]+h[5], h[9] or 12):
            site, info, addend = struct.unpack_from(">IIi", data, offset)
            symbol = struct.unpack_from(">IIIBBH", symbols, (info >> 8) * 16)
            relocations.append(dict(offset=site, type=info & 255, target=cstr(strings, symbol[0]), addend=addend))
    return dict(path=path, sha256=hashlib.sha256(data).hexdigest(), text=contents(text_index), relocations=relocations)

left, right = map(elf, objects)
ltext, rtext = left.pop("text"), right.pop("text")
differences = []
for offset in range(0, max(len(ltext), len(rtext)), 4):
    l, r = ltext[offset:offset+4], rtext[offset:offset+4]
    if l != r:
        differences.append(dict(offset=offset, retail_hex=l.hex(), generated_hex=r.hex()))
result = dict(retail=left, generated=right, retail_text_size=len(ltext), generated_text_size=len(rtext),
              raw_text_equal=ltext == rtext, instruction_word_differences=differences,
              relocations_equal=left["relocations"] == right["relocations"],
              source_sha256=hashlib.sha256(Path("src/game/game_fn_80171BB4.c").read_bytes()).hexdigest())
(out / "elf-comparison.json").write_text(json.dumps(result, indent=2) + "\n")
assert hashlib.sha1(Path("build/GEDE01/main.dol").read_bytes()).hexdigest() == "ea24b6af954876ce072562ff39cdb4c81d32be1f"
print(json.dumps(result, indent=2))
