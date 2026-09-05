# Eternal Darkness: Sanity's Requiem matching decompilation

This repository targets the US GameCube release **GEDE01, revision 0**. The architectural goal is a byte-identical matching decompilation; the practical goal is a durable, source-driven modding platform built on that matching foundation.

The repository contains no game image, extracted executable, asset, proprietary SDK source, or Metrowerks binary. You must supply a legally obtained matching disc image locally.

## Verified baseline

- Disc: GEDE01, disc 0, revision 0; Redump SHA-1 `2bebaa7a17d69057f8c02fe00349b558abc30ff6`
- `main.dol`: 3,156,384 bytes; SHA-1 `ea24b6af954876ce072562ff39cdb4c81d32be1f`
- Entry point: `0x80005308`
- Modules: no REL, RSO, alternate DOL, ELF, map, or symbol file was found in a complete 1,680-file scan
- Toolchain: Metrowerks CodeWarrior confirmed; linker family narrowed to GC 1.0-2.6; exact patch versions and flags are not yet proven

## Bootstrap

From this directory on Linux:

```sh
python3 tools/bootstrap.py
python3 tools/ingest_disc.py --image /path/to/your/GEDE01-rev0.rvz
python3 configure.py
.tools/bin/ninja
```

`bootstrap.py` downloads hash-pinned DTK 1.8.3, Ninja 1.13.2, wibo 1.0.3,
and pinned open-source `dtk-template` build helpers. The build may download remaining
pinned public tools. It does not and must not download proprietary compilers; place
lawfully obtained MWCC binaries in ignored `compilers/` or pass `--compilers`.

The ingestion script fails closed unless the disc header, Redump identity, and `main.dol` hashes all match. It extracts only `boot.bin` and `main.dol` into ignored `orig/GEDE01/sys/` and records local provenance in an ignored report.

## Matching contract

A function or translation unit is not marked matching because it is equivalent C. It is matching only when:

1. `objdiff` reports a 100% object match, including relocations;
2. the matching build still produces the expected whole-DOL SHA-1; and
3. the status is generated from build evidence, not handwritten.

Use separate output trees for experiments and mods:

```sh
python3 configure.py --non-matching --build-dir build-mod
.tools/bin/ninja -f build-mod/build.ninja
```

See `docs/` for the clean-room boundary, current analysis, compiler experiment matrix, Ghidra workflow, mod roadmap, and PC execution track.

<!-- progress:start -->
## Progress

Generated from `objdiff` build evidence (`reports/GEDE01/progress.json`), verified against `main.dol` SHA-1 `ea24b6af954876ce072562ff39cdb4c81d32be1f`.

| Metric | Matched | Total | Percent |
| --- | ---: | ---: | ---: |
| Code bytes | 746,172 | 2,300,692 | **32.43%** |
| Functions | 4,766 | 8,216 | 58.01% |
| Objects (TUs) | 4,999 | 6,162 | 81.13% |

Denominators are the whole retail `main.dol`. Percentages count only functions that `objdiff` reports at 100%, relocations included; reconstructions registered as documented `NonMatching` are not counted. Most matched objects are small, so the object percentage runs far ahead of the code percentage — **code bytes is the honest measure of how far along this is.**
<!-- progress:end -->

## PC execution

Boot milestone (2026-08-11): **Eternal Darkness reaches the title screen on PC through DolRecomp + RecompCore with zero interpreter fallback for guest CPU execution.** The experiment is isolated on a separate `boot-experiment` branch and machine; it does not change the matching strategy, the exact-match acceptance bar, or scheduler priorities, and no runtime hacks land in this tree.

The long-term goal is a PC port with a modern renderer, ray tracing, and upgraded textures, materials, and models while preserving the original gameplay logic. As matching coverage grows, recovered source functions are to progressively replace static-recompiled blocks under the gated host-replacement track defined in `docs/pc-execution.md`.

## Contributors

Outside contributions are welcome and are credited in
[`CONTRIBUTORS.md`](CONTRIBUTORS.md). They are rebuilt and re-verified here
before landing, and they reach this repository through a squashing publish, so
that file — not the commit log — is the record of who matched what.

If you are picking a function to work on, note that an automated chain is
continuously extending the frontier upward through the address space; check
`reports/GEDE01/progress.json` (`next_target`) to see where it currently is, so
you are not duplicating work in flight. Anything well below that frontier still
registered as `NonMatching` in `configure.py` is fair game and unlikely to
collide.
