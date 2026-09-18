#!/usr/bin/env python3
from run_experiments import *
import re
variants = {}
# Group non-escaping locals into aggregates to test MWCC scalar-replacement order.
groups = {
    "aggregate-buffers": ["vertex_data", "index_data", "color_data"],
    "aggregate-entry-buffers": ["entries", "vertex_data", "index_data", "color_data"],
    "aggregate-buffers-entry": ["vertex_data", "index_data", "color_data", "entries"],
    "aggregate-cursors": ["entries", "color"],
    "aggregate-induction": ["vertex_offset", "i"],
    "aggregate-all-pointers": ["entries", "vertex_data", "index_data", "color_data", "color", "self"],
}
for name, group in groups.items():
    code = recovered
    for var in group:
        code = re.sub(r"    (?:register )?(?:u8\*|int) " + var + r";\n", "", code)
    code = re.sub(r"\b(" + "|".join(group) + r")\b", r"state.\1", code)
    fields = " ".join(("int " if x in ("i", "vertex_offset") else "u8* ") + x + ";" for x in group)
    code = code.replace("{\n    u8 count;", "{\n    struct { " + fields + " } state;\n    u8 count;")
    variants[name] = code
try:
    results = [measure(name, code) for name, code in variants.items()]
    (OUT / "measurements3.json").write_text(json.dumps(results, indent=2) + "\n")
finally:
    SOURCE.write_text(recovered)
