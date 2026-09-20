# fn_80129D54, attempt 6

Assignment: b2ce7d09-cb0d-47ee-91b3-fdc67aacfab6. Accepted base: e82b2bc81ad2c0bae25fc136704776a7a7f332c2.

The accepted base already contains the clean independent C translation unit and its NonMatching registration. The source recovered in preserved commit c31127fbdf476ce5c2eb045c2113590f68d3d339 is identical to that baseline. No source, registration, split, compiler-policy, runtime, or global-progress change is needed for this attempted result.

## Hypothesis and measured experiments

Earlier reports cover reordered or missing cases/default, case-1 continue/goto, unlabeled break/goto before the first case, and default continue. This attempt instead tests whether nested control flow, eliminated during constant folding or later optimization, leaves an empty block whose branch survives MWCC cleanup. The eight source replacements and their source hashes are recorded in hypotheses-results.json; hypotheses.py applies each replacement only to this function, builds it with the canonical Ninja rule, saves raw objdiff JSON, and restores the original source in a finally block.

Seven experiments (empty do/while, do/break, while/break, nested constant switch, nested same-value switch, if/else with both arms breaking, and a zero-trip call loop) produce 136 bytes and 97.14286%, just like the baseline. The local one-iteration loop produces 180 bytes and 0.0%; its emitted loop and changed register allocation are visible in its raw diff. No variant is retained as a separate C translation unit.

## Final evidence and interpretation

Run the following from eternal-darkness-decomp to reproduce the experiments and then the final verification:

    python3 reports/GEDE01/b2ce7d09-cb0d-47ee-91b3-fdc67aacfab6/hypotheses.py
    python3 reports/GEDE01/b2ce7d09-cb0d-47ee-91b3-fdc67aacfab6/verify.py

The final verification script runs python3 configure.py and .tools/bin/ninja -j2; captures their actual stdout/stderr and exit codes; records the canonical compiler command; runs canonical objdiff and relocation-strict objdiff with functionRelocDiffs=all; saves raw readelf/objdump output; checks the required DOL SHA-1; and runs the existing legal audit. All explicitly created evidence and build outputs remain inside this worktree. No toolchain or retail input is modified.

Canonical and relocation-strict objdiff both measure 97.14286% and their raw JSON is equal. Retail has 140 text bytes, generated C has 136. Retail alone contains an unreachable unconditional branch at function offset 0x48 (address 0x80129D9C), targeting offset 0x68. The instruction before it is an unconditional branch to the same destination, and no local branch targets 0x48. Subsequent instructions and their local branch destinations shift by four bytes. verification.json records the independent raw-word comparison after normalizing only those local branch destinations. This is an explained mismatch, not a byte match.

The actual ELF relocation tables contain THREE entries: ADDR16_HA to fn_801A9FA4 at 0x0a, ADDR16_LO to fn_801A9FA4 at 0x22, and REL24 to fn_801287C4 at retail 0x64 / generated 0x60. Each has addend zero. Objdiff also propagates fn_801A9FA4 to an R_PPC_NONE reference at retail instruction 0x58 / generated 0x54; that fourth displayed reference is not a fourth ELF relocation. verify.py independently parses both ELF files and checks every actual relocation's type, target name, signed addend, and mapped byte offset.

The final linked DOL remains retail-exact with SHA-1 ea24b6af954876ce072562ff39cdb4c81d32be1f. Because this function remains NonMatching, the linked DOL uses the original split object; this hash does not establish a match for the reconstructed C.

Only assignment-specific textual evidence is committed. The pre-existing CLAUDE.md worktree modification is excluded. No generated binaries or private inputs are staged, and no remote is pushed.

Raw build logs retain the existing linker warnings about ignored sections. Raw tool whitespace is deliberately preserved; whitespace checks apply to authored scripts, Markdown, and JSON, not tool log formatting.
