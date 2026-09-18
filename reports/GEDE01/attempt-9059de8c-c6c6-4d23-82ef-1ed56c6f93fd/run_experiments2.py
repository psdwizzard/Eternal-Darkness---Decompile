#!/usr/bin/env python3
from run_experiments import *
variants = {}
direct = recovered.replace("u8* object)", "u8* self)").replace("    register u8* self;\n", "").replace("    self = object;\n", "")
variants["direct-parameter"] = direct
variants["direct-entry-first"] = direct.replace("    u8* entries;\n", "").replace("    u8* vertex_data;", "    u8* entries;\n    u8* vertex_data;")
scoped = recovered.replace("    int vertex_offset;\n", "").replace("    int i;\n", "").replace("    for (i = 0, vertex_offset = 0;", "    {\n    int i;\n    int vertex_offset;\n    for (i = 0, vertex_offset = 0;").replace("    DCFlushRange(vertex_data", "    }\n\n    DCFlushRange(vertex_data")
variants["scoped-induction"] = scoped
variants["direct-entry-first-scoped"] = scoped.replace("u8* object)", "u8* self)").replace("    register u8* self;\n", "").replace("    self = object;\n", "").replace("    u8* entries;\n", "").replace("    u8* vertex_data;", "    u8* entries;\n    u8* vertex_data;")
variants["derived-shift-add"] = recovered.replace("    int vertex_offset;\n", "").replace("i = 0, vertex_offset = 0", "i = 0").replace("vertex_data + vertex_offset", "vertex_data + ((i << 4) + (i << 3))").replace("        vertex_offset += 0x18;\n", "")
try:
    results = [measure(name, code) for name, code in variants.items()]
    (OUT / "measurements2.json").write_text(json.dumps(results, indent=2) + "\n")
finally:
    SOURCE.write_text(recovered)
