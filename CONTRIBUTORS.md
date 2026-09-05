# Contributors

Most of this tree is produced by an automated matching chain. The functions
below were matched by people who sent them in from outside that chain, and
every one of them was independently rebuilt and verified here before it landed:
100% in `objdiff` on both the canonical basis and the relocation-strict basis
(`function_reloc_diffs=name_address`), with the whole-DOL SHA-1 gate
`ea24b6af954876ce072562ff39cdb4c81d32be1f` unchanged.

Outside contributions land as ordinary commits in the upstream monorepo and
reach this repository through a squashing publish, so the per-contribution
commits are not visible here. This file is the durable record of who did what.

## Andrew ([@ateich](https://github.com/ateich))

**284 functions, 73,448 matched code bytes.**

### Script handlers and narrowed values ([#1](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/1), [#2](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/2), [#3](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/3)) — 6 functions, 7,488 bytes

| Function | Bytes | Contribution |
| --- | ---: | --- |
| `fn_80177434` | 6,752 | Script constant registration ([#2](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/2)) |
| `fn_8000EB14` | 192 | Script field handler ([#1](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/1)) |
| `fn_8000EBD4` | 192 | Script field handler ([#1](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/1)) |
| `fn_8016B400` | 180 | Header-table read ([#3](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/3)) |
| `fn_8015AC94` | 108 | Narrowed value reaching a call ([#3](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/3)) |
| `fn_8015AD00` | 64 | Narrowed value reaching a call ([#3](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/3)) |

### Commutative operand order ([#5](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/5)) — 8 functions, 1,780 bytes

| Function | Bytes | Retail | Ours (before) |
| --- | ---: | --- | --- |
| `fn_800E8130` | 348 | `cmpw r31, r3` | `cmpw r3, r31` |
| `fn_80158F6C` | 284 | `or r4, r30, r0` | `or r4, r0, r30` |
| `fn_801294DC` | 268 | `cmpw r0, r28` | `cmpw r28, r0` |
| `fn_80063030` | 244 | `cmpw r31, r3` | `cmpw r3, r31` |
| `fn_801749A8` | 236 | `fcmpu cr0, f0, f1` | `fcmpu cr0, f1, f0` |
| `fn_80096F04` | 216 | `cmpw r31, r3` | `cmpw r3, r31` |
| `fn_800BE8D4` | 100 | `cmpw r30, r3` | `cmpw r3, r30` |
| `fn_800DB95C` | 84 | `cmpw r31, r3` | `cmpw r3, r31` |

Each of these was exactly one instruction from retail. This chain had already
eliminated six condition spellings and every compiler revision from GC/1.1 to
GC/2.0, and had written the class off as unfixable register-allocation
divergence. Both eliminations were correct and both were beside the point: MWCC
canonicalizes a comparison to temp-first while a call is left inline in the
condition, so no spelling changes what the operands *are*. Hoisting the call
result into a named local removes the canonicalization, after which source
order controls the encoding. 72 further flag combinations were eliminated on
`fn_800DB95C` in the course of establishing it.

### Tier 2 near-misses ([#6](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/6)) — 7 functions, 1,720 bytes

| Function | Bytes | Lever |
| --- | ---: | --- |
| `fn_80192318` | 728 | Compared byte must live in an `unsigned int`; widening both operands regresses |
| `fn_800C7C0C` | 448 | One local declaration moved two slots earlier |
| `fn_801A7E04` | 164 | `type` is a field of the object, not the last member of the shape |
| `fn_801A7EA8` | 152 | Same shape correction |
| `fn_80129108` | 84 | Mask parameters declared `long`, not `int` |
| `fn_80139D88` | 76 | Bind both call arguments to locals, assigned in retail's load order |
| `fn_80088F08` | 68 | `unsigned int inverted = ~mask;` before the branch supplies the register pressure |

`fn_80129108` is the sharpest of these: `long` and `int` are both 32-bit signed
under these flags, so MWCC is distinguishing the type *names* rather than their
representation. This PR also documented that units with an `externalize` rule
are rewritten after compilation, so a single-unit compile under-reports them by
exactly the externalized relocations — a measurement trap that applies
tree-wide.

### Tier 2, second round ([#7](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/7)) — 7 functions, 1,784 bytes

| Function | Bytes | Lever |
| --- | ---: | --- |
| `fn_800C65FC` | 384 | The #5 hoist, plus an externalize rule sharing the s16-to-float bias constant |
| `fn_800AFEC0` | 364 | Parse cursor is a `u32` offset with a compound add, not a recast pointer |
| `fn_8013DE44` | 264 | The #5 hoist lever extends to `fmuls`, constant on the right |
| `fn_8012CCF0` | 256 | Slot-pointer sum must land in the product's register |
| `fn_8015FF18` | 208 | Corrected a real bug — see below |
| `fn_8012CDF0` | 180 | Same slot-pointer edit |
| `fn_80132D50` | 128 | `do/while` rewritten as `for`, flipping constant materialization order |

`fn_8015FF18`'s committed source was not merely misshapen, it was **wrong**:
retail's `addi` writes the index register, so the entry block is `index++` then
`offset = index;`. Our source bumped only `offset`, leaving `index` stale by one
on the negative-value path for the rest of the function. A NonMatching function
was concealing a behavioural defect, and pursuing the last two instructions is
what surfaced it. That is the argument for byte-exactness as a correctness
standard, made concrete.


Beyond the bytes, these contributions added reusable MWCC codegen
findings to `docs/matching.md`, each one established by trying the alternatives
and reporting their scores rather than by assertion:

- A narrowed helper return value has to live in a `short` local. Written as an
  `int` with a `(short)` cast at the test, the compiler sign-extends into a
  scratch register and passes the un-narrowed value on.
- A table base has to be cast into a local pointer once. Casting inline at each
  use makes the compiler fold base and index into an address before loading;
  retail keeps them in separate registers and uses `lwzx`.
- The string-pool externalization technique that made `fn_80177434` — by a wide
  margin the largest single matched function in this tree — reachable at all.
- The commutative-operand hoist, and its extension to `fmuls`, which together
  retired a whole class this chain had recorded as blocked.

Signature decisions in these contributions were argued from evidence, including
cases where two spellings produce identical bytes and the tie was broken by
consistency with an adjacent function that already matches. Every lever above is
recorded in `docs/matching.md` together with the alternatives that failed *and
their scores*, which is the standard this project wants and rarely gets: the
negative results are what stop the next person re-deriving them.

### Extern qualifiers and first-load scheduling ([#8](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/8)) — 7 functions, 2,676 bytes

| Function | Bytes | Previous score |
| --- | ---: | ---: |
| `fn_8002B748` | 824 | 96.79612% |
| `fn_8006B488` | 408 | 92.15686% |
| `fn_80066BB8` | 332 | 95.12048% |
| `fn_80074580` | 332 | 90.36144% |
| `fn_8008DF64` | 276 | 94.202896% |
| `fn_800BB4C4` | 256 | 90.625% |
| `fn_800DA308` | 248 | 93.548386% |

MWCC schedules an external object's first load from the qualifiers on its
*declaration*, even when type, width and storage are identical. Adding `const`
to three scalar declarations and removing it from four aggregate ones moved
every load into the retail order with no change to control flow, local
lifetimes or compiler flags. `fn_8002B748` additionally needed a post-compile
rule that retains the MWCC-emitted `.sdata2` copy and renames local symbol
`@59` to `lbl_8064E038` — the `.sdata2` externalization used elsewhere in the
tree deletes that data and could not work here.

### Const-qualified scalar externs ([#9](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/9)) — 14 functions, 2,528 bytes

The same lever at scale: `const` on 21 read-only float extern declarations,
with `volatile` deliberately retained on `lbl_8064F7F0`. Thirteen of the
fourteen function bodies are untouched. Starting scores ranged from 71.14286%
(`fn_800A4670`) to 97.13043% (`fn_800E801C`). `fn_800A32B8` is the clearest
demonstration: the non-const declaration already produced the correct 240-byte
size and all nine relocation targets and types, and still scheduled the
`lbl_8064EEA0` load after the saved-register stores instead of after `mflr`.

### Per-object compiler settings in the audio code ([#10](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/10)) — 8 functions, 1,640 bytes

| Function | Bytes | Settings |
| --- | ---: | --- |
| `fn_801AE91C` | 348 | GC/1.3 `-O3,p` |
| `fn_801B2528` | 244 | GC/1.2.5n `-O4,p` |
| `fn_801B3470` | 232 | GC/1.2.5n `-O4,p`, exceptions on |
| `fn_801A9B94` | 228 | GC/1.3 `-O1,p` |
| `fn_801B2748` | 208 | GC/1.2.5n `-O4,p`, exceptions on |
| `fn_801B2878` | 156 | GC/1.2.5n `-O4,p` |
| `fn_801B1B0C` | 148 | GC/1.3 `-O3` |
| `fn_801A99B4` | 76 | GC/1.3 `-O1,p` |

The audio objects were never going to match on the game library defaults. Four
move to GC/1.3 at a lower optimization level, four to GC/1.2.5n with the old
scheduling and peephole overrides dropped, and two of those need
`-Cpp_exceptions on` purely to reproduce their retail `extab` and
`extabindex` sections. Two details worth keeping: the per-object optimization
list has to *replace* `-O4,p`, not follow it (appending reached 94.47369% on
`fn_801A99B4` where replacing reached 100%), and a compiler setting alone was
never sufficient — six of the eight also needed a source correction, with the
setting-only scores recorded in `docs/matching.md` as evidence.

These three PRs took the tree from 29.358124% to 29.6556% matched code, 4,397
to 4,426 functions and 4,630 to 4,659 objects. Each was built and measured
separately on both the canonical and the `function_reloc_diffs=name_address`
basis; `build/GEDE01/main.dol` still hashes to
`ea24b6af954876ce072562ff39cdb4c81d32be1f`.

### September 5, 2026 — six PRs, 227 functions, 53,832 bytes

PRs [#11](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/11) through [#16](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/16), landed together. This single day moved
the tree from 29.937601% to 32.277420% matched code, 4,506 to 4,733 functions and
4,739 to 4,966 objects — the largest contribution the project has received.

Each PR was applied, built and measured separately. The aggregate function delta
of +227 equals the sum of the six per-PR claims exactly, and the tree was then
rebuilt from an empty build directory with zero failures and an unchanged DOL
SHA-1.

Two of these also improved the build's own honesty rather than just its numbers.
`tools/retarget_elf_relocation.py` (new in [#11](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/11)) reads the retail DOL and
refuses to rebind a relocation whose compiler-side bytes disagree with the retail
value, and `--require-section-symbols` in `tools/externalize_elf_symbol.py`
forces every nonempty symbol in a discarded section to be named and verified,
failing on any unverified nonzero byte. Together they close a real gap: an
unguarded externalization could previously report 100% on a constant that
differed from retail. That change makes past work more trustworthy, not just
future work.

### Guarded compiler-local data externalization ([#11](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/11)) — 34 functions, 13,164 bytes

Rebinds a compiler-local constant onto its retail symbol only after the compiler's own bytes are checked against the retail DOL.

| Function | Bytes |
| --- | ---: |
| `fn_801B1BA0` | 1,960 |
| `fn_80153A24` | 736 |
| `fn_801926EC` | 696 |
| `fn_801916D0` | 684 |
| `fn_8018D400` | 648 |
| `fn_80192F54` | 624 |
| `fn_80187BB4` | 576 |
| `fn_80174F2C` | 568 |
| _26 more_ | 6,672 |

### Function-scoped compiler pragmas ([#12](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/12)) — 44 functions, 6,836 bytes

MWCC optimization controls set immediately before a function and reset immediately after, so no object-wide flags change.

| Function | Bytes |
| --- | ---: |
| `fn_8016BA4C` | 704 |
| `fn_801A0284` | 460 |
| `fn_8014FE64` | 380 |
| `fn_8014FFE0` | 376 |
| `fn_800CFCD4` | 288 |
| `fn_800E8524` | 272 |
| `fn_8011ECF8` | 268 |
| `fn_801ACB0C` | 260 |
| _36 more_ | 3,828 |

### Extern qualifiers and parameter copies ([#13](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/13)) — 17 functions, 2,536 bytes

| Function | Bytes |
| --- | ---: |
| `fn_8015DD94` | 304 |
| `fn_8009E4BC` | 264 |
| `fn_8005BCC0` | 228 |
| `fn_800F35E4` | 188 |
| `fn_800D9F2C` | 180 |
| `fn_8012B8A8` | 172 |
| `fn_800D078C` | 160 |
| `fn_8006016C` | 144 |
| _9 more_ | 896 |

### Declarations, expressions and indexing ([#14](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/14)) — 9 functions, 1,576 bytes

| Function | Bytes |
| --- | ---: |
| `fn_8019A5DC` | 488 |
| `fn_8012CF08` | 276 |
| `fn_80198318` | 264 |
| `fn_800EC318` | 172 |
| `fn_8011F808` | 136 |
| `fn_80134F08` | 116 |
| `fn_80144430` | 64 |
| `fn_8011F7E0` | 40 |
| _1 more_ | 20 |

### Declaration order and local lifetimes ([#15](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/15)) — 37 functions, 10,452 bytes

| Function | Bytes |
| --- | ---: |
| `fn_801AA6D0` | 808 |
| `fn_800A0DE4` | 636 |
| `fn_801755FC` | 576 |
| `fn_8019C06C` | 512 |
| `fn_800E2150` | 500 |
| `fn_8015D7D4` | 500 |
| `fn_80067EB8` | 444 |
| `fn_8008D31C` | 408 |
| _29 more_ | 6,068 |

### Structural reconstruction ([#16](https://github.com/psdwizzard/Eternal-Darkness---Decompile/pull/16)) — 86 functions, 19,268 bytes

The largest single batch landed on this project.

| Function | Bytes |
| --- | ---: |
| `fn_8014DB5C` | 1,188 |
| `fn_80096A44` | 788 |
| `fn_8008ABD4` | 620 |
| `fn_8007C354` | 584 |
| `fn_800D88DC` | 508 |
| `fn_8019A8C4` | 496 |
| `fn_8019F320` | 488 |
| `fn_8008F064` | 448 |
| _78 more_ | 14,148 |
