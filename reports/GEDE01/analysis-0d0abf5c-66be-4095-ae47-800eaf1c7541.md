# fn_801F8748, attempt 5

Assignment: `0d0abf5c-66be-4095-ae47-800eaf1c7541`.
Accepted base: `87cff7e78f5eeac624b3daa63233124010364280`.
Result: attempted; retained as NonMatching under the unchanged GC/1.3 registration
and existing `-use_lmw_stmw on` option. No configuration, split, compiler-policy,
neighboring-source, runtime, or global-progress changes were needed.

## Preserved work and new hypotheses

Studied source and reports from `61e5094a6a5f5cf1a8c5146bc4bb700c180d960e`,
`5c2be83f3361994071ef7e17f41c9b1651a514d5`,
`075e3687ff8b4ec8011697346b02ef3a493497b3`, and
`ee30a1a57d429708c08990c17382b509a8f9b883` through `git show`.
Recovered the last commit's useful StatePart/GlobalState decomposition and retained
the accepted base's local order, control flow, and pre-negation sum structure.
The earlier lifetime and lmw/stmw experiments were not repeated as new discoveries.

The previous 0x2C-byte Vec3Workspace was an **unverified frame-size hypothesis**,
not a recovered type. Callee analysis disproves that allocation size: fn_802114E0
writes a 48-byte matrix, including a four-byte write at offset 44. fn_80211710
reads paired singles at offsets 0, 8, 16, 24, 32, and 40 from its first argument,
covering the same 48 bytes. The verification script extracts these offsets and
widths from the retail-backed linked callees and asserts complete coverage of
bytes 0 through 47. The raw measured metadata is in the verification log.

Existing independent callers corroborate the matrix interpretation:
`eternal-darkness-decomp/src/game/game_fn_801F800C.c` declares Matrix34 and passes
it to both callees; `eternal-darkness-decomp/src/game/game_fn_801861C4.c` declares
the producer with a quaternion input. Neither caller was edited or shared into
this reconstruction. The final TU defines its own `float Matrix34[3][4]`.
Its local starts at stack offset 0x58 and ends at 0x88; the compiler naturally
produces the retail 0xB0 frame and r25-r31 save area at 0x94. No unused workspace
padding remains. This explains the earlier score without claiming the old
44-byte workspace was correct.

The second successful hypothesis concerns the two plane stores. Previously the
second assignment read the first destination back, causing MWCC to emit `frsp`
while forwarding the stored float. A float dot-product temporary, followed by
two independent negated stores in retail order, emits the retail `fmuls`,
`fmadds`, `fneg` sequence and uses the same result for both stores without `frsp`.
The score improves from 89.46896% to 90.1931% under the same pooled-relocation
comparison settings; generated text shrinks from 552 to 548 bytes.

Source-level address hypotheses were also measured: StatePart arrays, typed byte
storage, an integer-address conversion, register-qualified pointers, an inline C
accessor, a global array, and single-element member arrays. These did not improve
the final candidate. Repeating direct global references worsened the score to
86.848274% and introduced repeated symbol materialization. No new compiler flags
or pragmas were used. Only the final independent C reconstruction is retained;
trial source differences and measured summaries are in assignment reports.

## Remaining divergence

Retail text is 580 bytes; the candidate is 548 bytes. Both canonical and
`function_reloc_diffs=all` comparisons measure 90.1931%. The existing default
PowerPC pool-relocation analysis is retained in both comparisons.

Eight address instructions remain absent after compiler folding:

- Retail derives the second position through base + 0x660, then + 0x198;
  the candidate uses one + 0x7F8. The first position similarly folds
  base + 0 followed by + 0x198 into one + 0x198.
- Retail rematerializes two StatePart bases before the six position stores;
  the candidate folds the y/z stores directly into r31-relative offsets.
- Retail rematerializes two StatePart bases for the plane stores; the candidate
  stores at r31 + 0x85C and r31 + 0x1FC.
- Retail materializes the two ray bases at + 0xCC0 and + 0xD48 before active-flag
  stores at + 0x40; the candidate stores directly at + 0xD00 and + 0xD88.

Related argument-move/instruction scheduling and relocation offsets therefore
differ. The frame, saved-register set, vector slots, final FP operation sequence,
and plane-store order now agree. This is not a byte match.

## Reproduction and verification

From `eternal-darkness-decomp`, run:

```
python3 reports/GEDE01/verify-0d0abf5c-66be-4095-ae47-800eaf1c7541.py
```

The script records exact commands, raw outputs, and exit statuses for
`python3 configure.py`, `.tools/bin/ninja -j2`, the effective compiler command,
canonical and relocation-strict objdiff, relocation tables with symbol names and
addends, DOL SHA-1, source/object SHA-256 identities, and legal audit. Both objects
have 25 ELF relocations; their ordered types, targets, and addends agree, but
their offsets do not. Equal relocation identities alone are not a match.

Expected and verified DOL SHA-1:
`ea24b6af954876ce072562ff39cdb4c81d32be1f`.
Because this TU remains NonMatching, the canonical DOL uses the retail object;
the hash establishes preservation of the canonical image, not correctness of
the attempted C object. No generated binary or private input is committed.

The pre-existing harness modification to `CLAUDE.md` is left untouched and is
excluded from the assignment commit. Trial comparison files were transient;
their measured section summaries are preserved in the trials JSON, while the
two final comparison files preserve the full raw objdiff outputs.

Report logs normalize CRLF and trailing whitespace for Git checks; command output
content and exit statuses are otherwise preserved.
