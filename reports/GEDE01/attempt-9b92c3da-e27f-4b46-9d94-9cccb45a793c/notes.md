# fn_801F50EC, attempt 6

Assignment: 9b92c3da-e27f-4b46-9d94-9cccb45a793c. Accepted base: e4db62be82cbe4b0c54e1863d13ad3e3c7550558.

## Preserved attempts reviewed

Reviewed the source and result envelopes from 5e8aeb38085adb4eb1a449ee1a70368d8664d6a4, 067b4ca5526d0e86c981ab604c1bc5d589149e72, a328ccdb8061dc3f6493e50e3a84e2b1354e305a, e67e212a98f27fa96f841ff45a351be6b365beb0, and f719f0d4a0d3283d2c65a4291bcb32b6580148d4. The accepted base already contained the exact preserved best C file (SHA-256 45167aafa4b8f50b15337707beaa888dd603d7bca8f75e71d855465387648224), its NonMatching GC/1.3 registration, and independent split. No historical commit needed cherry-picking.

## New hypothesis and measured result

Earlier attempts staged temporary offsets before conversion to the persistent output pointer. This attempt instead makes the destination base, block base, and persistent output address all unsigned 32-bit integers, converting to a u16 pointer only at the two stores. The offset and final address thus share a single variable live across both calls. This produces the retail r25 accumulation chain without changing the ABI, arithmetic, loop bounds, stores, or calls. All destination arithmetic is in bytes; unsigned int and pointers are both 32 bits on this target.

Changing only the output variable gave 95.47059%: it obtained r25 but hoisted the block conversion into r31 and rotated the remaining nonvolatile allocation. Giving all three addresses the same unsigned integer representation restores the original nonvolatile allocation and improves canonical and relocation-strict objdiff from 97.17647% to **97.35294%**, still 340/340 bytes. The retained source is the all-integer-staged experiment, plus a comment; its two final raw objdiff files exactly equal that experiment's output.

Five instructions differ, at actual function-relative offsets 0x38, 0x3c, 0x48, 0x4c, and 0x5c. Retail calculates high column bits in r4 before low bits in r3. The candidate calculates low bits in r4 before high bits in r3, then shifts r3 into r4. Both now add row offset plus low bits into r25, then add the shifted high bits. The final add uses r25,r25,r26 instead of retail r25,r26,r25. Direct ELF .text comparison confirms exactly these five differing words, with 330/340 bytes equal. This raw byte count is distinct from objdiff's weighted score.

## Bounded follow-up experiments

The experiment ledger records 89 measured formulations with exact patches relative to the accepted-base source and build stdout/stderr. Identical raw objdiff outputs are deduplicated into 22 files and referenced by each record. No alternate C translation units remain.

Integer signedness/width changes, high/low temporary types, block declaration placement, multiplication versus shifts, comma sequencing, separate final-address temporaries, and interleaving the three address stages with the three sample stores did not improve on 97.35294%. Union representations caused spills; narrowing offset casts retained an extra mask. Pointer conversion experiments lost the desired accumulator allocation. Some controls converged to the previously documented staged-pointer and staged-offset failure patterns; the improvement comes specifically from the new persistent all-integer address representation. Avoid rerunning the recorded formulations.

## Verification and scope

Used unchanged canonical GC/1.3 compiler flags and the existing use_lmw_stmw source pragma. Ran python3 configure.py and .tools/bin/ninja -j2 successfully, with raw final logs preserved here. Canonical and function_reloc_diffs=name_address objdiff reports are identical. readelf confirms both objects have exactly two R_PPC_REL24 calls, at 0x74 and 0x100, both targeting fn_801F4FC8 with zero addends. Final verification records all five disassembly and machine-word differences.

The DOL SHA-1 is ea24b6af954876ce072562ff39cdb4c81d32be1f. The function remains NonMatching, so the DOL gate verifies the retail-backed build, not linkage of this unmatched C candidate. No registration, split, runtime, compiler, gate, neighboring source, README, or global progress edits were made. The pre-existing CLAUDE.md modification is outside this assignment and is not included. Only this function source and assignment reports are staged. No remote push, assembly, binary artifacts, or private inputs are included.

The readable build.log normalizes linker CRLF line endings to LF. build-raw.json preserves the exact combined build output, including CRLF, with its SHA-256.
