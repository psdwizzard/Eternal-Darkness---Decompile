# fn_801A9FA4 — attempt 5

Result: matched. Canonical and `function_reloc_diffs=name_address` objdiff both
report 100% for the 996-byte function and its eight-byte constant. Independent
ELF checks confirm byte-identical `.text` and `.sdata2`, and equality of all
31 relocation offsets, types, targets, and addends. The promoted C function
links into a full DOL with SHA-1 `ea24b6af954876ce072562ff39cdb4c81d32be1f`.

## New compiler hypothesis and source change

Reviewed the preserved source changes from `e17ae7a4` and `0b035f28`, their
result envelopes, and the preserved 99.65864% raw objdiff. The existing base
already had the corrected word-width call signature. The initial new
hypothesis was that separating the emitter's live range at queue submission
would change coalescing. That, pointer parameter type changes, and equivalent
guard shapes were neutral. Recorded declaration/branch-layout probes also
failed to improve the frontier; malformed experimental declarations were
rejected by the compiler and never retained.

A differently typed local alias revealed the useful distinction: the
compiler retained that local's allocation identity instead of coalescing it
with the original `void*` parameter. The initial integer alias moved object
to r29 and position to r26 but swapped divisor/packed and moved the initial
copy. Declaring packed before divisor and initializing scale after the local
object alias corrected both issues. An opaque `struct SoundEmitter*` alias
produced the same code without integer-pointer round trips or an invented
object layout. A plain `void*` alias was measured and did not preserve the
allocation, scoring 99.5984%.

The final source keeps the original void-pointer ABI, declares the typed
object alias between sound and packed, and performs scale extraction after
object initialization. This removes all 16 register differences. Before the
data split, the result was 99.97992%, with only the compiler-local conversion
constant relocation remaining.

## Constant ownership and strict relocation evidence

Added only `.sdata2 start:0x80650E58 end:0x80650E60` to this function's existing
split registration. The bytes are `4330000000000000`, the compiler's unsigned
integer-to-double bias. This was previously unassigned data, so no neighboring
function or data registration was edited. With its actual constant in the
same independent TU, objdiff pairs the local `@67` with the retail constant
at section offset zero and reaches 100%, including strict mode. No objdiff
mapping, relaxation, compiler policy, or verification gate was changed.

The independent ELF verifier preserves raw relocation names and addends in
its report. Defined local data targets are compared by section, offset plus
addend, and exact section bytes; external targets must have the same name,
value, and addend. All 31 agree. The full linked DOL hash independently checks
the final addresses and contents, including this constant at 0x80650E58.

## Reproduction and scope

From `eternal-darkness-decomp`, run:

```sh
python3 configure.py
.tools/bin/ninja -j2
python3 reports/GEDE01/verify-a6a930f0-73d9-48bb-a3c0-e6ea1a1692ef.py
```

The compiler remains GC/1.3 (`mwcc_242_53`), with all original canonical
settings, including `-schedule off -opt nopeephole -use_lmw_stmw on`.
The exact compiler executable SHA-256 and build exit codes are in the build
metadata. Full build output, final canonical/strict objdiff, baseline, key
intermediate raw measurements, trial patches/results, and legal audit output
are preserved as assignment-specific reports. Trial paths inside the trial
report are relative to `eternal-darkness-decomp`; the envelope uses paths
relative to the worktree root.

Only the target source, its Matching registration, its constant split, and
assignment-specific reports are changed. No assembly, shared reconstruction,
private-input edits, neighboring edits, global-progress edits, or remote
pushes were used. The pre-existing unrelated `CLAUDE.md` modification is left
untouched and excluded from the commit.
