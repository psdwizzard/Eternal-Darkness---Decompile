# fn_80131460 — attempt 5

Accepted base: b536cc89679d53d68e411187419d9e335bbe96e4.
Preserved attempt inspected: 4a4893bfd171d4a04c1ffc53993491aa806f7726.
The accepted source was already identical to that preserved source. Earlier
attempt diagnoses and the preserved source diff were reviewed before experiments.
The initial canonical build and fresh baseline reproduced 99.55109%.

New hypothesis: explicit descriptor-base assignment followed by pointer compound
addition changes MWCC's expression evaluation and register coalescing, even when
array subscripting and commuted ordinary pointer addition do not. Initializing the
base before reading kind removed all descriptor setup register differences.

The transition result is now computed into a separate int temporary before the
transition store. This gives MWCC a distinct result lifetime while the unmodified
adjustment remains live for the subtraction. It emits exactly the retail
`add r4,r5,r4` and the corresponding store. Simply reusing counter leaves the
result in r5; compound addition into adjustment commutes the source operands.
No assembly, compiler changes, relocation rewriting, or neighboring edits were
used. The fallback loop retains the corrected `lbl_8064CF6C != 0` condition.

Experiment sequence:
- experiment.py starts from the preserved Git source and retains explicit_base
  (99.79876%).
- experiment2.py starts from that retained source and retains adjust_counter
  (99.90712%).
- combined.json additionally moves each descriptor-base assignment before its
  kind load (99.96904%). This was the input to experiment3.py and experiment4.py.
- experiment3.py does not improve the score and retains the combined source.
- experiment4.py retains new_result_s16 (100%). Final source only reformats that
  block and removes the obsolete NonMatching comment.
The experiment scripts operate on the current source; this sequence documents
which intermediate state each expects. Per-variant JSON files are raw objdiff
outputs, and per-variant logs contain the canonical single-object Ninja output.

Final verification:
- Canonical and `function_reloc_diffs=name_address` strict objdiff: 100%.
- Exactly 1292 bytes in each .text section, byte-for-byte equal.
- Exactly 85 ELF relocations: offsets, types, symbol names, addends equal.
- Objdiff reports 126 relocation-bearing instruction records on each side;
  that count includes synthesized R_PPC_NONE address references.
- Existing GC/1.3 canonical flags retained, including -use_lmw_stmw on.
- Only this function's configure.py registration promoted to Matching; split
  boundaries already correct and unchanged.
- Final canonical build uses the candidate in the link and retains expected DOL.
- verify.py records hashes and asserts byte/relocation/DOL equality.
- Pre-existing CLAUDE.md modification is unrelated and excluded from the commit.
