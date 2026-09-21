"""Reproduce the assignment's byte and ELF relocation comparison.

Run from eternal-darkness-decomp; reads only this worktree's build outputs.
"""
import json
from pathlib import Path
import struct

ASSIGNMENT = "220bb767-e8ac-4a16-b193-4938a484f4cd"


def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02", "Expected ELF32 big endian"
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    sections = [struct.unpack_from(">10I", data, header[6] + i * header[11])
                for i in range(header[12])]

    def contents(section):
        return data[section[4]:section[4] + section[5]]

    def string(table, offset):
        return table[offset:table.index(b"\0", offset)].decode()

    names = contents(sections[header[13]])
    text_index = next(i for i, s in enumerate(sections)
                      if string(names, s[0]) == ".text")
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symtab = sections[section[6]]
        strings = contents(sections[symtab[6]])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from(">IIi", data, offset)
            symbol = struct.unpack_from(">IIIBBH", data,
                                        symtab[4] + (info >> 8) * symtab[9])
            relocations.append({"offset": address, "type": info & 255,
                                "target": string(strings, symbol[0]),
                                "addend": addend})
    return contents(sections[text_index]), relocations


target_path = "build/GEDE01/obj/game/game_fn_801A852C.o"
base_path = "build/GEDE01/src/game/game_fn_801A852C.o"
target, target_relocations = elf(target_path)
base, base_relocations = elf(base_path)
diff = json.loads(Path(f"reports/GEDE01/objdiff-{ASSIGNMENT}.json").read_text())
instructions = {}
relocation_instructions = {}
for side in ("left", "right"):
    symbol = next(s for s in diff[side]["symbols"] if s["name"] == "fn_801A852C")
    instructions[side] = [i["instruction"] for i in symbol["instructions"]
                          if "instruction" in i]
    relocation_instructions[side] = [i for i in instructions[side] if "relocation" in i]

output = {
    "assignment_id": ASSIGNMENT,
    "target_path": target_path,
    "base_path": base_path,
    "target_size": len(target),
    "base_size": len(base),
    "bytes_equal": target == base,
    "differing_instruction_offsets": [i for i in range(0, max(len(target), len(base)), 4)
                                      if target[i:i + 4] != base[i:i + 4]],
    "target_elf_relocations": target_relocations,
    "base_elf_relocations": base_relocations,
    "elf_relocation_targets_and_addends_equal": target_relocations == base_relocations,
    "objdiff_relocation_bearing_instruction_count": {
        side: len(items) for side, items in relocation_instructions.items()},
    "objdiff_relocation_bearing_instructions_equal":
        relocation_instructions["left"] == relocation_instructions["right"],
    "instruction_differences": [
        {"offset": int(left.get("address", 0)),
         "target": left["formatted"], "base": right["formatted"]}
        for left, right in zip(instructions["left"], instructions["right"])
        if left != right],
}
print(json.dumps(output, indent=2))
assert len(target) == len(base) == 168
assert target_relocations == base_relocations
assert relocation_instructions["left"] == relocation_instructions["right"]
