import pathlib, subprocess, json, difflib, hashlib
ROOT=pathlib.Path.cwd()
ID='2b641f5c-55e8-47f6-8a73-b1b3757163c0'
SOURCE=pathlib.Path('src/game/game_fn_80093D20.c')
REPORT=pathlib.Path('reports/GEDE01')
base=subprocess.check_output(['git','show','0433a0513c00e533d6912ea87bf6daca38e39555:eternal-darkness-decomp/src/game/game_fn_80093D20.c'],text=True)
results=[]
def run(name, source):
    SOURCE.write_text(source)
    build=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80093D20.o']
    p=subprocess.run(build,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    entry={'name':name,'source_patch_from_base':''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile='base',tofile=name)), 'source_sha256':hashlib.sha256(source.encode()).hexdigest(),'build_command':build,'build_exit_code':p.returncode,'build_raw':p.stdout}
    if p.returncode==0:
        raw=REPORT/f'objdiff-{ID}-{name}.raw.json'
        cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80093D20','fn_80093D20','-o',str(raw),'--format','json']
        q=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        entry.update(diff_command=cmd,diff_exit_code=q.returncode,diff_raw=q.stdout,raw_report=str(raw))
        if q.returncode==0:
            d=json.loads(raw.read_text())
            s=next(x for x in d['left']['symbols'] if x['name']=='fn_80093D20')
            entry.update(score=s['match_percent'],size=next(x for x in d['right']['symbols'] if x['name']=='fn_80093D20')['size'],differences=sum(x.get('diff_kind','DIFF_NONE')!='DIFF_NONE' for x in s['instructions']))
    results.append(entry)
    (REPORT/f'experiments-{ID}.json').write_text(json.dumps(results,indent=2)+'\n')
    print(name,entry.get('score'),entry.get('size'),entry.get('differences'),flush=True)
    return entry
if __name__=='__main__':
    original_source = SOURCE.read_text()
    try:
        run('baseline',base)
        guard=base.replace('    if (converted_resource != 0) {\n        if (runtime->kind', '    if (converted_resource == 0) return;\n    {\n        if (runtime->kind')
        run('null_guard',guard)
        split=base.replace('            if (source_id == current_id && runtime->state != 0 &&\n                ((*runtime->state & 0x00020000) == 0)) {','            if (source_id != current_id) goto finish_resource;\n            if (runtime->state == 0) goto finish_resource;\n            if ((*runtime->state & 0x00020000) != 0) goto finish_resource;\n            {').replace('        fn_80128C28(converted_resource, fn_8003CB6C, id);','finish_resource:\n        fn_80128C28(converted_resource, fn_8003CB6C, id);')
        run('shared_cleanup',split)
        run('guards_combined',split.replace('    if (converted_resource != 0) {\n        if (runtime->kind','    if (converted_resource == 0) return;\n    {\n        if (runtime->kind'))
        ladder=base.replace('        return;\n    }\n\n    if (room != lbl_8064D18C)', '    } else if (room != lbl_8064D18C)').replace('        return;\n    }\n\n    converted_resource = fn_801294DC(resource, 0x18, 0x20, 10);', '    } else {\n    converted_resource = fn_801294DC(resource, 0x18, 0x20, 10);')
        ladder=ladder[:-2]+'    }\n}\n'
        run('else_ladder',ladder)
    finally:
        SOURCE.write_text(original_source)
