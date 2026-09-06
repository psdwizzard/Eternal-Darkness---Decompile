#!/usr/bin/env python3
"""Validate declaration counts and call-site evidence in a drift proposal."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

import declaration_drift_proposal
import signature_audit


ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report", type=Path, required=True)
    parser.add_argument("--source", type=Path, default=ROOT / "src/game")
    parser.add_argument(
        "--retail-evidence",
        type=Path,
        default=ROOT / "config/GEDE01/retail-return-shapes.json",
    )
    args = parser.parse_args()

    report = json.loads(args.report.read_text(encoding="utf-8"))
    source = args.source.resolve()
    retail_evidence = args.retail_evidence.resolve()
    audit = signature_audit.audit(source, retail_evidence)
    eligible = list(audit["return_register_contradictions"])
    eligible.extend(audit["abi_divergent"])
    eligible.sort(key=lambda item: (-int(item["declarations"]), str(item["symbol"])))
    by_symbol = {item["symbol"]: item for item in eligible}
    assert [item["symbol"] for item in report["symbols"]] == [
        item["symbol"] for item in eligible[:declaration_drift_proposal.TOP_SYMBOLS]
    ]
    truths = audit["ground_truth_by_symbol"]
    print(f"AUDIT declarations={audit['declarations']} symbols={audit['symbols']}")

    variant_total = 0
    declaration_total = 0
    call_total = 0
    believed_total = 0
    for item in report["symbols"]:
        symbol = item["symbol"]
        measured = by_symbol[symbol]
        assert item["declaration_count"] == measured["declarations"]
        assert item["total_affected_tu_count"] == measured["affected_translation_units"]
        assert item["affected_translation_units"] == measured["translation_units"]
        measured_variants = {
            (variant["signature"], variant["count"])
            for variant in measured["variants"]
        }
        measured_signatures = {signature for signature, _ in measured_variants}
        truth = truths.get(symbol)
        reading = item["believed_correct_reading"]
        assert item["confidence"] in {"high", "low"}
        assert set(item["confidence_by_component"]) == {"return_shape", "parameters"}
        assert set(item["confidence_by_component"].values()) <= {"high", "low"}
        definition_grounded = (
            truth is not None and truth.get("kind") == "definition"
        )
        if definition_grounded:
            assert reading["status"] == "resolved"
            assert reading["declaration"] == truth["declaration"]
            assert item["confidence"] == "high"
            assert item["confidence_by_component"] == {
                "return_shape": "high", "parameters": "high"
            }
        else:
            if reading["declaration"] is None:
                assert truth is not None
                assert truth.get("kind") == "retail-epilogue"
                assert reading["status"] == "return-shape-only"
                assert reading["return_shape"] == truth["return_shape"]
                assert item["confidence_by_component"] == {
                    "return_shape": "high", "parameters": "low"
                }
            else:
                assert reading["status"] == "resolved"
                assert reading["declaration"] in measured_signatures

        expected_disagreeing_sites = sorted({
            site
            for variant in measured["variants"]
            if variant["signature"] != reading["declaration"]
            for site in variant["sites"]
        })
        expected_disagreeing_tus = sorted({
            site.rsplit(":", 1)[0] for site in expected_disagreeing_sites
        })
        assert item["disagreeing_declaration_sites"] == expected_disagreeing_sites
        assert item["disagreeing_translation_units"] == expected_disagreeing_tus
        assert item["estimated_blast_radius_tus"] == len(expected_disagreeing_tus)
        assert reading["confidence_rationale"]

        if truth is not None and truth.get("kind") == "retail-epilogue":
            assert item["confidence_by_component"] == {
                "return_shape": "high", "parameters": "low"
            }
            assert item["confidence"] == "low"

        union: set[str] = set()
        for variant in item["competing_declarations"]:
            assert (variant["declaration"], variant["count"]) in measured_variants
            declaration_sites = variant["declaration_sites"]
            declaring_tus = sorted({
                site.rsplit(":", 1)[0] for site in declaration_sites
            })
            expected_calls = sorted(
                call
                for tu in declaring_tus
                for call in declaration_drift_proposal.call_sites(
                    ROOT / tu, symbol, tu
                )
            )
            assert variant["count"] == len(declaration_sites)
            assert variant["call_site_evidence"] == expected_calls
            assert not (set(declaration_sites) & set(expected_calls))
            variant_total += 1
            declaration_total += len(declaration_sites)
            call_total += len(expected_calls)
            union.update(expected_calls)

        believed_calls = reading["call_site_evidence"]
        assert believed_calls == sorted(union)
        believed_total += len(union)
        print(
            f"SYMBOL name={symbol} declarations={measured['declarations']} "
            f"affected_tus={measured['affected_translation_units']} "
            f"variants={len(item['competing_declarations'])} "
            f"variant_call_sites={sum(len(v['call_site_evidence']) for v in item['competing_declarations'])} "
            f"believed_correct_call_sites={len(union)} status=valid"
        )

    print(
        f"TOTAL symbols={len(report['symbols'])} variants={variant_total} "
        f"declaration_sites={declaration_total} variant_call_sites={call_total} "
        f"believed_correct_call_sites={believed_total} invalid_call_sites=0 "
        f"source_rewrites={report['proposal_summary']['source_rewrites_applied']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
