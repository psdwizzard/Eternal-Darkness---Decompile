"""Run from eternal-darkness-decomp; restores the accepted C after testing.
Hypothesis: explicit register storage for conversion results changes MWCC's
interference/allocation ordering relative to the long-lived string base.
Each record preserves a unified source patch, commands, raw output and objdiff.
"""
import difflib
import hashlib
import json
from pathlib import Path
import subprocess

out = Path("reports/GEDE01/e2e9c9e8-aae8-441e-8fc6-b5b58e722e21")
source = Path("src/game/game_fn_80171BB4.c")
saved_source = source.read_text()
original = subprocess.check_output(["git", "show", "3c72fc0334ee3b3fe980baa76c30b49ef43d3566:eternal-darkness-decomp/src/game/game_fn_80171BB4.c"], text=True)
import sys
records = json.loads((out / "experiments.json").read_text()) if len(sys.argv) > 1 else []

def run(cmd):
    result = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    record = dict(command=cmd, exit_code=result.returncode, output=result.stdout)
    if result.returncode:
        raise RuntimeError(record)
    return record

variants = [("baseline", original)]
for names in [("arg1",), ("arg2",), ("arg3",), ("arg4",), ("arg5",),
              ("arg1", "arg2", "arg3", "arg4", "arg5")]:
    variant = original
    for name in names:
        variant = variant.replace("    int " + name + ";", "    register int " + name + ";")
    variants.append(("register-" + "-".join(names), variant))
# A separate aggregate-storage test of the same allocation hypothesis:
# MWCC may scalar-replace this automatic record in a different order.
variant = original
for name in ("arg1", "arg2", "arg3", "arg4", "arg5"):
    variant = variant.replace("    int " + name + ";\n", "")
variant = variant.replace("    unsigned char clamped3;", "    struct { int arg4, arg2, arg1, arg3, arg5; } args;\n    unsigned char clamped3;")
import re
head, body = variant.split("    const char* strings", 1)
for name in ("arg1", "arg2", "arg3", "arg4", "arg5"):
    body = re.sub(r"\b" + name + r"\b", "args." + name, body)
variants.append(("aggregate-arguments", head + "    const char* strings" + body))
# Include the base and clamped values in the scalar-replaced aggregate.
for include_clamps in (False, True):
    variant = original
    fields = ["int arg4", "int arg2", "int arg1", "int arg3", "int arg5", "const char* strings"]
    names = ["arg4", "arg2", "arg1", "arg3", "arg5", "strings"]
    if include_clamps:
        fields += ["unsigned char clamped3", "signed char clamped5"]
        names += ["clamped3", "clamped5"]
    for field in fields:
        if field == "const char* strings":
            variant = variant.replace("    const char* strings = lbl_8024FF00;", "    args.strings = lbl_8024FF00;")
        else:
            variant = variant.replace("    " + field + ";\n", "")
    head, body = variant.split("    args.strings", 1)
    for name in names:
        body = re.sub(r"\b" + name + r"\b", "args." + name, body)
    variant = head + "    struct { " + "; ".join(fields) + "; } args;\n    args.strings" + body
    variants.append(("aggregate-base" + ("-and-clamps" if include_clamps else ""), variant))
# Narrow aggregate storage to the base and selected scalars. The array-pointer
# member variant also preserves array-address (addi 0) semantics on first use.
for selected in [(), ("arg1",), ("arg2",), ("arg4",), ("arg3",), ("arg5",), ("arg1", "arg3"), ("arg1", "arg5"), ("arg3", "arg5"), ("arg1", "arg3", "arg5")]:
    for array_base in (False, True):
        variant = original
        for name in selected:
            variant = variant.replace("    int " + name + ";\n", "")
            variant = re.sub(r"\b" + name + r"\b", "args." + name, variant)
        field = "const char (*strings)[1]" if array_base else "const char* strings"
        decl = "    struct { " + "; ".join(["int " + n for n in selected] + [field]) + "; } args;\n"
        init = "    args.strings = (const char (*)[1])lbl_8024FF00;" if array_base else "    args.strings = lbl_8024FF00;"
        variant = variant.replace("    const char* strings = lbl_8024FF00;", "MARKER")
        variant = re.sub(r"\bstrings\b", "(*args.strings)" if array_base else "args.strings", variant)
        variant = variant.replace("MARKER", decl + init)
        variants.append(("narrow-base" + ("-" + "-".join(selected) if selected else "") + ("-array" if array_base else ""), variant))
