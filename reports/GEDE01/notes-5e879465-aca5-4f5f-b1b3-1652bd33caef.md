# fn_801A7BA0 — attempt 5

The accepted base already contains the exact source blob from preserved commit
caa2e0210a73d85c279d26b2122cd0b02db07e8d; provenance records the identical Git blob
IDs and no source/registration/split delta between the two commits. No recovery
edit was necessary. The independent translation unit remains NonMatching and
covers only 0x801A7BA0–0x801A7D20. No canonical flag or registration changed.

## Prior attempts studied

- 3890db59: rejected compiler override (`-use_lmw_stmw on`); not repeated.
- 1d7be817: canonical 92.052086% baseline and helper/register/loop mismatch.
- ef7e290c: explicit retail-order induction updates scored 91.979164%; not repeated.
- caa2e021: direct format symbols scored 73.28125%; not repeated.

## Distinct hypothesis and result

Move `char* strings = lbl_80251528;` immediately after
`Set* set = fn_8015C390(2);`, with no other source change. This narrows the
string pointer's live range across the lookup call, testing whether register
coloring and prologue scheduling depend on that lifetime. The generated set
pointer moved from r31 to r30 (retail's register), but strings moved to r31
instead of retail r29; x remained r23 instead of r31. String-address materialization
moved after the lookup. The compiler retained _savegpr_23/_restgpr_23 and 392
bytes. Strict score fell to 88.71875%; the source was restored exactly.
The raw experimental objdiff and compiler output are preserved separately.
No alternative C translation unit was retained.

## Reproduction (from eternal-darkness-decomp)

```sh
python3 configure.py
.tools/bin/ninja -j2
build/tools/objdiff-cli diff -p . -u main/game/game_fn_801A7BA0 -o reports/GEDE01/objdiff-canonical-ASSIGNMENT.json --format json-pretty fn_801A7BA0
build/tools/objdiff-cli diff -p . -u main/game/game_fn_801A7BA0 -o reports/GEDE01/objdiff-ASSIGNMENT.json -c function_reloc_diffs=name_address --format json-pretty fn_801A7BA0
sha1sum build/GEDE01/main.dol
sha1sum -c config/GEDE01/build.sha1
build/binutils/powerpc-eabi-objdump -drt build/GEDE01/obj/game/game_fn_801A7BA0.o build/GEDE01/src/game/game_fn_801A7BA0.o
python3 tools/legal_audit.py
```

Replace ASSIGNMENT with 5e879465-aca5-4f5f-b1b3-1652bd33caef.
Full configure, build (exit 0), hash, canonical and strict objdiff, and raw
object disassembly/relocations are preserved. Objdiff's inferred R_PPC_NONE
string addends are 60, 72, 84, 108, 132 on both sides. The actual ELF relocation
records are also available in the objdump output; the two helper calls are
extra generated relocations. This is not a relocation-strict match.

## Final divergence

Canonical and relocation-strict objdiff both measure 92.052086%: retail is 384 bytes, generated is 392. GC/1.3 emits addi r11 plus R_PPC_REL24 calls to _savegpr_23 (0x14) and _restgpr_23 (0x174), with absent/null objdiff addends, instead of retail inline stmw r23 (0x18) and lmw r23 (0x16c). Nonvolatile allocation rotates (retail x r31/entry r23/i r24/draw_y r25/detail_x r26/status_x r27/line_y r28/strings r29/set r30; generated r23/r24/r25/r26/r27/r28/r29/r30/r31). Prologue string-address scheduling differs. Generated loop increments i/entry/line_y at 0x154/0x158/0x15c versus retail line_y/i/entry at 0x150/0x154/0x158. Delaying the string-pointer initialization until after fn_8015C390 retained helper calls and 392 bytes and reduced strict similarity to 88.71875%; reverted.

The DOL SHA-1 is ea24b6af954876ce072562ff39cdb4c81d32be1f. Because this
function is NonMatching, the normal link uses its retail object; the hash
verifies the canonical project build, not a match of the reconstructed C.
Only assignment reports are committed. The pre-existing CLAUDE.md modification
is left untouched. No assembly, compiler pragma, object patch, runtime change,
progress edit, neighboring-function edit, or private binary is included.
