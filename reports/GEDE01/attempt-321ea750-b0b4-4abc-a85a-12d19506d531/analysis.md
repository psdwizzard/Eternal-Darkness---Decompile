# fn_80198850 — assignment 321ea750-b0b4-4abc-a85a-12d19506d531

The accepted base is a1bb038eb5805a9324d7da3d0a4bf6dabd99428e. Reviewed preserved commits 0bae921496833a366e62ac47dad68b0a0e14df6c, d6d6c3d7cfb1a599954613386ca9bd4434119ec7, af0058eb63c5c6c0daa42229bcfe4c80d1f53bea and 2ea2718170318f217a5a43e5e8480ff82cd36f46 through git show. Their raw reports contain only left/right objdiff records. The supplied handoff additionally documents the failed standard abs and struct-member experiments. The accepted base already includes the unsigned inline helper from af0058eb; no recovery/cherry-pick was necessary.

## New hypothesis and measurements

The retail function preserves its third parameter and puts it in the return register at the end. Treating that as an irrelevant move concealed a missing return value in the prior void reconstruction. Returning the u8 count raises canonical objdiff from 91.4% (360 bytes) to 95.57895% (368 bytes), reproducing the full retail prologue and tail.

The remaining three missing moves follow absolute-value calculations. Retaining unsigned input arithmetic but returning a signed int creates the required conversion temporaries. An early return in the negative branch (or a ternary return) gives 99.42105% and 380 bytes, with only the loop point pointer and first loaded coordinate assigned to opposite registers. This differs from a standard signed abs implementation: the negation is unsigned and the return conversion is signed.

Computing the point pointer from the loop index, `point = &points[i * 3]`, instead of carrying an explicitly incremented pointer produces 100% and all 380 retail bytes. Strength reduction still generates the expected pointer induction, with the correct allocation. The initially considered outer inline-loop helper was not implemented because the return-register evidence gave a more direct explanation.

## Reproduction and scope

`experiments.json` indexes every measured source variant and its raw objdiff result. Each `*-reproduction.json` embeds the exact complete source, SHA-256, command arrays, exit codes, and raw compiler/objdiff output. To replay a variant, write its source field to `src/game/game_fn_80198850.c` and run its commands from `eternal-darkness-decomp`. These are report snapshots; there is only one compiled reconstruction translation unit.

`measure.py` records a variant currently in that source file. `verify.py` records configure, the requested full Ninja build, DOL SHA-1, separate canonical/strict objdiff commands, readelf relocations and symbols, and legal audit. `bytecheck.py` independently compares the complete .text bytes and resolves ELF32 RELA entries to symbol names, values and signed addends; bytecheck.json captures its raw stdout. The final legal audit after staging is captured separately.

Only this function source, its Matching registration, and assignment reports are changed. Existing GC/1.3 flags including -O4,p, -inline auto and -use_lmw_stmw on are unchanged. Existing independent split is retained. No assembly or compiler-policy changes were introduced. The neighboring caller currently declares this function void and ignores its result; it is left untouched under the explicit assignment scope. A pre-existing CLAUDE.md modification is also left untouched and excluded from the commit. No private inputs or binaries are included.
