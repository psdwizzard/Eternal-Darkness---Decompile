import difflib, hashlib, json, pathlib, subprocess
ROOT = pathlib.Path(__file__).resolve().parents[2]
ID = "3c952361-ba01-426a-be54-2d29cc63214a"
REPORT = ROOT / "reports/GEDE01"
SOURCE = ROOT / "src/game/game_fn_8018F948.c"
BASE = subprocess.check_output(["git", "show", "046901eed9dfdbb26827c43fb177d390fbc781a1:eternal-darkness-decomp/src/game/game_fn_8018F948.c"], cwd=ROOT).decode()
LOG = []
def run(args):
    p = subprocess.run(args, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    LOG.append({"command": args, "cwd": "eternal-darkness-decomp", "exit_code": p.returncode, "output": p.stdout})
    (REPORT / ("commands-"+ID+".json")).write_text(json.dumps(LOG, indent=2)+"\n")
    if p.returncode: raise RuntimeError(p.stdout)
    return p.stdout

def probe(name, source):
    SOURCE.write_text(source)
    patch = "".join(difflib.unified_diff(BASE.splitlines(True), source.splitlines(True), fromfile="a/eternal-darkness-decomp/src/game/game_fn_8018F948.c", tofile="b/eternal-darkness-decomp/src/game/game_fn_8018F948.c"))
    (REPORT / ("probe-"+ID+"-"+name+".patch")).write_text(patch)
    run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_8018F948.o"])
    output = "reports/GEDE01/objdiff-"+ID+"-"+name+".json"
    run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_8018F948", "fn_8018F948", "-o", output, "--format", "json-pretty"])
    d = json.loads((ROOT / output).read_text())
    sym = next(s for s in d['left']['symbols'] if s['name']=='fn_8018F948')
    right = next(s for s in d['right']['symbols'] if s['name']=='fn_8018F948')
    result = {"probe": name, "match_percent": sym['match_percent'], "retail_size": sym['size'], "compiled_size": right['size'], "object_sha256": hashlib.sha256((ROOT/'build/GEDE01/src/game/game_fn_8018F948.o').read_bytes()).hexdigest()}
    LOG.append(result)
    (REPORT / ("commands-"+ID+".json")).write_text(json.dumps(LOG, indent=2)+"\n")
    print(json.dumps(result), flush=True)

try:
    run([".tools/bin/ninja", "-t", "commands", "build/GEDE01/src/game/game_fn_8018F948.o"])
    probe('baseline', BASE)
    probe('memcpy-coordinates', BASE.replace('fixed = lbl_80651D80;', 'memcpy(&fixed, &lbl_80651D80, sizeof(fixed));'))
    original = """    u8 i;
    u8* cfg;
    void* fst;
    void* snd;
    u8* obj;
    ShortCoord3 fixed;
    u32 first_value;
    u32 second_value;
    u8 count;
    u8* entry;
    u8* values;"""
    reordered = """    u8* entry;
    u8* cfg;
    void* snd;
    void* fst;
    u8* obj;
    u8* values;
    u8 count;
    u8 i;
    ShortCoord3 fixed;
    u32 first_value;
    u32 second_value;"""
    probe('declaration-order', BASE.replace(original, reordered))
    helper = 'static inline ShortCoord3 fixed_coordinates(void)\n{\n    return lbl_80651D80;\n}\n\n'
    probe('inline-coordinate-return', BASE.replace('void fn_8018F948(', helper + 'void fn_8018F948(').replace('fixed = lbl_80651D80;', 'fixed = fixed_coordinates();'))
    knr = 'void fn_8018F948(object, first, second, config)\nu8* config;\nvoid* second;\nvoid* first;\nu8* object;'
    probe('knr-parameter-declarations', BASE.replace('void fn_8018F948(u8* object, void* first, void* second, u8* config)', knr))
finally:
    SOURCE.write_text(BASE)
    run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_8018F948.o"])
