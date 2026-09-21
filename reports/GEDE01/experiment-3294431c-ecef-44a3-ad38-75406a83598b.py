"""Assignment-local, reversible source lifetime probes. Run from project directory."""
import json, subprocess, hashlib
from pathlib import Path
ID = "3294431c-ecef-44a3-ad38-75406a83598b"
source = Path("src/game/game_fn_8008D5D4.c")
base = source.read_text()
records_path = Path(f"reports/GEDE01/probes-{ID}.json")
records = json.loads(records_path.read_text()) if records_path.exists() else []
def run(cmd):
    p = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return {"command": " ".join(cmd), "exit_code": p.returncode, "raw_output": p.stdout}
def probe(name, text):
    if any(r["name"] == name for r in records):
        return
    source.write_text(text)
    record = {"name": name, "source_sha256": hashlib.sha256(text.encode()).hexdigest(), "commands": []}
    record["commands"].append(run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_8008D5D4.o"]))
    if record["commands"][-1]["exit_code"] == 0:
        out = f"build/GEDE01/{ID}-probe.json"
        record["commands"].append(run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_8008D5D4", "fn_8008D5D4", "-o", out, "--format", "json-pretty"]))
        d = json.loads(Path(out).read_text())
        record["symbol_metadata"] = {side:[{k:v for k,v in s.items() if k != "instructions"} for s in d[side]["symbols"] if s["name"] == "fn_8008D5D4"][0] for side in ["left","right"]}
        record["report_sha256"] = hashlib.sha256(Path(out).read_bytes()).hexdigest()
    records.append(record)
    print(name, record.get("symbol_metadata", record["commands"]), flush=True)
    Path(f"reports/GEDE01/probes-{ID}.json").write_text(json.dumps(records, indent=2)+"\n")
try:
    probe("baseline", base)
    v = base.replace("    void* message;\n", "").replace("message", "effect")
    probe("reuse_effect_for_message", v)
    v = base.replace("    Runtime8008D5D4* runtime;\n", "").replace("runtime = fn_80201B8C(mode);", "mode = fn_80201B8C(mode);").replace("fn_801A717C(runtime)", "fn_801A717C(mode)").replace("runtime->value50", "((Runtime8008D5D4*)mode)->value50")
    probe("reuse_mode_for_runtime", v)
    probe("reuse_mode_runtime_and_effect_message", v.replace("    void* message;\n", "").replace("message", "effect"))
    probe("reuse_object_for_message", base.replace("        message = fn_801A717C(runtime);\n        fn_8012B344(object);", "        message = fn_801A717C(runtime);\n        fn_8012B344(object);\n        object = message;").replace("fn_801A7470(message", "fn_801A7470(object").replace("fn_801A74A0(message", "fn_801A74A0(object").replace("fn_801A74A8(message", "fn_801A74A8(object").replace("target, message)", "target, object)").replace("fn_801A7228(message)", "fn_801A7228(object)"))
    v = base.replace("extern void* fn_801A7498(void*);", "extern unsigned int fn_801A7498(void*);").replace("    void* target;", "    unsigned int target;").replace("fn_801A74A0(message, target)", "fn_801A74A0(message, (void*)target)")
    probe("unsigned_target_id", v)
    probe("signed_target_id", v.replace("unsigned int", "int"))
    for name in ["target", "mode", "object", "effect"]:
        import re
        v = base
        if name in ["target", "mode"]:
            v = v.replace(f"    void* {name};", f"    struct {{ void* p; }} {name};")
            start = v.index("    target =")
            v = v[:start] + re.sub(r"\b" + name + r"\b", name+".p", v[start:])
        else:
            v = v.replace(f"void* {name},", f"void* {name}_arg,").replace(f"void* {name})", f"void* {name}_arg)")
            start = v.index("    target =")
            v = v[:start] + f"    struct {{ void* p; }} {name};\n    {name}.p = {name}_arg;\n" + re.sub(r"\b" + name + r"\b", name+".p", v[start:])
        probe("scalar_replacement_"+name, v)
    import itertools, re
    for names in [("target","mode"),("target","object"),("target","effect"),("mode","object"),("mode","effect"),("target","mode","object"),("target","mode","effect"),("target","mode","object","effect")]:
        v = base
        for name in names:
            if name in ["target", "mode"]:
                v = v.replace(f"    void* {name};", f"    struct {{ void* p; }} {name};")
            else:
                v = v.replace(f"void* {name},", f"void* {name}_arg,").replace(f"void* {name})", f"void* {name}_arg)")
        start = v.index("    target =")
        body = v[start:]
        for name in names:
            body = re.sub(r"\b" + name + r"\b", name+".p", body)
        preamble = "".join(f"    struct {{ void* p; }} {name};\n    {name}.p = {name}_arg;\n" for name in names if name in ["object","effect"])
        probe("scalar_replacement_"+"_".join(names), v[:start]+preamble+body)
    v = base.replace("    void* message;", "    void* old_object;").replace("        message = fn_801A717C(runtime);\n        fn_8012B344(object);", "        old_object = object;\n        object = fn_801A717C(runtime);\n        fn_8012B344(old_object);")
    v = v.replace("message", "object")
    probe("overwrite_object_before_cleanup_call", v)
    v = base.replace("    void* message;", "    void* old_mode;").replace("        message = fn_801A717C(runtime);", "        mode = fn_801A717C(runtime);").replace("message", "mode")
    probe("overwrite_mode_with_message", v)
    decls = ["    void* target;", "    int value;", "    void* mode;", "    int flags;", "    int state;", "    Runtime8008D5D4* runtime;", "    void* message;"]
    import itertools
    for order in itertools.permutations([0,2,6]):
        rest = [1,3,4,5]
        v = base.replace("\n".join(decls), "\n".join(decls[i] for i in list(order)+rest))
        probe("declaration_priority_"+"_".join(map(str,order)), v)
    for order in itertools.permutations([0,2,3,5,6]):
        v = base.replace("\n".join(decls), "\n".join(decls[i] for i in list(order)+[1,4]))
        probe("persistent_declaration_order_"+"_".join(map(str,order)), v)
        if records[-1].get("symbol_metadata",{}).get("left",{}).get("match_percent") == 100:
            break
finally:
    source.write_text(base)
