# fn_8017C1C8 — attempt 5

## Result

Matched with the existing canonical GC/1.3 flags. Canonical and relocation-strict objdiff-cli 3.6.1 both report 100% for all 232 bytes. The unrelocated text bytes also compare equal directly. The promoted Matching translation unit is linked into a complete DOL identical to the supplied retail DOL, SHA-1 `ea24b6af954876ce072562ff39cdb4c81d32be1f`.

## Distinct hypothesis and measurements

Read the preserved attempt-4 source and raw report in commit `50ae74fa800ea9d652c45f5ebceb1ce997ad884e`, the attempt-3 envelope in `ce65096445dbaf3cc40e0a542ed87f47fa4d319c`, and the handoff diagnoses of earlier attempts. The strongest reconstruction was already present at the accepted base. Previous expression/type experiments left only r0 versus r4 at offsets 0x60 and 0x64.

The new hypothesis was that the result has a second use as an argument to the diagnostic call, making r4 the appropriate register. Inspection found neighboring callers declaring `fn_8017BA60(char*, int)` and passing their result. The retail string at `lbl_80250FC4` reads `Unmount result:`. This is evidence for a missing result argument rather than a compiler-version difference.

1. A variadic diagnostic declaration with `request->result` as the second argument selected the exact retail load/compare register. It measured 98.27586% and 236 bytes because the variadic ABI added `crclr cr1eq` before the call. Raw output is in the assignment-specific variadic probe report.
2. A fixed `char*, int` declaration and the same second argument produced 100% and 232 bytes, without the extra CR instruction. This matches the established neighboring declarations. The diagnostic callee's existing empty implementation is not edited.

The final independent C translation unit retains the previous volatile-qualified value-index read and changes only the diagnostic signature/call plus its now-obsolete NonMatching comment. Its existing split boundaries remain 0x8017C1C8–0x8017C2B0. Only this function's registration was promoted to Matching. No compiler policy, neighboring source, runtime, README, or global progress file was edited.

## Verification

Run the assignment-specific verifier from `eternal-darkness-decomp`. It records the compiler hash and Ninja compiler command, reruns both objdiff modes, compares ELF text directly, enumerates every emitted relocation including names and explicit addends, compares linked function bytes and the complete DOL, and runs the legal audit. Current ELF files contain 13 RELA records each; all match and all addends are zero. The prior handoff's nine R_PPC_NONE metadata records are not present as additional relocation entries in these freshly built ELF files.

The build log captures `python3 configure.py` and `.tools/bin/ninja -j2` after promotion. Existing linker warnings about ignored sections remain; the build and DOL check exit successfully. The unrelated pre-existing `CLAUDE.md` modification was excluded from the commit. No generated binaries or private inputs are included. No model change, delegation, or remote push occurred.
