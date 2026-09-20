# fn_8006B21C attempt 6

The accepted base already contains the exact source preserved by d8b4fe6ec9c52fec33eb0cf6f712ec5400e82024; recovery.json records the comparison. Its independent translation unit remains NonMatching. No compiler policy, registration, split, neighboring source, runtime, or progress edits were needed.

New hypothesis: inline C argument boundaries could preserve the root and State address materializations that normal local pointer propagation eliminates. Three static inline helpers performed the root assignment, four State stores, and State link/initialization. This compiled to 320 bytes and 96.68293%, with both missing additions still missing. The helpers were rejected.

Follow-up experiments tested a typed external GlobalState (96.87805%), integer/pointer conversion boundaries (96.68293%), explicit register locals (96.87805%), a union carrying the State address as integer/pointer (92.53658%, 332 bytes and extra stack traffic), and a complete structure with sizeof-based clears and a typed state + 1 link (96.87805%). None improved the retained source. Numbered JSON records contain exact source patches, invocations and captured output; companion objdiff files are unmodified raw measurements. baseline.json and experiments.py make the additional experiments reproducible from the project directory. All experimental C changes were reverted; there is one retained C translation unit.

The remaining mismatches are retail +0x24 (addi r3,r31,0), +0x3c (addi r5,r31,0x654 and corresponding State-relative stores), and +0x98/+0x9c (root-relative linked-buffer address and State-relative destination). The generated function is eight bytes shorter. Current evidence does not establish a permitted source spelling that reproduces these address materializations. No match is claimed.

The full DOL verification uses the existing NonMatching registration, hence the link retains retail instructions for this function. A passing DOL hash validates the canonical project build; it does not promote this C candidate. The final separate canonical and name_address relocation-strict commands and their outputs are recorded in the assignment verification JSON.
