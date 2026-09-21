# fn_8018CB70 attempt 6

Base: `a30aee164a819a82b55a1c12054d4ce793a39d09`.

Reviewed preserved commits `6f72b6ed`, `3fc6e682`, `64ee6c2e`, `092446c7`, and `f2247cdc` through git show. Earlier work already tested explicit count-minus-eight bounds, declaration ordering, integer-address saved-pointer storage, and a register hint. The last attempt contains detailed raw verification; the rejected attempt documents the explicit-bound and declaration-order outcomes without reproducible probes. No previously documented variant was deliberately repeated except the retained baseline.

New hypothesis: sequential `*dest++` stores change pointer-induction lowering and register interference while the optimizer may recover the same store offsets. This produced a byte-identical object. The bounded follow-up tested equivalent inner/outer loop forms, rather than declaration order or manual unrolling.

| Probe | Bytes | Strict objdiff % | Object versus baseline |
| --- | ---: | ---: | --- |
| baseline | 424 | 95.896225 | Identical |
| sequential_postincrement | 424 | 95.896225 | Identical |
| inner_postincrement_test | 256 | 50.433964 | Different |
| outer_do_while | 424 | 95.896225 | Identical |
| outer_update_expression | 424 | 95.896225 | Identical |
| inner_inclusive_bound | 432 | 91.396225 | Different |

The postincrement test changes unrolling and shrinks the function to 256 bytes. The inclusive-bound form introduces extra count-minus-one/count-minus-nine values, grows the function to 432 bytes, and shifts the pointer and outer counter to r9/r10. Neither improves the baseline. Do/while and the outer update-expression forms are byte-identical to baseline. The initial reconstruction is retained unchanged, with its existing NonMatching registration and independent translation unit.

Exact probe sources, hypotheses, command arrays, exit codes, disassemblies, object hashes, and raw strict objdiff results are in the assignment's probes JSON. Reproduce with `python3 reports/GEDE01/probes-3f5313be-e7de-46b2-bfbf-2794eb1cf1b8.py` from `eternal-darkness-decomp`; its finally block restores the baseline source. The verification script rebuilds the restored source and captures configure, ninja, legal audit, DOL hash, readelf relocation tables, dtk ELF information, disassemblies, canonical objdiff, and strict name/address objdiff. All flags remain canonical.

The linked DOL uses the retail object for this NonMatching unit. Its expected hash validates the unchanged canonical link, not a claim that this reconstruction matches.
