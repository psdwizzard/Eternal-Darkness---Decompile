import json, subprocess, pathlib
ID='45c922c0-94a4-434c-83a3-43d7e6891437'
root=pathlib.Path(__file__).resolve().parents[2]
source=root/'src/game/game_fn_80175BB8.c'
original=source.read_text()
report=root/'reports/GEDE01'
records=[]
def run(args):
    p=subprocess.run(args,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    record={'command':args,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'raw_output':p.stdout}
    records.append(record)
    (report/f'commands-{ID}.json').write_text(json.dumps(records,indent=2)+'\n')
    if p.returncode: raise RuntimeError(record)
    return p.stdout
variants=[('baseline',original),('array_pointer',original.replace('const char* strings = lbl_8024FF00;', 'const char (*strings)[0x1000] = (const char (*)[0x1000])lbl_8024FF00;').replace('state, strings,','state, *strings,').replace('strings + 0x','*strings + 0x'))]
try:
    for label,code in variants:
        source.write_text(code)
        records.append({'variant':label,'hypothesis':'Pointer to character array retains array-to-pointer address formation at each use without changing accesses or compiler options.' if label!='baseline' else 'Accepted source baseline','source':code})
        run(['.tools/bin/ninja','-j2','-v','build/GEDE01/src/game/game_fn_80175BB8.o','build/GEDE01/obj/game/game_fn_80175BB8.o'])
        for strict in (False,True):
            output=f'reports/GEDE01/objdiff-{ID}-{label}-{"strict" if strict else "canonical"}.json'
            args=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80175BB8','fn_80175BB8','-o',output,'--format','json-pretty']
            if strict: args+=['-c','function_reloc_diffs=name_address']
            run(args)
            data=json.loads((root/output).read_text())
            print(label,strict, str(data)[:400],flush=True)
finally:
    source.write_text(original)
    (report/f'commands-{ID}.json').write_text(json.dumps(records,indent=2)+'\n')
