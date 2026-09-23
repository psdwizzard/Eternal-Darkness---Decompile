#!/usr/bin/env python3
"""Assignment-local experiments; execute from eternal-darkness-decomp.

Run with baseline, early_font, inline_store, or register_bases.
Each run writes the selected variant, builds it, and appends raw comparisons.
Run baseline last to restore the accepted source; then run python3 configure.py
and .tools/bin/ninja -j2. No compiler flags or registrations are changed.
"""
import json, subprocess, pathlib, difflib, sys
source = pathlib.Path('src/game/game_fn_801E5BD8.c')
evidence = pathlib.Path('reports/GEDE01/objdiff-c5162fde-1812-4cfe-b53f-683f1d07070f.json')
base = subprocess.check_output(['git','show','9727a7fd2b1efcc36d49b4342317f31794f898ef:eternal-darkness-decomp/src/game/game_fn_801E5BD8.c'],text=True)
def run(argv):
    p = subprocess.run(argv,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    return {'cwd':'eternal-darkness-decomp','argv':argv,'returncode':p.returncode,'output':p.stdout}
def measure(name, text):
    source.write_text(text)
    record = {'name':name,'source_diff':''.join(difflib.unified_diff(base.splitlines(True),text.splitlines(True),fromfile='accepted-base',tofile=name)), 'commands':[]}
    command=run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801E5BD8.o'])
    record['commands'].append(command)
    if command['returncode']==0:
        for kind, config in [('canonical',[]),('relocation_strict',['-c','function_reloc_diffs=name_address'])]:
            command=run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801E5BD8','fn_801E5BD8','-o','-','--format','json']+config)
            output=command.pop('output'); command['raw_json']=json.loads(output); record[kind]=command
        s=next(s for s in record['relocation_strict']['raw_json']['left']['symbols'] if s['name']=='fn_801E5BD8')
        print(name,s.get('match_percent'),flush=True)
        for side in ['left','right']:
            sym=next(s for s in record['relocation_strict']['raw_json'][side]['symbols'] if s['name']=='fn_801E5BD8')
            record[side+'_instructions']=[{'address':i['instruction'].get('address','0'),'formatted':i['instruction']['formatted']} for i in sym['instructions'] if 'instruction' in i]
    else: print(name,command['output'],flush=True)
    data=json.loads(evidence.read_text());data['experiments'].append(record);evidence.write_text(json.dumps(data,indent=2)+'\n')
    return record
if __name__ == '__main__':
    name=sys.argv[1]
    text=base
    if name=='early_font':
        text=text.replace('            slots->strings[index] = string;', '            void* font = lbl_8064D568;\n            slots->strings[index] = string;').replace('slots->fonts[index] = lbl_8064D568;', 'slots->fonts[index] = font;')
    elif name=='inline_store':
        helper='static inline void store_slot(u8** strings, u32* indices, void** fonts, u32 index, u8* string, void* font)\n{\n    strings[index] = string;\n    indices[index] = index;\n    fonts[index] = font;\n}\n\n'
        text=text.replace('int fn_801E5BD8',helper+'int fn_801E5BD8')
        text=text.replace('            slots->strings[index] = string;\n            slots->indices[index] = index;\n            slots->fonts[index] = lbl_8064D568;', '            store_slot(slots->strings, slots->indices, slots->fonts, index, string, lbl_8064D568);')
    elif name=='register_bases':
        text=text.replace('            slots->strings[index] = string;', '            register u8** strings = slots->strings;\n            register u32* indices = slots->indices;\n            register void** fonts = slots->fonts;\n            strings[index] = string;')
        text=text.replace('slots->indices[index]', 'indices[index]').replace('slots->fonts[index]', 'fonts[index]').replace('slots->strings[2]', 'strings[2]')
    elif name!='baseline': raise ValueError(name)
    measure(name,text)