# Refine the successful split: retained scalar arg4/arg2 and aggregate base,
# arg1/arg3/arg5. Compare clamp membership and structure-member addressing.
for clamp_members in [(), ("clamped3",), ("clamped5",), ("clamped3", "clamped5")]:
    for struct_address in (False, True):
        names = ["arg1", "arg3", "arg5"] + list(clamp_members)
        types = {"arg1": "int", "arg3": "int", "arg5": "int", "clamped3": "unsigned char", "clamped5": "signed char"}
        variant = original
        for name in names:
            variant = variant.replace("    " + types[name] + " " + name + ";\n", "")
            variant = re.sub(r"\b" + name + r"\b", "args." + name, variant)
        base_type = "const struct StringBase* strings" if struct_address else "const char* strings"
        decl = "    struct { " + "; ".join([types[n] + " " + n for n in names] + [base_type]) + "; } args;\n"
        init = "    args.strings = (const struct StringBase*)lbl_8024FF00;" if struct_address else "    args.strings = lbl_8024FF00;"
        variant = variant.replace("    const char* strings = lbl_8024FF00;", "MARKER")
        variant = re.sub(r"\bstrings\b", "args.strings->text" if struct_address else "args.strings", variant)
        variant = variant.replace("MARKER", decl + init)
        if struct_address:
            variant = "struct StringBase { char text[1]; };\n" + variant
        variants.append(("refine" + ("-" + "-".join(clamp_members) if clamp_members else "") + ("-struct-address" if struct_address else ""), variant))
# Last-instruction address expressions on the best storage split.
best = next(v for n, v in variants if n == "narrow-base-arg1-arg3")
for name, expr in [
    ("address-of-element", "&args.strings[0]"),
    ("integer-member-address", "(const char*)((unsigned int)args.strings + 0)"),
    ("array-lvalue-address", "(const char (*)[1024])args.strings"),
]:
    # The array-lvalue form is dereferenced to preserve the original parameter.
    if name == "array-lvalue-address":
        expr = "*(" + expr + ")"
    variant = best.replace("state, args.strings, 5,", "state, " + expr + ", 5,")
    variants.append(("last-" + name, variant))
try:
    for name, variant in variants:
        if len(sys.argv) > 1 and not name.startswith(sys.argv[1]):
            continue
        records = [r for r in records if r["name"] != name]
        source.write_text(variant)
        rec = dict(name=name, source_sha256=hashlib.sha256(variant.encode()).hexdigest(),
                   patch="".join(difflib.unified_diff(original.splitlines(True), variant.splitlines(True), fromfile=str(source), tofile=str(source))), commands=[])
        rec["commands"].append(run([".tools/bin/ninja", "-j2", "-v", "build/GEDE01/src/game/game_fn_80171BB4.o"]))
        obj = Path("build/GEDE01/src/game/game_fn_80171BB4.o")
        rec["object_sha256"] = hashlib.sha256(obj.read_bytes()).hexdigest()
        diffpath = out / (name + ".raw.json")
        rec["commands"].append(run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_80171BB4", "-c", "function_reloc_diffs=name_address", "-o", str(diffpath)]))
        data = json.loads(diffpath.read_text())
        sym = next(s for s in data["left"]["symbols"] if s["name"] == "fn_80171BB4")
        rec["match_percent"] = sym["match_percent"]
        rec["raw_objdiff"] = str(diffpath)
        records.append(rec)
        (out / "experiments.json").write_text(json.dumps(records, indent=2) + "\n")
        print(name, sym["match_percent"], rec["object_sha256"], flush=True)
finally:
    source.write_text(saved_source)
    result = run([".tools/bin/ninja", "-j2", "-v", "build/GEDE01/src/game/game_fn_80171BB4.o"])
    (out / "restore-command.json").write_text(json.dumps(result, indent=2) + "\n")
