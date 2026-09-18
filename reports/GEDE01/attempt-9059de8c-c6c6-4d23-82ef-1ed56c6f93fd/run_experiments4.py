#!/usr/bin/env python3
from run_experiments import *
import re
variants = {}
# One-element arrays provide a different scalar-replacement input than struct fields.
for name, var, typ in [("array-entry", "entries", "u8*"), ("array-offset", "vertex_offset", "int"), ("array-color", "color", "u8*")]:
    code = recovered.replace("    " + typ + " " + var + ";\n", "")
    code = re.sub(r"\b" + var + r"\b", var + "[0]", code)
    code = code.replace("    u8 count;", "    " + typ + " " + var + "[1];\n    u8 count;")
    variants[name] = code
# Distinguish pointer induction from integer-address induction without moving any loads.
variants["integer-entry-address"] = recovered.replace("    u8* entries;", "    unsigned long entry_address;").replace("entries = *(u8**)(self + 0x4C);", "entry_address = (unsigned long)*(u8**)(self + 0x4C);").replace("entries[0x21]", "((u8*)entry_address)[0x21]").replace("entries[0x20]", "((u8*)entry_address)[0x20]").replace("fn_80188C1C(entries,", "fn_80188C1C((void*)entry_address,").replace("entries += 0x38;", "entry_address += 0x38;")
variants["long-offset"] = recovered.replace("    int vertex_offset;", "    long vertex_offset;")
# Constant subtraction makes the same induction recurrence but changes its IR form.
variants["negative-offset"] = recovered.replace("vertex_data + vertex_offset", "vertex_data - vertex_offset").replace("vertex_offset += 0x18;", "vertex_offset -= 0x18;")
try:
    results = [measure(name, code) for name, code in variants.items()]
    (OUT / "measurements4.json").write_text(json.dumps(results, indent=2) + "\n")
finally:
    SOURCE.write_text(recovered)
