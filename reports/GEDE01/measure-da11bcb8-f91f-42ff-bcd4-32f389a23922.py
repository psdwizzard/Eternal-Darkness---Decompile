"""Assignment-local measurement; run from eternal-darkness-decomp."""
import hashlib
import json
import subprocess
import sys
from pathlib import Path
assignment = 'da11bcb8-f91f-42ff-bcd4-32f389a23922'
out = Path(f'reports/GEDE01/objdiff-{assignment}.json')
command = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_801E995C', 'fn_801E995C', '-c', 'function_reloc_diffs=name_address', '-o', str(out), '--format', 'json']
r = subprocess.run(command, capture_output=True, text=True, check=True)
d = json.loads(out.read_text())
a, b = [next(s for s in d[k]['symbols'] if s['name'] == 'fn_801E995C') for k in ('left', 'right')]
m = [{'offset': x.get('instruction', {}).get('address', '0'), 'target': x.get('instruction', {}).get('formatted'), 'candidate': y.get('instruction', {}).get('formatted'), 'diff_kind': x.get('diff_kind')} for x,y in zip(a['instructions'],b['instructions']) if x.get('diff_kind')]
p = Path(f'reports/GEDE01/experiments-{assignment}.json')
rows = json.loads(p.read_text()) if p.exists() else []
rows.append({'hypothesis': sys.argv[1], 'command': command, 'returncode': r.returncode, 'stdout': r.stdout, 'stderr': r.stderr, 'source_sha256': hashlib.sha256(Path('src/game/game_fn_801E995C.c').read_bytes()).hexdigest(), 'score': a['match_percent'], 'target_size': a['size'], 'candidate_size': b['size'], 'raw_mismatches': m})
p.write_text(json.dumps(rows, indent=2)+'\n')
print(sys.argv[1], a['match_percent'], a['size'], b['size'], 'mismatches',len(m))
for x in m: print(hex(int(x['offset'])),x['target'],'|',x['candidate'])
