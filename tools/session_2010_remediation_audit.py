#!/usr/bin/env python3
import ast
import json
from pathlib import Path


def load(path):
    return json.loads(Path(path).read_text())


tree = ast.parse(Path("configure.py").read_text())
paths = [
    node.args[1].value
    for node in ast.walk(tree)
    if isinstance(node, ast.Call)
    and isinstance(node.func, ast.Name)
    and node.func.id == "Object"
    and len(node.args) >= 2
    and isinstance(node.args[0], ast.Name)
    and node.args[0].id == "NonMatching"
    and isinstance(node.args[1], ast.Constant)
    and isinstance(node.args[1].value, str)
]
report = load("build/GEDE01/report.json")
by_source = {
    unit.get("metadata", {}).get("source_path", "").removeprefix("src/"): unit
    for unit in report["units"]
}
units = [by_source[path] for path in paths if path in by_source]
cluster = sorted(
    (
        (unit.get("measures", {}).get("fuzzy_match_percent"), unit["metadata"]["source_path"])
        for unit in units
        if 99.8 <= unit.get("measures", {}).get("fuzzy_match_percent", -1) <= 99.92
    ),
    reverse=True,
)
print(
    f"current calls={len(paths)} unique={len(set(paths))} mapped={len(units)} "
    f"unmapped={sum(path not in by_source for path in paths)} "
    f"exact_100_candidates={sum(unit.get('measures', {}).get('fuzzy_match_percent') == 100.0 for unit in units)} "
    f"retail_code_bytes={sum(int(unit.get('measures', {}).get('total_code', 0)) for unit in units)} "
    f"retail_data_bytes={sum(int(unit.get('measures', {}).get('total_data', 0)) for unit in units)} "
    f"functions={sum(int(unit.get('measures', {}).get('total_functions', 0)) for unit in units)} "
    f"report_units={len(report['units'])}"
)
print(f"cluster_99.8_to_99.92 count={len(cluster)}")
for score, source in cluster:
    print(f"cluster score={score} source={source}")

session_1810 = load("reports/GEDE01/nonmatching-100-percent-consolidation-session-1810.json")
print(
    f"history session=1810 candidates_documented={len(session_1810['candidates'])} "
    f"reclaimed_documented={sum(item.get('status_after') == 'Matching' for item in session_1810['candidates'])}"
)
for session in (1890, 1970):
    inventory = load(
        f"reports/GEDE01/nonmatching-100-percent-consolidation-session-{session}.json"
    )["inventory"]
    print(
        f"history session={session} candidates_documented={inventory['aggregate_fuzzy_100_candidates']} "
        f"reclaimed_documented={inventory['reclaimed_registered_objects']}"
    )
current = load("reports/GEDE01/nonmatching-100-percent-consolidation-session-2010.json")
print(
    f"history session=2010 candidates_documented={current['current_inventory']['aggregate_fuzzy_100_candidates']} "
    f"reclaimed_documented={current['current_inventory']['reclaimed_objects']}"
)

chain = load("../.darkfoundry/decomp-chain-state.json")
frontier = load("reports/GEDE01/frontier-801FB270-801FB3B4-session-2009.json")
progress = load("reports/GEDE01/progress.json")
print(
    f"chain assigned_target={chain['assigned_target']} accepted_frontier={chain['accepted_frontier']} "
    f"candidate_frontier={chain['candidate_frontier']}"
)
print(f"frontier next_target={frontier['next_target']}")
print(
    f"progress session_2009_range={progress['session_2009']['range']} "
    f"frontier_evidence={progress['session_2009']['frontier_evidence']}"
)
