# fn_801AB50C — attempt 5

Matched on accepted base a145c5141d474cc1f4ed458043998355dc1ad13e.
The source on this base was already identical to preserved commit
ffd6ad60b996eb8a728ce52181697722c25e045f. Its raw historical strict report
was inspected with git show; it was not copied as new evidence. Earlier
700d9ed078e12ee895933af9568b80cf2193b895 and
24684ed79dff6b8967fd39d7fb0c391db62f2a2f commit summaries and the supplied prior
attempt diagnoses were reviewed before experiments.

## New hypotheses and measurements

* Assign the three special-ID volume loads inside their guarded conditions,
  preserving the global guard before the load. This avoids the historical
  failed unconditional-hoisting variant and removes three register moves.
* Use conditional expressions for inactive-state clamps. Split the 0x1E6
  readiness test from the threshold test: retail skips the case when
  fn_80048688 returns zero; the former combined test incorrectly cleared
  lbl_8064D2E0 on that path. These changes plus the unsigned zero test on
  fn_801C9078 measured 98.03902%, 1936 bytes.
* The fixed two-argument fn_801B0B64 prototype is valid for **all** calls.
  The first handle load already supplies r4 across the switch comparisons.
  Prior interpretations of apparent one-argument calls missed that lifetime.
  The implementation in src/game/game_fn_801B0B64.c confirms (Entry*, int).
* src/game/game_fn_801AAE68.c confirms float precedes the position pointer.
  Restoring this argument order resolves call setup scheduling. Its first
  argument is unsigned short; fn_800486E8 forwards fn_800E4918, whose source
  returns unsigned short and whose retail assembly returns an lhzx result.
  That return type avoids an unnecessary truncation and restores register
  allocation. The position helper is declared void*, matching its own TU.
* Truncate the first volume clamp before forming the second conditional
  clamp, preserving the byte semantics and lifetime boundary. With the
  prototype fixes the measured score became 99.69815%, then 99.97536%,
  both at 1948 bytes. Only the active-state initial/target load order remained.
* Reusing a local limit in the final conditional regressed to 99.76386%,
  1944 bytes. Expanding the active-state min expression directly instead
  places the initial-volume operand first while preserving the retail
  conditional branch. Final result: 100%, 1948 bytes. Only this final C
  reconstruction is retained.

The unsigned compare is after fn_801C9078, not fn_801AB3CC as the previous
diagnosis stated. The fn_801C9078 implementation consumes its pointer in r3;
the call now explicitly passes record, which is already resident in r3.

## Final gates

Canonical compiler: GC/1.3, unchanged per-object -schedule off,
-opt nopeephole, -use_lmw_stmw on and unchanged project defaults.
The compiler command is recorded in verification JSON. No assembly,
postprocessing, compiler policy change, or neighboring function edit.
Only this object's configure.py registration changed to Matching; its
existing independent TU and split boundaries were retained.

Fresh default and functionRelocDiffs=all objdiff outputs both report 100%.
The assignment-local verification script independently checks raw .text
byte equality and all 57 ELF RELA tuples (offset, type, target name, signed
addend), then verifies the DOL SHA-1. It also verifies the link inputs use
the C object and exclude this function's retail object. Run it from
eternal-darkness-decomp:

```
python3 configure.py
.tools/bin/ninja -j2
build/tools/objdiff-cli diff -1 build/GEDE01/obj/game/game_fn_801AB50C.o -2 build/GEDE01/src/game/game_fn_801AB50C.o -o reports/GEDE01/canonical-7decd9c1-770e-4027-9b68-ce04a9cc18bd.json fn_801AB50C
build/tools/objdiff-cli diff -1 build/GEDE01/obj/game/game_fn_801AB50C.o -2 build/GEDE01/src/game/game_fn_801AB50C.o -c functionRelocDiffs=all -o reports/GEDE01/objdiff-7decd9c1-770e-4027-9b68-ce04a9cc18bd.json fn_801AB50C
python3 reports/GEDE01/verify-7decd9c1-770e-4027-9b68-ce04a9cc18bd.py
```

The completed build log includes the DOL hash gate passing. Expected and
measured SHA-1: ea24b6af954876ce072562ff39cdb4c81d32be1f. Legal audit passes.
Build warnings about .ignored sections are pre-existing linker warnings.
No tracked global progress or README file changed. The pre-existing
CLAUDE.md modification is excluded from the commit.
