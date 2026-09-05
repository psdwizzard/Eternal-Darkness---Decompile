#!/usr/bin/env python3
"""Generate GEDE01 matching or non-matching builds with dtk-template helpers."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

try:
    from tools.project import Object, ProgressCategory, ProjectConfig, calculate_progress, generate_build, is_windows
except ModuleNotFoundError:
    raise SystemExit("Bootstrap helpers are missing. Run: python3 tools/bootstrap.py")

VERSION = "GEDE01"

parser = argparse.ArgumentParser()
parser.add_argument("mode", choices=["configure", "progress"], default="configure", nargs="?")
parser.add_argument("--version", choices=[VERSION], default=VERSION, type=str.upper)
parser.add_argument("--build-dir", type=Path, default=Path("build"))
parser.add_argument("--binutils", type=Path)
parser.add_argument("--compilers", type=Path)
parser.add_argument("--mw-version", default="GC/1.3",
                    choices=["GC/1.2.5n", "GC/1.3", "GC/1.3.2", "GC/1.3.2r", "GC/2.0"])
parser.add_argument("--dtk", type=Path, default=Path(".tools/bin/dtk"))
parser.add_argument("--objdiff", type=Path)
parser.add_argument("--sjiswrap", type=Path)
parser.add_argument("--ninja", type=Path, default=Path(".tools/bin/ninja"))
parser.add_argument("--map", action="store_true")
parser.add_argument("--debug", action="store_true")
parser.add_argument("--non-matching", action="store_true")
parser.add_argument("--no-progress", dest="progress", action="store_false")
parser.add_argument("--verbose", action="store_true")
if not is_windows():
    parser.add_argument("--wrapper", type=Path)
args = parser.parse_args()

config = ProjectConfig()
config.version = args.version
config.build_dir = args.build_dir
config.config_path = Path("config") / VERSION / "config.yml"
config.check_sha_path = Path("config") / VERSION / "build.sha1"
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
# Never auto-download proprietary compiler binaries. The ignored local directory
# must be populated by the user or replaced with an explicitly supplied path.
config.compilers_path = args.compilers or Path("compilers")
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.generate_map = args.map
config.non_matching = args.non_matching
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper or Path("tools/mwcc_wrapper.py")
if not config.non_matching:
    config.asm_dir = None

# Pinned public tooling. The helper downloads these and verifies its release metadata.
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# The retail DOL links independently built inputs from two compiler lines.
# Game/runtime objects follow the selected live candidate; Nintendo SDK archive
# objects are fingerprinted to GC/1.2.5n.
GAME_MW_VERSION = args.mw_version
SDK_MW_VERSION = "GC/1.2.5n"
LIBRARY_MW_VERSIONS = {
    "game": GAME_MW_VERSION,
    "Runtime.PPCEABI.H": GAME_MW_VERSION,
    "NdevExi2A": SDK_MW_VERSION,
    "amcstubs": SDK_MW_VERSION,
    "os": SDK_MW_VERSION,
    "dvd": SDK_MW_VERSION,
    "si": SDK_MW_VERSION,
    "exi": SDK_MW_VERSION,
    "gx": SDK_MW_VERSION,
    "base": SDK_MW_VERSION,
}

config.asflags = ["-mgekko", "--strip-local-absolute", "-I include", f"-I build/{VERSION}/include"]
config.ldflags = ["-fp hardware", "-nodefaults"]
config.custom_build_rules = [
    {
        "name": "externalize_game_801C90A4_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @23 lbl_80650FB8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@23=lbl_80650FB8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801C8160_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @23 lbl_80650FB8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@23=lbl_80650FB8 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801C2D9C_conversion_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @14 lbl_80650F70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650F80 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_80650F70 --redefine-sym=@16=lbl_80650F80 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801C2AAC_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @3 lbl_80650F70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@3=lbl_80650F70 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801C2980_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @3 lbl_80650F50 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@3=lbl_80650F50 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801B02F0_jumptable",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @59 jumptable_8025183C "
            "orig/GEDE01/sys/main.dol --require-whole-section && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@59=jumptable_8025183C --remove-section=.data "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801AFA74_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @25 lbl_80650EA0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@25=lbl_80650EA0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801AC8AC_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650E88 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650E88 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801ABD3C_table_and_conversion_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @25 jumptable_80251660 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @27 lbl_80650E80 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@25=jumptable_80251660 --redefine-sym=@27=lbl_80650E80 "
            "--remove-section=.data --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801AB154_conversion_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @29 lbl_80650E80 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @32 lbl_80650E88 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@29=lbl_80650E80 --redefine-sym=@32=lbl_80650E88 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A93E8_conversion_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650E40 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_80650E40 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A7E04_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 lbl_80650DF0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650DF0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A7EA8_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650DF0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_80650DF0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A4CE0_conversion_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @33 lbl_80650D90 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @35 lbl_80650D88 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@33=lbl_80650D90 --redefine-sym=@35=lbl_80650D88 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A6CB4_entries",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 lbl_8023B190 orig/GEDE01/sys/main.dol "
            "--require-whole-section && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8023B190 --remove-section=.rodata "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A6C58_entries",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 lbl_8023B0B0 orig/GEDE01/sys/main.dol "
            "--require-whole-section && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8023B0B0 --remove-section=.rodata "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "name_game_801A6ADC_jumptable",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @27 jumptable_80251364 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@27=jumptable_80251364 --remove-section=.data "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "NAME JUMPTABLE $in",
    },
    {
        "name": "externalize_game_801A6410_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 lbl_80650DB0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_80650DB0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A5FB0_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @67 lbl_80650DB0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@67=lbl_80650DB0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801A1F18_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650D20 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_80650D20 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8019E8C8_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @51 lbl_80650C60 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@51=lbl_80650C60 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8019E5E4_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @38 lbl_80650C60 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@38=lbl_80650C60 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8019CFC4_constant",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @5 lbl_80650C38 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@5=lbl_80650C38 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8019CC28_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @28 lbl_80650C30 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@28=lbl_80650C30 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801991E0_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_80650BB8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@17=lbl_80650BB8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80198BF4_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650B98 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650B98 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80198AAC_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @20 lbl_80650B98 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@20=lbl_80650B98 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80197910_conversion_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @42 lbl_80650B98 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @48 lbl_80650BA0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@42=lbl_80650B98 --redefine-sym=@48=lbl_80650BA0 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80194F80_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 lbl_80650B58 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_80650B58 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80193F3C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 lbl_80650B60 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650B64 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @18 lbl_80650B58 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @19 lbl_80650B68 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_80650B60 --redefine-sym=@16=lbl_80650B64 "
            "--redefine-sym=@18=lbl_80650B58 --redefine-sym=@19=lbl_80650B68 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80193E1C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_80650B50 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @20 lbl_80650B58 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@17=lbl_80650B50 --redefine-sym=@20=lbl_80650B58 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801931C4_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @66 lbl_80650B18 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@66=lbl_80650B18 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80192F54_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @34 lbl_80650B18 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@34=lbl_80650B18 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80191F58_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @74 lbl_80650B18 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@74=lbl_80650B18 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8019197C_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 lbl_80650B18 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_80650B18 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80191360_zero",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @5 lbl_80650B20 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@5=lbl_80650B20 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8018F81C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @7 lbl_80650AEC orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650AF0 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650AF8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@7=lbl_80650AEC --redefine-sym=@8=lbl_80650AF0 "
            "--redefine-sym=@10=lbl_80650AF8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "globalize_game_8018F1D0_scale",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_80650AC8 "
            "--globalize-symbol=lbl_80650AC8 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_8018D688_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@8=lbl_80650A70 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8018D2E0_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @22 lbl_80650AA4 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @23 lbl_80650A68 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @24 lbl_80650AA8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@22=lbl_80650AA4 "
            "--redefine-sym=@23=lbl_80650A68 --redefine-sym=@24=lbl_80650AA8 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8018D1F0_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @22 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650A9C orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_80650AA0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@19=lbl_80650A70 "
            "--redefine-sym=@22=lbl_80650A78 --redefine-sym=@16=lbl_80650A9C "
            "--redefine-sym=@17=lbl_80650AA0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80189968_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@16=lbl_80650A70 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80189760_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@16=lbl_80650A70 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801896A0_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@9=lbl_80650A70 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801895E8_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --redefine-sym=@9=lbl_80650A70 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80189390_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650A88 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @11 lbl_80650A90 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @21 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_80650A70 --redefine-sym=@10=lbl_80650A88 "
            "--redefine-sym=@11=lbl_80650A90 --redefine-sym=@21=lbl_80650A78 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801891D8_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A88 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @19 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650A8C orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_80650A70 --redefine-sym=@9=lbl_80650A88 "
            "--redefine-sym=@19=lbl_80650A78 --redefine-sym=@10=lbl_80650A8C "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80189028_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A88 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @18 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650A70 --redefine-sym=@9=lbl_80650A88 "
            "--redefine-sym=@18=lbl_80650A78 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80188E28_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A88 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650A70 --redefine-sym=@9=lbl_80650A88 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80188C1C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @14 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @12 lbl_80650A80 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_80650A78 --redefine-sym=@12=lbl_80650A80 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80188B44_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A78 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_80650A78 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80188A7C_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650A70 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_80650A70 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801878E0_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650A40 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650A48 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650A40 --redefine-sym=@10=lbl_80650A48 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80187120_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650A30 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650A38 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_80650A30 --redefine-sym=@10=lbl_80650A38 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80186E10_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 lbl_80650A30 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_80650A38 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_80650A30 --redefine-sym=@17=lbl_80650A38 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8018FEDC_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 lbl_80650B08 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650B08 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801865EC_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_80650A10 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_80650A10 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80185AE8_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 lbl_80650A10 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_80650A10 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801859FC_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_80650A00 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_80650A00 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80180DDC_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650950 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650950 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017E958_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650930 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650930 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017E850_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_80650930 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650930 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017718C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_806506A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801770F8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_806506B0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80176FA0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_806506B0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80176DF4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_806506A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017652C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801762E8_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_806506A8 --redefine-sym=@10=lbl_80650708 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80176220_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_806506A8 --redefine-sym=@10=lbl_80650708 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80176160_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_806506B0 --redefine-sym=@10=lbl_80650708 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80176098_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_806506A8 --redefine-sym=@10=lbl_80650708 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80172BB0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801726EC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @21 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@21=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801719B4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801718F4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80171664_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @20 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@20=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80170E9C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80170DF4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80170A40_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017038C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801704F8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801706DC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "normalize_game_TRKNubWelcome_symbols",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=lbl_80239BC0=@62_80239BC0 $in && touch $out"
        ),
        "description": "NORMALIZE $in",
    },
    {
        "name": "normalize_game_TRK_main_symbols",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=TRK_mainError=TRK_mainError_8032A570 $in && touch $out"
        ),
        "description": "NORMALIZE $in",
    },
    {
        "name": "normalize_game_data_80239E18_symbols",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=lbl_80239E18=@stringBase0_80239E18 $in && touch $out"
        ),
        "description": "NORMALIZE $in",
    },
    {
        "name": "normalize_game_data_80239E10_symbols",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--add-symbol=lbl_80239E12=.rodata:2,global,object $in && touch $out"
        ),
        "description": "NORMALIZE $in",
    },
    {
        "name": "externalize_game_8016E8F8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @25 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@25=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016FEF8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "normalize_game_8016DF4C_symbols",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @41 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@40=jumptable_8024FFA8 "
            "--redefine-sym=@41=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "NORMALIZE $in",
    },
    {
        "name": "externalize_game_8016D2B8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @29 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@29=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016D1F8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016C774_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016C4BC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016C238_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @14 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016C164_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016C0BC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016BE1C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80175E64_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80175F0C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806506B0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80175FD4_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_806506A8 --redefine-sym=@10=lbl_80650708 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016BF60_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8016BD0C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_806506A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80169650_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_80650670 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80167B5C_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650660 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8015EDC0_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650658 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80155814_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @51 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@51=lbl_80650618 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8012DB28_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @21 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@21=lbl_806501E8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801128E4_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064FF70 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801126E0_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_8064FF68 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800E4980_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_8064F6B8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800A4798_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_8064EE78 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "globalize_game_800A2130_constants",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_8064EE70 "
            "--redefine-sym=@16=lbl_8064EE78 "
            "--globalize-symbol=lbl_8064EE70 "
            "--globalize-symbol=lbl_8064EE78 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_8009C424_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_8064ED80 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80095FDC_switches",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @27 && "
            "python3 tools/externalize_elf_symbol.py $in @28 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@27=jumptable_80245308 "
            "--redefine-sym=@28=jumptable_8024528C "
            "--remove-section=.data $in && touch $out"
        ),
        "description": "EXTERNALIZE SWITCHES $in",
    },
    {
        "name": "externalize_game_80074310_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_8064E888 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80066888_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @31 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@31=lbl_8064E6E0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "globalize_game_8005FD84_bias",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@25=lbl_8064E5C0 "
            "--globalize-symbol=lbl_8064E5C0 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_8005EC6C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @17 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@17=lbl_8064E5C0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80033180_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @95 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@95=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80033038_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @25 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@25=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80032B84_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @14 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8003232C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @56 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@56=lbl_8064E188 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8002E3F0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @47 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@47=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8002DAE0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @120 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@120=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8002EA68_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @102 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@102=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8002F428_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @127 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@127=lbl_8064E038 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "globalize_game_8002B748_bias",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@59=lbl_8064E038 "
            "--globalize-symbol=lbl_8064E038 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_800272B4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @29 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@29=lbl_8064DFD8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8001B874_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_8064DEA0 --redefine-sym=@11=lbl_8064DEA4 "
            "--remove-section=.sdata2 $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8001B808_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @5 && "
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@5=lbl_8064DEA0 --redefine-sym=@6=lbl_8064DEA4 "
            "--remove-section=.sdata2 $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_70",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @70 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@70=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_flags_4",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 lbl_80237F2C orig/GEDE01/sys/main.dol "
            "--require-whole-section && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_80237F2C --remove-section=.rodata $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE FLAGS $in",
    },
    {
        "name": "name_game_80024F28_switches",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@36=jumptable_8023DE74 "
            "--redefine-sym=@37=jumptable_8023DE38 $in && touch $out"
        ),
        "description": "NAME SWITCHES $in",
    },
    {
        "name": "name_game_8000D8A4_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=jumptable_8023C248 $in && touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "globalize_game_bias",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@39=lbl_8064DCE8 "
            "--globalize-symbol=lbl_8064DCE8 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @31 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@31=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_17",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @17 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@17=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_12",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_8",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_15",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_30",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @30 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@30=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_16",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_18",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_19",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_13",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_14",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @14 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_9",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_10",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_6",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_46",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @46 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@46=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_11",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_21",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @21 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@21=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_20",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @20 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@20=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_98",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @98 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@98=lbl_8064DCE8 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_unsigned_bias_8",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_unsigned_bias_10",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_unsigned_bias_19",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_unsigned_bias_15",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_unsigned_bias_36",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @36 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@36=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_bias_16_unsigned_bias_19",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "python3 tools/externalize_elf_symbol.py $in @19 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_8064DCE8 "
            "--redefine-sym=@19=lbl_8064DE60 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800359A0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @123 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@123=lbl_8064E210 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80036C40_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_8064E210 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80038878_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @34 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@34=lbl_8064E210 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80048ADC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064E3A0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80052310_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064E4C0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "name_game_8001E644_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@44=jumptable_8023D8D4 $in "
            "&& touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "name_game_8001FE1C_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@98=jumptable_8023D9C0 $in && touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "name_game_80020E94_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@57=jumptable_8023DA70 $in "
            "&& touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "name_game_8005EE9C_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@39=jumptable_80243D64 $in && touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "name_game_8016D9C0_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=jumptable_8024FF88 $in && touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "name_game_80071A58_switch",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@14=jumptable_802445D0 $in && touch $out"
        ),
        "description": "NAME SWITCH $in",
    },
    {
        "name": "globalize_game_8008F890_bias",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064EC18 "
            "--globalize-symbol=lbl_8064EC18 $in && touch $out"
        ),
        "description": "GLOBALIZE $in",
    },
    {
        "name": "externalize_game_800A4428_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064EE78 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80096830_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_8064EC90 "
            "--redefine-sym=@13=lbl_8064ECD8 "
            "--remove-section=.sdata2 $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800A2FCC_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @10 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@10=lbl_8064EE98 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80078500_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064E888 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80079908_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_8064E930 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8007B2F4_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8064E978 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8007B540_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8064E990 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8007B640_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8064E99C --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8007BA3C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @4 && "
            "python3 tools/externalize_elf_symbol.py $in @5 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@4=lbl_8064E9C0 --redefine-sym=@5=lbl_8064E9C8 "
            "--remove-section=.sdata2 $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800886D8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @19 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@19=lbl_8064EB88 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800934A0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_8064EC90 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800A3894_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_8064EE98 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800A7E88_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064EF28 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800C17EC_unsigned_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_8064F170 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800C59F0_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_8064F158 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800C65FC_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @30 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@30=lbl_8064F158 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800C644C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_8064F158 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800CB760_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @28 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@28=lbl_8064F2A0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_800CB8F4_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @26 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@26=lbl_8064F2A0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8010F184_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_8064FE78 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_801141B8_switch",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @29 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@29=jumptable_8024E0F8 --remove-section=.data $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8014AF38_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @11 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@11=lbl_80650490 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8014B494_biases",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @7 && "
            "python3 tools/externalize_elf_symbol.py $in @9 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@7=lbl_80650490 "
            "--redefine-sym=@9=lbl_806504A0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80153898_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @5 && "
            "python3 tools/externalize_elf_symbol.py $in @7 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@5=lbl_806505A8 "
            "--redefine-sym=@7=lbl_806505B0 --remove-section=.sdata2 $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80157C0C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_80650620 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8015DC54_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_80650640 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80158B20_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @12 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@12=lbl_80650628 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179398_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_806508A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017960C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_806508A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_806508A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017974C_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_806508A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806508A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179904_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @8 lbl_806508A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@8=lbl_806508A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017A9B8_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @6 lbl_806508A8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@6=lbl_806508A8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179A18_zero",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @7 lbl_806508C0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@7=lbl_806508C0 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179A74_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_806508B8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806508B8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179EB8_zero",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @15 lbl_80650860 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@15=lbl_80650860 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80179F20_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @9 lbl_806508C8 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @10 lbl_80650860 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@9=lbl_806508C8 --redefine-sym=@10=lbl_80650860 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017A010_zero",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @24 lbl_80650860 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @25 lbl_806508C0 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@24=lbl_80650860 --redefine-sym=@25=lbl_806508C0 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017A12C_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @18 lbl_80650860 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_806508C8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@18=lbl_80650860 --redefine-sym=@17=lbl_806508C8 "
            "--remove-section=.sdata2 --rename-section=.comment=.ignored $in "
            "&& touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_8017A1C0_constants",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 lbl_80650860 orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @17 lbl_806508CC orig/GEDE01/sys/main.dol && "
            "python3 tools/externalize_elf_symbol.py $in @18 lbl_806508C8 orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_80650860 --redefine-sym=@17=lbl_806508CC "
            "--redefine-sym=@18=lbl_806508C8 --remove-section=.sdata2 "
            "--rename-section=.comment=.ignored $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80173D44_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_806506A8 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80174184_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @16 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@16=lbl_806506A8 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80173F04_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @22 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@22=lbl_806506A8 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80174358_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @22 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@22=lbl_806506A8 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_game_80198154_signed_bias",
        "command": (
            "python3 tools/externalize_elf_symbol.py $in @13 && "
            "build/binutils/powerpc-eabi-objcopy "
            "--redefine-sym=@13=lbl_80650B98 --remove-section=.sdata2 "
            "$in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
    {
        "name": "externalize_string_pool_80250588",
        "command": (
            "build/binutils/powerpc-eabi-objcopy "
            "--add-symbol lbl_80250588=.data:0,global,object $in && "
            "python3 tools/externalize_string_pool.py $in lbl_80250588 "
            "orig/GEDE01/sys/main.dol && "
            "build/binutils/powerpc-eabi-objcopy --strip-symbol='...data.0' "
            "--remove-section=.data $in && touch $out"
        ),
        "description": "EXTERNALIZE $in",
    },
]

# A renamed compiler-local symbol must contain the retail value it claims to
# represent whenever it has a complete, relocation-free file-backed value.
# Every invocation must map to a retail symbol and DOL. The externalizer rejects
# values without complete file backing and currently exempts relocation-backed
# values from raw-byte comparison because their object bytes are unresolved.
guarded_externalize_rules = set()
for rule in config.custom_build_rules:
    command = rule["command"]
    if "externalize_elf_symbol.py" not in command:
        continue
    mappings = dict(re.findall(r"--redefine-sym=([^= ]+)=([^ ]+)", command))
    locals_to_externalize = re.findall(
        r"python3 tools/externalize_elf_symbol\.py \$in ([^ ]+)", command
    )
    for local in locals_to_externalize:
        retail = mappings.get(local)
        if retail is None:
            raise ValueError(
                f"externalization of {local} in rule {rule['name']} has no "
                "retail symbol mapping"
            )
        guarded_invocation = (
            f"python3 tools/externalize_elf_symbol.py $in {local} {retail} "
            f"orig/{VERSION}/sys/main.dol"
        )
        if guarded_invocation in command:
            continue
        invocation = rf"python3 tools/externalize_elf_symbol\.py \$in {re.escape(local)}(?=\s|$)"
        command, replacements = re.subn(
            invocation,
            rf"\g<0> {retail} orig/{VERSION}/sys/main.dol",
            command,
        )
        if replacements != 1:
            raise ValueError(
                f"expected one externalization of {local} in rule {rule['name']}, "
                f"found {replacements}"
            )
    rule["command"] = command
    guarded_externalize_rules.add(rule["name"])
# The string-pool externalizer performs its own retail byte verification and
# must rerun whenever the retail DOL changes, just like the symbol externalizers.
guarded_externalize_rules.add("externalize_string_pool_80250588")
config.custom_build_steps = {
    "post-compile": [
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801C90A4.externalized"],
            "rule": "externalize_game_801C90A4_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801C90A4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801C8160.externalized"],
            "rule": "externalize_game_801C8160_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801C8160.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801C2D9C.externalized"],
            "rule": "externalize_game_801C2D9C_conversion_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801C2D9C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801C2AAC.externalized"],
            "rule": "externalize_game_801C2AAC_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801C2AAC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801C2980.externalized"],
            "rule": "externalize_game_801C2980_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801C2980.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801B02F0.externalized"],
            "rule": "externalize_game_801B02F0_jumptable",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801B02F0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801AFA74.externalized"],
            "rule": "externalize_game_801AFA74_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801AFA74.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801AC8AC.externalized"],
            "rule": "externalize_game_801AC8AC_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801AC8AC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801ABD3C.externalized"],
            "rule": "externalize_game_801ABD3C_table_and_conversion_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801ABD3C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801AB154.externalized"],
            "rule": "externalize_game_801AB154_conversion_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801AB154.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A93E8.externalized"],
            "rule": "externalize_game_801A93E8_conversion_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A93E8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A7E04.externalized"],
            "rule": "externalize_game_801A7E04_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A7E04.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A7EA8.externalized"],
            "rule": "externalize_game_801A7EA8_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A7EA8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A4CE0.externalized"],
            "rule": "externalize_game_801A4CE0_conversion_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A4CE0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A6CB4.externalized"],
            "rule": "externalize_game_801A6CB4_entries",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A6CB4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A6C58.externalized"],
            "rule": "externalize_game_801A6C58_entries",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A6C58.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A6ADC.named"],
            "rule": "name_game_801A6ADC_jumptable",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A6ADC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A6410.externalized"],
            "rule": "externalize_game_801A6410_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A6410.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A5FB0.externalized"],
            "rule": "externalize_game_801A5FB0_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A5FB0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801A1F18.externalized"],
            "rule": "externalize_game_801A1F18_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801A1F18.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8019E8C8.externalized"],
            "rule": "externalize_game_8019E8C8_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8019E8C8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8019E5E4.externalized"],
            "rule": "externalize_game_8019E5E4_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8019E5E4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8019CFC4.externalized"],
            "rule": "externalize_game_8019CFC4_constant",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8019CFC4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8019CC28.externalized"],
            "rule": "externalize_game_8019CC28_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8019CC28.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801991E0.externalized"],
            "rule": "externalize_game_801991E0_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801991E0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80198BF4.externalized"],
            "rule": "externalize_game_80198BF4_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80198BF4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80198AAC.externalized"],
            "rule": "externalize_game_80198AAC_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80198AAC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80198154.externalized"],
            "rule": "externalize_game_80198154_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80198154.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80197910.externalized"],
            "rule": "externalize_game_80197910_conversion_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80197910.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80194F80.externalized"],
            "rule": "externalize_game_80194F80_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80194F80.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80177434.externalized"],
            "rule": "externalize_string_pool_80250588",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80177434.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80193F3C.externalized"],
            "rule": "externalize_game_80193F3C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80193F3C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80193E1C.externalized"],
            "rule": "externalize_game_80193E1C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80193E1C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801931C4.externalized"],
            "rule": "externalize_game_801931C4_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801931C4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80192F54.externalized"],
            "rule": "externalize_game_80192F54_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80192F54.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80191F58.externalized"],
            "rule": "externalize_game_80191F58_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80191F58.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8019197C.externalized"],
            "rule": "externalize_game_8019197C_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8019197C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80191360.externalized"],
            "rule": "externalize_game_80191360_zero",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80191360.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018F81C.externalized"],
            "rule": "externalize_game_8018F81C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018F81C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018F1D0.globalized"],
            "rule": "globalize_game_8018F1D0_scale",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018F1D0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018D688.externalized"],
            "rule": "externalize_game_8018D688_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018D688.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018D2E0.externalized"],
            "rule": "externalize_game_8018D2E0_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018D2E0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018D1F0.externalized"],
            "rule": "externalize_game_8018D1F0_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018D1F0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80189968.externalized"],
            "rule": "externalize_game_80189968_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80189968.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80189760.externalized"],
            "rule": "externalize_game_80189760_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80189760.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801896A0.externalized"],
            "rule": "externalize_game_801896A0_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801896A0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801895E8.externalized"],
            "rule": "externalize_game_801895E8_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801895E8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80189390.externalized"],
            "rule": "externalize_game_80189390_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80189390.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801891D8.externalized"],
            "rule": "externalize_game_801891D8_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801891D8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80189028.externalized"],
            "rule": "externalize_game_80189028_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80189028.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80188E28.externalized"],
            "rule": "externalize_game_80188E28_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80188E28.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80188C1C.externalized"],
            "rule": "externalize_game_80188C1C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80188C1C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80188B44.externalized"],
            "rule": "externalize_game_80188B44_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80188B44.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80188A7C.externalized"],
            "rule": "externalize_game_80188A7C_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80188A7C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801878E0.externalized"],
            "rule": "externalize_game_801878E0_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801878E0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80187120.externalized"],
            "rule": "externalize_game_80187120_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80187120.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80186E10.externalized"],
            "rule": "externalize_game_80186E10_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80186E10.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8018FEDC.externalized"],
            "rule": "externalize_game_8018FEDC_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8018FEDC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801865EC.externalized"],
            "rule": "externalize_game_801865EC_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801865EC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80185AE8.externalized"],
            "rule": "externalize_game_80185AE8_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80185AE8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801859FC.externalized"],
            "rule": "externalize_game_801859FC_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801859FC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80180DDC.externalized"],
            "rule": "externalize_game_80180DDC_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80180DDC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017E958.externalized"],
            "rule": "externalize_game_8017E958_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017E958.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017E850.externalized"],
            "rule": "externalize_game_8017E850_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017E850.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017718C.externalized"],
            "rule": "externalize_game_8017718C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017718C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801770F8.externalized"],
            "rule": "externalize_game_801770F8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801770F8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80176FA0.externalized"],
            "rule": "externalize_game_80176FA0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80176FA0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80176DF4.externalized"],
            "rule": "externalize_game_80176DF4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80176DF4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80174358.externalized"],
            "rule": "externalize_game_80174358_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80174358.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80173F04.externalized"],
            "rule": "externalize_game_80173F04_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80173F04.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80174184.externalized"],
            "rule": "externalize_game_80174184_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80174184.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017553C.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017553C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80173D44.externalized"],
            "rule": "externalize_game_80173D44_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80173D44.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80173770.externalized"],
            "rule": "externalize_game_801726EC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80173770.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801734B4.externalized"],
            "rule": "externalize_game_8016E8F8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801734B4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80173270.externalized"],
            "rule": "externalize_game_8016C238_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80173270.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80172DB8.externalized"],
            "rule": "externalize_game_8016C238_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80172DB8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80172C78.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80172C78.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80172BB0.externalized"],
            "rule": "externalize_game_80172BB0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80172BB0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801726EC.externalized"],
            "rule": "externalize_game_801726EC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801726EC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017250C.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017250C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80171F30.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80171F30.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801719B4.externalized"],
            "rule": "externalize_game_801719B4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801719B4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801718F4.externalized"],
            "rule": "externalize_game_801718F4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801718F4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80171664.externalized"],
            "rule": "externalize_game_80171664_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80171664.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017138C.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017138C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80170A40.externalized"],
            "rule": "externalize_game_80170A40_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80170A40.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801706DC.externalized"],
            "rule": "externalize_game_801706DC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801706DC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_TRKNubWelcome.normalized"],
            "rule": "normalize_game_TRKNubWelcome_symbols",
            "inputs": [f"build/{VERSION}/src/game/game_TRKNubWelcome.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_TRK_main.normalized"],
            "rule": "normalize_game_TRK_main_symbols",
            "inputs": [f"build/{VERSION}/src/game/game_TRK_main.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_data_80239E10.normalized"],
            "rule": "normalize_game_data_80239E10_symbols",
            "inputs": [f"build/{VERSION}/src/game/game_data_80239E10.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_data_80239E18.normalized"],
            "rule": "normalize_game_data_80239E18_symbols",
            "inputs": [f"build/{VERSION}/src/game/game_data_80239E18.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017652C.externalized"],
            "rule": "externalize_game_8017652C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017652C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80170E9C.externalized"],
            "rule": "externalize_game_80170E9C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80170E9C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80175E64.externalized"],
            "rule": "externalize_game_80175E64_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80175E64.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80175F0C.externalized"],
            "rule": "externalize_game_80175F0C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80175F0C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80175FD4.externalized"],
            "rule": "externalize_game_80175FD4_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80175FD4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80176098.externalized"],
            "rule": "externalize_game_80176098_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80176098.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80176160.externalized"],
            "rule": "externalize_game_80176160_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80176160.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80176220.externalized"],
            "rule": "externalize_game_80176220_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80176220.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801762E8.externalized"],
            "rule": "externalize_game_801762E8_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801762E8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80170DF4.externalized"],
            "rule": "externalize_game_80170DF4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80170DF4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016E8F8.externalized"],
            "rule": "externalize_game_8016E8F8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016E8F8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016FEF8.externalized"],
            "rule": "externalize_game_8016FEF8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016FEF8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801704F8.externalized"],
            "rule": "externalize_game_801704F8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801704F8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016DF4C.normalized"],
            "rule": "normalize_game_8016DF4C_symbols",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016DF4C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016D2B8.externalized"],
            "rule": "externalize_game_8016D2B8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016D2B8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016D040.externalized"],
            "rule": "externalize_game_8016BE1C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016D040.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016D1F8.externalized"],
            "rule": "externalize_game_8016D1F8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016D1F8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016C774.externalized"],
            "rule": "externalize_game_8016C774_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016C774.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016C4BC.externalized"],
            "rule": "externalize_game_8016C4BC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016C4BC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016C238.externalized"],
            "rule": "externalize_game_8016C238_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016C238.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016C164.externalized"],
            "rule": "externalize_game_8016C164_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016C164.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016C0BC.externalized"],
            "rule": "externalize_game_8016C0BC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016C0BC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017038C.externalized"],
            "rule": "externalize_game_8017038C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017038C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016BE1C.externalized"],
            "rule": "externalize_game_8016BE1C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016BE1C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016BF60.externalized"],
            "rule": "externalize_game_8016BF60_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016BF60.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016BD0C.externalized"],
            "rule": "externalize_game_8016BD0C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016BD0C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80169650.externalized"],
            "rule": "externalize_game_80169650_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80169650.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80167B5C.externalized"],
            "rule": "externalize_game_80167B5C_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80167B5C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8015EDC0.externalized"],
            "rule": "externalize_game_8015EDC0_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8015EDC0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8015DC54.externalized"],
            "rule": "externalize_game_8015DC54_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8015DC54.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80158B20.externalized"],
            "rule": "externalize_game_80158B20_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80158B20.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179398.externalized"],
            "rule": "externalize_game_80179398_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179398.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017960C.externalized"],
            "rule": "externalize_game_8017960C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017960C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017974C.externalized"],
            "rule": "externalize_game_8017974C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017974C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179904.externalized"],
            "rule": "externalize_game_80179904_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179904.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017A9B8.externalized"],
            "rule": "externalize_game_8017A9B8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017A9B8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179A18.externalized"],
            "rule": "externalize_game_80179A18_zero",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179A18.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179A74.externalized"],
            "rule": "externalize_game_80179A74_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179A74.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179EB8.externalized"],
            "rule": "externalize_game_80179EB8_zero",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179EB8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80179F20.externalized"],
            "rule": "externalize_game_80179F20_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80179F20.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017A010.externalized"],
            "rule": "externalize_game_8017A010_zero",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017A010.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017A12C.externalized"],
            "rule": "externalize_game_8017A12C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017A12C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8017A1C0.externalized"],
            "rule": "externalize_game_8017A1C0_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8017A1C0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80157C0C.externalized"],
            "rule": "externalize_game_80157C0C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80157C0C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80155814.externalized"],
            "rule": "externalize_game_80155814_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80155814.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80153898.externalized"],
            "rule": "externalize_game_80153898_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80153898.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8014B494.externalized"],
            "rule": "externalize_game_8014B494_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8014B494.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8014AF38.externalized"],
            "rule": "externalize_game_8014AF38_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8014AF38.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8012DB28.externalized"],
            "rule": "externalize_game_8012DB28_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8012DB28.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801141B8.externalized"],
            "rule": "externalize_game_801141B8_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801141B8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801128E4.externalized"],
            "rule": "externalize_game_801128E4_signed_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801128E4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_801126E0.externalized"],
            "rule": "externalize_game_801126E0_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_801126E0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8010F184.externalized"],
            "rule": "externalize_game_8010F184_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8010F184.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800E4980.externalized"],
            "rule": "externalize_game_800E4980_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800E4980.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800C17EC.externalized"],
            "rule": "externalize_game_800C17EC_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800C17EC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800C59F0.externalized"],
            "rule": "externalize_game_800C59F0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800C59F0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800C644C.externalized"],
            "rule": "externalize_game_800C644C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800C644C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800C65FC.externalized"],
            "rule": "externalize_game_800C65FC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800C65FC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800CB760.externalized"],
            "rule": "externalize_game_800CB760_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800CB760.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800CB8F4.externalized"],
            "rule": "externalize_game_800CB8F4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800CB8F4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80078500.externalized"],
            "rule": "externalize_game_80078500_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80078500.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80079908.externalized"],
            "rule": "externalize_game_80079908_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80079908.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8007B2F4.externalized"],
            "rule": "externalize_game_8007B2F4_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8007B2F4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8007B540.externalized"],
            "rule": "externalize_game_8007B540_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8007B540.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8007B640.externalized"],
            "rule": "externalize_game_8007B640_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8007B640.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8007BA3C.externalized"],
            "rule": "externalize_game_8007BA3C_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8007BA3C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800886D8.externalized"],
            "rule": "externalize_game_800886D8_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800886D8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800934A0.externalized"],
            "rule": "externalize_game_800934A0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800934A0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A3894.externalized"],
            "rule": "externalize_game_800A3894_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A3894.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A7E88.externalized"],
            "rule": "externalize_game_800A7E88_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A7E88.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A4798.externalized"],
            "rule": "externalize_game_800A4798_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A4798.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A2FCC.externalized"],
            "rule": "externalize_game_800A2FCC_unsigned_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A2FCC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A2130.globalized"],
            "rule": "globalize_game_800A2130_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A2130.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8009C424.externalized"],
            "rule": "externalize_game_8009C424_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8009C424.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80096830.externalized"],
            "rule": "externalize_game_80096830_biases",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80096830.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80095FDC.switches_named"],
            "rule": "externalize_game_80095FDC_switches",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80095FDC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8008F890.globalized"],
            "rule": "globalize_game_8008F890_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8008F890.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800A4428.externalized"],
            "rule": "externalize_game_800A4428_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800A4428.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80074310.externalized"],
            "rule": "externalize_game_80074310_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80074310.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80066888.externalized"],
            "rule": "externalize_game_80066888_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80066888.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8005FD84.globalized"],
            "rule": "globalize_game_8005FD84_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8005FD84.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8005EC6C.externalized"],
            "rule": "externalize_game_8005EC6C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8005EC6C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80052310.externalized"],
            "rule": "externalize_game_80052310_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80052310.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80048B24.externalized"],
            "rule": "externalize_game_80048ADC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80048B24.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80048ADC.externalized"],
            "rule": "externalize_game_80048ADC_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80048ADC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80020E94.named"],
            "rule": "name_game_80020E94_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80020E94.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8005EE9C.named"],
            "rule": "name_game_8005EE9C_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8005EE9C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8016D9C0.named"],
            "rule": "name_game_8016D9C0_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8016D9C0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80071A58.named"],
            "rule": "name_game_80071A58_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80071A58.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001FE1C.named"],
            "rule": "name_game_8001FE1C_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001FE1C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001E644.named"],
            "rule": "name_game_8001E644_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001E644.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80038878.externalized"],
            "rule": "externalize_game_80038878_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80038878.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80036C40.externalized"],
            "rule": "externalize_game_80036C40_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80036C40.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800359A0.externalized"],
            "rule": "externalize_game_800359A0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800359A0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80033180.externalized"],
            "rule": "externalize_game_80033180_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80033180.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80033038.externalized"],
            "rule": "externalize_game_80033038_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80033038.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80032B84.externalized"],
            "rule": "externalize_game_80032B84_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80032B84.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8003232C.externalized"],
            "rule": "externalize_game_8003232C_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8003232C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8002E3F0.externalized"],
            "rule": "externalize_game_8002E3F0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8002E3F0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8002DAE0.externalized"],
            "rule": "externalize_game_8002DAE0_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8002DAE0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8002EA68.externalized"],
            "rule": "externalize_game_8002EA68_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8002EA68.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8002F428.externalized"],
            "rule": "externalize_game_8002F428_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8002F428.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8002B748.globalized"],
            "rule": "globalize_game_8002B748_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8002B748.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800272B4.externalized"],
            "rule": "externalize_game_800272B4_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800272B4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80024F28.switches_named"],
            "rule": "name_game_80024F28_switches",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80024F28.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001CE94.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001CE94.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001CD58.externalized"],
            "rule": "externalize_game_unsigned_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001CD58.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001C078.externalized"],
            "rule": "externalize_game_bias_17",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001C078.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001B874.externalized"],
            "rule": "externalize_game_8001B874_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001B874.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001B808.externalized"],
            "rule": "externalize_game_8001B808_constants",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001B808.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001B294.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001B294.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001B124.externalized"],
            "rule": "externalize_game_unsigned_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001B124.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001AF68.externalized"],
            "rule": "externalize_game_bias_16_unsigned_bias_19",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001AF68.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001ADF8.externalized"],
            "rule": "externalize_game_unsigned_bias_19",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001ADF8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001AAB8.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001AAB8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8001A6C4.externalized"],
            "rule": "externalize_game_bias_70",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8001A6C4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019F98.externalized"],
            "rule": "externalize_game_bias_19",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019F98.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019D2C.externalized"],
            "rule": "externalize_game_bias_18",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019D2C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019C10.externalized"],
            "rule": "externalize_game_bias_12",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019C10.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019940.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019940.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800194D0.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800194D0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019244.externalized"],
            "rule": "externalize_game_bias_16",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019244.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80019054.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80019054.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80018EF4.externalized"],
            "rule": "externalize_game_bias_13",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80018EF4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017DB0.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017DB0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017CC8.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017CC8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017C3C.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017C3C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017AE4.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017AE4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017A3C.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017A3C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800179AC.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800179AC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80017910.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80017910.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800119FC.externalized"],
            "rule": "externalize_game_flags_4",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800119FC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000FFD8.externalized"],
            "rule": "externalize_game_bias_9",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000FFD8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000F4B0.externalized"],
            "rule": "externalize_game_bias_13",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000F4B0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000EFC4.externalized"],
            "rule": "externalize_game_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000EFC4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800094C0.globalized"],
            "rule": "globalize_game_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800094C0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800096E0.externalized"],
            "rule": "externalize_game_bias",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800096E0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800098C0.externalized"],
            "rule": "externalize_game_bias_17",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800098C0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800099D8.externalized"],
            "rule": "externalize_game_bias_12",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800099D8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80009AB4.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80009AB4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000A26C.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000A26C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800171C0.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800171C0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800176F0.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800176F0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000AC88.externalized"],
            "rule": "externalize_game_bias_18",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000AC88.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000AEB4.externalized"],
            "rule": "externalize_game_bias_13",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000AEB4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000AFB4.externalized"],
            "rule": "externalize_game_bias_9",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000AFB4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000B1B8.externalized"],
            "rule": "externalize_game_bias_6",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000B1B8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000B36C.externalized"],
            "rule": "externalize_game_bias_12",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000B36C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000B630.externalized"],
            "rule": "externalize_game_bias_18",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000B630.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000B7FC.externalized"],
            "rule": "externalize_game_bias_18",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000B7FC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000B900.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000B900.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000BA0C.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000BA0C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000BAA0.externalized"],
            "rule": "externalize_game_bias_9",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000BAA0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000BC40.externalized"],
            "rule": "externalize_game_bias_17",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000BC40.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000C06C.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000C06C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000C17C.externalized"],
            "rule": "externalize_game_bias_9",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000C17C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000C400.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000C400.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000C848.externalized"],
            "rule": "externalize_game_bias_12",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000C848.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000C91C.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000C91C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000D0BC.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000D0BC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000D3D4.externalized"],
            "rule": "externalize_game_bias_6",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000D3D4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000D8A4.switch_named"],
            "rule": "name_game_8000D8A4_switch",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000D8A4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000E054.externalized"],
            "rule": "externalize_game_bias_6",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000E054.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000E0AC.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000E0AC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000E96C.externalized"],
            "rule": "externalize_game_bias_21",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000E96C.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000F774.externalized"],
            "rule": "externalize_game_bias_98",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000F774.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000EB14.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000EB14.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000EBD4.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000EBD4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000ED44.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000ED44.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000E138.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000E138.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000E1C4.externalized"],
            "rule": "externalize_game_bias_16",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000E1C4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000D590.externalized"],
            "rule": "externalize_game_bias_46",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000D590.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000DA50.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000DA50.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_8000DAF4.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_8000DAF4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80012DA8.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80012DA8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80012F40.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80012F40.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80012FD0.externalized"],
            "rule": "externalize_game_bias_12",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80012FD0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800131E8.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800131E8.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80013340.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80013340.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80013870.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80013870.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80013CB0.externalized"],
            "rule": "externalize_game_bias_9",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80013CB0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80013D54.externalized"],
            "rule": "externalize_game_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80013D54.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800142DC.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800142DC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800144CC.externalized"],
            "rule": "externalize_game_bias_20",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800144CC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80014784.externalized"],
            "rule": "externalize_game_bias_15",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80014784.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800149D4.externalized"],
            "rule": "externalize_game_bias_30",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800149D4.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015058.externalized"],
            "rule": "externalize_game_bias_21",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015058.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015320.externalized"],
            "rule": "externalize_game_bias_16",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015320.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015568.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015568.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800156FC.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800156FC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015BE0.externalized"],
            "rule": "externalize_game_bias_11",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015BE0.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015D40.externalized"],
            "rule": "externalize_game_bias_16",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015D40.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80015F04.externalized"],
            "rule": "externalize_game_bias_19",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80015F04.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80016128.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80016128.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80016270.externalized"],
            "rule": "externalize_game_bias_14",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80016270.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80016904.externalized"],
            "rule": "externalize_game_unsigned_bias_8",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80016904.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_800173CC.externalized"],
            "rule": "externalize_game_unsigned_bias_36",
            "inputs": [f"build/{VERSION}/src/game/game_fn_800173CC.o"],
        },
        {
            "outputs": [f"build/{VERSION}/src/game/game_fn_80016B24.externalized"],
            "rule": "externalize_game_bias_10",
            "inputs": [f"build/{VERSION}/src/game/game_fn_80016B24.o"],
        },
    ]
}
if args.map:
    config.ldflags.append("-mapunused")
if args.debug:
    config.ldflags.append("-g")

# This is a testable starting hypothesis, not a fingerprint result.
for steps in config.custom_build_steps.values():
    for step in steps:
        if step["rule"] in guarded_externalize_rules:
            step.setdefault("implicit", []).append(f"orig/{VERSION}/sys/main.dol")

config.linker_version = GAME_MW_VERSION
cflags_base = [
    "-nodefaults", "-proc gekko", "-align powerpc", "-enum int", "-fp hardware",
    "-Cpp_exceptions off", "-O4,p", "-inline auto", '-pragma "cats off"',
    '-pragma "warn_notinlined off"', "-maxerrors 1", "-nosyspath", "-RTTI off",
    "-fp_contract on", "-str reuse", "-multibyte", "-i include", f"-i build/{VERSION}/include",
    f"-DVERSION_{VERSION}",
]
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
]
if args.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")


def cflags_with_optimization(optimization):
    return [optimization if flag == "-O4,p" else flag for flag in cflags_base]


Matching = True
NonMatching = False
Equivalent = config.non_matching

# SDK objects are promoted only after objdiff and the whole-DOL hash gate pass.
config.warn_missing_config = False
config.warn_missing_source = False
config.libs = [
    {
        "lib": "game",
        "mw_version": LIBRARY_MW_VERSIONS["game"],
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/game_prefix_800068E0.c"),
            Object(Matching, "game/game_fn_800069DC.c"),
            Object(Matching, "game/game_fn_80006B38.c"),
            Object(Matching, "game/game_fn_80006D50.c"),
            Object(Matching, "game/game_fn_80006F30.c"),
            Object(Matching, "game/game_fn_800070E4.c"),
            Object(Matching, "game/game_fn_8000738C.c"),
            Object(Matching, "game/game_fn_800073E4.c"),
            Object(Matching, "game/game_fn_8000755C.c"),
            # fn_80008014 sits at 96.11%: MWCC schedules the loop index copy
            # into the latch instead of the body. See reports/GEDE01/
            # matching-cycle-2026-07-25.md. fn_80008134 is 100%.
            Object(NonMatching, "game/game_fn_80008014.c"),
            Object(Matching, "game/game_fn_80008154.c"),
            Object(Matching, "game/game_fn_800082A4.c"),
            Object(Matching, "game/game_fn_80008438.c"),
            Object(Matching, "game/game_fn_800086CC.c"),
            Object(Matching, "game/game_fn_80008710.c"),
            Object(Matching, "game/game_fn_80008724.c"),
            Object(Matching, "game/game_fn_80008738.c"),
            Object(Matching, "game/game_fn_800087E8.c"),
            Object(Matching, "game/game_fn_80008888.c"),
            Object(
                Matching,
                "game/game_fn_80008910.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000A7C4.c"),
            Object(Matching, "game/game_fn_8000A844.c"),
            Object(Matching, "game/game_fn_8000A8C4.c"),
            Object(Matching, "game/game_fn_8000A9A4.c"),
            Object(Matching, "game/game_fn_8000AA8C.c"),
            Object(Matching, "game/game_fn_8000AB88.c"),
            Object(Matching, "game/game_fn_8000AC88.c"),
            Object(Matching, "game/game_fn_8000AE14.c"),
            Object(Matching, "game/game_fn_8000AEB4.c"),
            Object(Matching, "game/game_fn_8000AFB4.c"),
            Object(Matching, "game/game_fn_8000B138.c"),
            Object(Matching, "game/game_fn_8000B1B8.c"),
            Object(
                Matching,
                "game/game_fn_8000B20C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000B36C.c"),
            Object(Matching, "game/game_fn_8000B444.c"),
            Object(Matching, "game/game_fn_8000B548.c"),
            Object(Matching, "game/game_fn_8000B5C8.c"),
            Object(
                Matching,
                "game/game_fn_8000B630.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000B734.c"),
            Object(
                Matching,
                "game/game_fn_8000B7FC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000B900.c"),
            Object(Matching, "game/game_fn_8000B98C.c"),
            Object(Matching, "game/game_fn_8000BA0C.c"),
            Object(Matching, "game/game_fn_8000BA98.c"),
            Object(Matching, "game/game_fn_8000BAA0.c"),
            Object(Matching, "game/game_fn_8000BB98.c"),
            Object(
                Matching,
                "game/game_fn_8000BC40.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000BDF8.c"),
            Object(Matching, "game/game_fn_8000BE60.c"),
            Object(Matching, "game/game_fn_8000BEF4.c"),
            Object(Matching, "game/game_fn_8000BF4C.c"),
            Object(Matching, "game/game_fn_8000BFEC.c"),
            Object(Matching, "game/game_fn_8000C06C.c"),
            Object(Matching, "game/game_fn_8000C17C.c"),
            Object(
                Matching,
                "game/game_fn_8000C220.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000C400.c"),
            Object(Matching, "game/game_fn_8000C578.c"),
            Object(
                Matching,
                "game/game_fn_8000C618.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8000C734.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000C848.c"),
            Object(
                Matching,
                "game/game_fn_8000C91C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8000CC68.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000CDEC.c"),
            Object(Matching, "game/game_fn_8000CED4.c"),
            Object(Matching, "game/game_fn_8000D070.c"),
            Object(Matching, "game/game_fn_8000D098.c"),
            Object(Matching, "game/game_fn_8000D0BC.c"),
            Object(Matching, "game/game_fn_8000D188.c"),
            Object(Matching, "game/game_fn_8000D218.c"),
            Object(Matching, "game/game_fn_8000D2B8.c"),
            Object(Matching, "game/game_fn_8000D354.c"),
            Object(Matching, "game/game_fn_8000D3D4.c"),
            Object(Matching, "game/game_fn_8000D428.c"),
            Object(Matching, "game/game_fn_8000D44C.c"),
            Object(Matching, "game/game_fn_8000D528.c"),
            Object(
                Matching,
                "game/game_fn_8000D590.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000D7C8.c"),
            Object(Matching, "game/game_fn_8000D8A4.c"),
            Object(Matching, "game/game_fn_8000D978.c"),
            Object(Matching, "game/game_fn_8000DA50.c"),
            Object(Matching, "game/game_fn_8000DAF4.c"),
            Object(
                Matching,
                "game/game_fn_8000DBD8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000DCF8.c"),
            Object(
                Matching,
                "game/game_fn_8000DDAC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000DFCC.c"),
            Object(Matching, "game/game_fn_8000E054.c"),
            Object(Matching, "game/game_fn_8000E0AC.c"),
            Object(Matching, "game/game_fn_8000E138.c"),
            Object(Matching, "game/game_fn_8000E1C4.c"),
            Object(Matching, "game/game_fn_8000E2A8.c"),
            Object(Matching, "game/game_fn_8000E428.c"),
            Object(
                Matching,
                "game/game_fn_8000E4CC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8000E664.c"),
            Object(Matching, "game/game_fn_8000E764.c"),
            Object(Matching, "game/game_fn_8000E84C.c"),
            # 99.81132%: four FPR operand fields differ while size and all
            # 16 relocation sites agree. Preserve the real C; do not replace
            # the vector-conversion block with inline assembly.
            Object(
                NonMatching,
                "game/game_fn_8000E96C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            # 99.833336%: the four instructions forming the final signed
            # integer-to-double temporary use 0x10/0x14 instead of retail's
            # reused 0x8/0xC slot; all 10 relocation sites agree.
            Object(Matching, "game/game_fn_8000EB14.c"),
            # 99.9375%: the four instructions forming the final signed
            # integer-to-double temporary use 0x10/0x14 instead of retail's
            # reused 0x8/0xC slot (same MWCC temp-allocation divergence as
            # fn_8000EB14); all 10 relocation sites agree.
            Object(Matching, "game/game_fn_8000EBD4.c"),
            Object(Matching, "game/game_fn_8000EC94.c"),
            Object(Matching, "game/game_fn_8000ED44.c"),
            Object(Matching, "game/game_fn_8000EDF0.c"),
            Object(Matching, "game/game_fn_8000EE9C.c"),
            Object(Matching, "game/game_fn_8000EFC4.c"),
            Object(NonMatching, "game/game_fn_8000F1DC.c"),
            Object(Matching, "game/game_fn_8000F38C.c"),
            Object(Matching, "game/game_fn_8000F430.c"),
            Object(Matching, "game/game_fn_8000F4B0.c"),
            Object(Matching, "game/game_fn_8000F5C8.c"),
            Object(Matching, "game/game_fn_8000F6AC.c"),
            # 99.45521%: the generated object has the exact 1652-byte size
            # and control flow; remaining deltas are callee-saved register
            # allocation in the long-lived handle/object webs.
            Object(NonMatching, "game/game_fn_8000F774.c"),
            # 97.94355%: real C reconstruction has the exact 496-byte
            # size and control flow, but MWCC allocates every long-lived
            # value one callee-saved register below retail.
            Object(NonMatching, "game/game_fn_8000FDE8.c"),
            Object(Matching, "game/game_fn_8000FFD8.c"),
            Object(Matching, "game/game_fn_8001007C.c"),
            # 100%: argument 1 is the object id and argument 3 is the value;
            # keeping them distinct preserves retail's three conversions.
            Object(Matching, "game/game_fn_800115CC.c"),
            Object(Matching, "game/game_fn_800116E8.c"),
            Object(Matching, "game/game_fn_800117CC.c"),
            Object(Matching, "game/game_fn_80011888.c"),
            Object(Matching, "game/game_fn_800119FC.c"),
            Object(Matching, "game/game_fn_80011B54.c"),
            Object(Matching, "game/game_fn_80011C10.c"),
            Object(Matching, "game/game_fn_80011CE0.c"),
            Object(Matching, "game/game_fn_80011E1C.c"),
            Object(Matching, "game/game_fn_80011ED8.c"),
            Object(Matching, "game/game_fn_80011F00.c"),
            Object(Matching, "game/game_fn_80011F6C.c"),
            Object(Matching, "game/game_fn_80012008.c"),
            Object(Matching, "game/game_fn_80012120.c"),
            Object(Matching, "game/game_fn_80012134.c"),
            Object(Matching, "game/game_fn_80012160.c"),
            Object(Matching, "game/game_fn_8001221C.c"),
            Object(Matching, "game/game_fn_80012278.c"),
            Object(Matching, "game/game_fn_800122F8.c"),
            Object(Matching, "game/game_fn_8001238C.c"),
            Object(Matching, "game/game_fn_8001243C.c"),
            Object(Matching, "game/game_fn_8001252C.c"),
            Object(Matching, "game/game_fn_800125AC.c"),
            Object(Matching, "game/game_fn_80012624.c"),
            Object(Matching, "game/game_fn_80012744.c"),
            Object(Matching, "game/game_fn_8001291C.c"),
            Object(Matching, "game/game_fn_8001299C.c"),
            Object(Matching, "game/game_fn_80012A88.c"),
            Object(Matching, "game/game_fn_80012B6C.c"),
            Object(Matching, "game/game_fn_80012CC4.c"),
            Object(Matching, "game/game_fn_80012DA8.c"),
            Object(Matching, "game/game_fn_80012E34.c"),
            Object(Matching, "game/game_fn_80012F40.c"),
            Object(Matching, "game/game_fn_80012FD0.c"),
            Object(Matching, "game/game_fn_80013098.c"),
            Object(Matching, "game/game_fn_80013154.c"),
            Object(Matching, "game/game_fn_800131E8.c"),
            Object(Matching, "game/game_fn_800132C0.c"),
            Object(Matching, "game/game_fn_80013340.c"),
            Object(
                Matching,
                "game/game_fn_800133CC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80013564.c"),
            Object(Matching, "game/game_fn_80013614.c"),
            Object(Matching, "game/game_fn_800136C4.c"),
            Object(Matching, "game/game_fn_80013748.c"),
            Object(Matching, "game/game_fn_800137DC.c"),
            Object(Matching, "game/game_fn_80013870.c"),
            Object(Matching, "game/game_fn_8001390C.c"),
            Object(Matching, "game/game_fn_800139F0.c"),
            Object(Matching, "game/game_fn_80013AD4.c"),
            Object(Matching, "game/game_fn_80013B98.c"),
            Object(Matching, "game/game_fn_80013CB0.c"),
            Object(Matching, "game/game_fn_80013D54.c"),
            Object(Matching, "game/game_fn_80013DEC.c"),
            Object(Matching, "game/game_fn_80013E6C.c"),
            Object(Matching, "game/game_fn_80013EEC.c"),
            Object(Matching, "game/game_fn_80013F88.c"),
            Object(Matching, "game/game_fn_800140E0.c"),
            Object(Matching, "game/game_fn_80014144.c"),
            Object(Matching, "game/game_fn_800141B4.c"),
            Object(Matching, "game/game_fn_80014238.c"),
            Object(
                Matching,
                "game/game_fn_800142DC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800144CC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80014784.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800149D4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80014CF8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80015058.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_800152B8.c"),
            Object(
                Matching,
                "game/game_fn_80015320.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80015568.c"),
            Object(Matching, "game/game_fn_800156FC.c"),
            Object(
                Matching,
                "game/game_fn_80015888.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800159B0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80015BE0.c"),
            Object(
                Matching,
                "game/game_fn_80015D40.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80015F04.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80016128.c"),
            Object(
                Matching,
                "game/game_fn_80016270.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80016414.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_800165AC.c"),
            Object(Matching, "game/game_fn_80016668.c"),
            Object(
                Matching,
                "game/game_fn_80016730.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80016904.c"),
            Object(Matching, "game/game_fn_80016994.c"),
            Object(NonMatching, "game/game_fn_800169FC.c"),
            Object(Matching, "game/game_fn_80016B24.c"),
            Object(Matching, "game/game_fn_80016BDC.c"),
            Object(Matching, "game/game_fn_80016C48.c"),
            Object(Matching, "game/game_fn_80016CE8.c"),
            Object(Matching, "game/game_fn_80016D68.c"),
            Object(Matching, "game/game_fn_80016F0C.c"),
            Object(Matching, "game/game_fn_80016F78.c"),
            Object(Matching, "game/game_fn_80016FE8.c"),
            Object(Matching, "game/game_fn_80017074.c"),
            Object(Matching, "game/game_fn_80017134.c"),
            Object(Matching, "game/game_fn_800171C0.c"),
            Object(Matching, "game/game_fn_80017260.c"),
            Object(NonMatching, "game/game_fn_800173CC.c"),
            Object(Matching, "game/game_fn_80017600.c"),
            Object(Matching, "game/game_fn_80017678.c"),
            Object(Matching, "game/game_fn_800176F0.c"),
            Object(Matching, "game/game_fn_80017884.c"),
            Object(Matching, "game/game_fn_80017910.c"),
            Object(Matching, "game/game_fn_800179AC.c"),
            Object(Matching, "game/game_fn_80017A3C.c"),
            Object(Matching, "game/game_fn_80017AE4.c"),
            Object(Matching, "game/game_fn_80017B80.c"),
            Object(Matching, "game/game_fn_80017C3C.c"),
            Object(Matching, "game/game_fn_80017CC8.c"),
            Object(Matching, "game/game_fn_80017DB0.c"),
            Object(Matching, "game/game_fn_80017ED0.c"),
            Object(NonMatching, "game/game_fn_80017FF8.c"),
            Object(Matching, "game/game_fn_80018598.c"),
            Object(Matching, "game/game_fn_80018650.c"),
            Object(NonMatching, "game/game_fn_80018708.c"),
            Object(Matching, "game/game_fn_80018C14.c"),
            Object(
                Matching,
                "game/game_fn_80018CC4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80018ED4.c"),
            Object(
                Matching,
                "game/game_fn_80018EF4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80019054.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80019244.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_800194D0.c"),
            Object(
                Matching,
                "game/game_fn_80019644.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80019788.c"),
            Object(Matching, "game/game_fn_80019808.c"),
            Object(Matching, "game/game_fn_800198A4.c"),
            Object(Matching, "game/game_fn_80019940.c"),
            Object(Matching, "game/game_fn_80019B08.c"),
            Object(Matching, "game/game_fn_80019B88.c"),
            Object(Matching, "game/game_fn_80019C10.c"),
            Object(Matching, "game/game_fn_80019D2C.c"),
            Object(Matching, "game/game_fn_80019ED8.c"),
            Object(
                Matching,
                "game/game_fn_80019F98.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8001A2A4.c"),
            Object(Matching, "game/game_fn_8001A378.c"),
            Object(Matching, "game/game_fn_8001A4C8.c"),
            Object(Matching, "game/game_fn_8001A568.c"),
            Object(Matching, "game/game_fn_8001A594.c"),
            Object(Matching, "game/game_fn_8001A600.c"),
            Object(Matching, "game/game_fn_8001A624.c"),
            Object(Matching, "game/game_fn_8001A6C4.c"),
            Object(Matching, "game/game_fn_8001AAB8.c"),
            Object(Matching, "game/game_fn_8001AB70.c"),
            Object(Matching, "game/game_fn_8001ABF0.c"),
            Object(Matching, "game/game_fn_8001AC70.c"),
            Object(Matching, "game/game_fn_8001AD78.c"),
            Object(Matching, "game/game_fn_8001ADF8.c"),
            Object(Matching, "game/game_fn_8001AF68.c"),
            Object(Matching, "game/game_fn_8001B124.c"),
            Object(Matching, "game/game_fn_8001B294.c"),
            Object(Matching, "game/game_fn_8001B3F0.c"),
            Object(
                Matching,
                "game/game_fn_8001B4AC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8001B6CC.c"),
            Object(Matching, "game/game_fn_8001B808.c"),
            Object(Matching, "game/game_fn_8001B874.c"),
            Object(Matching, "game/game_fn_8001B978.c"),
            Object(Matching, "game/game_fn_8001BA5C.c"),
            Object(
                Matching,
                "game/game_fn_8001BAE4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8001BED0.c"),
            Object(Matching, "game/game_fn_8001BF50.c"),
            Object(Matching, "game/game_fn_8001BFD0.c"),
            Object(
                Matching,
                "game/game_fn_8001C078.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8001C250.c"),
            Object(Matching, "game/game_fn_8001C310.c"),
            Object(Matching, "game/game_fn_8001C38C.c"),
            Object(Matching, "game/game_fn_8001C500.c"),
            Object(Matching, "game/game_fn_8001C55C.c"),
            Object(Matching, "game/game_fn_8001C6D8.c"),
            Object(Matching, "game/game_fn_8001C83C.c"),
            Object(NonMatching, "game/game_fn_8001CA04.c"),
            Object(Matching, "game/game_fn_8001CB10.c"),
            Object(Matching, "game/game_fn_8001CB88.c"),
            Object(Matching, "game/game_fn_8001CC00.c"),
            Object(Matching, "game/game_fn_8001CC6C.c"),
            Object(Matching, "game/game_fn_8001CD58.c"),
            Object(Matching, "game/game_fn_8001CE14.c"),
            Object(Matching, "game/game_fn_8001CE94.c"),
            Object(Matching, "game/game_fn_8001CF38.c"),
            Object(Matching, "game/game_fn_8001CFB8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8001D0F8.c"),
            Object(Matching, "game/game_fn_8001D11C.c"),
            Object(Matching, "game/game_fn_8001D130.c"),
            Object(Matching, "game/game_fn_8001D1BC.c"),
            Object(Matching, "game/game_fn_8001D2EC.c"),
            Object(Matching, "game/game_fn_8001D36C.c"),
            Object(Matching, "game/game_fn_8001D3F8.c"),
            Object(Matching, "game/game_fn_8001D4C4.c"),
            Object(Matching, "game/game_fn_8001D510.c"),
            Object(Matching, "game/game_fn_8001D56C.c"),
            Object(Matching, "game/game_fn_8001D5A8.c"),
            Object(NonMatching, "game/main.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_data_8023D020.c"),
            Object(Matching, "game/game_data_8023D5B8.c"),
            Object(Matching, "game/game_data_8023D77C.c"),
            Object(Matching, "game/game_data_8023D884.c"),
            Object(Matching, "game/game_fn_8001D91C.c"),
            Object(Matching, "game/game_fn_8001D9FC.c"),
            Object(Matching, "game/game_fn_8001DA04.c"),
            Object(Matching, "game/game_fn_8001DA0C.c"),
            Object(Matching, "game/game_fn_8001DA18.c"),
            Object(Matching, "game/game_fn_8001DA7C.c"),
            Object(Matching, "game/game_fn_8001DB04.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8001DE68.c"),
            Object(NonMatching, "game/game_fn_8001DE84.c"),
            Object(NonMatching, "game/game_fn_8001DFEC.c"),
            Object(Matching, "game/game_fn_8001E134.c"),
            Object(Matching, "game/game_fn_8001E13C.c"),
            Object(NonMatching, "game/game_fn_8001E144.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8001E604.c"),
            Object(Matching, "game/game_fn_8001E644.c"),
            Object(Matching, "game/game_data_8023D918.c"),
            Object(NonMatching, "game/game_fn_8001E894.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8001F754.c"),
            Object(Matching, "game/game_fn_8001F758.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8001FB94.c"),
            Object(Matching, "game/game_fn_8001FE1C.c"),
            Object(Matching, "game/game_fn_8002014C.c"),
            Object(Matching, "game/game_data_8023DA2C.c"),
            Object(NonMatching, "game/game_fn_80020150.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80020D70.c"),
            Object(Matching, "game/game_fn_80020D90.c"),
            Object(Matching, "game/game_fn_80020E94.c"),
            Object(Matching, "game/game_data_8023DAB4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023DAB8.c"),
            Object(Matching, "game/game_data_8023DD84.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80021234.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80021490.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80021714.c"),
            Object(Matching, "game/game_fn_800217F4.c"),
            Object(NonMatching, "game/game_fn_8002188C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80023230.c"),
            Object(NonMatching, "game/game_fn_80023258.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80023674.c"),
            Object(Matching, "game/game_fn_800236A0.c"),
            Object(Matching, "game/game_fn_80023710.c"),
            Object(Matching, "game/game_fn_80023800.c"),
            Object(Matching, "game/game_fn_8002387C.c"),
            Object(Matching, "game/game_fn_800238BC.c"),
            Object(Matching, "game/game_fn_80023918.c"),
            Object(Matching, "game/game_fn_80023A68.c"),
            Object(Matching, "game/game_fn_80023B40.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80023C20.c"),
            Object(Matching, "game/game_fn_80023CF8.c"),
            Object(Matching, "game/game_fn_80023EA8.c"),
            Object(Matching, "game/game_fn_80023ED4.c"),
            Object(Matching, "game/game_fn_80024040.c"),
            Object(Matching, "game/game_fn_80024100.c"),
            Object(Matching, "game/game_fn_800242B8.c"),
            Object(Matching, "game/game_fn_800243E8.c"),
            Object(Matching, "game/game_fn_80024434.c"),
            Object(Matching, "game/game_fn_80024468.c"),
            Object(Matching, "game/game_fn_800244C4.c"),
            Object(Matching, "game/game_fn_800244F4.c"),
            Object(Matching, "game/game_fn_80024570.c"),
            Object(Matching, "game/game_fn_80024594.c"),
            Object(Matching, "game/game_fn_80024638.c"),
            Object(Matching, "game/game_fn_800246B8.c"),
            Object(Matching, "game/game_fn_8002476C.c"),
            Object(Matching, "game/game_fn_80024794.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8002487C.c"),
            Object(Matching, "game/game_fn_800248C0.c"),
            Object(Matching, "game/game_fn_8002495C.c"),
            Object(Matching, "game/game_fn_80024B74.c"),
            Object(Matching, "game/game_fn_80024B78.c"),
            Object(Matching, "game/game_fn_80024D08.c"),
            Object(Matching, "game/game_fn_80024D3C.c"),
            Object(Matching, "game/game_fn_80024F28.c"),
            Object(Matching, "game/game_data_8023DEB0.c"),
            Object(Matching, "game/game_data_8023DF88.c"),
            Object(Matching, "game/game_data_8023DFAC.c"),
            Object(Matching, "game/game_data_8023DFD0.c"),
            Object(Matching, "game/game_data_8023E030.c"),
            Object(Matching, "game/game_data_8023E070.c"),
            Object(Matching, "game/game_data_8023E088.c"),
            Object(Matching, "game/game_data_8023E0E8.c"),
            Object(Matching, "game/game_data_8023E118.c"),
            Object(Matching, "game/game_data_8023E154.c"),
            Object(Matching, "game/game_data_8023E280.c"),
            Object(Matching, "game/game_data_8023E388.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023E410.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023E448.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023E4E8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023E7C0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023E868.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EA80.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EAC0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EAE8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EC18.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EC50.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023ECBC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023ECE8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EE40.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EE80.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EE94.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EEE4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EF34.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023EF84.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F204.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F350.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F49C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F560.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F6AC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F7C4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023F904.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023FA44.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023FB90.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023FCD0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023FE1C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8023FF7C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_802400DC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8024023C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_8024039C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_802404FC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_80240648.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_802407A8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_80240908.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_data_80240A68.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80025A78.c"),
            Object(Matching, "game/game_fn_80025AA0.c"),
            Object(
                Matching,
                "game/game_fn_80025AA4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80025D28.c"),
            Object(Matching, "game/game_fn_80025F48.c"),
            Object(Matching, "game/game_fn_80026060.c"),
            Object(Matching, "game/game_fn_80026070.c"),
            Object(Matching, "game/game_fn_80026118.c"),
            Object(Matching, "game/game_fn_8002617C.c"),
            Object(Matching, "game/game_fn_80026280.c"),
            Object(NonMatching, "game/game_fn_80026320.c"),
            Object(Matching, "game/game_fn_80026740.c"),
            Object(Matching, "game/game_fn_80026744.c"),
            Object(Matching, "game/game_fn_80026754.c"),
            Object(
                NonMatching,
                "game/game_fn_80026768.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80026DAC.c"),
            Object(Matching, "game/game_fn_80026DBC.c"),
            Object(
                NonMatching,
                "game/game_fn_80026DC8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80027030.c"),
            Object(Matching, "game/game_fn_80027150.c"),
            Object(Matching, "game/game_fn_80027290.c"),
            Object(Matching, "game/game_fn_8002729C.c"),
            Object(Matching, "game/game_fn_800272A8.c"),
            Object(
                Matching,
                "game/game_fn_800272B4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80027614.c"),
            Object(Matching, "game/game_fn_80027638.c"),
            Object(Matching, "game/game_fn_80027640.c"),
            Object(Matching, "game/game_fn_80027730.c"),
            Object(Matching, "game/game_fn_800277A4.c"),
            Object(Matching, "game/game_fn_800277DC.c"),
            Object(Matching, "game/game_fn_80027854.c"),
            Object(
                Matching,
                "game/game_fn_80027948.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80027B78.c"),
            Object(Matching, "game/game_fn_80027C38.c"),
            Object(Matching, "game/game_fn_80027D40.c"),
            Object(Matching, "game/game_fn_80027E34.c"),
            Object(Matching, "game/game_fn_80027F0C.c"),
            Object(Matching, "game/game_fn_80027F10.c"),
            Object(Matching, "game/game_fn_80027F3C.c"),
            Object(Matching, "game/game_fn_80027F44.c"),
            Object(Matching, "game/game_fn_80028098.c"),
            Object(Matching, "game/game_fn_800280FC.c"),
            Object(
                NonMatching,
                "game/game_fn_80028198.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800289A4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80028B44.c"),
            Object(Matching, "game/game_fn_80028BE4.c"),
            Object(Matching, "game/game_fn_80028D54.c"),
            Object(Matching, "game/game_fn_80028E0C.c"),
            Object(Matching, "game/game_fn_80028E88.c"),
            Object(Matching, "game/game_fn_800291A0.c"),
            Object(Matching, "game/game_fn_8002A444.c"),
            Object(Matching, "game/game_fn_8002A4C8.c"),
            Object(Matching, "game/game_fn_8002A508.c"),
            Object(Matching, "game/game_fn_8002A590.c"),
            Object(Matching, "game/game_fn_8002A63C.c"),
            Object(Matching, "game/game_fn_8002A6CC.c"),
            Object(Matching, "game/game_fn_8002A754.c"),
            Object(Matching, "game/game_fn_8002A858.c"),
            Object(Matching, "game/game_fn_8002AA18.c"),
            Object(Matching, "game/game_fn_8002AB08.c"),
            Object(Matching, "game/game_fn_8002AB84.c"),
            Object(Matching, "game/game_fn_8002B5B0.c"),
            Object(NonMatching, "game/game_fn_8002B5B4.c"),
            Object(Matching, "game/game_fn_8002B624.c"),
            Object(Matching, "game/game_fn_8002B650.c"),
            Object(Matching, "game/game_fn_8002B688.c"),
            Object(Matching, "game/game_fn_8002B6B0.c"),
            Object(
                Matching,
                "game/game_fn_8002B748.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002BA80.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002BC7C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_8002BFE0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002C160.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8002C4BC.c"),
            Object(
                Matching,
                "game/game_fn_8002C7A8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8002C7A8_data.c"),
            Object(
                Matching,
                "game/game_fn_8002CBF8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D094.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D17C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D3B0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D4DC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D69C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002D8C8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_8002DAE0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002E248.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002E3F0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002E77C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002EA18.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8002EA68.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_8002F428.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_8002FAE8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_80031544.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_80031694.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800317AC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80031948.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80031A00.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80031BE0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80031C78.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_80031D24.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80031FE4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8003232C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800326C0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032860.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032924.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_800329E8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032A0C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_80032A5C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032B18.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032B84.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032CB0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80032E90.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80033038.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8003315C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_80033180.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_800337C8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80033970.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80033D5C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80034054.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80034114.c"),
            Object(
                NonMatching,
                "game/game_fn_80034708.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80035534.c"),
            Object(Matching, "game/game_fn_800355F0.c"),
            Object(Matching, "game/game_fn_80035628.c"),
            Object(Matching, "game/game_fn_8003565C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80035890.c"),
            Object(Matching, "game/game_fn_80035958.c"),
            Object(
                NonMatching,
                "game/game_fn_800359A0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80035FB8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80036060.c"),
            Object(Matching, "game/game_fn_800360B0.c"),
            Object(Matching, "game/game_fn_80036104.c"),
            Object(Matching, "game/game_fn_80036198.c"),
            Object(NonMatching, "game/game_fn_800361F8.c"),
            Object(
                NonMatching,
                "game/game_fn_80036374.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_data_80036374.c"),
            Object(
                NonMatching,
                "game/game_fn_800365C8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_data_800365C8.c"),
            Object(
                Matching,
                "game/game_fn_80036A1C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80036B7C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80036C40.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80036D38.c"),
            Object(Matching, "game/game_fn_80036D5C.c"),
            Object(Matching, "game/game_fn_80036DA4.c"),
            Object(Matching, "game/game_fn_80036DF0.c"),
            Object(Matching, "game/game_fn_80036E14.c"),
            Object(Matching, "game/game_fn_80036E50.c"),
            Object(
                Matching,
                "game/game_fn_80036E8C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_800374EC.c"),
            Object(Matching, "game/game_fn_80037AF4.c"),
            Object(Matching, "game/game_fn_800382C0.c"),
            Object(Matching, "game/game_fn_80038308.c"),
            Object(Matching, "game/game_fn_80038464.c"),
            Object(Matching, "game/game_fn_80038544.c"),
            Object(Matching, "game/game_fn_800385D0.c"),
            Object(Matching, "game/game_fn_80038650.c"),
            Object(Matching, "game/game_fn_800386FC.c"),
            Object(Matching, "game/game_fn_8003877C.c"),
            Object(Matching, "game/game_fn_800387FC.c"),
            Object(Matching, "game/game_fn_80038878.c"),
            Object(
                Matching,
                "game/game_fn_800389E0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80038C28.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80038DAC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80038E5C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80039044.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80048ADC.c"),
            Object(Matching, "game/game_fn_80048B24.c"),
            Object(Matching, "game/game_fn_80048B68.c"),
            Object(Matching, "game/game_fn_80048C2C.c"),
            Object(Matching, "game/game_fn_80048C50.c"),
            Object(Matching, "game/game_fn_80048C74.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800490E8.c"),
            Object(Matching, "game/game_fn_8004910C.c"),
            Object(Matching, "game/game_fn_8004914C.c"),
            Object(Matching, "game/game_fn_8004918C.c"),
            Object(Matching, "game/game_fn_80049194.c"),
            Object(Matching, "game/game_fn_8004919C.c"),
            Object(Matching, "game/game_fn_80049220.c"),
            Object(Matching, "game/game_fn_80049304.c"),
            Object(Matching, "game/game_fn_80049388.c"),
    Object(Matching, "game/game_fn_80049418.c"),
    Object(Matching, "game/game_fn_8004948C.c"),
    Object(Matching, "game/game_fn_8004958C.c"),
    Object(Matching, "game/game_fn_80049694.c"),
    Object(Matching, "game/game_fn_800496EC.c"),
    Object(Matching, "game/game_fn_80049774.c"),
    Object(NonMatching, "game/game_fn_80049818.c"),
    Object(NonMatching, "game/game_fn_8004998C.c"),
    Object(NonMatching, "game/game_fn_80049E74.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80050728.c"),
    Object(Matching, "game/game_fn_80050730.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80050950.c"),
    Object(Matching, "game/game_fn_8005099C.c"),
    Object(Matching, "game/game_fn_800509DC.c"),
    Object(Matching, "game/game_fn_80050A20.c"),
    Object(Matching, "game/game_fn_80050A48.c"),
    Object(Matching, "game/game_fn_80050A7C.c"),
    Object(NonMatching, "game/game_fn_80050B08.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80052218.c"),
    Object(Matching, "game/game_fn_80052228.c"),
    Object(Matching, "game/game_fn_80052250.c"),
    Object(Matching, "game/game_fn_8005227C.c"),
    Object(Matching, "game/game_fn_800522A4.c"),
    Object(Matching, "game/game_fn_80052310.c"),
    Object(Matching, "game/game_fn_80052424.c"),
    Object(Matching, "game/game_fn_8005251C.c"),
    Object(Matching, "game/game_fn_80052580.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80052670.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80052900.c"),
    Object(Matching, "game/game_fn_80052BBC.c"),
    Object(NonMatching, "game/game_fn_80052CC0.c"),
    Object(NonMatching, "game/game_fn_80053048.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800531F0.c"),
    Object(Matching, "game/game_fn_80053600.c"),
    Object(Matching, "game/game_fn_800537CC.c"),
    Object(Matching, "game/game_fn_8005391C.c"),
    Object(NonMatching, "game/game_fn_800539D8.c"),
    Object(Matching, "game/game_fn_80053E50.c"),
    Object(Matching, "game/game_fn_80054040.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800542B4.c"),
    Object(NonMatching, "game/game_fn_800542D0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80054700.c"),
    Object(Matching, "game/game_fn_80054758.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80054844.c"),
    Object(Matching, "game/game_fn_80054A04.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80054B04.c"),
    Object(Matching, "game/game_fn_80054BC4.c"),
    Object(Matching, "game/game_fn_80054BCC.c"),
    Object(Matching, "game/game_fn_80054C14.c"),
    Object(Matching, "game/game_fn_80054CA0.c"),
    Object(Matching, "game/game_fn_80054D14.c"),
    Object(Matching, "game/game_fn_80054DF4.c"),
    Object(Matching, "game/game_fn_80054ED8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80055350.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80055A64.c"),
    Object(Matching, "game/game_fn_80055C88.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80055EE0.c"),
    Object(Matching, "game/game_fn_800560C0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80056374.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80056624.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800568A4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80056B88.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80056E18.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80057154.c"),
    Object(Matching, "game/game_fn_800572D8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800577A0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80057AC0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80057E3C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80058154.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80058394.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80058834.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80058FF4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005948C.c"),
    Object(Matching, "game/game_fn_80059678.c"),
    Object(Matching, "game/game_fn_80059CBC.c"),
    Object(Matching, "game/game_fn_8005A108.c"),
    Object(Matching, "game/game_fn_8005A75C.c"),
    Object(Matching, "game/game_fn_8005AC7C.c"),
    Object(Matching, "game/game_fn_8005AF34.c"),
    Object(NonMatching, "game/game_fn_8005B528.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005BBB4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005BC64.c"),
    Object(NonMatching, "game/game_fn_8005BCC0.c"),
    Object(Matching, "game/game_fn_8005E94C.c"),
    Object(Matching, "game/game_fn_8005E9E4.c"),
    Object(Matching, "game/game_fn_8005EA38.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005EC6C.c"),
    Object(Matching, "game/game_fn_8005EE9C.c"),
    Object(NonMatching, "game/game_fn_8005EF94.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005F758.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8005F8D0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005FCD4.c"),
    Object(Matching, "game/game_fn_8005FD84.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8005FF94.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006010C.c"),
    Object(Matching, "game/game_fn_8006012C.c"),
    Object(NonMatching, "game/game_fn_8006016C.c"),
    Object(NonMatching, "game/game_fn_800601FC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8006053C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800606BC.c"),
    Object(NonMatching, "game/game_fn_800607BC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80060840.c"),
    Object(NonMatching, "game/game_fn_80060904.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80060C24.c"),
    Object(Matching, "game/game_data_80060C28.c"),
    Object(NonMatching, "game/game_fn_80060C28.c"),
    Object(Matching, "game/game_fn_80060D4C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80060F10.c"),
    Object(NonMatching, "game/game_fn_80060F9C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800614A8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80062ED0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80063030.c"),
    Object(NonMatching, "game/game_fn_80063124.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8006330C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80063C78.c"),
    Object(NonMatching, "game/game_fn_80063D60.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80063E64.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80064B38.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80064E2C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006534C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80065428.c"),
    Object(Matching, "game/game_fn_80065454.c"),
    Object(NonMatching, "game/game_fn_800654F8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_data_80239008.c"),
    Object(Matching, "game/game_data_80239044.c"),
    Object(Matching, "game/game_data_80239054.c"),
    Object(Matching, "game/game_data_80239060.c"),
    Object(Matching, "game/game_data_8023906C.c"),
    Object(Matching, "game/game_data_80239078.c"),
    Object(Matching, "game/game_data_80239084.c"),
    Object(Matching, "game/game_data_80239090.c"),
    Object(Matching, "game/game_data_802390A0.c"),
    Object(Matching, "game/game_data_802390B4.c"),
    Object(Matching, "game/game_data_802390C8.c"),
    Object(Matching, "game/game_data_802390D4.c"),
    Object(Matching, "game/game_data_802390E0.c"),
    Object(Matching, "game/game_data_802390EC.c"),
    Object(Matching, "game/game_data_802390F8.c"),
    Object(Matching, "game/game_data_80239110.c"),
    Object(Matching, "game/game_data_80239188.c"),
    Object(Matching, "game/game_data_80239194.c"),
    Object(Matching, "game/game_data_802391C4.c"),
    Object(Matching, "game/game_data_802391D0.c"),
    Object(Matching, "game/game_data_802391E8.c"),
    Object(Matching, "game/game_data_802391F8.c"),
    Object(Matching, "game/game_data_802393AC.c"),
    Object(Matching, "game/game_data_802393C0.c"),
    Object(Matching, "game/game_data_802393CC.c"),
    Object(Matching, "game/game_data_802393D8.c"),
    Object(Matching, "game/game_data_802393E4.c"),
    Object(Matching, "game/game_data_802393F0.c"),
    Object(Matching, "game/game_data_802393FC.c"),
    Object(Matching, "game/game_data_80239408.c"),
    Object(Matching, "game/game_data_80239414.c"),
    Object(Matching, "game/game_data_80239420.c"),
    Object(Matching, "game/game_data_80239450.c"),
    Object(Matching, "game/game_data_8023945C.c"),
    Object(Matching, "game/game_data_80239490.c"),
    Object(Matching, "game/game_data_80239530.c"),
    Object(Matching, "game/game_data_8023953C.c"),
    Object(Matching, "game/game_data_80239548.c"),
    Object(Matching, "game/game_data_80239554.c"),
    Object(Matching, "game/game_data_80239560.c"),
    Object(Matching, "game/game_data_80239620.c"),
    Object(Matching, "game/game_data_80239630.c"),
    Object(Matching, "game/game_data_8023963C.c"),
    Object(Matching, "game/game_data_80239648.c"),
    Object(Matching, "game/game_data_80239654.c"),
    Object(Matching, "game/game_data_80239660.c"),
    Object(Matching, "game/game_data_8023966C.c"),
    Object(Matching, "game/game_data_80239678.c"),
    Object(Matching, "game/game_data_80239688.c"),
    Object(Matching, "game/game_data_80239694.c"),
    Object(Matching, "game/game_data_802396A0.c"),
    Object(Matching, "game/game_data_802396B0.c"),
    Object(Matching, "game/game_data_802396BC.c"),
    Object(Matching, "game/game_data_802396C8.c"),
    Object(Matching, "game/game_data_802396D4.c"),
    Object(Matching, "game/game_data_802396E0.c"),
    Object(Matching, "game/game_data_802396F0.c"),
    Object(Matching, "game/game_data_8023972C.c"),
    Object(Matching, "game/game_data_80239750.c"),
    Object(Matching, "game/game_data_8023975C.c"),
    Object(Matching, "game/game_data_80239768.c"),
    Object(Matching, "game/game_data_80239778.c"),
    Object(Matching, "game/game_data_80239788.c"),
    Object(Matching, "game/game_data_8023979C.c"),
    Object(Matching, "game/game_data_802397B0.c"),
    Object(Matching, "game/game_data_802397BC.c"),
    Object(Matching, "game/game_data_802397C8.c"),
    Object(Matching, "game/game_data_802397D8.c"),
    Object(Matching, "game/game_data_802397F0.c"),
    Object(Matching, "game/game_data_80239800.c"),
    Object(Matching, "game/game_data_8023980C.c"),
    Object(Matching, "game/game_data_80239818.c"),
    Object(Matching, "game/game_data_80239824.c"),
    Object(Matching, "game/game_data_80239830.c"),
    Object(Matching, "game/game_data_8023983C.c"),
    Object(Matching, "game/game_data_80239854.c"),
    Object(Matching, "game/game_data_80239860.c"),
    Object(Matching, "game/game_data_8023986C.c"),
    Object(Matching, "game/game_data_80239878.c"),
    Object(Matching, "game/game_data_80239884.c"),
    Object(Matching, "game/game_data_80239890.c"),
    Object(Matching, "game/game_data_8023989C.c"),
    Object(Matching, "game/game_data_802398A8.c"),
    Object(Matching, "game/game_data_802398B8.c"),
    Object(Matching, "game/game_data_802398C8.c"),
    Object(Matching, "game/game_data_802398E0.c"),
    Object(Matching, "game/game_data_802398EC.c"),
    Object(Matching, "game/game_data_802398F8.c"),
    Object(Matching, "game/game_data_80239934.c"),
    Object(Matching, "game/game_data_80239940.c"),
    Object(Matching, "game/game_data_8023994C.c"),
    Object(Matching, "game/game_data_80239958.c"),
    Object(Matching, "game/game_data_80239968.c"),
    Object(Matching, "game/game_data_80239978.c"),
    Object(Matching, "game/game_data_80239988.c"),
    Object(Matching, "game/game_data_80239998.c"),
    Object(Matching, "game/game_data_802399A8.c"),
    Object(Matching, "game/game_data_802399B8.c"),
    Object(Matching, "game/game_data_802399C8.c"),
    Object(Matching, "game/game_data_802399D8.c"),
    Object(Matching, "game/game_data_80239A78.c"),
    Object(Matching, "game/game_data_80239B18.c"),
    Object(Matching, "game/game_data_80239B24.c"),
    Object(Matching, "game/game_data_80239B30.c"),
    Object(Matching, "game/game_data_80239B40.c"),
    Object(Matching, "game/game_data_80239B50.c"),
    Object(Matching, "game/game_data_80239B74.c"),
    Object(Matching, "game/game_data_80239B80.c"),
    Object(Matching, "game/game_data_80239B8C.c"),
    Object(Matching, "game/game_data_80239B98.c"),
    Object(Matching, "game/game_data_80239BC0.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239BE0.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239C00.c"),
    Object(Matching, "game/game_data_80239C10.c"),
    Object(Matching, "game/game_data_80239C38.c"),
    Object(Matching, "game/game_data_80239C60.c"),
    Object(Matching, "game/game_data_80239C88.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239CAC.c"),
    Object(Matching, "game/game_data_80239CD0.c"),
    Object(Matching, "game/game_data_80239CE8.c"),
    Object(Matching, "game/game_data_80239D00.c"),
    Object(Matching, "game/game_data_80239DE0.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239E10.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239E18.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_80239E40.c"),
    Object(Matching, "game/game_data_80239E68.c"),
    Object(Matching, "game/game_data_80239E88.c"),
    Object(Matching, "game/game_data_80239EC0.c"),
    Object(Matching, "game/game_data_80239EF0.c"),
    Object(Matching, "game/game_data_80239F20.c"),
    Object(Matching, "game/game_data_8023A028.c"),
    Object(Matching, "game/game_data_8023A0A8.c"),
    Object(Matching, "game/game_data_8023A0B8.c"),
    Object(Matching, "game/game_data_8023A0F8.c"),
    Object(Matching, "game/game_data_8023A160.c"),
    Object(Matching, "game/game_data_8023A1F8.c"),
    Object(Matching, "game/game_data_8023A208.c"),
    Object(Matching, "game/game_data_8023A220.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_8023A268.c", extra_cflags=["-sdata 0"]),
    Object(Matching, "game/game_data_8023A278.c"),
    Object(Matching, "game/game_data_8023A298.c"),
    Object(Matching, "game/game_data_8023A2A4.c"),
    Object(Matching, "game/game_data_8023A2E0.c"),
    Object(Matching, "game/game_data_8023A3B0.c"),
    Object(Matching, "game/game_data_8023A3C0.c"),
    Object(Matching, "game/game_data_8023A414.c"),
    Object(Matching, "game/game_data_8023A444.c"),
    Object(Matching, "game/game_data_8023A630.c"),
    Object(Matching, "game/game_data_8023A63C.c"),
    Object(Matching, "game/game_data_8023A650.c"),
    Object(Matching, "game/game_data_8023A660.c"),
    Object(Matching, "game/game_data_8023A670.c"),
    Object(Matching, "game/game_data_8023A680.c"),
    Object(Matching, "game/game_data_8023A690.c"),
    Object(Matching, "game/game_data_8023A69C.c"),
    Object(Matching, "game/game_data_8023A6B8.c"),
    Object(Matching, "game/game_data_8023A6C8.c"),
    Object(Matching, "game/game_data_8023A6D8.c"),
    Object(Matching, "game/game_data_8023A6E8.c"),
    Object(Matching, "game/game_data_8023A6F4.c"),
    Object(Matching, "game/game_data_8023A700.c"),
    Object(Matching, "game/game_data_8023A70C.c"),
    Object(Matching, "game/game_data_8023A718.c"),
    Object(Matching, "game/game_data_8023A728.c"),
    Object(Matching, "game/game_data_8023A738.c"),
    Object(Matching, "game/game_data_8023A744.c"),
    Object(Matching, "game/game_data_8023A750.c"),
    Object(Matching, "game/game_data_8023A760.c"),
    Object(Matching, "game/game_data_8023A76C.c"),
    Object(Matching, "game/game_data_8023A778.c"),
    Object(Matching, "game/game_data_8023A788.c"),
    Object(Matching, "game/game_data_8023A798.c"),
    Object(Matching, "game/game_data_8023A7F8.c"),
    Object(Matching, "game/game_data_8023A868.c"),
    Object(Matching, "game/game_data_8023A878.c"),
    Object(Matching, "game/game_data_8023A890.c"),
    Object(Matching, "game/game_data_8023A8B0.c"),
    Object(Matching, "game/game_data_8023A900.c"),
    Object(Matching, "game/game_data_8023A988.c"),
    Object(Matching, "game/game_data_8023A994.c"),
    Object(Matching, "game/game_data_8023B018.c"),
    Object(Matching, "game/game_data_8023B028.c"),
    Object(Matching, "game/game_data_8023B038.c"),
    Object(Matching, "game/game_data_8023B044.c"),
    Object(Matching, "game/game_data_8023B050.c"),
    Object(Matching, "game/game_data_8023B05C.c"),
    Object(Matching, "game/game_data_8023B068.c"),
    Object(Matching, "game/game_data_8023B078.c"),
    Object(Matching, "game/game_data_8023B088.c"),
    Object(Matching, "game/game_data_8023B094.c"),
    Object(Matching, "game/game_data_8023B0A0.c"),
    Object(Matching, "game/game_data_8023B0B0.c"),
    Object(Matching, "game/game_data_8023B190.c"),
    Object(Matching, "game/game_data_8023B2B0.c"),
    Object(Matching, "game/game_data_8023B2D0.c"),
    Object(Matching, "game/game_data_8023B2F0.c"),
    Object(Matching, "game/game_data_8023B330.c"),
    Object(Matching, "game/game_data_8023B348.c"),
    Object(Matching, "game/game_data_8023B3D0.c"),
    Object(Matching, "game/game_data_8023B458.c"),
    Object(Matching, "game/game_data_8023B558.c"),
    Object(Matching, "game/game_data_8023B564.c"),
    Object(Matching, "game/game_data_8023B570.c"),
    Object(Matching, "game/game_data_8023B5A8.c"),
    Object(Matching, "game/game_data_8023B5B4.c"),
    Object(Matching, "game/game_data_8023B5C0.c"),
    Object(Matching, "game/game_data_8023B6A8.c"),
    Object(Matching, "game/game_data_8023B6C8.c"),
    Object(Matching, "game/game_data_8023B768.c"),
    Object(Matching, "game/game_data_8023B78C.c"),
    Object(Matching, "game/game_data_8023B798.c"),
    Object(Matching, "game/game_data_8023B7A8.c"),
    Object(Matching, "game/game_data_8023B7B4.c"),
    Object(Matching, "game/game_data_8023B7C0.c"),
    Object(Matching, "game/game_data_8023B7CC.c"),
    Object(Matching, "game/game_data_8023B7D8.c"),
    Object(Matching, "game/game_data_8023B7E4.c"),
    Object(Matching, "game/game_data_8023B7F0.c"),
    Object(Matching, "game/game_data_8023B7FC.c"),
    Object(Matching, "game/game_data_8023B808.c"),
    Object(Matching, "game/game_data_8023B814.c"),
    Object(Matching, "game/game_data_8023B820.c"),
    Object(Matching, "game/game_data_8023B830.c"),
    Object(Matching, "game/game_data_8023B858.c"),
    Object(Matching, "game/game_data_8023B880.c"),
    Object(Matching, "game/game_data_8023B890.c"),
    Object(Matching, "game/game_data_8023B8A0.c"),
    Object(Matching, "game/game_data_8023B8B8.c"),
    Object(Matching, "game/game_data_8023B8D0.c"),
    Object(Matching, "game/game_data_8023B8E0.c"),
    Object(Matching, "game/game_data_8023B940.c"),
    Object(Matching, "game/game_data_8023BED8.c"),
    Object(Matching, "game/game_fn_80066754.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80066888.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80066A0C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80066AEC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80066BB8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80066D04.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80066D80.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80066E78.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80067180.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006749C.c"),
    Object(NonMatching, "game/game_fn_800674E4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80067650.c"),
    Object(Matching, "game/game_fn_800676C8.c"),
    Object(Matching, "game/game_fn_80067728.c"),
    Object(NonMatching, "game/game_fn_80067764.c"),
    Object(NonMatching, "game/game_fn_80067848.c"),
    Object(NonMatching, "game/game_fn_80067858.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80067A18.c"),
    Object(Matching, "game/game_fn_80067B6C.c"),
    Object(NonMatching, "game/game_fn_80067BAC.c"),
    Object(NonMatching, "game/game_fn_80067C20.c"),
    Object(Matching, "game/game_fn_80067D30.c"),
    Object(Matching, "game/game_fn_80067DA4.c"),
    Object(Matching, "game/game_fn_80067E24.c"),
    Object(NonMatching, "game/game_fn_80067EB8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80068074.c"),
    Object(NonMatching, "game/game_fn_800680C0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800681A0.c"),
    Object(Matching, "game/game_fn_800681C8.c"),
    Object(Matching, "game/game_fn_80068230.c"),
    Object(NonMatching, "game/game_fn_80068290.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800683E4.c"),
    Object(NonMatching, "game/game_fn_8006845C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_data_800685A4.c"),
    Object(Matching, "game/game_fn_800685A4.c"),
    Object(Matching, "game/game_fn_80068668.c"),
    Object(NonMatching, "game/game_fn_80068674.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006872C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80068870.c"),
    Object(Matching, "game/game_fn_80068994.c"),
    Object(NonMatching, "game/game_fn_80068AAC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80068FE0.c"),
    Object(Matching, "game/game_fn_8006A478.c"),
    Object(Matching, "game/game_fn_8006A4D4.c"),
    Object(Matching, "game/game_fn_8006A518.c"),
    Object(Matching, "game/game_fn_8006A9D0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006AA88.c"),
    Object(Matching, "game/game_fn_8006AB18.c"),
    Object(Matching, "game/game_fn_8006ABF0.c"),
    Object(Matching, "game/game_fn_8006AEA4.c"),
    Object(Matching, "game/game_fn_8006AF20.c"),
    Object(Matching, "game/game_fn_8006B0A0.c"),
    Object(NonMatching, "game/game_fn_8006B0F0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006B1C0.c"),
    Object(NonMatching, "game/game_fn_8006B21C.c"),
    Object(Matching, "game/game_fn_8006B364.c"),
    Object(NonMatching, "game/game_fn_8006B40C.c"),
    Object(Matching, "game/game_fn_8006B488.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8006B620.c"),
    Object(NonMatching, "game/game_fn_8006B70C.c"),
    Object(Matching, "game/game_fn_8006B804.c"),
    Object(NonMatching, "game/game_fn_8006B96C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006BCB4.c"),
    Object(Matching, "game/game_fn_8006BCE4.c"),
    Object(Matching, "game/game_fn_8006BD40.c"),
    Object(Matching, "game/game_fn_8006BD78.c"),
    Object(Matching, "game/game_fn_8006BE44.c"),
    Object(Matching, "game/game_fn_8006BE84.c"),
    Object(Matching, "game/game_fn_8006BE8C.c"),
    Object(Matching, "game/game_fn_8006BEE4.c"),
    Object(Matching, "game/game_fn_8006BEEC.c"),
    Object(Matching, "game/game_fn_8006BEF4.c"),
    Object(Matching, "game/game_fn_8006BF1C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006C89C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006C92C.c"),
    Object(Matching, "game/game_fn_8006C9C0.c"),
    Object(Matching, "game/game_fn_8006C9D4.c"),
    Object(Matching, "game/game_fn_8006C9E4.c"),
    Object(NonMatching, "game/game_fn_8006C9F0.c"),
    Object(Matching, "game/game_fn_8006CAB8.c"),
    Object(Matching, "game/game_fn_8006CAC4.c"),
    Object(Matching, "game/game_fn_8006CACC.c"),
    Object(Matching, "game/game_fn_8006CAE4.c"),
    Object(Matching, "game/game_fn_8006CB30.c"),
    Object(Matching, "game/game_fn_8006CB64.c"),
    Object(Matching, "game/game_fn_8006CEE4.c"),
    Object(Matching, "game/game_fn_8006D0A8.c"),
    Object(Matching, "game/game_fn_8006D12C.c"),
    Object(Matching, "game/game_fn_8006D198.c"),
    Object(NonMatching, "game/game_fn_8006D1DC.c"),
    Object(Matching, "game/game_fn_8006D254.c"),
    Object(Matching, "game/game_fn_8006D2C8.c"),
    Object(Matching, "game/game_fn_8006D344.c"),
    Object(Matching, "game/game_fn_8006D3E4.c"),
    Object(Matching, "game/game_fn_8006D444.c"),
    Object(Matching, "game/game_fn_8006D488.c"),
    Object(Matching, "game/game_fn_8006D4DC.c"),
    Object(NonMatching, "game/game_fn_8006D548.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006DE98.c"),
    Object(NonMatching, "game/game_fn_8006DEF8.c"),
    Object(Matching, "game/game_fn_8006E3D4.c"),
    Object(Matching, "game/game_fn_8006E3F8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8006E53C.c"),
    Object(NonMatching, "game/game_fn_8006E644.c"),
    Object(Matching, "game/game_fn_8006E6EC.c"),
    Object(NonMatching, "game/game_fn_8006E754.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8006EA4C.c"),
    Object(NonMatching, "game/game_fn_8006EB60.c"),
    Object(Matching, "game/game_fn_8006EC74.c"),
    Object(Matching, "game/game_fn_8006EC8C.c"),
    Object(NonMatching, "game/game_fn_8006ECD4.c"),
    Object(NonMatching, "game/game_fn_8006ED3C.c"),
    Object(Matching, "game/game_fn_8006ED98.c"),
    Object(Matching, "game/game_fn_8006EDA0.c"),
    Object(Matching, "game/game_fn_8006EE9C.c"),
    Object(Matching, "game/game_fn_8006EF48.c"),
    Object(NonMatching, "game/game_fn_8006F544.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006F6A4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8006FD90.c"),
    Object(Matching, "game/game_fn_80070884.c"),
    Object(Matching, "game/game_fn_80070A6C.c"),
    Object(Matching, "game/game_fn_80070AAC.c"),
    Object(Matching, "game/game_fn_80070AD0.c"),
    Object(Matching, "game/game_fn_80070B68.c"),
    Object(Matching, "game/game_fn_80070C3C.c"),
    Object(Matching, "game/game_fn_80070CD8.c"),
    Object(Matching, "game/game_fn_80070E30.c"),
    Object(Matching, "game/game_fn_80070E98.c"),
    Object(Matching, "game/game_fn_80070EF8.c"),
    Object(Matching, "game/game_fn_80071258.c"),
    Object(Matching, "game/game_fn_800712D8.c"),
    Object(Matching, "game/game_fn_80071324.c"),
    Object(Matching, "game/game_fn_800714CC.c"),
    Object(Matching, "game/game_fn_80071550.c"),
    Object(Matching, "game/game_fn_80071900.c"),
    Object(Matching, "game/game_fn_80071950.c"),
    Object(NonMatching, "game/game_fn_800719D8.c"),
    Object(Matching, "game/game_fn_80071A58.c"),
    Object(Matching, "game/game_fn_80071D5C.c"),
    Object(Matching, "game/game_fn_80071D84.c"),
    Object(Matching, "game/game_fn_80071DB0.c"),
    Object(Matching, "game/game_fn_80071DD8.c"),
    Object(Matching, "game/game_fn_80071FF8.c"),
    Object(Matching, "game/game_fn_80072070.c"),
    Object(Matching, "game/game_fn_80072354.c"),
    Object(NonMatching, "game/game_fn_80072368.c"),
    Object(NonMatching, "game/game_fn_800723A8.c"),
    Object(Matching, "game/game_fn_8007249C.c"),
    Object(Matching, "game/game_fn_800724F8.c"),
    Object(Matching, "game/game_fn_8007255C.c"),
    Object(Matching, "game/game_fn_80072E48.c"),
    Object(Matching, "game/game_fn_80073204.c"),
    Object(NonMatching, "game/game_fn_80073728.c"),
    Object(NonMatching, "game/game_fn_80074040.c"),
    Object(Matching, "game/game_fn_800740A0.c"),
    Object(Matching, "game/game_fn_800740E8.c"),
    Object(NonMatching, "game/game_fn_8007412C.c"),
    Object(NonMatching, "game/game_fn_800741E8.c"),
    Object(Matching, "game/game_fn_80074310.c"),
    Object(Matching, "game/game_fn_80074440.c"),
    Object(Matching, "game/game_fn_80074580.c"),
    Object(NonMatching, "game/game_fn_800746CC.c"),
    Object(NonMatching, "game/game_fn_800747CC.c"),
    Object(NonMatching, "game/game_fn_80074864.c"),
    Object(NonMatching, "game/game_fn_80077704.c"),
    Object(NonMatching, "game/game_fn_800777B0.c"),
    Object(Matching, "game/game_fn_8007780C.c"),
    Object(Matching, "game/game_fn_8007785C.c"),
    Object(NonMatching, "game/game_fn_80077880.c"),
    Object(Matching, "game/game_fn_80077F90.c"),
    Object(NonMatching, "game/game_fn_800781E8.c"),
    Object(Matching, "game/game_fn_8007827C.c"),
    Object(Matching, "game/game_fn_800784DC.c"),
    Object(Matching, "game/game_fn_80078500.c"),
    Object(NonMatching, "game/game_fn_80078608.c"),
    Object(Matching, "game/game_fn_80078CA4.c"),
    Object(Matching, "game/game_fn_80079008.c"),
    Object(Matching, "game/game_fn_80079054.c"),
    Object(NonMatching, "game/game_fn_800790C0.c"),
    Object(Matching, "game/game_fn_8007917C.c"),
    Object(Matching, "game/game_fn_8007923C.c"),
    Object(NonMatching, "game/game_fn_8007930C.c"),
    Object(Matching, "game/game_fn_800798C4.c"),
    Object(Matching, "game/game_fn_80079908.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80079AA4.c"),
    Object(Matching, "game/game_fn_80079C50.c"),
    Object(NonMatching, "game/game_fn_80079D24.c"),
    Object(Matching, "game/game_fn_8007A1C0.c"),
    Object(Matching, "game/game_fn_8007B2F4.c"),
    Object(Matching, "game/game_fn_8007B374.c"),
    Object(Matching, "game/game_fn_8007B3C4.c"),
    Object(Matching, "game/game_fn_8007B540.c"),
    Object(Matching, "game/game_fn_8007B640.c"),
    Object(NonMatching, "game/game_fn_8007B828.c"),
    Object(Matching, "game/game_fn_8007BA3C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8007BC44.c"),
    Object(Matching, "game/game_fn_8007BCD4.c"),
    Object(Matching, "game/game_fn_8007BCFC.c"),
    Object(Matching, "game/game_fn_8007BD14.c"),
    Object(NonMatching, "game/game_fn_8007BD40.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8007C13C.c"),
    Object(Matching, "game/game_fn_8007C17C.c"),
    Object(Matching, "game/game_fn_8007C1D8.c"),
    Object(Matching, "game/game_fn_8007C22C.c"),
    Object(NonMatching, "game/game_fn_8007C354.c"),
    Object(Matching, "game/game_fn_8007C59C.c"),
    Object(NonMatching, "game/game_fn_8007C6AC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8007C814.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8007C90C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8007CAC4.c"),
    Object(NonMatching, "game/game_fn_8007CB6C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8007CD5C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8007CFB0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8007D294.c"),
    Object(Matching, "game/game_fn_8007D2B4.c"),
    Object(Matching, "game/game_fn_8007D3C0.c"),
    Object(Matching, "game/game_fn_8007D4D4.c"),
    Object(NonMatching, "game/game_fn_8007D4D8.c"),
    Object(Matching, "game/game_fn_8007D69C.c"),
    Object(NonMatching, "game/game_fn_8007D744.c"),
    Object(Matching, "game/game_fn_8007D834.c"),
    Object(Matching, "game/game_fn_8007D848.c"),
    Object(Matching, "game/game_fn_8007D944.c"),
    Object(Matching, "game/game_fn_8007F650.c"),
    Object(NonMatching, "game/game_fn_8007F770.c"),
    Object(Matching, "game/game_fn_8007FAC0.c"),
    Object(Matching, "game/game_fn_8007FAC8.c"),
    Object(Matching, "game/game_fn_8007FFB4.c"),
    Object(NonMatching, "game/game_fn_80080458.c"),
    Object(Matching, "game/game_fn_800804C4.c"),
    Object(NonMatching, "game/game_fn_80080530.c"),
    Object(Matching, "game/game_fn_80080588.c"),
    Object(Matching, "game/game_fn_800809B4.c"),
    Object(NonMatching, "game/game_fn_80080A38.c"),
    Object(Matching, "game/game_fn_80081254.c"),
    Object(Matching, "game/game_fn_800812E4.c"),
    Object(Matching, "game/game_fn_80081874.c"),
    Object(Matching, "game/game_fn_80081FF8.c"),
    Object(Matching, "game/game_fn_800824C8.c"),
    Object(Matching, "game/game_fn_80082DE4.c"),
    Object(Matching, "game/game_fn_800835CC.c"),
    Object(Matching, "game/game_fn_80083604.c"),
    Object(Matching, "game/game_fn_8008363C.c"),
    Object(Matching, "game/game_fn_80084260.c"),
    Object(Matching, "game/game_fn_800861F4.c"),
    Object(Matching, "game/game_fn_800861F8.c"),
    Object(Matching, "game/game_fn_80086204.c"),
    Object(Matching, "game/game_fn_80086218.c"),
    Object(Matching, "game/game_fn_80087794.c"),
    Object(Matching, "game/game_fn_800877B8.c"),
    Object(Matching, "game/game_fn_800877FC.c"),
    Object(Matching, "game/game_fn_80087840.c"),
    Object(Matching, "game/game_fn_800878F4.c"),
    Object(Matching, "game/game_fn_8008799C.c"),
    Object(Matching, "game/game_fn_800879E0.c"),
    Object(NonMatching, "game/game_fn_80087A24.c"),
    Object(NonMatching, "game/game_fn_80087BA8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80087D64.c"),
    Object(NonMatching, "game/game_fn_80087EC4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80088060.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80088298.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80088528.c"),
    Object(Matching, "game/game_fn_80088588.c"),
    Object(Matching, "game/game_fn_800886D8.c"),
    Object(Matching, "game/game_fn_80088818.c"),
    Object(NonMatching, "game/game_fn_80088844.c"),
    Object(Matching, "game/game_fn_80088890.c"),
    Object(NonMatching, "game/game_fn_80088A04.c"),
    Object(Matching, "game/game_fn_80088B04.c"),
    Object(Matching, "game/game_fn_80088C04.c"),
    Object(NonMatching, "game/game_fn_80088D04.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80088E44.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80088F08.c"),
    Object(NonMatching, "game/game_fn_80088F4C.c"),
    Object(Matching, "game/game_fn_800890F4.c"),
    Object(Matching, "game/game_fn_800891F4.c"),
    Object(Matching, "game/game_fn_800891FC.c"),
    Object(Matching, "game/game_fn_80089204.c"),
    Object(Matching, "game/game_fn_80089754.c"),
    Object(Matching, "game/game_fn_800898E0.c"),
    Object(NonMatching, "game/game_fn_80089A34.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80089EE8.c"),
    Object(NonMatching, "game/game_fn_8008A0B4.c"),
    Object(NonMatching, "game/game_fn_8008A2E0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008A5B8.c"),
    Object(NonMatching, "game/game_fn_8008A6F8.c"),
    Object(Matching, "game/game_fn_8008A808.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008A8D8.c"),
    Object(Matching, "game/game_fn_8008A914.c"),
    Object(NonMatching, "game/game_fn_8008A96C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008ABCC.c"),
    Object(NonMatching, "game/game_fn_8008ABD4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008AE40.c"),
    Object(Matching, "game/game_fn_8008AF24.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008C750.c"),
    Object(Matching, "game/game_fn_8008C778.c"),
    Object(Matching, "game/game_fn_8008C7A0.c"),
    Object(Matching, "game/game_fn_8008C7C0.c"),
    Object(NonMatching, "game/game_fn_8008C7F8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008C93C.c"),
    Object(Matching, "game/game_fn_8008C9AC.c"),
    Object(Matching, "game/game_fn_8008C9BC.c"),
    Object(Matching, "game/game_fn_8008CA28.c"),
    Object(Matching, "game/game_fn_8008CA70.c"),
    Object(NonMatching, "game/game_fn_8008CA84.c"),
    Object(Matching, "game/game_fn_8008CAD4.c"),
    Object(Matching, "game/game_fn_8008CBA4.c"),
    Object(Matching, "game/game_fn_8008CBB8.c"),
    Object(Matching, "game/game_fn_8008CBD4.c"),
    Object(Matching, "game/game_fn_8008CBE8.c"),
    Object(Matching, "game/game_fn_8008CC20.c"),
    Object(Matching, "game/game_fn_8008CC50.c"),
    Object(Matching, "game/game_fn_8008CC84.c"),
    Object(Matching, "game/game_fn_8008CDA0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008CEF0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008D31C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008D4B4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008D5D4.c"),
    Object(NonMatching, "game/game_fn_8008D6E4.c"),
    Object(NonMatching, "game/game_fn_8008D9F4.c"),
    Object(NonMatching, "game/game_fn_8008DBA8.c"),
    Object(Matching, "game/game_fn_8008DD24.c"),
    Object(NonMatching, "game/game_fn_8008DD78.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008DF64.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008E078.c"),
    Object(NonMatching, "game/game_fn_8008E110.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008E294.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008E3D8.c"),
    Object(NonMatching, "game/game_fn_8008E430.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008E670.c"),
    Object(NonMatching, "game/game_fn_8008E71C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008E810.c"),
    Object(Matching, "game/game_fn_8008E88C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008ED9C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008EF28.c"),
    Object(Matching, "game/game_fn_8008EFA8.c"),
    Object(NonMatching, "game/game_fn_8008F064.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8008F224.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008F5B4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8008F860.c"),
    Object(Matching, "game/game_fn_8008F890.c"),
    Object(NonMatching, "game/game_fn_8008F960.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80090004.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80090204.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800902D0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009050C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009073C.c"),
    Object(NonMatching, "game/game_fn_80090FF4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80091124.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80092BBC.c"),
    Object(Matching, "game/game_fn_80092C30.c"),
    Object(Matching, "game/game_fn_80092CCC.c"),
    Object(NonMatching, "game/game_fn_80092D90.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80092FA4.c"),
    Object(NonMatching, "game/game_fn_800930B0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80093148.c"),
    Object(Matching, "game/game_fn_800931D0.c"),
    Object(NonMatching, "game/game_fn_80093264.c"),
    Object(Matching, "game/game_fn_800933A0.c"),
    Object(Matching, "game/game_fn_800934A0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80093B80.c"),
    Object(Matching, "game/game_fn_80093C04.c"),
    Object(NonMatching, "game/game_fn_80093D20.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80093F6C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80094DD0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009552C.c"),
    Object(Matching, "game/game_fn_800955A4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80095654.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80095774.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_80095894.c"),
    Object(Matching, "game/game_fn_80095C20.c"),
    Object(NonMatching, "game/game_fn_80095D10.c"),
    Object(NonMatching, "game/game_fn_80095E64.c"),
    Object(Matching, "game/game_fn_80095FDC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80096208.c"),
    Object(Matching, "game/game_fn_80096690.c"),
    Object(NonMatching, "game/game_fn_80096710.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80096830.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009697C.c"),
    Object(NonMatching, "game/game_fn_80096A44.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80096D58.c"),
    Object(Matching, "game/game_fn_80096E24.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80096F04.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_80096FDC.c"),
    Object(Matching, "game/game_fn_80097014.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800971A0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800972D0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8009A0EC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009A2B8.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_8009A404.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009C28C.c"),
    Object(Matching, "game/game_fn_8009C300.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009C424.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009C820.c"),
    Object(Matching, "game/game_fn_8009C870.c"),
    Object(Matching, "game/game_fn_8009C90C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009C980.c"),
    Object(Matching, "game/game_fn_8009DBE4.c"),
    Object(Matching, "game/game_fn_8009DC54.c"),
    Object(Matching, "game/game_fn_8009DDC8.c"),
    Object(Matching, "game/game_fn_8009DE10.c"),
    Object(Matching, "game/game_fn_8009DE50.c"),
    Object(Matching, "game/game_fn_8009E0D4.c"),
    Object(NonMatching, "game/game_fn_8009E2E8.c"),
    Object(Matching, "game/game_fn_8009E39C.c"),
    Object(NonMatching, "game/game_fn_8009E4BC.c"),
    Object(Matching, "game/game_fn_8009E710.c"),
    Object(NonMatching, "game/game_fn_8009E808.c"),
    Object(Matching, "game/game_fn_8009EA3C.c"),
    Object(Matching, "game/game_fn_8009EAB0.c"),
    Object(Matching, "game/game_fn_8009EC34.c"),
    Object(Matching, "game/game_fn_8009ED44.c"),
    Object(Matching, "game/game_fn_8009EEBC.c"),
    Object(Matching, "game/game_fn_8009EF8C.c"),
    Object(Matching, "game/game_fn_8009F07C.c"),
    Object(Matching, "game/game_fn_8009F1C4.c"),
    Object(Matching, "game/game_fn_8009F258.c"),
    Object(Matching, "game/game_fn_8009F360.c"),
    Object(Matching, "game/game_fn_8009F41C.c"),
    Object(Matching, "game/game_fn_8009F534.c"),
    Object(NonMatching, "game/game_fn_8009F664.c"),
    Object(NonMatching, "game/game_fn_8009F700.c"),
    Object(Matching, "game/game_fn_8009F7D4.c"),
    Object(Matching, "game/game_fn_8009F8CC.c"),
    Object(Matching, "game/game_fn_8009F99C.c"),
    Object(Matching, "game/game_fn_8009FB0C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_8009FD08.c"),
    Object(Matching, "game/game_fn_8009FE98.c"),
    Object(Matching, "game/game_fn_8009FEF0.c"),
    Object(Matching, "game/game_fn_800A0018.c"),
    Object(NonMatching, "game/game_fn_800A0140.c"),
    Object(NonMatching, "game/game_fn_800A0324.c"),
    Object(Matching, "game/game_fn_800A0B68.c"),
    Object(Matching, "game/game_fn_800A0C0C.c"),
    Object(NonMatching, "game/game_fn_800A0CC0.c"),
    Object(NonMatching, "game/game_fn_800A0DE4.c"),
    Object(Matching, "game/game_fn_800A1060.c"),
    Object(Matching, "game/game_fn_800A1150.c"),
    Object(NonMatching, "game/game_fn_800A1278.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A1438.c"),
    Object(Matching, "game/game_fn_800A1580.c"),
    Object(Matching, "game/game_fn_800A15C0.c"),
    Object(Matching, "game/game_fn_800A16AC.c"),
    Object(Matching, "game/game_fn_800A1724.c"),
    Object(Matching, "game/game_fn_800A17C4.c"),
    Object(Matching, "game/game_fn_800A18AC.c"),
    Object(Matching, "game/game_fn_800A1938.c"),
    Object(NonMatching, "game/game_fn_800A197C.c"),
    Object(Matching, "game/game_fn_800A1A04.c"),
    Object(Matching, "game/game_fn_800A1A24.c"),
    Object(Matching, "game/game_fn_800A1A50.c"),
    Object(Matching, "game/game_fn_800A1A84.c"),
    Object(Matching, "game/game_fn_800A1AE0.c"),
    Object(NonMatching, "game/game_fn_800A1AF0.c"),
    Object(Matching, "game/game_fn_800A1B90.c"),
    Object(Matching, "game/game_fn_800A1C50.c"),
    Object(Matching, "game/game_fn_800A1CD0.c"),
    Object(Matching, "game/game_fn_800A1D18.c"),
    Object(Matching, "game/game_fn_800A1D1C.c"),
    Object(Matching, "game/game_fn_800A1D20.c"),
    Object(Matching, "game/game_fn_800A1D24.c"),
    Object(Matching, "game/game_fn_800A1D28.c"),
    Object(Matching, "game/game_fn_800A1D4C.c"),
    Object(NonMatching, "game/game_fn_800A1DA0.c"),
    Object(Matching, "game/game_fn_800A1E94.c"),
    Object(Matching, "game/game_fn_800A1EEC.c"),
    Object(Matching, "game/game_fn_800A1F58.c"),
    Object(Matching, "game/game_fn_800A1FC0.c"),
    Object(Matching, "game/game_fn_800A200C.c"),
    Object(Matching, "game/game_fn_800A2018.c"),
    Object(Matching, "game/game_fn_800A2060.c"),
    Object(Matching, "game/game_fn_800A2068.c"),
    Object(Matching, "game/game_fn_800A20C0.c"),
    Object(Matching, "game/game_fn_800A2130.c"),
    Object(Matching, "game/game_fn_800A2200.c"),
    Object(Matching, "game/game_fn_800A2220.c"),
    Object(Matching, "game/game_fn_800A22D8.c"),
    Object(Matching, "game/game_fn_800A2308.c"),
    Object(Matching, "game/game_fn_800A230C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A2384.c"),
    Object(NonMatching, "game/game_fn_800A2414.c"),
    Object(Matching, "game/game_fn_800A2430.c"),
    Object(Matching, "game/game_fn_800A24A4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A2598.c"),
    Object(Matching, "game/game_fn_800A25D8.c"),
    Object(NonMatching, "game/game_fn_800A2688.c"),
    Object(Matching, "game/game_fn_800A270C.c"),
    Object(Matching, "game/game_fn_800A2A80.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A2B04.c"),
    Object(Matching, "game/game_fn_800A2B80.c"),
    Object(NonMatching, "game/game_fn_800A2B8C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800A2D1C.c"),
    Object(Matching, "game/game_fn_800A2D78.c"),
    Object(Matching, "game/game_fn_800A2DBC.c"),
    Object(Matching, "game/game_fn_800A2DC8.c"),
    Object(Matching, "game/game_fn_800A2E00.c"),
    Object(Matching, "game/game_fn_800A2E5C.c"),
    Object(Matching, "game/game_fn_800A2E64.c"),
    Object(Matching, "game/game_fn_800A2ED8.c"),
    Object(Matching, "game/game_fn_800A2F0C.c"),
    Object(Matching, "game/game_fn_800A2F7C.c"),
    Object(Matching, "game/game_fn_800A2FCC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A306C.c"),
    Object(Matching, "game/game_fn_800A3074.c"),
    Object(Matching, "game/game_fn_800A30AC.c"),
    Object(Matching, "game/game_fn_800A30B8.c"),
    Object(Matching, "game/game_fn_800A30C0.c"),
    Object(Matching, "game/game_fn_800A30CC.c"),
    Object(Matching, "game/game_fn_800A30F4.c"),
    Object(NonMatching, "game/game_fn_800A3104.c"),
    Object(NonMatching, "game/game_fn_800A3180.c"),
    Object(Matching, "game/game_fn_800A3240.c"),
    Object(Matching, "game/game_fn_800A3274.c"),
    Object(Matching, "game/game_fn_800A32B8.c"),
    Object(Matching, "game/game_fn_800A33A8.c"),
    Object(Matching, "game/game_fn_800A3468.c"),
    Object(Matching, "game/game_fn_800A3564.c"),
    Object(Matching, "game/game_fn_800A3570.c"),
    Object(Matching, "game/game_fn_800A357C.c"),
    Object(NonMatching, "game/game_fn_800A3588.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A36F4.c"),
    Object(Matching, "game/game_fn_800A37CC.c"),
    Object(Matching, "game/game_fn_800A383C.c"),
    Object(Matching, "game/game_fn_800A3894.c"),
    Object(NonMatching, "game/game_fn_800A397C.c"),
    Object(Matching, "game/game_fn_800A3A10.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A3AC4.c"),
    Object(Matching, "game/game_fn_800A3C2C.c"),
    Object(NonMatching, "game/game_fn_800A3C4C.c"),
    Object(NonMatching, "game/game_fn_800A3C84.c"),
    Object(Matching, "game/game_fn_800A3D90.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800A3E94.c"),
    Object(NonMatching, "game/game_fn_800A40C4.c"),
    Object(NonMatching, "game/game_fn_800A41CC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A4368.c"),
    Object(Matching, "game/game_fn_800A43E8.c"),
    Object(Matching, "game/game_fn_800A4428.c"),
    Object(Matching, "game/game_fn_800A44D4.c"),
    Object(Matching, "game/game_fn_800A44E0.c"),
    Object(Matching, "game/game_fn_800A4530.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A45B0.c"),
    Object(Matching, "game/game_fn_800A4634.c"),
    Object(Matching, "game/game_fn_800A4670.c"),
    Object(Matching, "game/game_fn_800A46C4.c"),
    Object(Matching, "game/game_fn_800A46F4.c"),
    Object(Matching, "game/game_fn_800A4724.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A4798.c"),
    Object(Matching, "game/game_fn_800A4978.c"),
    Object(Matching, "game/game_fn_800A49FC.c"),
    Object(Matching, "game/game_fn_800A4A60.c"),
    Object(Matching, "game/game_fn_800A4A90.c"),
    Object(Matching, "game/game_fn_800A4C98.c"),
    Object(Matching, "game/game_fn_800A4D04.c"),
    Object(Matching, "game/game_fn_800A4D48.c"),
    Object(NonMatching, "game/game_fn_800A4DD4.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A4EC8.c"),
    Object(Matching, "game/game_fn_800A4F44.c"),
    Object(NonMatching, "game/game_fn_800A4F98.c"),
    Object(NonMatching, "game/game_fn_800A509C.c"),
    Object(Matching, "game/game_fn_800A5330.c"),
    Object(NonMatching, "game/game_fn_800A57D4.c"),
    Object(NonMatching, "game/game_fn_800A5948.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A76A0.c"),
    Object(Matching, "game/game_fn_800A7738.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A7860.c"),
    Object(NonMatching, "game/game_fn_800A78E0.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(NonMatching, "game/game_fn_800A7A68.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A7D34.c"),
    Object(Matching, "game/game_fn_800A7E88.c"),
    Object(Matching, "game/game_fn_800A7F1C.c"),
    Object(Matching, "game/game_fn_800A7F8C.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A8034.c"),
    Object(Matching, "game/game_fn_800A8040.c"),
    Object(NonMatching, "game/game_fn_800A80CC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800A821C.c"),
    Object(Matching, "game/game_fn_800A82C8.c"),
    Object(Matching, "game/game_fn_800A831C.c"),
    Object(Matching, "game/game_fn_800A83DC.c", extra_cflags=["-use_lmw_stmw on"]),
    Object(Matching, "game/game_fn_800AA6F4.c"),
    Object(NonMatching, "game/game_fn_800AA7F0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800AA8A0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800AA94C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800AAAB8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800AAB90.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800AAD14.c"),
            Object(Matching, "game/game_fn_800ACED0.c"),
            Object(Matching, "game/game_fn_800ACFE0.c"),
            Object(Matching, "game/game_fn_800ACFE8.c"),
            Object(Matching, "game/game_fn_800AD208.c"),
            Object(Matching, "game/game_fn_800AD210.c"),
            Object(Matching, "game/game_fn_800AD218.c"),
            Object(Matching, "game/game_fn_800AD230.c"),
            Object(Matching, "game/game_fn_800AD238.c"),
            Object(Matching, "game/game_fn_800AD244.c"),
            Object(Matching, "game/game_fn_800AD2AC.c"),
            Object(Matching, "game/game_fn_800AD2B4.c"),
            Object(Matching, "game/game_fn_800AD2DC.c"),
            Object(Matching, "game/game_fn_800AD354.c"),
            Object(Matching, "game/game_fn_800AD3A4.c"),
            Object(Matching, "game/game_fn_800AD3E4.c"),
            Object(Matching, "game/game_fn_800AD430.c"),
            Object(Matching, "game/game_fn_800AD484.c"),
            Object(Matching, "game/game_fn_800AD4E8.c"),
            Object(Matching, "game/game_fn_800AD538.c"),
            Object(NonMatching, "game/game_fn_800AD540.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800ADB44.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800ADC2C.c"),
            Object(Matching, "game/game_fn_800AE254.c"),
            Object(Matching, "game/game_fn_800AE2D4.c"),
            Object(Matching, "game/game_fn_800AE348.c"),
            Object(Matching, "game/game_fn_800AE35C.c"),
            Object(Matching, "game/game_fn_800AE368.c"),
            Object(Matching, "game/game_fn_800AE380.c"),
            Object(Matching, "game/game_fn_800AE3FC.c"),
            Object(Matching, "game/game_fn_800AE864.c"),
            Object(Matching, "game/game_fn_800AE88C.c"),
            Object(Matching, "game/game_fn_800AE954.c"),
            Object(NonMatching, "game/game_fn_800AE9D0.c"),
            Object(Matching, "game/game_fn_800AF0AC.c"),
            Object(Matching, "game/game_fn_800AF11C.c"),
            Object(Matching, "game/game_fn_800AF1C0.c"),
            Object(NonMatching, "game/game_fn_800AF230.c"),
            Object(Matching, "game/game_fn_800AF2D4.c"),
            Object(Matching, "game/game_fn_800AF6D4.c"),
            Object(Matching, "game/game_fn_800AF6DC.c"),
            Object(Matching, "game/game_fn_800AF7E4.c"),
            Object(Matching, "game/game_fn_800AFBA8.c"),
            Object(Matching, "game/game_fn_800AFC30.c"),
            Object(Matching, "game/game_fn_800AFCD0.c"),
            Object(Matching, "game/game_fn_800AFDA4.c"),
            Object(Matching, "game/game_fn_800AFE30.c"),
            Object(Matching, "game/game_fn_800AFEC0.c"),
            Object(NonMatching, "game/game_fn_800B002C.c"),
            Object(Matching, "game/game_fn_800B01D8.c"),
            Object(Matching, "game/game_fn_800B035C.c"),
            Object(Matching, "game/game_fn_800B0954.c"),
            Object(Matching, "game/game_fn_800B18F8.c"),
            Object(Matching, "game/game_fn_800B193C.c"),
            Object(Matching, "game/game_fn_800B1944.c"),
            Object(Matching, "game/game_fn_800B194C.c"),
            Object(Matching, "game/game_fn_800B1974.c"),
            Object(Matching, "game/game_fn_800B19A4.c"),
            Object(Matching, "game/game_fn_800B1AA0.c"),
            Object(Matching, "game/game_fn_800B1AB0.c"),
            Object(Matching, "game/game_fn_800B2548.c"),
            Object(Matching, "game/game_fn_800B25AC.c"),
            Object(Matching, "game/game_fn_800B25F4.c"),
            Object(Matching, "game/game_fn_800B261C.c"),
            Object(Matching, "game/game_fn_800B2624.c"),
            Object(Matching, "game/game_fn_800B267C.c"),
            Object(Matching, "game/game_fn_800B2778.c"),
            Object(Matching, "game/game_fn_800B283C.c"),
            Object(Matching, "game/game_fn_800B2AE8.c"),
            Object(Matching, "game/game_fn_800B2E60.c"),
            Object(NonMatching, "game/game_fn_800B2EC0.c"),
            Object(Matching, "game/game_fn_800B3064.c"),
            Object(Matching, "game/game_fn_800B3178.c"),
            Object(Matching, "game/game_fn_800B3304.c"),
            Object(Matching, "game/game_fn_800B34CC.c"),
            Object(Matching, "game/game_fn_800B35AC.c"),
            Object(Matching, "game/game_fn_800B36FC.c"),
            Object(Matching, "game/game_fn_800B376C.c"),
            Object(Matching, "game/game_fn_800B3898.c"),
            Object(Matching, "game/game_fn_800B39A8.c"),
            Object(Matching, "game/game_fn_800B3AF8.c"),
            Object(Matching, "game/game_fn_800B3B90.c"),
            Object(Matching, "game/game_fn_800B3C78.c"),
            Object(Matching, "game/game_fn_800B3DB0.c"),
            Object(Matching, "game/game_fn_800B3F24.c"),
            Object(Matching, "game/game_fn_800B3F58.c"),
            Object(Matching, "game/game_fn_800B3FC4.c"),
            Object(Matching, "game/game_fn_800B4028.c"),
            Object(Matching, "game/game_fn_800B4098.c"),
            Object(Matching, "game/game_fn_800B40FC.c"),
            Object(Matching, "game/game_fn_800B41CC.c"),
            Object(Matching, "game/game_fn_800B4268.c"),
            Object(Matching, "game/game_fn_800B4308.c"),
            Object(Matching, "game/game_fn_800B433C.c"),
            Object(Matching, "game/game_fn_800B43B4.c"),
            Object(Matching, "game/game_fn_800B442C.c"),
            Object(Matching, "game/game_fn_800B447C.c"),
            Object(Matching, "game/game_fn_800B44CC.c"),
            Object(Matching, "game/game_fn_800B451C.c"),
            Object(Matching, "game/game_fn_800B4558.c"),
            Object(Matching, "game/game_fn_800B4594.c"),
            Object(Matching, "game/game_fn_800B45D0.c"),
            Object(Matching, "game/game_fn_800B4660.c"),
            Object(Matching, "game/game_fn_800B4818.c"),
            Object(Matching, "game/game_fn_800B4844.c"),
            Object(Matching, "game/game_fn_800B48E4.c"),
            Object(Matching, "game/game_fn_800B4938.c"),
            Object(Matching, "game/game_fn_800B4990.c"),
            Object(Matching, "game/game_fn_800B4A48.c"),
            Object(Matching, "game/game_fn_800B4ABC.c"),
            Object(Matching, "game/game_fn_800B566C.c"),
            Object(Matching, "game/game_fn_800B5828.c"),
            Object(Matching, "game/game_fn_800B5D10.c"),
            Object(Matching, "game/game_fn_800B5D94.c"),
            Object(Matching, "game/game_fn_800B5F1C.c"),
            Object(Matching, "game/game_fn_800B5F78.c"),
            Object(Matching, "game/game_fn_800B6024.c"),
            Object(Matching, "game/game_fn_800B611C.c"),
            Object(Matching, "game/game_fn_800B61B8.c"),
            Object(Matching, "game/game_fn_800B6234.c"),
            Object(Matching, "game/game_fn_800B63C0.c"),
            Object(Matching, "game/game_fn_800B64AC.c"),
            Object(Matching, "game/game_fn_800B6548.c"),
            Object(Matching, "game/game_fn_800B65E4.c"),
            Object(Matching, "game/game_fn_800B669C.c"),
            Object(Matching, "game/game_fn_800B66F8.c"),
            Object(Matching, "game/game_fn_800B6718.c"),
            Object(Matching, "game/game_fn_800B6840.c"),
            Object(Matching, "game/game_fn_800B689C.c"),
            Object(Matching, "game/game_fn_800B6908.c"),
            Object(Matching, "game/game_fn_800B692C.c"),
            Object(Matching, "game/game_fn_800B6960.c"),
            Object(Matching, "game/game_fn_800B6A24.c"),
            Object(Matching, "game/game_fn_800B6A48.c"),
            Object(Matching, "game/game_fn_800B6B00.c"),
            Object(Matching, "game/game_fn_800B6C00.c"),
            Object(Matching, "game/game_fn_800B6C88.c"),
            Object(Matching, "game/game_fn_800B6D10.c"),
            Object(Matching, "game/game_fn_800B6E40.c"),
            Object(Matching, "game/game_fn_800B7C6C.c"),
            Object(Matching, "game/game_fn_800B7C80.c"),
            Object(Matching, "game/game_fn_800B7D20.c"),
            Object(Matching, "game/game_fn_800B7D78.c"),
            Object(Matching, "game/game_fn_800B7DA0.c"),
            Object(Matching, "game/game_fn_800B7E44.c"),
            Object(Matching, "game/game_fn_800B7EC0.c"),
            Object(Matching, "game/game_fn_800B811C.c"),
            Object(Matching, "game/game_fn_800B84A8.c"),
            Object(Matching, "game/game_fn_800B84C8.c"),
            Object(NonMatching, "game/game_fn_800B84DC.c"),
            Object(Matching, "game/game_fn_800B8DBC.c"),
            Object(Matching, "game/game_fn_800B8E28.c"),
            Object(Matching, "game/game_fn_800B8F38.c"),
            Object(Matching, "game/game_fn_800B8F6C.c"),
            Object(Matching, "game/game_fn_800B8F80.c"),
            Object(Matching, "game/game_fn_800B8F94.c"),
            Object(Matching, "game/game_fn_800B9260.c"),
            Object(Matching, "game/game_fn_800B92A0.c"),
            Object(Matching, "game/game_fn_800B92AC.c"),
            Object(Matching, "game/game_fn_800B933C.c"),
            Object(Matching, "game/game_fn_800B936C.c"),
            Object(Matching, "game/game_fn_800B93F0.c"),
            Object(Matching, "game/game_fn_800B9454.c"),
            Object(Matching, "game/game_fn_800B9460.c"),
            Object(Matching, "game/game_fn_800B9474.c"),
            Object(Matching, "game/game_fn_800B9C88.c"),
            Object(Matching, "game/game_fn_800B9FE8.c"),
            Object(Matching, "game/game_fn_800BA068.c"),
            Object(Matching, "game/game_fn_800BA124.c"),
            Object(Matching, "game/game_fn_800BADEC.c"),
            Object(Matching, "game/game_fn_800BB1EC.c"),
            Object(Matching, "game/game_fn_800BB3F8.c"),
            Object(Matching, "game/game_fn_800BB450.c"),
            Object(Matching, "game/game_fn_800BB4C4.c"),
            Object(NonMatching, "game/game_fn_800BB5C4.c"),
            Object(Matching, "game/game_fn_800BB6A0.c"),
            Object(NonMatching, "game/game_fn_800BB7A8.c"),
            Object(Matching, "game/game_fn_800BB8AC.c"),
            Object(NonMatching, "game/game_fn_800BB9A4.c"),
            Object(Matching, "game/game_fn_800BBA84.c"),
            Object(NonMatching, "game/game_fn_800BBAF0.c"),
            Object(Matching, "game/game_fn_800BBBC4.c"),
            Object(Matching, "game/game_fn_800BBC40.c"),
            Object(Matching, "game/game_fn_800BBE04.c"),
            Object(Matching, "game/game_fn_800BBE18.c"),
            Object(Matching, "game/game_fn_800BBF2C.c"),
            Object(Matching, "game/game_fn_800BBF6C.c"),
            Object(Matching, "game/game_fn_800BC000.c"),
            Object(Matching, "game/game_fn_800BC028.c"),
            Object(Matching, "game/game_fn_800BC6D8.c"),
            Object(Matching, "game/game_fn_800BCCC4.c"),
            Object(Matching, "game/game_fn_800BD384.c"),
            Object(Matching, "game/game_fn_800BD5F4.c"),
            Object(Matching, "game/game_fn_800BD628.c"),
            Object(Matching, "game/game_fn_800BD638.c"),
            Object(Matching, "game/game_fn_800BD6F0.c"),
            Object(Matching, "game/game_fn_800BD748.c"),
            Object(Matching, "game/game_fn_800BD750.c"),
            Object(Matching, "game/game_fn_800BD7F0.c"),
            Object(Matching, "game/game_fn_800BD7FC.c"),
            Object(Matching, "game/game_fn_800BD808.c"),
            Object(Matching, "game/game_fn_800BD818.c"),
            Object(Matching, "game/game_fn_800BD828.c"),
            Object(Matching, "game/game_fn_800BD944.c"),
            Object(NonMatching, "game/game_fn_800BDE24.c"),
            Object(Matching, "game/game_fn_800BE0F4.c"),
            Object(NonMatching, "game/game_fn_800BE158.c"),
            Object(Matching, "game/game_fn_800BE1F4.c"),
            Object(Matching, "game/game_fn_800BE260.c"),
            Object(NonMatching, "game/game_fn_800BE2CC.c"),
            Object(Matching, "game/game_fn_800BE390.c"),
            Object(NonMatching, "game/game_fn_800BE70C.c"),
            Object(Matching, "game/game_fn_800BE86C.c"),
            Object(Matching, "game/game_fn_800BE894.c"),
            Object(Matching, "game/game_fn_800BE8D4.c"),
            Object(NonMatching, "game/game_fn_800BE938.c"),
            Object(Matching, "game/game_fn_800BEB04.c"),
            Object(Matching, "game/game_fn_800BEBE4.c"),
            Object(Matching, "game/game_fn_800BF060.c"),
            Object(NonMatching, "game/game_fn_800BF0C0.c"),
            Object(Matching, "game/game_fn_800BF7C0.c"),
            Object(Matching, "game/game_fn_800BF81C.c"),
            Object(NonMatching, "game/game_fn_800BFF14.c"),
            Object(Matching, "game/game_fn_800BFF84.c"),
            Object(NonMatching, "game/game_fn_800BFFDC.c"),
            Object(Matching, "game/game_fn_800C0240.c"),
            Object(NonMatching, "game/game_fn_800C030C.c"),
            Object(Matching, "game/game_fn_800C16F4.c"),
            Object(Matching, "game/game_fn_800C17EC.c"),
            Object(Matching, "game/game_fn_800C1AB8.c"),
            Object(Matching, "game/game_fn_800C1D54.c"),
            Object(NonMatching, "game/game_fn_800C1D60.c"),
            Object(Matching, "game/game_fn_800C23D8.c"),
            Object(Matching, "game/game_fn_800C2528.c"),
            Object(Matching, "game/game_fn_800C262C.c"),
            Object(Matching, "game/game_fn_800C2708.c"),
            Object(Matching, "game/game_fn_800C280C.c"),
            Object(Matching, "game/game_fn_800C3418.c"),
            Object(Matching, "game/game_fn_800C34A8.c"),
            Object(Matching, "game/game_fn_800C3854.c"),
            Object(NonMatching, "game/game_fn_800C3958.c"),
            Object(Matching, "game/game_fn_800C39D0.c"),
            Object(NonMatching, "game/game_fn_800C3A74.c"),
            Object(Matching, "game/game_fn_800C3CE4.c"),
            Object(Matching, "game/game_fn_800C3D24.c"),
            Object(Matching, "game/game_fn_800C438C.c"),
            Object(Matching, "game/game_fn_800C43AC.c"),
            Object(Matching, "game/game_fn_800C4880.c"),
            Object(Matching, "game/game_fn_800C4A74.c"),
            Object(NonMatching, "game/game_fn_800C4AA0.c"),
            Object(Matching, "game/game_fn_800C4B6C.c"),
            Object(Matching, "game/game_fn_800C4E94.c"),
            # 90.625%: size-exact, with only r30/r31 allocation differences.
            Object(NonMatching, "game/game_fn_800C5258.c"),
            Object(Matching, "game/game_fn_800C59F0.c"),
            Object(Matching, "game/game_fn_800C5EFC.c"),
            Object(Matching, "game/game_fn_800C5FA4.c"),
            Object(Matching, "game/game_fn_800C61F8.c"),
            Object(Matching, "game/game_fn_800C63D8.c"),
            Object(Matching, "game/game_fn_800C644C.c"),
            Object(Matching, "game/game_fn_800C65FC.c"),
            Object(Matching, "game/game_fn_800C677C.c"),
            Object(Matching, "game/game_fn_800C6F50.c"),
            Object(Matching, "game/game_fn_800C7028.c"),
            # 83.05556%: size differs by one instruction due to argument-save scheduling.
            Object(NonMatching, "game/game_fn_800C77B4.c"),
            # 83.05556%: size differs by one instruction due to argument-save scheduling.
            Object(NonMatching, "game/game_fn_800C77FC.c"),
            # 53.846153%: size-exact; argument setup is scheduled around the prologue differently.
            Object(NonMatching, "game/game_fn_800C7844.c"),
            Object(Matching, "game/game_fn_800C7878.c"),
            Object(Matching, "game/game_fn_800C78C4.c"),
            Object(Matching, "game/game_fn_800C7A54.c"),
            Object(Matching, "game/game_fn_800C7AEC.c"),
            Object(Matching, "game/game_fn_800C7B74.c"),
            # 99.91071%: size-exact; two instructions allocate the short-lived
            # secondary runtime to r30 rather than retail's reused r27.
            Object(Matching, "game/game_fn_800C7C0C.c"),
            Object(Matching, "game/game_fn_800C7DCC.c"),
            # 91.72941%: behavior-complete; remaining differences are the
            # aggregate/outgoing stack area and callee-saved register allocation.
            Object(NonMatching, "game/game_fn_800C7E40.c"),
            Object(Matching, "game/game_fn_800C80E8.c"),
            Object(Matching, "game/game_fn_800C81E0.c"),
            Object(Matching, "game/game_fn_800C82F0.c"),
            # 76.475%: behavior-complete color interpolation setup; remaining
            # differences are aggregate stack placement and byte-copy scheduling.
            Object(NonMatching, "game/game_fn_800C8394.c"),
            Object(Matching, "game/game_fn_800C8434.c"),
            # 88.039215%: size-exact behavior-complete angle interpolation;
            # remaining differences are float-conversion scheduling and threshold register choice.
            Object(NonMatching, "game/game_fn_800C849C.c"),
            # 87.864%: behavior-complete peer scan and dispatch; remaining
            # differences are aggregate stack placement and temporary scheduling.
            Object(NonMatching, "game/game_fn_800C8568.c"),
            Object(Matching, "game/game_fn_800C9164.c"),
            Object(Matching, "game/game_fn_800C91F8.c"),
            Object(Matching, "game/game_fn_800C9268.c"),
            Object(Matching, "game/game_fn_800C928C.c"),
            # 99.18519%: size-exact vector effect wrapper; the remaining
            # differences are equivalent r4/r6 scratch allocation and scheduling.
            Object(NonMatching, "game/game_fn_800C92E8.c"),
            Object(Matching, "game/game_fn_800C94FC.c"),
            # 97.0% initial honest-C reconstruction; equivalent r6/r7 allocation.
            Object(NonMatching, "game/game_fn_800C9508.c"),
            Object(Matching, "game/game_fn_800C9660.c"),
            Object(Matching, "game/game_fn_800C96B4.c"),
            Object(Matching, "game/game_fn_800C96C4.c"),
            Object(Matching, "game/game_fn_800C96CC.c"),
            Object(Matching, "game/game_fn_800C99B4.c"),
            Object(Matching, "game/game_fn_800C9A2C.c"),
            Object(Matching, "game/game_fn_800C9AD4.c"),
            Object(Matching, "game/game_fn_800C9B08.c"),
            Object(Matching, "game/game_fn_800C9B74.c"),
            Object(Matching, "game/game_fn_800C9BA8.c"),
            # 87.34849% size-exact honest-C reconstruction; remaining
            # differences are branch layout and split signed-conversion constant identity.
            Object(NonMatching, "game/game_fn_800C9C60.c"),
            Object(Matching, "game/game_fn_800C9D68.c"),
            Object(Matching, "game/game_fn_800CA13C.c"),
            Object(Matching, "game/game_fn_800CA1BC.c"),
            Object(Matching, "game/game_fn_800CA2C8.c"),
            Object(Matching, "game/game_fn_800CA4B8.c"),
            Object(Matching, "game/game_fn_800CA530.c"),
            # 83.888885% size-exact honest-C reconstruction; remaining
            # differences are equivalent r29-r31 allocation and prologue scheduling.
            Object(NonMatching, "game/game_fn_800CA554.c"),
            Object(Matching, "game/game_fn_800CA5C0.c"),
            Object(Matching, "game/game_fn_800CA660.c"),
            Object(Matching, "game/game_fn_800CA6DC.c"),
            # 89.25532% honest-C reconstruction; remaining differences are
            # callee-saved allocation and signed max-expression codegen.
            Object(NonMatching, "game/game_fn_800CA7D4.c"),
            Object(Matching, "game/game_fn_800CAB80.c"),
            Object(Matching, "game/game_fn_800CAC5C.c"),
            Object(Matching, "game/game_fn_800CAF7C.c"),
            # 96.71171% honest-C reconstruction; remaining differences are
            # MWCC boolean-result register allocation and normalization.
            Object(NonMatching, "game/game_fn_800CB098.c"),
            Object(Matching, "game/game_fn_800CB694.c"),
            Object(Matching, "game/game_fn_800CB760.c"),
            Object(Matching, "game/game_fn_800CB8F4.c"),
            Object(Matching, "game/game_fn_800CC2D8.c"),
            Object(Matching, "game/game_fn_800CC3BC.c"),
            Object(Matching, "game/game_fn_800CC458.c"),
            Object(Matching, "game/game_fn_800CCA44.c"),
            Object(Matching, "game/game_fn_800CCDA8.c"),
            Object(Matching, "game/game_fn_800CCE78.c"),
            Object(Matching, "game/game_fn_800CCF60.c"),
            Object(Matching, "game/game_fn_800CD458.c"),
            Object(Matching, "game/game_fn_800CD568.c"),
            # 97.52525% size-exact honest-C reconstruction; remaining
            # differences are a global callee-saved-register permutation.
            Object(NonMatching, "game/game_fn_800CD6C0.c"),
            # 99.655174% size-exact honest-C reconstruction; remaining
            # differences are one equivalent final r3/r4 scratch choice.
            Object(NonMatching, "game/game_fn_800CD84C.c"),
            Object(Matching, "game/game_fn_800CDD84.c"),
            Object(Matching, "game/game_fn_800CE3BC.c"),
            # 96.36364% size-exact honest-C reconstruction; remaining
            # differences are an equivalent r4/r5 data/index allocation pair.
            Object(NonMatching, "game/game_fn_800CE524.c"),
            # 94.809525% honest-C reconstruction; remaining differences are
            # base-pointer materialization and equivalent indexed stores.
            Object(NonMatching, "game/game_fn_800CE698.c"),
            Object(Matching, "game/game_fn_800CE8B8.c"),
            Object(Matching, "game/game_fn_800CE8E8.c"),
            Object(Matching, "game/game_fn_800CE914.c"),
            Object(Matching, "game/game_fn_800CE9A4.c"),
            Object(Matching, "game/game_fn_800CEA1C.c"),
            Object(Matching, "game/game_fn_800CEB10.c"),
            Object(Matching, "game/game_fn_800CEF94.c"),
            Object(Matching, "game/game_fn_800CEFE8.c"),
            Object(Matching, "game/game_fn_800CF03C.c"),
            Object(Matching, "game/game_fn_800CF0C8.c"),
            Object(Matching, "game/game_fn_800CF220.c"),
            Object(Matching, "game/game_fn_800CF2DC.c"),
            Object(Matching, "game/game_fn_800CF32C.c"),
            Object(Matching, "game/game_fn_800CF3D4.c"),
            Object(Matching, "game/game_fn_800CF46C.c"),
            Object(Matching, "game/game_fn_800CF52C.c"),
            Object(NonMatching, "game/game_fn_800CF598.c"),
            Object(Matching, "game/game_fn_800CF8D0.c"),
            Object(Matching, "game/game_fn_800CF904.c"),
            Object(NonMatching, "game/game_fn_800CFA3C.c"),
            Object(NonMatching, "game/game_fn_800CFC04.c"),
            Object(NonMatching, "game/game_fn_800CFCD4.c"),
            Object(Matching, "game/game_fn_800CFDF4.c"),
            Object(Matching, "game/game_fn_800CFE30.c"),
            Object(Matching, "game/game_fn_800CFE88.c"),
            Object(Matching, "game/game_fn_800CFF04.c"),
            Object(Matching, "game/game_fn_800CFFFC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D00C0.c"),
            Object(Matching, "game/game_fn_800D00C8.c"),
            Object(Matching, "game/game_fn_800D0454.c"),
            Object(Matching, "game/game_fn_800D04A4.c"),
            Object(Matching, "game/game_fn_800D0510.c"),
            Object(Matching, "game/game_fn_800D0584.c"),
            Object(Matching, "game/game_fn_800D05FC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D06DC.c"),
            Object(NonMatching, "game/game_fn_800D078C.c"),
            Object(NonMatching, "game/game_fn_800D082C.c"),
            Object(Matching, "game/game_fn_800D0A04.c"),
            Object(Matching, "game/game_fn_800D0AA8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800D0B74.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D30A4.c"),
            Object(Matching, "game/game_fn_800D3148.c"),
            Object(NonMatching, "game/game_fn_800D322C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D3374.c"),
            Object(Matching, "game/game_fn_800D3410.c"),
            Object(NonMatching, "game/game_fn_800D34B8.c"),
            Object(NonMatching, "game/game_fn_800D3598.c"),
            Object(NonMatching, "game/game_fn_800D3620.c"),
            Object(Matching, "game/game_fn_800D36F4.c"),
            Object(Matching, "game/game_fn_800D3718.c"),
            Object(NonMatching, "game/game_fn_800D373C.c"),
            Object(NonMatching, "game/game_fn_800D386C.c"),
            Object(NonMatching, "game/game_fn_800D38CC.c"),
            Object(Matching, "game/game_fn_800D3F24.c"),
            Object(Matching, "game/game_fn_800D3FC8.c"),
            Object(Matching, "game/game_fn_800D406C.c"),
            Object(Matching, "game/game_fn_800D40A8.c"),
            Object(Matching, "game/game_fn_800D4100.c"),
            Object(NonMatching, "game/game_fn_800D4214.c"),
            Object(Matching, "game/game_fn_800D4310.c"),
            Object(Matching, "game/game_fn_800D5EFC.c"),
            Object(Matching, "game/game_fn_800D5FA0.c"),
            Object(NonMatching, "game/game_fn_800D607C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800D61C4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D6294.c"),
            Object(Matching, "game/game_fn_800D6314.c"),
            Object(Matching, "game/game_fn_800D6358.c"),
            Object(Matching, "game/game_fn_800D6430.c"),
            Object(Matching, "game/game_fn_800D64A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D6588.c"),
            Object(NonMatching, "game/game_fn_800D6638.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D6724.c"),
            Object(Matching, "game/game_fn_800D67A4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D6910.c"),
            Object(Matching, "game/game_fn_800D6974.c"),
            Object(Matching, "game/game_fn_800D6A20.c"),
            Object(NonMatching, "game/game_fn_800D6A28.c"),
            Object(Matching, "game/game_fn_800D8644.c"),
            Object(Matching, "game/game_fn_800D86E8.c"),
            Object(Matching, "game/game_fn_800D8744.c"),
            Object(Matching, "game/game_fn_800D877C.c"),
            Object(Matching, "game/game_fn_800D87B4.c"),
            Object(Matching, "game/game_fn_800D87EC.c"),
            Object(Matching, "game/game_fn_800D8828.c"),
            Object(NonMatching, "game/game_fn_800D88DC.c"),
            Object(Matching, "game/game_fn_800D8AD8.c"),
            Object(Matching, "game/game_fn_800D8B6C.c"),
            Object(Matching, "game/game_fn_800D8B74.c"),
            Object(Matching, "game/game_fn_800D8C3C.c"),
            Object(Matching, "game/game_fn_800D8CB8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D8E30.c"),
            Object(NonMatching, "game/game_fn_800D8EC4.c"),
            Object(Matching, "game/game_fn_800D8F38.c"),
            Object(NonMatching, "game/game_fn_800D9064.c"),
            Object(Matching, "game/game_fn_800D91AC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800D9278.c"),
            Object(Matching, "game/game_fn_800D93B4.c"),
            Object(NonMatching, "game/game_fn_800D9428.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800D9614.c"),
            Object(Matching, "game/game_fn_800D9AE8.c"),
            Object(Matching, "game/game_fn_800D9BB8.c"),
            Object(Matching, "game/game_fn_800D9BE0.c"),
            Object(Matching, "game/game_fn_800D9C48.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800D9D64.c"),
            Object(NonMatching, "game/game_fn_800D9E10.c"),
            Object(NonMatching, "game/game_fn_800D9F2C.c"),
            Object(NonMatching, "game/game_fn_800D9FE0.c"),
            Object(NonMatching, "game/game_fn_800DA05C.c"),
            Object(Matching, "game/game_fn_800DA0C4.c"),
            Object(Matching, "game/game_fn_800DA110.c"),
            Object(Matching, "game/game_fn_800DA1D4.c"),
            Object(Matching, "game/game_fn_800DA278.c"),
            Object(Matching, "game/game_fn_800DA308.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DA400.c"),
            Object(Matching, "game/game_fn_800DAFA8.c"),
            Object(NonMatching, "game/game_fn_800DAFCC.c"),
            Object(Matching, "game/game_fn_800DB150.c"),
            Object(Matching, "game/game_fn_800DB204.c"),
            Object(NonMatching, "game/game_fn_800DB2BC.c"),
            Object(Matching, "game/game_fn_800DB348.c"),
            Object(Matching, "game/game_fn_800DB37C.c"),
            Object(NonMatching, "game/game_fn_800DB430.c"),
            Object(NonMatching, "game/game_fn_800DB4F4.c"),
            Object(Matching, "game/game_fn_800DB62C.c"),
            Object(NonMatching, "game/game_fn_800DB660.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DB838.c"),
            Object(Matching, "game/game_fn_800DB874.c"),
            Object(Matching, "game/game_fn_800DB95C.c"),
            Object(Matching, "game/game_fn_800DB9B0.c"),
            Object(Matching, "game/game_fn_800DBA0C.c"),
            Object(Matching, "game/game_fn_800DBA84.c"),
            Object(Matching, "game/game_fn_800DBB24.c"),
            Object(NonMatching, "game/game_fn_800DBC0C.c"),
            Object(Matching, "game/game_fn_800DBD74.c"),
            Object(Matching, "game/game_fn_800DBE34.c"),
            Object(Matching, "game/game_fn_800DBEC4.c"),
            Object(Matching, "game/game_fn_800DBF3C.c"),
            Object(Matching, "game/game_fn_800DBF44.c"),
            Object(NonMatching, "game/game_fn_800DBF60.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DC250.c"),
            Object(NonMatching, "game/game_fn_800DC2B8.c"),
            Object(Matching, "game/game_fn_800DC398.c"),
            Object(NonMatching, "game/game_fn_800DC3A0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800DC4D4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800DC9A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800DCBC0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800DCFE0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DD050.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DD284.c"),
            Object(Matching, "game/game_fn_800DE354.c"),
            Object(Matching, "game/game_fn_800DE3F8.c"),
            Object(Matching, "game/game_fn_800DE468.c"),
            Object(Matching, "game/game_fn_800DE4D8.c"),
            Object(NonMatching, "game/game_fn_800DE648.c"),
            Object(NonMatching, "game/game_fn_800DE704.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DE8C8.c"),
            Object(NonMatching, "game/game_fn_800DE8FC.c"),
            Object(Matching, "game/game_fn_800DEA28.c"),
            Object(Matching, "game/game_fn_800DEA88.c"),
            Object(NonMatching, "game/game_fn_800DFD54.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800DFEB0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E0330.c"),
            Object(Matching, "game/game_fn_800E05BC.c"),
            Object(Matching, "game/game_fn_800E0708.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E193C.c"),
            Object(Matching, "game/game_fn_800E19CC.c"),
            Object(NonMatching, "game/game_fn_800E1AA8.c"),
            Object(Matching, "game/game_fn_800E1B40.c"),
            Object(Matching, "game/game_fn_800E1BF4.c"),
            Object(Matching, "game/game_fn_800E1C9C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E1DB0.c"),
            Object(NonMatching, "game/game_fn_800E1E68.c"),
            Object(Matching, "game/game_fn_800E20A4.c"),
            Object(Matching, "game/game_fn_800E2128.c"),
            Object(NonMatching, "game/game_fn_800E2150.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E2344.c"),
            Object(NonMatching, "game/game_fn_800E33B8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E4010.c"),
            Object(NonMatching, "game/game_fn_800E406C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E41FC.c"),
            Object(Matching, "game/game_fn_800E428C.c"),
            Object(Matching, "game/game_fn_800E42E8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800E43CC.c"),
            Object(Matching, "game/game_fn_800E4458.c"),
            Object(Matching, "game/game_fn_800E44E0.c"),
            Object(Matching, "game/game_fn_800E4520.c"),
            Object(Matching, "game/game_fn_800E4558.c"),
            Object(Matching, "game/game_fn_800E4594.c"),
            Object(Matching, "game/game_fn_800E45C0.c"),
            Object(Matching, "game/game_fn_800E45C8.c"),
            Object(Matching, "game/game_fn_800E45F4.c"),
            Object(Matching, "game/game_fn_800E463C.c"),
            Object(Matching, "game/game_fn_800E4648.c"),
            Object(Matching, "game/game_fn_800E4674.c"),
            Object(Matching, "game/game_fn_800E46A0.c"),
            Object(Matching, "game/game_fn_800E46CC.c"),
            Object(Matching, "game/game_fn_800E46F8.c"),
            Object(Matching, "game/game_fn_800E4728.c"),
            Object(Matching, "game/game_fn_800E4750.c"),
            Object(NonMatching, "game/game_fn_800E475C.c"),
            Object(Matching, "game/game_fn_800E4834.c"),
            Object(Matching, "game/game_fn_800E4840.c"),
            Object(Matching, "game/game_fn_800E48AC.c"),
            Object(NonMatching, "game/game_fn_800E4918.c"),
            Object(Matching, "game/game_fn_800E4954.c"),
            Object(Matching, "game/game_fn_800E4980.c"),
            Object(Matching, "game/game_fn_800E4A50.c"),
            Object(Matching, "game/game_fn_800E4AB8.c"),
            Object(Matching, "game/game_fn_800E4ABC.c"),
            Object(Matching, "game/game_fn_800E4AC4.c"),
            Object(Matching, "game/game_fn_800E5000.c"),
            Object(Matching, "game/game_fn_800E5044.c"),
            Object(Matching, "game/game_fn_800E5050.c"),
            Object(Matching, "game/game_fn_800E507C.c"),
            Object(NonMatching, "game/game_fn_800E50AC.c"),
            Object(Matching, "game/game_fn_800E7770.c"),
            Object(Matching, "game/game_fn_800E7838.c"),
            Object(Matching, "game/game_fn_800E790C.c"),
            Object(Matching, "game/game_fn_800E7950.c"),
            Object(Matching, "game/game_fn_800E7964.c"),
            Object(Matching, "game/game_fn_800E7F70.c"),
            Object(Matching, "game/game_fn_800E7FA4.c"),
            Object(Matching, "game/game_fn_800E801C.c"),
            Object(Matching, "game/game_fn_800E8130.c"),
            Object(NonMatching, "game/game_fn_800E828C.c"),
            Object(Matching, "game/game_fn_800E8384.c"),
            Object(Matching, "game/game_fn_800E840C.c"),
            Object(NonMatching, "game/game_fn_800E8524.c"),
            Object(NonMatching, "game/game_fn_800E8634.c"),
            Object(Matching, "game/game_fn_800E8720.c"),
            Object(Matching, "game/game_fn_800E9DE0.c"),
            Object(Matching, "game/game_fn_800E9F10.c"),
            Object(Matching, "game/game_fn_800E9F40.c"),
            Object(Matching, "game/game_fn_800E9F84.c"),
            Object(Matching, "game/game_fn_800EA08C.c"),
            Object(Matching, "game/game_fn_800EA0D0.c"),
            Object(Matching, "game/game_fn_800EA0FC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_800EA27C.c"),
            Object(Matching, "game/game_fn_800EA3A0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800EA428.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800EA4D0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800EAF48.c"),
            Object(Matching, "game/game_fn_800EB434.c"),
            Object(Matching, "game/game_fn_800EB438.c"),
            Object(Matching, "game/game_fn_800EB5A0.c"),
            Object(Matching, "game/game_fn_800EB6BC.c"),
            Object(Matching, "game/game_fn_800EB744.c"),
            Object(Matching, "game/game_fn_800EB74C.c"),
            Object(Matching, "game/game_fn_800EC314.c"),
            Object(NonMatching, "game/game_fn_800EC318.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800EC3C4.c"),
            Object(Matching, "game/game_fn_800EC5EC.c"),
            Object(Matching, "game/game_fn_800EC640.c"),
            Object(Matching, "game/game_fn_800EC6C4.c"),
            Object(Matching, "game/game_fn_800ED024.c"),
            Object(Matching, "game/game_fn_800ED6F4.c"),
            Object(Matching, "game/game_fn_800ED6F8.c"),
            Object(Matching, "game/game_fn_800ED70C.c"),
            Object(Matching, "game/game_fn_800ED720.c"),
            Object(Matching, "game/game_fn_800ED790.c"),
            Object(Matching, "game/game_fn_800ED9D8.c"),
            Object(Matching, "game/game_fn_800ED9DC.c"),
            Object(Matching, "game/game_fn_800EE3F4.c"),
            Object(Matching, "game/game_fn_800EE3F8.c"),
            Object(Matching, "game/game_fn_800EE404.c"),
            Object(Matching, "game/game_fn_800EE410.c"),
            Object(Matching, "game/game_fn_800EE41C.c"),
            Object(Matching, "game/game_fn_800EE444.c"),
            Object(Matching, "game/game_fn_800EE468.c"),
            Object(Matching, "game/game_fn_800EEB44.c"),
            Object(Matching, "game/game_fn_800EEC0C.c"),
            Object(NonMatching, "game/game_fn_800EEC44.c"),
            Object(NonMatching, "game/game_TRKNubMainLoop.c"),
            Object(Matching, "game/game_TRKDestructEvent.c"),
            Object(Matching, "game/game_fn_800EEF1C.c"),
            Object(Matching, "game/game_fn_800EEF34.c"),
            Object(NonMatching, "game/game_TRKGetNextEvent.c"),
            Object(Matching, "game/game_TRKInitializeEventQueue.c"),
            Object(Matching, "game/game_TRKNubWelcome.c"),
            Object(Matching, "game/game_TRKTerminateNub.c"),
            Object(NonMatching, "game/game_TRKInitializeNub.c", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_800EF56C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800EFC6C.c"),
            Object(Matching, "game/game_fn_800EFC9C.c"),
            Object(Matching, "game/game_TRKGetBuffer.c"),
            Object(NonMatching, "game/game_TRKInitializeMessageBuffers.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800EFEA8.c"),
            Object(Matching, "game/game_TRKInitializeSerialHandler.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800EFED4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKGetInput.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_usr_put_initialize.c"),
            Object(Matching, "game/game_fn_800F0278.c"),
            # Honest C is size-short by one redundant retail clrlwi before the bounds check.
            Object(NonMatching, "game/game_TRKDispatchMessage.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKInitializeDispatcher.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F039C.c"),
            Object(Matching, "game/game_fn_800F0540.c"),
            Object(Matching, "game/game_fn_800F0B70.c"),
            # Honest C is size-exact; only the range compare's temporary registers differ.
            Object(NonMatching, "game/game_fn_800F0CC4.c"),
            Object(Matching, "game/game_fn_800F2820.c"),
            Object(Matching, "game/game_fn_800F28D8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F29BC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F2A78.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F2B28.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F2BE0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F2BEC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F2BFC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800F2D8C.c"),
            Object(Matching, "game/game_fn_800F2EAC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800F34BC.c"),
            Object(Matching, "game/game_fn_800F34C4.c"),
            Object(Matching, "game/game_fn_800F34CC.c"),
            Object(Matching, "game/game_fn_800F34D4.c"),
            Object(Matching, "game/game_fn_800F35AC.c"),
            # Honest C is size-close; MWCC swaps the word pointer/count registers.
            Object(NonMatching, "game/game_fn_800F35E4.c"),
            Object(Matching, "game/game_fn_800F36A0.c"),
            Object(Matching, "game/game_fn_800F36A8.c"),
            Object(Matching, "game/game_fn_800F36B0.c"),
            Object(Matching, "game/game_TRKTargetSetInputPendingPtr.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F3C60.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKTargetSetStopped.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKTargetStopped.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F3C98.c"),
            Object(Matching, "game/game_fn_800F3EDC.c", extra_cflags=["-sdata 0"]),
            # Honest C; MWCC folds the constant kind checks retained by retail.
            Object(NonMatching, "game/game_fn_800F3EEC.c", extra_cflags=["-sdata 0"]),
            # Honest C; retail retains constant-controlled decrement branches.
            Object(NonMatching, "game/game_fn_800F3F68.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F4420.c"),
            Object(Matching, "game/game_fn_800F44C4.c"),
            Object(Matching, "game/game_fn_800F4F30.c"),
            Object(Matching, "game/game_fn_800F4F38.c"),
            Object(Matching, "game/game_fn_800F4F40.c"),
            Object(Matching, "game/game_fn_800F4F48.c"),
            Object(Matching, "game/game_TRKInitializeTarget.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F5030.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_EnableMetroTRKInterrupts.c"),
            Object(Matching, "game/game_fn_800F5400.c"),
            Object(Matching, "game/game_TRK_main.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKUARTInterruptHandler.c"),
            Object(Matching, "game/game_TRK_board_display.c"),
            Object(Matching, "game/game_UnreserveEXI2Port.c"),
            Object(Matching, "game/game_ReserveEXI2Port.c"),
            # Honest C; MWCC folds the global address temporary into lwzu.
            Object(NonMatching, "game/game_fn_800F564C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F5754.c"),
            Object(Matching, "game/game_TRKInitializeIntDrivenUART.c", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_InitMetroTRKCommTable.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_TRKEXICallBack.c"),
            Object(Matching, "game/game_TRKTargetContinue.c"),
            Object(Matching, "game/game_fn_800F592C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F593C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F5948.c"),
            Object(Matching, "game/game_fn_800F59CC.c"),
            Object(Matching, "game/game_fn_800F5A88.c"),
            Object(NonMatching, "game/game___va_arg.c"),
            Object(NonMatching, "game/game_fn_800F5C54.c", extra_cflags=["-sdata 0"]),
            # Honest C; these are the compiler's own long-long shift primitives,
            # so direct expressions recurse and expanded word operations differ
            # in the helper's special register allocation.
            Object(NonMatching, "game/game_fn_800F61F4.c"),
            Object(NonMatching, "game/game_fn_800F6218.c"),
            Object(NonMatching, "game/game_fn_800F623C.c"),
            Object(Matching, "game/game___unregister_fragment.c"),
            Object(Matching, "game/game___register_fragment.c"),
            # Honest C; MWCC retains the arena end in r31 instead of retail r30.
            Object(NonMatching, "game/game_fn_800F66DC.c"),
            Object(Matching, "game/game_exit.c"),
            Object(Matching, "game/game_fn_800F6848.c"),
            Object(Matching, "game/game_fn_800F6E38.c"),
            # Honest C; remaining differences are loop register allocation and
            # MWCC's mask/or spelling versus retail's rlwimi mode update.
            Object(NonMatching, "game/game___close_all.c"),
            Object(Matching, "game/game_fn_800F8B3C.c"),
            Object(Matching, "game/game_fn_800F8BAC.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game___flush_buffer.c"),
            Object(Matching, "game/game___prep_buffer.c"),
            Object(Matching, "game/game_fn_800F8CF0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F8D14.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F8D2C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F8D44.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F8D5C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F8D74.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fwrite.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fseek.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F96C0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game___memrchr.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_memchr.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game___stdio_atexit.c"),
            Object(Matching, "game/game_fn_800F9D4C.c", extra_cflags=["-sdata 0", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_800F9E2C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_vprintf.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F9F20.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800F9FE4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FA0B0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game___FileWrite.c", extra_cflags=["-sdata 0"]),
            # Honest C round-to-even decimal reducer; remaining differences are
            # local allocation and equivalent loop/control-flow spelling.
            Object(NonMatching, "game/game_fn_800FAFD4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FBFA8.c"),
            Object(Matching, "game/game_fn_800FBFB0.c"),
            Object(Matching, "game/game_fn_800FC094.c", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_800FD018.c", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_800FD0C8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FD198.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_strchr.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FD1E8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FD350.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FD39C.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FD3C8.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_strlen.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_800FEC70.c"),
            Object(Matching, "game/game_fwide.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80101960.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80102320.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80102340.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80102360.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80102380.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_801023A0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_801023C0.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_801023E4.c", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80102408.c", extra_cflags=["-sdata 0"]),
            # The image codec cluster is a GC/1.2.5n island. These honest
            # reconstructions retain table initialization, component setup,
            # recursive tree loading, bitstream traversal and buffer sizing;
            # remaining differences are loop unrolling, boolean lowering and
            # local register allocation.
            Object(NonMatching, "game/game_fn_8010242C.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_8010278C.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_801028A8.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_80102C6C.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80106A6C.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80106A8C.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_80106AC0.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_801078C0.c", mw_version="GC/1.2.5n", extra_cflags=["-sdata 0"]),
            Object(Matching, "game/game_fn_80108470.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_80108478.c"),
            Object(Matching, "game/game_fn_801084B0.c"),
            Object(Matching, "game/game_fn_801084E0.c"),
            Object(Matching, "game/game_fn_80108510.c"),
            Object(Matching, "game/game_fn_80108BD4.c"),
            Object(Matching, "game/game_fn_80108C24.c"),
            Object(Matching, "game/game_fn_80109198.c"),
            Object(Matching, "game/game_fn_801093C4.c"),
            Object(Matching, "game/game_fn_801093CC.c"),
            Object(Matching, "game/game_fn_801093D4.c"),
            Object(Matching, "game/game_fn_801093E4.c"),
            Object(Matching, "game/game_fn_801093F4.c"),
            Object(Matching, "game/game_fn_8010940C.c"),
            Object(NonMatching, "game/game_fn_80109424.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80109574.c"),
            Object(Matching, "game/game_fn_80109628.c"),
            Object(Matching, "game/game_fn_801096C4.c"),
            Object(Matching, "game/game_fn_80109790.c"),
            Object(Matching, "game/game_fn_80109868.c"),
            Object(NonMatching, "game/game_fn_801098C0.c"),
            Object(Matching, "game/game_fn_80109AD4.c"),
            Object(Matching, "game/game_fn_80109B24.c"),
            Object(Matching, "game/game_fn_80109B94.c"),
            Object(Matching, "game/game_fn_80109C5C.c"),
            Object(NonMatching, "game/game_fn_80109CB0.c"),
            Object(NonMatching, "game/game_fn_80109D20.c"),
            Object(Matching, "game/game_fn_80109D90.c"),
            Object(Matching, "game/game_fn_80109DBC.c"),
            Object(Matching, "game/game_fn_80109E44.c"),
            Object(Matching, "game/game_fn_80109EEC.c"),
            Object(Matching, "game/game_fn_8010ACF8.c"),
            Object(Matching, "game/game_fn_8010B33C.c"),
            Object(Matching, "game/game_fn_8010B398.c"),
            Object(Matching, "game/game_fn_8010B400.c"),
            Object(Matching, "game/game_fn_8010B45C.c"),
            Object(Matching, "game/game_fn_8010C1CC.c"),
            Object(NonMatching, "game/game_fn_8010D2D4.c"),
            Object(Matching, "game/game_fn_8010DA50.c"),
            Object(Matching, "game/game_fn_8010DA94.c"),
            Object(Matching, "game/game_fn_8010F144.c"),
            Object(Matching, "game/game_fn_8010F148.c"),
            Object(Matching, "game/game_fn_8010F15C.c"),
            Object(Matching, "game/game_fn_8010F168.c"),
            Object(Matching, "game/game_fn_8010F174.c"),
            Object(Matching, "game/game_fn_8010F180.c"),
            Object(Matching, "game/game_fn_8010F184.c"),
            Object(Matching, "game/game_fn_8010F218.c"),
            # Honest periodic controller update; remaining differences are MWCC
            # long-return lowering and local allocation around the query chain.
            Object(NonMatching, "game/game_fn_8010F2A4.c"),
            Object(Matching, "game/game_fn_8010F3DC.c"),
            Object(Matching, "game/game_fn_8010F404.c"),
            # Honest selector test; remaining difference is argument-register
            # scheduling around the three-way selection helper.
            Object(NonMatching, "game/game_fn_8010F8B0.c"),
            Object(Matching, "game/game_fn_8010F930.c"),
            # Honest mode update; remaining differences are two equivalent
            # selection-helper schedules.
            Object(NonMatching, "game/game_fn_8010F9D8.c"),
            # Honest mode dispatch; remaining differences are selection-table
            # argument-register scheduling.
            Object(NonMatching, "game/game_fn_8010FB5C.c"),
            # Honest signed selection cursor update; remaining differences are
            # local allocation and branch scheduling in the bounded scan.
            Object(NonMatching, "game/game_fn_8010FC3C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8010FED4.c"),
            # Large mode dispatcher retained as assembly after bounded triage.
            # Honest event callback reconstruction; remaining differences are
            # saved-register allocation around the selection helpers.
            Object(NonMatching, "game/game_fn_8011038C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80110534.c"),
            Object(Matching, "game/game_fn_801116A4.c"),
            Object(Matching, "game/game_fn_80111724.c"),
            Object(Matching, "game/game_fn_80111750.c"),
            Object(Matching, "game/game_fn_80111780.c"),
            Object(Matching, "game/game_fn_801118E8.c"),
            Object(Matching, "game/game_fn_80111BB0.c"),
            Object(Matching, "game/game_fn_80112230.c"),
            Object(Matching, "game/game_fn_80112258.c"),
            Object(Matching, "game/game_fn_80112614.c"),
            Object(Matching, "game/game_fn_8011261C.c"),
            Object(Matching, "game/game_fn_801126E0.c"),
            # Honest behavior-complete C; MWCC coalesces the item/horizontal
            # live ranges instead of retaining retail's r28-r30 allocation.
            Object(NonMatching, "game/game_fn_80112754.c"),
            Object(Matching, "game/game_fn_801128AC.c"),
            Object(Matching, "game/game_fn_801128E4.c"),
            Object(Matching, "game/game_fn_80112928.c"),
            Object(Matching, "game/game_fn_801132B8.c"),
            Object(Matching, "game/game_fn_801139D4.c"),
            Object(Matching, "game/game_fn_80113AB8.c"),
            Object(Matching, "game/game_fn_80113B50.c"),
            Object(Matching, "game/game_fn_80113B64.c"),
            Object(Matching, "game/game_fn_80113BA8.c"),
            Object(Matching, "game/game_fn_80113CF8.c"),
            Object(Matching, "game/game_fn_80113D50.c"),
            # Honest table search; the retail unroll assigns shape/entry to
            # r7/r6 while this compiler source shape assigns them to r6/r7.
            Object(NonMatching, "game/game_fn_80113E48.c"),
            Object(Matching, "game/game_fn_80113F54.c"),
            Object(Matching, "game/game_fn_80114048.c"),
            Object(Matching, "game/game_fn_801141B8.c"),
            Object(Matching, "game/game_fn_80117A7C.c"),
            Object(Matching, "game/game_fn_80117AAC.c"),
            Object(Matching, "game/game_fn_80117E58.c"),
            Object(Matching, "game/game_fn_80117EC8.c"),
            Object(NonMatching, "game/game_fn_80117EF0.c"),
            Object(Matching, "game/game_fn_80117F30.c"),
            Object(Matching, "game/game_fn_80117FA0.c"),
            Object(Matching, "game/game_fn_80117FDC.c"),
            Object(Matching, "game/game_fn_8011804C.c"),
            Object(Matching, "game/game_fn_80118060.c"),
            Object(Matching, "game/game_fn_80118080.c"),
            Object(Matching, "game/game_fn_801180A8.c"),
            Object(Matching, "game/game_fn_8011824C.c"),
            Object(Matching, "game/game_fn_80118288.c"),
            Object(Matching, "game/game_fn_80118340.c"),
            # Size-exact behavior-complete C; the remaining eight differences
            # are equivalent volatile-register and indexed-address choices.
            Object(NonMatching, "game/game_fn_80118370.c"),
            Object(Matching, "game/game_fn_80118528.c"),
            Object(Matching, "game/game_fn_8011857C.c"),
            Object(NonMatching, "game/game_fn_80118670.c"),
            Object(Matching, "game/game_fn_80119550.c"),
            Object(Matching, "game/game_fn_80119BEC.c"),
            Object(Matching, "game/game_fn_80119C2C.c"),
            Object(NonMatching, "game/game_fn_80119C70.c"),
            Object(NonMatching, "game/game_fn_80119DB4.c"),
            Object(Matching, "game/game_fn_80119E3C.c"),
            Object(Matching, "game/game_fn_80119E90.c"),
            Object(Matching, "game/game_fn_80119ED4.c"),
            Object(Matching, "game/game_fn_80119F6C.c"),
            Object(Matching, "game/game_fn_8011A79C.c"),
            Object(Matching, "game/game_fn_8011B734.c"),
            Object(Matching, "game/game_fn_8011B740.c"),
            Object(Matching, "game/game_fn_8011B74C.c"),
            Object(Matching, "game/game_fn_8011B864.c"),
            Object(Matching, "game/game_fn_8011B86C.c"),
            Object(Matching, "game/game_fn_8011BA1C.c"),
            Object(Matching, "game/game_fn_8011BB48.c"),
            Object(Matching, "game/game_fn_8011BB88.c"),
            Object(Matching, "game/game_fn_8011BBB8.c"),
            Object(Matching, "game/game_fn_8011BBE8.c"),
            Object(Matching, "game/game_fn_8011BCC0.c"),
            Object(Matching, "game/game_fn_8011BCF0.c"),
            Object(Matching, "game/game_fn_8011BD20.c"),
            Object(Matching, "game/game_fn_8011C028.c"),
            # Size-exact honest C; remaining differences are indexed halfword
            # load scheduling and the equivalent r8/r10 argument allocation.
            Object(NonMatching, "game/game_fn_8011C0F0.c"),
            Object(Matching, "game/game_fn_8011C1AC.c"),
            Object(Matching, "game/game_fn_8011C1F8.c"),
            Object(Matching, "game/game_fn_8011C22C.c"),
            Object(Matching, "game/game_fn_8011C274.c"),
            Object(Matching, "game/game_fn_8011C348.c"),
            Object(Matching, "game/game_fn_8011C3E4.c"),
            Object(Matching, "game/game_fn_8011C428.c"),
            Object(Matching, "game/game_fn_8011C468.c"),
            Object(Matching, "game/game_fn_8011C4D8.c"),
            # Honest C; MWCC materializes the initial zero in r6 rather than
            # reusing the later r3, leaving one extra instruction.
            Object(NonMatching, "game/game_fn_8011C6BC.c"),
            Object(Matching, "game/game_fn_8011C798.c"),
            Object(Matching, "game/game_fn_8011C830.c"),
            Object(Matching, "game/game_fn_8011CC20.c"),
            Object(Matching, "game/game_fn_8011CD00.c"),
            Object(Matching, "game/game_fn_8011CD98.c"),
            Object(Matching, "game/game_fn_8011CDD4.c"),
            Object(Matching, "game/game_fn_8011CE1C.c"),
            Object(Matching, "game/game_fn_8011CEF4.c"),
            Object(Matching, "game/game_fn_8011CFF8.c"),
            Object(Matching, "game/game_fn_8011D36C.c"),
            Object(Matching, "game/game_fn_8011D470.c"),
            Object(Matching, "game/game_fn_8011D558.c"),
            Object(Matching, "game/game_fn_8011D5C0.c"),
            Object(Matching, "game/game_fn_8011D604.c"),
            Object(Matching, "game/game_fn_8011D638.c"),
            Object(Matching, "game/game_fn_8011D698.c"),
            Object(Matching, "game/game_fn_8011D6DC.c"),
            Object(Matching, "game/game_fn_8011D724.c"),
            Object(Matching, "game/game_fn_8011D804.c"),
            Object(Matching, "game/game_fn_8011DD74.c"),
            Object(Matching, "game/game_fn_8011DD78.c"),
            Object(Matching, "game/game_fn_8011DD8C.c"),
            Object(Matching, "game/game_fn_8011DF6C.c"),
            Object(Matching, "game/game_fn_8011DFA8.c"),
            Object(Matching, "game/game_fn_8011E174.c"),
            Object(Matching, "game/game_fn_8011E190.c"),
            Object(Matching, "game/game_fn_8011E19C.c"),
            Object(Matching, "game/game_fn_8011E1B8.c"),
            Object(Matching, "game/game_fn_8011E1C4.c"),
            Object(Matching, "game/game_fn_8011E234.c"),
            Object(Matching, "game/game_fn_8011E26C.c"),
            Object(Matching, "game/game_fn_8011E7E8.c"),
            Object(Matching, "game/game_fn_8011E800.c"),
            Object(Matching, "game/game_fn_8011E824.c"),
            Object(Matching, "game/game_fn_8011E83C.c"),
            Object(Matching, "game/game_fn_8011E84C.c"),
            Object(Matching, "game/game_fn_8011E85C.c"),
            Object(Matching, "game/game_fn_8011E86C.c"),
            Object(Matching, "game/game_fn_8011E87C.c"),
            Object(Matching, "game/game_fn_8011E884.c"),
            Object(Matching, "game/game_fn_8011E8D8.c"),
            Object(Matching, "game/game_fn_8011E918.c"),
            Object(Matching, "game/game_fn_8011E98C.c"),
            Object(Matching, "game/game_fn_8011EA00.c"),
            Object(Matching, "game/game_fn_8011EA60.c"),
            Object(Matching, "game/game_fn_8011EAB4.c"),
            Object(Matching, "game/game_fn_8011EAF4.c"),
            Object(Matching, "game/game_fn_8011EAFC.c"),
            Object(Matching, "game/game_fn_8011EB04.c"),
            Object(Matching, "game/game_fn_8011EB0C.c"),
            Object(Matching, "game/game_fn_8011EB14.c"),
            Object(Matching, "game/game_fn_8011EB1C.c"),
            Object(Matching, "game/game_fn_8011EB24.c"),
            Object(Matching, "game/game_fn_8011EBB8.c"),
            Object(Matching, "game/game_fn_8011EBFC.c"),
            Object(NonMatching, "game/game_fn_8011ECF8.c"),
            Object(NonMatching, "game/game_fn_8011EE04.c"),
            Object(Matching, "game/game_fn_8011F0C0.c"),
            Object(Matching, "game/game_fn_8011F0E8.c"),
            Object(Matching, "game/game_fn_8011F104.c"),
            Object(Matching, "game/game_fn_8011F114.c"),
            Object(Matching, "game/game_fn_8011F130.c"),
            Object(Matching, "game/game_fn_8011F134.c"),
            Object(NonMatching, "game/game_fn_8011F140.c"),
            Object(Matching, "game/game_fn_8011F220.c"),
            Object(Matching, "game/game_fn_8011F244.c"),
            Object(Matching, "game/game_fn_8011F2B8.c"),
            Object(Matching, "game/game_fn_8011F304.c"),
            Object(Matching, "game/game_fn_8011F3B4.c"),
            Object(NonMatching, "game/game_fn_8011F41C.c"),
            Object(Matching, "game/game_fn_8011F574.c"),
            Object(NonMatching, "game/game_fn_8011F598.c"),
            Object(Matching, "game/game_fn_8011F6A4.c"),
            Object(Matching, "game/game_fn_8011F6F0.c"),
            Object(Matching, "game/game_fn_8011F6F8.c"),
            Object(Matching, "game/game_fn_8011F700.c"),
            Object(Matching, "game/game_fn_8011F760.c"),
            Object(Matching, "game/game_fn_8011F768.c"),
            Object(Matching, "game/game_fn_8011F770.c"),
            Object(Matching, "game/game_fn_8011F778.c"),
            Object(Matching, "game/game_fn_8011F788.c"),
            Object(Matching, "game/game_fn_8011F798.c"),
            Object(Matching, "game/game_fn_8011F7A0.c"),
            Object(Matching, "game/game_fn_8011F7BC.c"),
            Object(Matching, "game/game_fn_8011F7D8.c"),
            Object(NonMatching, "game/game_fn_8011F7E0.c"),
            Object(NonMatching, "game/game_fn_8011F808.c"),
            Object(NonMatching, "game/game_fn_8011F890.c"),
            Object(Matching, "game/game_fn_8011F8FC.c"),
            Object(Matching, "game/game_fn_8011F904.c"),
            Object(Matching, "game/game_fn_8011F90C.c"),
            Object(Matching, "game/game_fn_8011F918.c"),
            Object(Matching, "game/game_fn_8011F938.c"),
            Object(Matching, "game/game_fn_8011F948.c"),
            Object(Matching, "game/game_fn_8011F950.c"),
            Object(Matching, "game/game_fn_8011F958.c"),
            Object(Matching, "game/game_fn_8011F9E4.c"),
            Object(Matching, "game/game_fn_8011F9F8.c"),
            Object(Matching, "game/game_fn_8011FA40.c"),
            Object(Matching, "game/game_fn_8011FA4C.c"),
            Object(Matching, "game/game_fn_8011FA60.c"),
            Object(Matching, "game/game_fn_8011FA6C.c"),
            Object(Matching, "game/game_fn_8011FA7C.c"),
            Object(Matching, "game/game_fn_8011FA8C.c"),
            Object(Matching, "game/game_fn_8011FAAC.c"),
            Object(Matching, "game/game_fn_8011FABC.c"),
            Object(Matching, "game/game_fn_8011FADC.c"),
            Object(Matching, "game/game_fn_8011FAEC.c"),
            Object(Matching, "game/game_fn_8011FAF4.c"),
            Object(Matching, "game/game_fn_8011FAFC.c"),
            Object(Matching, "game/game_fn_8011FB24.c"),
            Object(Matching, "game/game_fn_8011FB3C.c"),
            Object(Matching, "game/game_fn_8011FB44.c"),
            Object(Matching, "game/game_fn_8011FB4C.c"),
            Object(Matching, "game/game_fn_8011FB54.c"),
            Object(Matching, "game/game_fn_8011FB5C.c"),
            Object(Matching, "game/game_fn_8011FB6C.c"),
            Object(Matching, "game/game_fn_8011FBC4.c"),
            Object(Matching, "game/game_fn_8011FBD0.c"),
            Object(Matching, "game/game_fn_8011FC38.c"),
            Object(Matching, "game/game_fn_8011FCB0.c"),
            Object(Matching, "game/game_fn_8011FCE4.c"),
            Object(Matching, "game/game_fn_8011FCEC.c"),
            Object(Matching, "game/game_fn_8011FCF4.c"),
            Object(Matching, "game/game_fn_8011FD64.c"),
            Object(Matching, "game/game_fn_8011FDF0.c"),
            Object(Matching, "game/game_fn_8011FE34.c"),
            Object(Matching, "game/game_fn_8011FE3C.c"),
            Object(Matching, "game/game_fn_8011FE4C.c"),
            Object(Matching, "game/game_fn_8011FE54.c"),
            Object(Matching, "game/game_fn_8011FE5C.c"),
            Object(Matching, "game/game_fn_8011FE64.c"),
            Object(Matching, "game/game_fn_8011FE6C.c"),
            Object(Matching, "game/game_fn_8011FED4.c"),
            Object(Matching, "game/game_fn_8011FEDC.c"),
            Object(Matching, "game/game_fn_8011FEE4.c"),
            Object(Matching, "game/game_fn_8011FEEC.c"),
            Object(Matching, "game/game_fn_8011FEF4.c"),
            Object(Matching, "game/game_fn_8011FEFC.c"),
            Object(Matching, "game/game_fn_8011FF04.c"),
            Object(Matching, "game/game_fn_8011FF0C.c"),
            Object(Matching, "game/game_fn_8011FF18.c"),
            Object(Matching, "game/game_fn_8011FF24.c"),
            Object(Matching, "game/game_fn_8011FF30.c"),
            Object(Matching, "game/game_fn_8011FF38.c"),
            Object(
                Matching,
                "game/game_fn_8011FF40.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801204E0.c"),
            Object(Matching, "game/game_fn_8012070C.c"),
            Object(Matching, "game/game_fn_8012072C.c"),
            Object(NonMatching, "game/game_fn_80120874.c"),
            Object(Matching, "game/game_fn_801208AC.c"),
            Object(NonMatching, "game/game_fn_801208CC.c"),
            Object(Matching, "game/game_fn_801209DC.c"),
            Object(Matching, "game/game_fn_80120A30.c"),
            Object(Matching, "game/game_fn_80120AD0.c"),
            Object(Matching, "game/game_fn_80120B4C.c"),
            Object(NonMatching, "game/game_fn_80120B58.c"),
            Object(Matching, "game/game_fn_80120BD0.c"),
            Object(Matching, "game/game_fn_80121104.c"),
            Object(Matching, "game/game_fn_8012110C.c"),
            Object(Matching, "game/game_fn_80121EC0.c"),
            Object(Matching, "game/game_fn_801225DC.c"),
            Object(Matching, "game/game_fn_8012260C.c"),
            Object(NonMatching, "game/game_fn_80122638.c"),
            Object(Matching, "game/game_fn_80123198.c"),
            Object(Matching, "game/game_fn_8012319C.c"),
            Object(Matching, "game/game_fn_801231AC.c"),
            Object(Matching, "game/game_fn_801231C0.c"),
            Object(Matching, "game/game_fn_8012343C.c"),
            Object(
                NonMatching,
                "game/game_fn_801235E4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80123708.c"),
            Object(Matching, "game/game_fn_80124128.c"),
            Object(NonMatching, "game/game_fn_80124664.c"),
            Object(NonMatching, "game/game_fn_80124750.c"),
            Object(NonMatching, "game/game_fn_801247F8.c"),
            Object(Matching, "game/game_fn_801248FC.c"),
            Object(
                NonMatching,
                "game/game_fn_80124A40.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(NonMatching, "game/game_fn_80124DBC.c"),
            Object(Matching, "game/game_fn_80125284.c"),
            Object(Matching, "game/game_fn_801252D8.c"),
            Object(NonMatching, "game/game_fn_80125664.c"),
            Object(Matching, "game/game_fn_80125D1C.c"),
            Object(NonMatching, "game/game_fn_80125D50.c"),
            Object(Matching, "game/game_fn_80125D88.c"),
            Object(Matching, "game/game_fn_80125DC8.c"),
            Object(Matching, "game/game_fn_80125DD0.c"),
            Object(NonMatching, "game/game_fn_80125DE0.c"),
            Object(Matching, "game/game_fn_80125EB8.c"),
            Object(Matching, "game/game_fn_80125FE4.c"),
            Object(Matching, "game/game_fn_80126050.c"),
            Object(Matching, "game/game_fn_80126070.c"),
            Object(NonMatching, "game/game_fn_80126084.c"),
            Object(Matching, "game/game_fn_801261C4.c"),
            Object(Matching, "game/game_fn_801261E8.c"),
            Object(Matching, "game/game_fn_80126718.c"),
            Object(Matching, "game/game_fn_8012671C.c"),
            Object(Matching, "game/game_fn_80126880.c"),
            Object(Matching, "game/game_fn_8012692C.c"),
            Object(NonMatching, "game/game_fn_80126A00.c"),
            Object(NonMatching, "game/game_fn_80126E80.c"),
            Object(NonMatching, "game/game_fn_80126FE0.c"),
            Object(NonMatching, "game/game_fn_801270DC.c"),
            Object(Matching, "game/game_fn_80127128.c"),
            Object(NonMatching, "game/game_fn_80127178.c"),
            Object(Matching, "game/game_fn_80127208.c"),
            Object(NonMatching, "game/game_fn_8012744C.c"),
            Object(NonMatching, "game/game_fn_801274F4.c"),
            Object(Matching, "game/game_fn_80127658.c"),
            Object(Matching, "game/game_fn_80127F90.c"),
            Object(Matching, "game/game_fn_80127FD8.c"),
            Object(Matching, "game/game_fn_80128058.c"),
            Object(Matching, "game/game_fn_80128228.c"),
            Object(Matching, "game/game_fn_801285C0.c"),
            Object(Matching, "game/game_fn_801285CC.c"),
            Object(Matching, "game/game_fn_801285D8.c"),
            Object(Matching, "game/game_fn_801285F8.c"),
            Object(Matching, "game/game_fn_80128600.c"),
            Object(Matching, "game/game_fn_80128608.c"),
            Object(Matching, "game/game_fn_80128610.c"),
            Object(Matching, "game/game_fn_80128618.c"),
            Object(Matching, "game/game_fn_80128754.c"),
            Object(Matching, "game/game_fn_801287B0.c"),
            Object(Matching, "game/game_fn_801287C0.c"),
            Object(Matching, "game/game_fn_801287C4.c"),
            Object(Matching, "game/game_fn_8012880C.c"),
            Object(Matching, "game/game_fn_801288DC.c"),
            Object(Matching, "game/game_fn_801289A0.c"),
            Object(Matching, "game/game_fn_80128A84.c"),
            Object(Matching, "game/game_fn_80128AB8.c"),
            Object(Matching, "game/game_fn_80128B10.c"),
            Object(Matching, "game/game_fn_80128B34.c"),
            Object(Matching, "game/game_fn_80128B8C.c"),
            Object(Matching, "game/game_fn_80128BE4.c"),
            Object(Matching, "game/game_fn_80128C28.c"),
            Object(Matching, "game/game_fn_80128C34.c"),
            Object(Matching, "game/game_fn_80128C3C.c"),
            Object(Matching, "game/game_fn_80128C44.c"),
            Object(NonMatching, "game/game_fn_80128C50.c"),
            Object(Matching, "game/game_fn_80128DA8.c"),
            Object(Matching, "game/game_fn_80128DCC.c"),
            Object(Matching, "game/game_fn_80128E30.c"),
            Object(Matching, "game/game_fn_80128E6C.c"),
            Object(Matching, "game/game_fn_80128EAC.c"),
            Object(Matching, "game/game_fn_80128EE4.c"),
            Object(Matching, "game/game_fn_80128F40.c"),
            Object(Matching, "game/game_fn_801290D0.c"),
            Object(Matching, "game/game_fn_80129108.c"),
            Object(Matching, "game/game_fn_8012915C.c"),
            Object(Matching, "game/game_fn_80129190.c"),
            Object(Matching, "game/game_fn_801291C4.c"),
            Object(Matching, "game/game_fn_801291CC.c"),
            Object(Matching, "game/game_fn_801291F0.c"),
            Object(Matching, "game/game_fn_80129228.c"),
            Object(Matching, "game/game_fn_80129258.c"),
            Object(Matching, "game/game_fn_8012927C.c"),
            Object(Matching, "game/game_fn_801292E0.c"),
            Object(Matching, "game/game_fn_80129334.c"),
            Object(Matching, "game/game_fn_80129364.c"),
            Object(NonMatching, "game/game_fn_8012939C.c"),
            Object(Matching, "game/game_fn_8012948C.c"),
            Object(Matching, "game/game_fn_801294DC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801295E8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012965C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801296E8.c"),
            Object(Matching, "game/game_fn_801296F8.c"),
            Object(Matching, "game/game_fn_80129748.c"),
            Object(NonMatching, "game/game_fn_8012976C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80129878.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80129928.c"),
            Object(Matching, "game/game_fn_8012998C.c"),
            Object(Matching, "game/game_fn_801299DC.c"),
            Object(NonMatching, "game/game_fn_80129A00.c"),
            Object(Matching, "game/game_fn_80129AF4.c"),
            Object(Matching, "game/game_fn_80129BA4.c"),
            Object(Matching, "game/game_fn_80129BE4.c"),
            Object(NonMatching, "game/game_fn_80129C2C.c"),
            Object(Matching, "game/game_fn_80129CE8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80129D54.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012A100.c"),
            Object(Matching, "game/game_fn_8012A13C.c"),
            Object(Matching, "game/game_fn_8012A1BC.c"),
            Object(Matching, "game/game_fn_8012A1FC.c"),
            Object(Matching, "game/game_fn_8012A23C.c"),
            Object(Matching, "game/game_fn_8012A244.c"),
            Object(Matching, "game/game_fn_8012A24C.c"),
            Object(Matching, "game/game_fn_8012A72C.c"),
            Object(Matching, "game/game_fn_8012AB2C.c"),
            Object(Matching, "game/game_fn_8012ABEC.c"),
            Object(NonMatching, "game/game_fn_8012AC74.c"),
            Object(Matching, "game/game_fn_8012ADA4.c"),
            Object(Matching, "game/game_fn_8012AFC4.c"),
            Object(Matching, "game/game_fn_8012AFE8.c"),
            Object(Matching, "game/game_fn_8012B018.c"),
            Object(NonMatching, "game/game_fn_8012B070.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012B290.c"),
            Object(Matching, "game/game_fn_8012B324.c"),
            Object(Matching, "game/game_fn_8012B344.c"),
            Object(Matching, "game/game_fn_8012B388.c"),
            Object(NonMatching, "game/game_fn_8012B408.c"),
            Object(NonMatching, "game/game_fn_8012B62C.c"),
            Object(Matching, "game/game_fn_8012B690.c"),
            Object(Matching, "game/game_fn_8012B6FC.c"),
            Object(NonMatching, "game/game_fn_8012B750.c"),
            Object(Matching, "game/game_fn_8012B7A0.c"),
            Object(Matching, "game/game_fn_8012B7D0.c"),
            Object(Matching, "game/game_fn_8012B814.c"),
            Object(Matching, "game/game_fn_8012B820.c"),
            Object(Matching, "game/game_fn_8012B830.c"),
            Object(Matching, "game/game_fn_8012B89C.c"),
            Object(NonMatching, "game/game_fn_8012B8A8.c"),
            Object(Matching, "game/game_fn_8012B954.c"),
            Object(Matching, "game/game_fn_8012B9C8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012BA28.c"),
            Object(Matching, "game/game_fn_8012BA84.c"),
            Object(Matching, "game/game_fn_8012BB34.c"),
            Object(Matching, "game/game_fn_8012BBE4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012BC98.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8012BD4C.c"),
            Object(NonMatching, "game/game_fn_8012BDCC.c"),
            Object(NonMatching, "game/game_fn_8012BE18.c"),
            Object(NonMatching, "game/game_fn_8012BE64.c"),
            Object(NonMatching, "game/game_fn_8012BE78.c"),
            Object(Matching, "game/game_fn_8012BE8C.c"),
            Object(Matching, "game/game_fn_8012C0A8.c"),
            Object(Matching, "game/game_fn_8012C108.c"),
            Object(Matching, "game/game_fn_8012C198.c"),
            Object(Matching, "game/game_fn_8012C1F8.c"),
            Object(Matching, "game/game_fn_8012C278.c"),
            Object(Matching, "game/game_fn_8012C2D0.c"),
            Object(Matching, "game/game_fn_8012C328.c"),
            Object(Matching, "game/game_fn_8012C370.c"),
            Object(NonMatching, "game/game_fn_8012C3B8.c"),
            Object(Matching, "game/game_fn_8012C438.c"),
            Object(Matching, "game/game_fn_8012C444.c"),
            Object(Matching, "game/game_fn_8012C458.c"),
            Object(Matching, "game/game_fn_8012C46C.c"),
            Object(Matching, "game/game_fn_8012C478.c"),
            Object(Matching, "game/game_fn_8012C5B0.c"),
            Object(NonMatching, "game/game_fn_8012C62C.c"),
            Object(NonMatching, "game/game_fn_8012C774.c"),
            Object(NonMatching, "game/game_fn_8012C804.c"),
            Object(Matching, "game/game_fn_8012CAC4.c"),
            Object(Matching, "game/game_fn_8012CB60.c"),
            Object(Matching, "game/game_fn_8012CBE8.c"),
            Object(Matching, "game/game_fn_8012CCF0.c"),
            Object(Matching, "game/game_fn_8012CDF0.c"),
            Object(Matching, "game/game_fn_8012CEA4.c"),
            Object(NonMatching, "game/game_fn_8012CF08.c"),
            Object(Matching, "game/game_fn_8012D01C.c"),
            Object(Matching, "game/game_fn_8012D074.c"),
            Object(Matching, "game/game_fn_8012D66C.c"),
            Object(Matching, "game/game_fn_8012D6C4.c"),
            Object(Matching, "game/game_fn_8012D7AC.c"),
            Object(Matching, "game/game_fn_8012D9D4.c"),
            Object(Matching, "game/game_fn_8012DA44.c"),
            Object(Matching, "game/game_fn_8012DB28.c"),
            Object(Matching, "game/game_fn_8012DBE8.c"),
            Object(Matching, "game/game_fn_8012DC80.c"),
            Object(Matching, "game/game_fn_8012DC94.c"),
            Object(Matching, "game/game_fn_8012E114.c"),
            Object(Matching, "game/game_fn_8012E19C.c"),
            Object(NonMatching, "game/game_fn_8012E200.c"),
            Object(Matching, "game/game_fn_8012E3AC.c"),
            Object(Matching, "game/game_fn_8012E42C.c"),
            Object(Matching, "game/game_fn_8012E498.c"),
            Object(Matching, "game/game_fn_8012E504.c"),
            Object(Matching, "game/game_fn_8012E524.c"),
            Object(Matching, "game/game_fn_8012F58C.c"),
            Object(Matching, "game/game_fn_8012F604.c"),
            Object(Matching, "game/game_fn_8012F674.c"),
            Object(Matching, "game/game_fn_8012F6E8.c"),
            Object(NonMatching, "game/game_fn_8012F700.c"),
            Object(NonMatching, "game/game_fn_8012F7D4.c"),
            Object(NonMatching, "game/game_fn_8012F8CC.c"),
            Object(Matching, "game/game_fn_8012FA54.c"),
            Object(Matching, "game/game_fn_8012FAB4.c"),
            Object(Matching, "game/game_fn_8012FB2C.c"),
            Object(NonMatching, "game/game_fn_8012FB50.c"),
            Object(Matching, "game/game_fn_8012FBF4.c"),
            Object(Matching, "game/game_fn_8012FCB0.c"),
            Object(Matching, "game/game_fn_8012FD1C.c"),
            Object(Matching, "game/game_fn_8012FDA0.c"),
            Object(Matching, "game/game_fn_8012FE10.c"),
            Object(Matching, "game/game_fn_8012FEC8.c"),
            Object(NonMatching, "game/game_fn_8012FF34.c"),
            Object(Matching, "game/game_fn_8012FFE0.c"),
            Object(Matching, "game/game_fn_8013009C.c"),
            Object(Matching, "game/game_fn_801300F0.c"),
            Object(Matching, "game/game_fn_80130108.c"),
            Object(Matching, "game/game_fn_80130148.c"),
            Object(Matching, "game/game_fn_8013017C.c"),
            Object(NonMatching, "game/game_fn_801301B0.c"),
            Object(Matching, "game/game_fn_80130214.c"),
            Object(NonMatching, "game/game_fn_80130258.c"),
            Object(Matching, "game/game_fn_801302BC.c"),
            Object(Matching, "game/game_fn_801302FC.c"),
            Object(Matching, "game/game_fn_8013033C.c"),
            Object(Matching, "game/game_fn_8013037C.c"),
            Object(Matching, "game/game_fn_801303BC.c"),
            Object(Matching, "game/game_fn_801303F0.c"),
            Object(Matching, "game/game_fn_8013041C.c"),
            Object(Matching, "game/game_fn_80130428.c"),
            Object(NonMatching, "game/game_fn_80130434.c"),
            Object(Matching, "game/game_fn_8013057C.c"),
            Object(Matching, "game/game_fn_801305D4.c"),
            Object(Matching, "game/game_fn_80130670.c"),
            Object(Matching, "game/game_fn_80130718.c"),
            Object(NonMatching, "game/game_fn_80130720.c"),
            Object(Matching, "game/game_fn_80130980.c"),
            Object(Matching, "game/game_fn_80130984.c"),
            Object(Matching, "game/game_fn_80130998.c"),
            Object(Matching, "game/game_fn_801312C0.c"),
            Object(Matching, "game/game_fn_8013133C.c"),
            Object(Matching, "game/game_fn_80131388.c"),
            Object(Matching, "game/game_fn_801313D8.c"),
            Object(Matching, "game/game_fn_801313EC.c"),
            Object(Matching, "game/game_fn_80131408.c"),
            Object(Matching, "game/game_fn_80131458.c"),
            Object(NonMatching, "game/game_fn_80131460.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013196C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80131A28.c"),
            Object(Matching, "game/game_fn_80131AA8.c"),
            Object(NonMatching, "game/game_fn_80131E8C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80132794.c"),
            Object(Matching, "game/game_fn_801328D4.c"),
            Object(Matching, "game/game_fn_80132A4C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80132B24.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80132C24.c"),
            Object(Matching, "game/game_fn_80132C94.c"),
            Object(Matching, "game/game_fn_80132D50.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801332E0.c"),
            Object(Matching, "game/game_fn_801332E8.c"),
            Object(Matching, "game/game_fn_801332F0.c"),
            Object(Matching, "game/game_fn_80133300.c"),
            Object(NonMatching, "game/game_fn_801333CC.c"),
            Object(NonMatching, "game/game_fn_80133510.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80133C20.c"),
            Object(Matching, "game/game_fn_80133EC0.c"),
            Object(Matching, "game/game_fn_80134210.c"),
            Object(NonMatching, "game/game_fn_80134EB0.c"),
            Object(NonMatching, "game/game_fn_80134F08.c"),
            Object(Matching, "game/game_fn_80134F7C.c"),
            Object(Matching, "game/game_fn_80134FD8.c"),
            Object(Matching, "game/game_fn_80134FF8.c"),
            Object(NonMatching, "game/game_fn_8013507C.c"),
            Object(Matching, "game/game_fn_8013523C.c"),
            Object(Matching, "game/game_fn_8013530C.c"),
            Object(Matching, "game/game_fn_8013535C.c"),
            Object(NonMatching, "game/game_fn_801353AC.c"),
            Object(Matching, "game/game_fn_801354A0.c"),
            Object(NonMatching, "game/game_fn_80135510.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80135748.c"),
            Object(Matching, "game/game_fn_801358AC.c"),
            Object(Matching, "game/game_fn_801358B4.c"),
            Object(Matching, "game/game_fn_801358C4.c"),
            Object(Matching, "game/game_fn_801358D0.c"),
            Object(Matching, "game/game_fn_80135968.c"),
            Object(Matching, "game/game_fn_80135970.c"),
            Object(Matching, "game/game_fn_801359B8.c"),
            Object(Matching, "game/game_fn_80135A38.c"),
            Object(NonMatching, "game/game_fn_80135A40.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80137DD4.c"),
            Object(Matching, "game/game_fn_80137E04.c"),
            Object(Matching, "game/game_fn_80137E60.c"),
            Object(Matching, "game/game_fn_80137ED0.c"),
            Object(NonMatching, "game/game_fn_80137EFC.c"),
            Object(Matching, "game/game_fn_80137FB8.c"),
            Object(Matching, "game/game_fn_801380EC.c"),
            Object(Matching, "game/game_fn_80138164.c"),
            Object(NonMatching, "game/game_fn_8013816C.c"),
            Object(Matching, "game/game_fn_80138224.c"),
            Object(Matching, "game/game_fn_8013824C.c"),
            Object(Matching, "game/game_fn_801382B4.c"),
            Object(NonMatching, "game/game_fn_801383B4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80138568.c"),
            Object(Matching, "game/game_fn_80138614.c"),
            Object(Matching, "game/game_fn_80138624.c"),
            Object(Matching, "game/game_fn_8013864C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801386C8.c"),
            Object(Matching, "game/game_fn_801386FC.c"),
            Object(Matching, "game/game_fn_80138778.c"),
            Object(Matching, "game/game_fn_801387E4.c"),
            Object(Matching, "game/game_fn_801387EC.c"),
            Object(Matching, "game/game_fn_80138860.c"),
            Object(Matching, "game/game_fn_80138894.c"),
            Object(Matching, "game/game_fn_801388F8.c"),
            Object(NonMatching, "game/game_fn_80138950.c"),
            Object(Matching, "game/game_fn_8013898C.c"),
            Object(Matching, "game/game_fn_80138994.c"),
            Object(NonMatching, "game/game_fn_80138A6C.c"),
            Object(NonMatching, "game/game_fn_80138B90.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80138CD4.c"),
            Object(Matching, "game/game_fn_80138D2C.c"),
            Object(Matching, "game/game_fn_80138DB4.c"),
            Object(Matching, "game/game_fn_80138E58.c"),
            Object(Matching, "game/game_fn_80138E64.c"),
            Object(Matching, "game/game_fn_80138E9C.c"),
            Object(Matching, "game/game_fn_80138F78.c"),
            Object(NonMatching, "game/game_fn_80138FE4.c"),
            Object(Matching, "game/game_fn_801390D4.c"),
            Object(NonMatching, "game/game_fn_8013915C.c"),
            Object(Matching, "game/game_fn_801391AC.c"),
            Object(NonMatching, "game/game_fn_801391D4.c"),
            Object(Matching, "game/game_fn_80139298.c"),
            Object(NonMatching, "game/game_fn_801392A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80139464.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801396A4.c"),
            Object(NonMatching, "game/game_fn_8013977C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801397F8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80139940.c"),
            Object(NonMatching, "game/game_fn_801399CC.c"),
            Object(NonMatching, "game/game_fn_80139B1C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80139C1C.c"),
            Object(Matching, "game/game_fn_80139C74.c"),
            Object(Matching, "game/game_fn_80139CFC.c"),
            Object(Matching, "game/game_fn_80139D10.c"),
            Object(Matching, "game/game_fn_80139D88.c"),
            Object(Matching, "game/game_fn_80139DD4.c"),
            Object(Matching, "game/game_fn_80139E04.c"),
            Object(Matching, "game/game_fn_80139E18.c"),
            Object(Matching, "game/game_fn_80139E20.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80139F28.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013A140.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013A3C8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013A538.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013AD48.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013B178.c"),
            Object(Matching, "game/game_fn_8013B798.c"),
            Object(Matching, "game/game_fn_8013B83C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013B8C0.c"),
            Object(Matching, "game/game_fn_8013B920.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013B9DC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013C050.c"),
            Object(Matching, "game/game_fn_8013C054.c"),
            Object(Matching, "game/game_fn_8013C264.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013C35C.c"),
            Object(NonMatching, "game/game_fn_8013C418.c"),
            Object(NonMatching, "game/game_fn_8013C460.c"),
            Object(NonMatching, "game/game_fn_8013C518.c"),
            Object(NonMatching, "game/game_fn_8013C7BC.c"),
            Object(Matching, "game/game_fn_8013C894.c"),
            Object(Matching, "game/game_fn_8013C8F0.c"),
            Object(Matching, "game/game_fn_8013C964.c"),
            Object(NonMatching, "game/game_fn_8013C9C4.c"),
            Object(NonMatching, "game/game_fn_8013CBE4.c"),
            Object(Matching, "game/game_fn_8013D618.c"),
            Object(NonMatching, "game/game_fn_8013D6A4.c"),
            Object(Matching, "game/game_fn_8013D7A8.c"),
            Object(Matching, "game/game_fn_8013D828.c"),
            Object(Matching, "game/game_fn_8013D88C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013D998.c"),
            Object(Matching, "game/game_fn_8013DAA8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013DB8C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013DE44.c"),
            Object(Matching, "game/game_fn_8013DF4C.c"),
            Object(Matching, "game/game_fn_8013E028.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8013E188.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8013E284.c"),
            Object(NonMatching, "game/game_fn_8013E714.c"),
            Object(Matching, "game/game_fn_8013EA5C.c"),
            Object(NonMatching, "game/game_fn_8013EB90.c"),
            Object(Matching, "game/game_fn_8013EF30.c"),
            Object(Matching, "game/game_fn_8013F078.c"),
            Object(Matching, "game/game_fn_8013F25C.c"),
            Object(NonMatching, "game/game_fn_8013F3C0.c"),
            Object(Matching, "game/game_fn_8013F4D0.c"),
            Object(Matching, "game/game_fn_8013F564.c"),
            Object(Matching, "game/game_fn_8013F600.c"),
            Object(Matching, "game/game_fn_8013F680.c"),
            Object(NonMatching, "game/game_fn_8013F6DC.c"),
            Object(Matching, "game/game_fn_8013F760.c"),
            Object(Matching, "game/game_fn_8013F878.c"),
            Object(Matching, "game/game_fn_8013F898.c"),
            Object(NonMatching, "game/game_fn_8013F980.c"),
            Object(Matching, "game/game_fn_8013FBE4.c"),
            Object(NonMatching, "game/game_fn_8013FDB4.c"),
            Object(Matching, "game/game_fn_8013FF44.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80140010.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80140258.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80140408.c"),
            Object(Matching, "game/game_fn_801409A8.c"),
            Object(Matching, "game/game_fn_801409AC.c"),
            Object(NonMatching, "game/game_fn_801409C0.c"),
            Object(NonMatching, "game/game_fn_801409EC.c"),
            Object(NonMatching, "game/game_fn_80140CD8.c"),
            Object(Matching, "game/game_fn_80140E58.c"),
            Object(Matching, "game/game_fn_80140E60.c"),
            Object(Matching, "game/game_fn_80140E68.c"),
            Object(NonMatching, "game/game_fn_80140E70.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80141484.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801415B4.c"),
            Object(NonMatching, "game/game_fn_80141EA8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801420F8.c"),
            Object(Matching, "game/game_fn_80142808.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80142944.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801429A8.c"),
            Object(NonMatching, "game/game_fn_80142A70.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80142FCC.c"),
            Object(Matching, "game/game_fn_80144160.c"),
            Object(Matching, "game/game_fn_80144164.c"),
            Object(Matching, "game/game_fn_80144178.c"),
            Object(Matching, "game/game_fn_801443F4.c"),
            Object(NonMatching, "game/game_fn_80144430.c"),
            Object(Matching, "game/game_fn_80144470.c"),
            Object(Matching, "game/game_fn_801445EC.c"),
            Object(Matching, "game/game_fn_801445F4.c"),
            Object(Matching, "game/game_fn_80144608.c"),
            Object(Matching, "game/game_fn_80144628.c"),
            Object(Matching, "game/game_fn_80144680.c"),
            Object(Matching, "game/game_fn_801446AC.c"),
            Object(Matching, "game/game_fn_801446B4.c"),
            Object(Matching, "game/game_fn_801446C4.c"),
            Object(Matching, "game/game_fn_801446D4.c"),
            Object(Matching, "game/game_fn_801446DC.c"),
            Object(Matching, "game/game_fn_801446E4.c"),
            Object(Matching, "game/game_fn_801446F4.c"),
            Object(Matching, "game/game_fn_801446FC.c"),
            Object(Matching, "game/game_fn_80144710.c"),
            Object(NonMatching, "game/game_fn_80144760.c"),
            Object(NonMatching, "game/game_fn_80144A2C.c"),
            Object(Matching, "game/game_fn_80144C40.c"),
            Object(NonMatching, "game/game_fn_80144C4C.c"),
            Object(Matching, "game/game_fn_80144E78.c"),
            Object(Matching, "game/game_fn_80144EE0.c"),
            Object(Matching, "game/game_fn_80144F48.c"),
            Object(Matching, "game/game_fn_80144F5C.c"),
            Object(NonMatching, "game/game_fn_80144F8C.c"),
            Object(Matching, "game/game_fn_801453FC.c"),
            Object(Matching, "game/game_fn_80145408.c"),
            Object(Matching, "game/game_fn_80145478.c"),
            Object(Matching, "game/game_fn_80145490.c"),
            Object(NonMatching, "game/game_fn_8014549C.c"),
            Object(NonMatching, "game/game_fn_80145754.c"),
            Object(NonMatching, "game/game_fn_80145774.c"),
            Object(Matching, "game/game_fn_80145E3C.c"),
            Object(Matching, "game/game_fn_80145E60.c"),
            Object(NonMatching, "game/game_fn_80145E6C.c"),
            Object(Matching, "game/game_fn_80145EDC.c"),
            Object(Matching, "game/game_fn_80145F54.c"),
            Object(Matching, "game/game_fn_80145FCC.c"),
            Object(Matching, "game/game_fn_80146004.c"),
            Object(Matching, "game/game_fn_80147E64.c"),
            Object(Matching, "game/game_fn_80147E88.c"),
            Object(Matching, "game/game_fn_80148254.c"),
            Object(Matching, "game/game_fn_80148294.c"),
            Object(Matching, "game/game_fn_801482B8.c"),
            Object(NonMatching, "game/game_fn_80148730.c"),
            Object(Matching, "game/game_fn_8014883C.c"),
            Object(Matching, "game/game_fn_80148940.c"),
            Object(Matching, "game/game_fn_80148B98.c"),
            Object(Matching, "game/game_fn_80148BCC.c"),
            Object(Matching, "game/game_fn_80148C0C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80148D08.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80149220.c"),
            Object(Matching, "game/game_fn_80149360.c"),
            Object(Matching, "game/game_fn_8014939C.c"),
            Object(NonMatching, "game/game_fn_801493D4.c"),
            Object(Matching, "game/game_fn_80149524.c"),
            Object(Matching, "game/game_fn_80149590.c"),
            Object(Matching, "game/game_fn_801495FC.c"),
            Object(Matching, "game/game_fn_80149668.c"),
            Object(Matching, "game/game_fn_801496D8.c"),
            Object(Matching, "game/game_fn_80149748.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801497E0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801498AC.c"),
            Object(Matching, "game/game_fn_80149920.c"),
            Object(Matching, "game/game_fn_801499C4.c"),
            Object(Matching, "game/game_fn_80149A68.c"),
            Object(Matching, "game/game_fn_80149B0C.c"),
            Object(Matching, "game/game_fn_80149B38.c"),
            Object(Matching, "game/game_fn_80149B60.c"),
            Object(Matching, "game/game_fn_80149C1C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80149CC4.c"),
            Object(Matching, "game/game_fn_80149D48.c"),
            Object(NonMatching, "game/game_fn_80149D58.c"),
            Object(Matching, "game/game_fn_80149D64.c"),
            Object(Matching, "game/game_fn_80149D98.c"),
            Object(Matching, "game/game_fn_80149E04.c"),
            Object(Matching, "game/game_fn_80149E28.c"),
            Object(Matching, "game/game_fn_80149EB8.c"),
            Object(Matching, "game/game_fn_80149EFC.c"),
            Object(Matching, "game/game_fn_80149F9C.c"),
            Object(Matching, "game/game_fn_80149FCC.c"),
            Object(Matching, "game/game_fn_80149FDC.c"),
            Object(Matching, "game/game_fn_8014A040.c"),
            Object(Matching, "game/game_fn_8014A0A8.c"),
            Object(Matching, "game/game_fn_8014A110.c"),
            Object(Matching, "game/game_fn_8014A178.c"),
            Object(Matching, "game/game_fn_8014A1E4.c"),
            Object(Matching, "game/game_fn_8014A248.c"),
            Object(Matching, "game/game_fn_8014A2AC.c"),
            Object(Matching, "game/game_fn_8014A314.c"),
            Object(NonMatching, "game/game_fn_8014A378.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014A6BC.c"),
            Object(NonMatching, "game/game_fn_8014AA1C.c"),
            Object(NonMatching, "game/game_fn_8014ACDC.c"),
            Object(Matching, "game/game_fn_8014AE54.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014AF38.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014B014.c"),
            Object(NonMatching, "game/game_fn_8014B0F0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014B33C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014B454.c"),
            Object(Matching, "game/game_fn_8014B494.c"),
            Object(NonMatching, "game/game_fn_8014B604.c"),
            Object(NonMatching, "game/game_fn_8014B610.c"),
            Object(Matching, "game/game_fn_8014B738.c"),
            Object(Matching, "game/game_fn_8014B768.c"),
            Object(Matching, "game/game_fn_8014B76C.c"),
            Object(NonMatching, "game/game_fn_8014B7B0.c"),
            Object(Matching, "game/game_fn_8014B888.c"),
            Object(Matching, "game/game_fn_8014B8D0.c"),
            Object(Matching, "game/game_fn_8014B928.c"),
            Object(Matching, "game/game_fn_8014B990.c"),
            Object(NonMatching, "game/game_fn_8014BA14.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014BEC4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014C060.c"),
            Object(NonMatching, "game/game_fn_8014C23C.c"),
            Object(Matching, "game/game_fn_8014C37C.c"),
            Object(NonMatching, "game/game_fn_8014C470.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014C5B0.c"),
            Object(Matching, "game/game_fn_8014C5D4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014C68C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014C7B0.c"),
            Object(Matching, "game/game_fn_8014C7B8.c"),
            Object(Matching, "game/game_fn_8014C7C0.c"),
            Object(Matching, "game/game_fn_8014C87C.c"),
            Object(Matching, "game/game_fn_8014C8F8.c"),
            Object(Matching, "game/game_fn_8014C988.c"),
            Object(Matching, "game/game_fn_8014C9F4.c"),
            Object(NonMatching, "game/game_fn_8014CA98.c"),
            Object(Matching, "game/game_fn_8014CB54.c"),
            Object(Matching, "game/game_fn_8014CB90.c"),
            Object(Matching, "game/game_fn_8014CBC0.c"),
            Object(Matching, "game/game_fn_8014CBE8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014CCB0.c"),
            Object(Matching, "game/game_fn_8014CE98.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014CFF4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014D100.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014D478.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014D98C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014DA68.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014DB5C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014E000.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014E20C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014E33C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014E4C0.c"),
            Object(Matching, "game/game_fn_8014E52C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014EAA4.c"),
            Object(Matching, "game/game_fn_8014EAC4.c"),
            Object(NonMatching, "game/game_fn_8014EB38.c"),
            Object(NonMatching, "game/game_fn_8014EC30.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014ECD8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014F320.c"),
            Object(Matching, "game/game_fn_8014F3A4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014F4CC.c"),
            Object(Matching, "game/game_fn_8014F53C.c"),
            Object(Matching, "game/game_fn_8014F5B8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014F65C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014F700.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014F834.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8014F9D4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014FB80.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014FCF4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8014FE64.c"),
            Object(NonMatching, "game/game_fn_8014FFE0.c"),
            Object(NonMatching, "game/game_fn_80150158.c"),
            Object(NonMatching, "game/game_fn_801501DC.c"),
            Object(NonMatching, "game/game_fn_8015023C.c"),
            Object(Matching, "game/game_fn_801502C0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80150400.c"),
            Object(Matching, "game/game_fn_80150950.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80150A24.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80150F20.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80151600.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80151D00.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152260.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152360.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152404.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152530.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152710.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152838.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8015295C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152A88.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152BCC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80152D84.c"),
            Object(Matching, "game/game_fn_80152E3C.c"),
            Object(Matching, "game/game_fn_80152F04.c"),
            Object(Matching, "game/game_fn_80152F90.c"),
            Object(Matching, "game/game_fn_80153050.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153104.c"),
            Object(Matching, "game/game_fn_80153140.c"),
            Object(Matching, "game/game_fn_8015319C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153250.c"),
            Object(Matching, "game/game_fn_801532B4.c"),
            Object(Matching, "game/game_fn_801533A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153464.c"),
            Object(Matching, "game/game_fn_801534D8.c"),
            Object(NonMatching, "game/game_fn_801535D8.c"),
            Object(Matching, "game/game_fn_80153880.c"),
            Object(Matching, "game/game_fn_80153898.c"),
            Object(Matching, "game/game_fn_80153904.c"),
            Object(NonMatching, "game/game_fn_80153A24.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153D04.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153DF0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80153F00.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80153FD0.c"),
            Object(Matching, "game/game_fn_801540EC.c"),
            Object(Matching, "game/game_fn_80154158.c"),
            Object(Matching, "game/game_fn_801541BC.c"),
            Object(Matching, "game/game_fn_8015424C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80154340.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80154428.c"),
            Object(Matching, "game/game_fn_801544C4.c"),
            Object(Matching, "game/game_fn_80154514.c"),
            Object(Matching, "game/game_fn_80154570.c"),
            Object(Matching, "game/game_fn_801545E4.c"),
            Object(Matching, "game/game_fn_80154754.c"),
            Object(NonMatching, "game/game_fn_801547CC.c"),
            Object(Matching, "game/game_fn_801549A8.c"),
            Object(Matching, "game/game_fn_80154A14.c"),
            Object(Matching, "game/game_fn_80154A98.c"),
            Object(Matching, "game/game_fn_80154B6C.c"),
            Object(Matching, "game/game_fn_80154CB4.c"),
            Object(Matching, "game/game_fn_80154D24.c"),
            Object(NonMatching, "game/game_fn_80154DB4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80154EC0.c"),
            Object(Matching, "game/game_fn_80154F10.c"),
            Object(NonMatching, "game/game_fn_80154F74.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801550C8.c"),
            Object(NonMatching, "game/game_fn_80155158.c"),
            Object(Matching, "game/game_fn_801552AC.c"),
            Object(NonMatching, "game/game_fn_80155330.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801555D4.c"),
            Object(Matching, "game/game_fn_80155644.c"),
            Object(Matching, "game/game_fn_801556DC.c"),
            Object(Matching, "game/game_fn_80155748.c"),
            Object(Matching, "game/game_fn_801557C4.c"),
            Object(Matching, "game/game_fn_80155814.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80155ABC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80155B5C.c"),
            Object(Matching, "game/game_fn_80155BB0.c"),
            Object(Matching, "game/game_fn_80155C88.c"),
            Object(Matching, "game/game_fn_80155D50.c"),
            Object(Matching, "game/game_fn_80155D64.c"),
            Object(Matching, "game/game_fn_80155D78.c"),
            Object(Matching, "game/game_fn_80155D9C.c"),
            Object(Matching, "game/game_fn_80155DAC.c"),
            Object(Matching, "game/game_fn_80155DB4.c"),
            Object(Matching, "game/game_fn_80155E08.c"),
            Object(Matching, "game/game_fn_80155E3C.c"),
            Object(Matching, "game/game_fn_80155E68.c"),
            Object(Matching, "game/game_fn_80155EBC.c"),
            Object(Matching, "game/game_fn_80155EF4.c"),
            Object(Matching, "game/game_fn_80155F40.c"),
            Object(Matching, "game/game_fn_80155F8C.c"),
            Object(Matching, "game/game_fn_80155FD8.c"),
            Object(Matching, "game/game_fn_80155FE8.c"),
            Object(Matching, "game/game_fn_80156010.c"),
            Object(Matching, "game/game_fn_80156080.c"),
            Object(Matching, "game/game_fn_801560CC.c"),
            Object(Matching, "game/game_fn_80156120.c"),
            Object(Matching, "game/game_fn_8015617C.c"),
            Object(Matching, "game/game_fn_80156190.c"),
            Object(Matching, "game/game_fn_801561B4.c"),
            Object(Matching, "game/game_fn_80156290.c"),
            Object(Matching, "game/game_fn_801562DC.c"),
            Object(Matching, "game/game_fn_801562E8.c"),
            Object(Matching, "game/game_fn_801563C0.c"),
            Object(Matching, "game/game_fn_8015644C.c"),
            Object(NonMatching, "game/game_fn_80156480.c"),
            Object(Matching, "game/game_fn_801565E0.c"),
            Object(Matching, "game/game_fn_8015662C.c"),
            Object(Matching, "game/game_fn_801566E0.c"),
            Object(Matching, "game/game_fn_8015677C.c"),
            Object(Matching, "game/game_fn_801568B8.c"),
            Object(Matching, "game/game_fn_801568C0.c"),
            Object(Matching, "game/game_fn_801568C8.c"),
            Object(Matching, "game/game_fn_801568D8.c"),
            Object(Matching, "game/game_fn_801568E4.c"),
            Object(Matching, "game/game_fn_801568F0.c"),
            Object(Matching, "game/game_fn_801568FC.c"),
            Object(Matching, "game/game_fn_80156904.c"),
            Object(Matching, "game/game_fn_8015690C.c"),
            Object(Matching, "game/game_fn_80156914.c"),
            Object(Matching, "game/game_fn_80156918.c"),
            Object(Matching, "game/game_fn_80156920.c"),
            Object(Matching, "game/game_fn_80156928.c"),
            Object(Matching, "game/game_fn_80156930.c"),
            Object(Matching, "game/game_fn_80156938.c"),
            Object(Matching, "game/game_fn_80156940.c"),
            Object(Matching, "game/game_fn_80156948.c"),
            Object(Matching, "game/game_fn_80156998.c"),
            Object(Matching, "game/game_fn_801569A0.c"),
            Object(Matching, "game/game_fn_80156B1C.c"),
            Object(Matching, "game/game_fn_80156C04.c"),
            Object(Matching, "game/game_fn_80156CBC.c"),
            Object(Matching, "game/game_fn_80156DA0.c"),
            Object(Matching, "game/game_fn_80156E50.c"),
            Object(Matching, "game/game_fn_80156EBC.c"),
            Object(Matching, "game/game_fn_80156F10.c"),
            Object(Matching, "game/game_fn_80156F78.c"),
            Object(Matching, "game/game_fn_80156F80.c"),
            Object(Matching, "game/game_fn_80156FF4.c"),
            Object(Matching, "game/game_fn_80157034.c"),
            Object(Matching, "game/game_fn_80157050.c"),
            Object(Matching, "game/game_fn_801570AC.c"),
            Object(Matching, "game/game_fn_801570F8.c"),
            Object(
                Matching,
                "game/game_fn_801571C4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80157308.c"),
            Object(
                NonMatching,
                "game/game_fn_80157360.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80157438.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_80157504.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_8015761C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80157688.c"),
            Object(Matching, "game/game_fn_801576C4.c"),
            Object(Matching, "game/game_fn_80157738.c"),
            Object(Matching, "game/game_fn_80157760.c"),
            Object(Matching, "game/game_fn_801577E0.c"),
            Object(Matching, "game/game_fn_80157824.c"),
            Object(Matching, "game/game_fn_8015784C.c"),
            Object(Matching, "game/game_fn_80157858.c"),
            Object(Matching, "game/game_fn_80157864.c"),
            Object(Matching, "game/game_fn_80157888.c"),
            Object(Matching, "game/game_fn_80157894.c"),
            Object(Matching, "game/game_fn_801578A0.c"),
            Object(Matching, "game/game_fn_801578AC.c"),
            Object(Matching, "game/game_fn_801578B8.c"),
            Object(Matching, "game/game_fn_801578E8.c"),
            Object(Matching, "game/game_fn_801578F4.c"),
            Object(Matching, "game/game_fn_80157900.c"),
            Object(Matching, "game/game_fn_8015790C.c"),
            Object(Matching, "game/game_fn_80157918.c"),
            Object(Matching, "game/game_fn_80157924.c"),
            Object(Matching, "game/game_fn_80157930.c"),
            Object(Matching, "game/game_fn_8015793C.c"),
            Object(Matching, "game/game_fn_80157948.c"),
            Object(Matching, "game/game_fn_80157994.c"),
            Object(Matching, "game/game_fn_801579E0.c"),
            Object(Matching, "game/game_fn_801579EC.c"),
            Object(Matching, "game/game_fn_801579F4.c"),
            Object(Matching, "game/game_fn_801579FC.c"),
            Object(Matching, "game/game_fn_80157A08.c"),
            Object(Matching, "game/game_fn_80157A28.c"),
            Object(Matching, "game/game_fn_80157A80.c"),
            Object(Matching, "game/game_fn_80157A8C.c"),
            Object(Matching, "game/game_fn_80157A98.c"),
            Object(Matching, "game/game_fn_80157AB8.c"),
            Object(Matching, "game/game_fn_80157AC4.c"),
            Object(Matching, "game/game_fn_80157B3C.c"),
            Object(Matching, "game/game_fn_80157B48.c"),
            Object(Matching, "game/game_fn_80157B54.c"),
            Object(Matching, "game/game_fn_80157B60.c"),
            Object(Matching, "game/game_fn_80157B6C.c"),
            Object(Matching, "game/game_fn_80157B80.c"),
            Object(Matching, "game/game_fn_80157B94.c"),
            Object(Matching, "game/game_fn_80157BA0.c"),
            Object(Matching, "game/game_fn_80157BAC.c"),
            Object(Matching, "game/game_fn_80157BB8.c"),
            Object(Matching, "game/game_fn_80157BC4.c"),
            Object(Matching, "game/game_fn_80157BD0.c"),
            Object(Matching, "game/game_fn_80157BDC.c"),
            Object(Matching, "game/game_fn_80157BE8.c"),
            Object(Matching, "game/game_fn_80157BF4.c"),
            Object(Matching, "game/game_fn_80157C00.c"),
            Object(Matching, "game/game_fn_80157C0C.c"),
            Object(Matching, "game/game_fn_80157C80.c"),
            Object(Matching, "game/game_fn_80157C88.c"),
            Object(Matching, "game/game_fn_80157C98.c"),
            Object(Matching, "game/game_fn_80157CB8.c"),
            Object(Matching, "game/game_fn_80157E14.c"),
            Object(Matching, "game/game_fn_80157E1C.c"),
            Object(Matching, "game/game_fn_80157E24.c"),
            Object(Matching, "game/game_fn_80157E34.c"),
            Object(Matching, "game/game_fn_80157EFC.c"),
            Object(Matching, "game/game_fn_80157FA8.c"),
            Object(Matching, "game/game_fn_80157FE0.c"),
            Object(Matching, "game/game_fn_80158038.c"),
            Object(Matching, "game/game_fn_80158210.c"),
            Object(Matching, "game/game_fn_8015821C.c"),
            Object(Matching, "game/game_fn_80158234.c"),
            Object(Matching, "game/game_fn_80158250.c"),
            Object(Matching, "game/game_fn_80158264.c"),
            Object(Matching, "game/game_fn_80158390.c"),
            Object(Matching, "game/game_fn_80158514.c"),
            Object(Matching, "game/game_fn_80158550.c"),
            Object(Matching, "game/game_fn_80158598.c"),
            Object(Matching, "game/game_fn_80158668.c"),
            Object(Matching, "game/game_fn_801586CC.c"),
            Object(Matching, "game/game_fn_801586FC.c"),
            Object(Matching, "game/game_fn_8015878C.c"),
            Object(Matching, "game/game_fn_80158794.c"),
            Object(Matching, "game/game_fn_801587C4.c"),
            Object(Matching, "game/game_fn_80158850.c"),
            Object(Matching, "game/game_fn_8015885C.c"),
            Object(Matching, "game/game_fn_80158868.c"),
            Object(Matching, "game/game_fn_80158950.c"),
            Object(Matching, "game/game_fn_801589AC.c"),
            Object(Matching, "game/game_fn_80158A44.c"),
            Object(Matching, "game/game_fn_80158ABC.c"),
            Object(Matching, "game/game_fn_80158B20.c"),
            Object(Matching, "game/game_fn_80158C0C.c"),
            Object(Matching, "game/game_fn_80158CC8.c"),
            Object(NonMatching, "game/game_fn_80158D38.c"),
            Object(NonMatching, "game/game_fn_80158E7C.c"),
            Object(Matching, "game/game_fn_80158E84.c"),
            Object(Matching, "game/game_fn_80158E88.c"),
            Object(Matching, "game/game_fn_80158ECC.c"),
            Object(Matching, "game/game_fn_80158F6C.c"),
            Object(NonMatching, "game/game_fn_80159088.c"),
            Object(Matching, "game/game_fn_8015917C.c"),
            Object(Matching, "game/game_fn_80159184.c"),
            Object(Matching, "game/game_fn_801593AC.c"),
            Object(Matching, "game/game_fn_801593B4.c"),
            Object(Matching, "game/game_fn_801593FC.c"),
            Object(NonMatching, "game/game_fn_80159440.c"),
            Object(Matching, "game/game_fn_80159630.c"),
            Object(Matching, "game/game_fn_8015977C.c"),
            Object(Matching, "game/game_fn_801597BC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801599BC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80159DD0.c"),
            Object(Matching, "game/game_fn_80159E0C.c"),
            Object(Matching, "game/game_fn_80159EEC.c"),
            Object(NonMatching, "game/game_fn_80159F34.c"),
            Object(Matching, "game/game_fn_8015A12C.c"),
            Object(Matching, "game/game_fn_8015A17C.c"),
            Object(Matching, "game/game_fn_8015A1AC.c"),
            Object(Matching, "game/game_fn_8015A1C0.c"),
            Object(Matching, "game/game_fn_8015A2E0.c"),
            Object(Matching, "game/game_fn_8015A314.c"),
            Object(NonMatching, "game/game_fn_8015A340.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8015AA0C.c"),
            Object(Matching, "game/game_fn_8015AA14.c"),
            Object(Matching, "game/game_fn_8015AA20.c"),
            Object(Matching, "game/game_fn_8015AA28.c"),
            Object(Matching, "game/game_fn_8015AA58.c"),
            Object(Matching, "game/game_fn_8015AABC.c"),
            Object(Matching, "game/game_fn_8015AB00.c"),
            Object(Matching, "game/game_fn_8015AB68.c"),
            Object(Matching, "game/game_fn_8015AB8C.c"),
            Object(Matching, "game/game_fn_8015ABD4.c"),
            Object(Matching, "game/game_fn_8015AC3C.c"),
            Object(Matching, "game/game_fn_8015AC74.c"),
            Object(Matching, "game/game_fn_8015AC84.c"),
            Object(Matching, "game/game_fn_8015AC94.c"),
            Object(Matching, "game/game_fn_8015AD00.c"),
            Object(Matching, "game/game_fn_8015AD40.c"),
            Object(Matching, "game/game_fn_8015AD88.c"),
            Object(Matching, "game/game_fn_8015ADD0.c"),
            Object(NonMatching, "game/game_fn_8015AEB8.c"),
            Object(NonMatching, "game/game_fn_8015B274.c"),
            Object(Matching, "game/game_fn_8015B5C8.c"),
            Object(Matching, "game/game_fn_8015B628.c"),
            Object(Matching, "game/game_fn_8015B708.c"),
            Object(Matching, "game/game_fn_8015B7CC.c"),
            Object(NonMatching, "game/game_fn_8015B800.c"),
            Object(NonMatching, "game/game_fn_8015BCB0.c"),
            Object(Matching, "game/game_fn_8015BDAC.c"),
            Object(NonMatching, "game/game_fn_8015BDF0.c"),
            Object(Matching, "game/game_fn_8015C020.c"),
            Object(NonMatching, "game/game_fn_8015C050.c"),
            Object(NonMatching, "game/game_fn_8015C194.c"),
            Object(Matching, "game/game_fn_8015C28C.c"),
            Object(Matching, "game/game_fn_8015C2FC.c"),
            Object(Matching, "game/game_fn_8015C348.c"),
            Object(Matching, "game/game_fn_8015C390.c"),
            Object(Matching, "game/game_fn_8015C3E0.c"),
            Object(Matching, "game/game_fn_8015C414.c"),
            Object(Matching, "game/game_fn_8015C470.c"),
            Object(Matching, "game/game_fn_8015C4A4.c"),
            Object(Matching, "game/game_fn_8015C524.c"),
            Object(Matching, "game/game_fn_8015C5A0.c"),
            Object(Matching, "game/game_fn_8015C5E4.c"),
            Object(Matching, "game/game_fn_8015C628.c"),
            Object(Matching, "game/game_fn_8015C71C.c"),
            Object(Matching, "game/game_fn_8015C7D8.c"),
            Object(Matching, "game/game_fn_8015C880.c"),
            Object(Matching, "game/game_fn_8015C8A4.c"),
            Object(Matching, "game/game_fn_8015C910.c"),
            Object(Matching, "game/game_fn_8015C918.c"),
            Object(Matching, "game/game_fn_8015C948.c"),
            Object(Matching, "game/game_fn_8015C9F0.c"),
            Object(Matching, "game/game_fn_8015CA00.c"),
            Object(NonMatching, "game/game_fn_8015CA08.c"),
            Object(Matching, "game/game_fn_8015CB00.c"),
            Object(NonMatching, "game/game_fn_8015CBB0.c"),
            Object(Matching, "game/game_fn_8015CDC0.c"),
            Object(Matching, "game/game_fn_8015CDF0.c"),
            Object(Matching, "game/game_fn_8015CE48.c"),
            Object(NonMatching, "game/game_fn_8015CFFC.c"),
            Object(Matching, "game/game_fn_8015D1C8.c"),
            Object(Matching, "game/game_fn_8015D304.c"),
            Object(Matching, "game/game_fn_8015D414.c"),
            Object(Matching, "game/game_fn_8015D424.c"),
            Object(Matching, "game/game_fn_8015D44C.c"),
            Object(Matching, "game/game_fn_8015D458.c"),
            Object(Matching, "game/game_fn_8015D4EC.c"),
            Object(Matching, "game/game_fn_8015D5B0.c"),
            Object(Matching, "game/game_fn_8015D630.c"),
            Object(Matching, "game/game_fn_8015D670.c"),
            Object(Matching, "game/game_fn_8015D6A0.c"),
            Object(
                Matching,
                "game/game_fn_8015D6D0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_8015D7D4.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8015D9C8.c"),
            Object(Matching, "game/game_fn_8015DA70.c"),
            Object(Matching, "game/game_fn_8015DAB0.c"),
            Object(Matching, "game/game_fn_8015DB74.c"),
            Object(NonMatching, "game/game_fn_8015DB84.c"),
            Object(NonMatching, "game/game_fn_8015DC54.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8015DD48.c"),
            Object(NonMatching, "game/game_fn_8015DD94.c"),
            Object(Matching, "game/game_fn_8015DEC4.c"),
            Object(Matching, "game/game_fn_8015DF24.c"),
            Object(NonMatching, "game/game_fn_8015DF60.c"),
            Object(Matching, "game/game_fn_8015E0A0.c"),
            Object(NonMatching, "game/game_fn_8015E168.c"),
            Object(NonMatching, "game/game_fn_8015E1A8.c"),
            Object(Matching, "game/game_fn_8015E4A4.c"),
            Object(Matching, "game/game_fn_8015E4B4.c"),
            Object(Matching, "game/game_fn_8015E4E8.c"),
            Object(Matching, "game/game_fn_8015E51C.c"),
            Object(Matching, "game/game_fn_8015E548.c"),
            Object(Matching, "game/game_fn_8015E5DC.c"),
            Object(Matching, "game/game_fn_8015E780.c"),
            Object(Matching, "game/game_fn_8015E788.c"),
            Object(Matching, "game/game_fn_8015E794.c"),
            Object(Matching, "game/game_fn_8015E7A0.c"),
            Object(Matching, "game/game_fn_8015E7A8.c"),
            Object(NonMatching, "game/game_fn_8015E7C8.c"),
            Object(Matching, "game/game_fn_8015E830.c"),
            Object(Matching, "game/game_fn_8015E86C.c"),
            Object(Matching, "game/game_fn_8015E8E8.c"),
            Object(Matching, "game/game_fn_8015E918.c"),
            Object(NonMatching, "game/game_fn_8015E9EC.c"),
            Object(Matching, "game/game_fn_8015EA7C.c"),
            Object(Matching, "game/game_fn_8015EAA0.c"),
            Object(Matching, "game/game_fn_8015EAD0.c"),
            Object(Matching, "game/game_fn_8015EB30.c"),
            Object(Matching, "game/game_fn_8015EBDC.c"),
            Object(NonMatching, "game/game_fn_8015EC10.c"),
            Object(Matching, "game/game_fn_8015EC60.c"),
            Object(Matching, "game/game_fn_8015ECCC.c"),
            Object(NonMatching, "game/game_fn_8015ECF8.c"),
            Object(Matching, "game/game_fn_8015EDC0.c"),
            Object(Matching, "game/game_fn_8015EE54.c"),
            Object(Matching, "game/game_fn_8015EE94.c"),
            Object(Matching, "game/game_fn_8015EED8.c"),
            Object(Matching, "game/game_fn_8015EF4C.c"),
            Object(Matching, "game/game_fn_8015EFEC.c"),
            Object(Matching, "game/game_fn_8015F048.c"),
            Object(Matching, "game/game_fn_8015F0C0.c"),
            Object(Matching, "game/game_fn_8015F12C.c"),
            Object(Matching, "game/game_fn_8015F1F8.c"),
            Object(Matching, "game/game_fn_8015F23C.c"),
            Object(Matching, "game/game_fn_8015F2B0.c"),
            Object(Matching, "game/game_fn_8015F334.c"),
            Object(Matching, "game/game_fn_8015F414.c"),
            Object(Matching, "game/game_fn_8015F448.c"),
            Object(Matching, "game/game_fn_8015F47C.c"),
            Object(Matching, "game/game_fn_8015F4D0.c"),
            Object(Matching, "game/game_fn_8015F694.c"),
            Object(Matching, "game/game_fn_8015F768.c"),
            Object(Matching, "game/game_fn_8015F7D4.c"),
            Object(Matching, "game/game_fn_8015F8B4.c"),
            Object(Matching, "game/game_fn_8015F988.c"),
            Object(Matching, "game/game_fn_8015F9B0.c"),
            Object(NonMatching, "game/game_fn_8015F9D4.c"),
            Object(Matching, "game/game_fn_8015FE80.c"),
            Object(Matching, "game/game_fn_8015FEB8.c"),
            Object(Matching, "game/game_fn_8015FF18.c"),
            Object(Matching, "game/game_fn_8015FFE8.c"),
            Object(Matching, "game/game_fn_80160024.c"),
            Object(Matching, "game/game_fn_801600AC.c"),
            Object(Matching, "game/game_fn_80160280.c"),
            Object(Matching, "game/game_fn_801603AC.c"),
            Object(Matching, "game/game_fn_8016044C.c"),
            Object(NonMatching, "game/game_fn_80160480.c"),
            Object(Matching, "game/game_fn_801604F8.c"),
            Object(Matching, "game/game_fn_8016057C.c"),
            Object(Matching, "game/game_fn_801605F4.c"),
            Object(Matching, "game/game_fn_80160628.c"),
            Object(NonMatching, "game/game_fn_80160748.c"),
            Object(Matching, "game/game_fn_801607D8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80160848.c"),
            Object(Matching, "game/game_fn_8016088C.c"),
            Object(Matching, "game/game_fn_801608D0.c"),
            Object(Matching, "game/game_fn_80160AA0.c"),
            Object(NonMatching, "game/game_fn_80160B18.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80160CE4.c"),
            Object(Matching, "game/game_fn_80160D10.c"),
            Object(Matching, "game/game_fn_80160D74.c"),
            Object(Matching, "game/game_fn_80160DD0.c"),
            Object(Matching, "game/game_fn_80160E50.c"),
            Object(Matching, "game/game_fn_80160EBC.c"),
            Object(Matching, "game/game_fn_80160F00.c"),
            Object(Matching, "game/game_fn_80160FAC.c"),
            Object(Matching, "game/game_fn_80160FEC.c"),
            Object(NonMatching, "game/game_fn_80161044.c"),
            Object(Matching, "game/game_fn_801610E8.c"),
            Object(Matching, "game/game_fn_80161164.c"),
            Object(Matching, "game/game_fn_801611F8.c"),
            Object(Matching, "game/game_fn_80161244.c"),
            Object(Matching, "game/game_fn_80161284.c"),
            Object(Matching, "game/game_fn_80161380.c"),
            Object(NonMatching, "game/game_fn_801613C8.c"),
            Object(Matching, "game/game_fn_80161428.c"),
            Object(Matching, "game/game_fn_8016152C.c"),
            Object(Matching, "game/game_fn_8016158C.c"),
            Object(Matching, "game/game_fn_8016160C.c"),
            Object(Matching, "game/game_fn_8016166C.c"),
            Object(Matching, "game/game_fn_801616EC.c"),
            Object(NonMatching, "game/game_fn_80161798.c"),
            Object(Matching, "game/game_fn_801618D0.c"),
            Object(Matching, "game/game_fn_80161948.c"),
            Object(Matching, "game/game_fn_801619BC.c"),
            Object(Matching, "game/game_fn_80161A34.c"),
            Object(Matching, "game/game_fn_80161AA0.c"),
            Object(Matching, "game/game_fn_80161B0C.c"),
            Object(Matching, "game/game_fn_80161B58.c"),
            Object(NonMatching, "game/game_fn_80161C30.c"),
            Object(Matching, "game/game_fn_80161CF8.c"),
            Object(Matching, "game/game_fn_80161D58.c"),
            Object(NonMatching, "game/game_fn_80161E20.c"),
            Object(Matching, "game/game_fn_80161ED8.c"),
            Object(Matching, "game/game_fn_80161F3C.c"),
            Object(Matching, "game/game_fn_80161FA0.c"),
            Object(Matching, "game/game_fn_80161FD0.c"),
            Object(Matching, "game/game_fn_8016203C.c"),
            Object(Matching, "game/game_fn_8016209C.c"),
            Object(Matching, "game/game_fn_80162114.c"),
            Object(Matching, "game/game_fn_80162188.c"),
            Object(Matching, "game/game_fn_801621D8.c"),
            Object(Matching, "game/game_fn_80162228.c"),
            Object(Matching, "game/game_fn_801622BC.c"),
            Object(Matching, "game/game_fn_801623B4.c"),
            Object(Matching, "game/game_fn_801624A8.c"),
            Object(Matching, "game/game_fn_80162874.c"),
            Object(Matching, "game/game_fn_80162BEC.c"),
            Object(Matching, "game/game_fn_80163224.c"),
            Object(Matching, "game/game_fn_8016393C.c"),
            Object(Matching, "game/game_fn_801639CC.c"),
            Object(Matching, "game/game_fn_801639E8.c"),
            Object(Matching, "game/game_fn_80163A9C.c"),
            Object(Matching, "game/game_fn_80163B14.c"),
            Object(Matching, "game/game_fn_80163BB4.c"),
            Object(Matching, "game/game_fn_80163C5C.c"),
            Object(Matching, "game/game_fn_80163DA4.c"),
            Object(Matching, "game/game_fn_80163E08.c"),
            Object(Matching, "game/game_fn_80163E3C.c"),
            Object(Matching, "game/game_fn_80163E94.c"),
            Object(Matching, "game/game_fn_80163ED4.c"),
            Object(Matching, "game/game_fn_80163F00.c"),
            Object(Matching, "game/game_fn_80163F38.c"),
            Object(Matching, "game/game_fn_80163FE4.c"),
            Object(Matching, "game/game_fn_80164088.c"),
            Object(Matching, "game/game_fn_801640C4.c"),
            Object(Matching, "game/game_fn_80164120.c"),
            Object(Matching, "game/game_fn_80164158.c"),
            Object(Matching, "game/game_fn_801641D4.c"),
            Object(Matching, "game/game_fn_8016425C.c"),
            Object(Matching, "game/game_fn_8016437C.c"),
            Object(Matching, "game/game_fn_801644B0.c"),
            Object(Matching, "game/game_fn_801644FC.c"),
            Object(Matching, "game/game_fn_8016457C.c"),
            Object(Matching, "game/game_fn_801645F8.c"),
            Object(Matching, "game/game_fn_801646BC.c"),
            Object(Matching, "game/game_fn_80164778.c"),
            Object(Matching, "game/game_fn_801647F8.c"),
            Object(Matching, "game/game_fn_80164898.c"),
            Object(Matching, "game/game_fn_801648B8.c"),
            Object(
                Matching,
                "game/game_fn_80164908.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801649CC.c"),
            Object(NonMatching, "game/game_fn_80164A64.c"),
            Object(Matching, "game/game_fn_80164BE4.c"),
            Object(Matching, "game/game_fn_80164C7C.c"),
            Object(Matching, "game/game_fn_80164D04.c"),
            Object(Matching, "game/game_fn_80164DF4.c"),
            Object(Matching, "game/game_fn_80164F7C.c"),
            Object(Matching, "game/game_fn_80165010.c"),
            Object(Matching, "game/game_fn_801650A8.c"),
            Object(
                Matching,
                "game/game_fn_80165198.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801652B4.c"),
            Object(
                Matching,
                "game/game_fn_8016536C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80165464.c"),
            Object(Matching, "game/game_fn_801655CC.c"),
            Object(Matching, "game/game_fn_8016560C.c"),
            Object(Matching, "game/game_fn_8016563C.c"),
            Object(
                Matching,
                "game/game_fn_8016576C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80165870.c"),
            Object(Matching, "game/game_fn_80165894.c"),
            Object(Matching, "game/game_fn_801658D0.c"),
            Object(Matching, "game/game_fn_80165934.c"),
            Object(Matching, "game/game_fn_80165A54.c"),
            Object(Matching, "game/game_fn_80165A9C.c"),
            Object(Matching, "game/game_fn_80165B78.c"),
            Object(
                Matching,
                "game/game_fn_80165C28.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80165CE8.c"),
            Object(Matching, "game/game_fn_80165DC0.c"),
            Object(Matching, "game/game_fn_80165EAC.c"),
            Object(Matching, "game/game_fn_80165F70.c"),
            Object(Matching, "game/game_fn_80165FC8.c"),
            Object(Matching, "game/game_fn_801660EC.c"),
            Object(Matching, "game/game_fn_80166190.c"),
            Object(Matching, "game/game_fn_8016623C.c"),
            Object(Matching, "game/game_fn_801662A0.c"),
            Object(Matching, "game/game_fn_80166334.c"),
            Object(Matching, "game/game_fn_801663A0.c"),
            Object(Matching, "game/game_fn_80166440.c"),
            Object(Matching, "game/game_fn_801665B0.c"),
            Object(Matching, "game/game_fn_8016668C.c"),
            Object(Matching, "game/game_fn_80166750.c"),
            Object(Matching, "game/game_fn_801667BC.c"),
            Object(Matching, "game/game_fn_801667E4.c"),
            Object(Matching, "game/game_fn_80166894.c"),
            Object(Matching, "game/game_fn_80166994.c"),
            Object(Matching, "game/game_fn_80166AC4.c"),
            Object(Matching, "game/game_fn_80166B5C.c"),
            Object(Matching, "game/game_fn_80166BD4.c"),
            Object(Matching, "game/game_fn_80166C14.c"),
            Object(Matching, "game/game_fn_80166DD4.c"),
            Object(
                NonMatching,
                "game/game_fn_80166E3C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80166F4C.c"),
            Object(Matching, "game/game_fn_80167014.c"),
            Object(Matching, "game/game_fn_801670A8.c"),
            Object(Matching, "game/game_fn_801670F4.c"),
            Object(Matching, "game/game_fn_80167128.c"),
            Object(Matching, "game/game_fn_801671D0.c"),
            Object(Matching, "game/game_fn_80167264.c"),
            Object(Matching, "game/game_fn_801672C8.c"),
            Object(Matching, "game/game_fn_8016731C.c"),
            Object(Matching, "game/game_fn_80167380.c"),
            Object(NonMatching, "game/game_fn_80167454.c"),
            Object(Matching, "game/game_fn_80167558.c"),
            Object(Matching, "game/game_fn_80167798.c"),
            Object(Matching, "game/game_fn_8016783C.c"),
            Object(Matching, "game/game_fn_801678BC.c"),
            Object(Matching, "game/game_fn_801678F4.c"),
            Object(Matching, "game/game_fn_801679F8.c"),
            Object(Matching, "game/game_fn_80167B5C.c"),
            Object(Matching, "game/game_fn_80167BA8.c"),
            Object(Matching, "game/game_fn_80167BF0.c"),
            Object(Matching, "game/game_fn_80167C28.c"),
            Object(Matching, "game/game_fn_80167CA0.c"),
            Object(Matching, "game/game_fn_80167D2C.c"),
            Object(Matching, "game/game_fn_80167D68.c"),
            Object(Matching, "game/game_fn_80167D80.c"),
            Object(Matching, "game/game_fn_80167DC8.c"),
            Object(Matching, "game/game_fn_80167E58.c"),
            Object(Matching, "game/game_fn_80167EB0.c"),
            Object(NonMatching, "game/game_fn_80167F48.c"),
            Object(Matching, "game/game_fn_80167FE4.c"),
            Object(Matching, "game/game_fn_80168018.c"),
            Object(Matching, "game/game_fn_8016804C.c"),
            Object(Matching, "game/game_fn_80168080.c"),
            Object(Matching, "game/game_fn_80168114.c"),
            Object(Matching, "game/game_fn_801681DC.c"),
            Object(Matching, "game/game_fn_801682B0.c"),
            Object(Matching, "game/game_fn_80168334.c"),
            Object(Matching, "game/game_fn_80168490.c"),
            Object(Matching, "game/game_fn_80168598.c"),
            Object(Matching, "game/game_fn_80168634.c"),
            Object(Matching, "game/game_fn_801686A8.c"),
            Object(Matching, "game/game_fn_801688B0.c"),
            Object(Matching, "game/game_fn_801688F8.c"),
            Object(Matching, "game/game_fn_801689EC.c"),
            Object(Matching, "game/game_fn_80168A08.c"),
            Object(Matching, "game/game_fn_80168A70.c"),
            Object(NonMatching, "game/game_fn_80168AE8.c"),
            Object(Matching, "game/game_fn_80168BAC.c"),
            Object(Matching, "game/game_fn_80168C74.c"),
            Object(Matching, "game/game_fn_80168CB0.c"),
            Object(Matching, "game/game_fn_80168CEC.c"),
            Object(Matching, "game/game_fn_80168E34.c"),
            Object(Matching, "game/game_fn_80168F84.c"),
            Object(Matching, "game/game_fn_80169068.c"),
            Object(Matching, "game/game_fn_801691AC.c"),
            Object(Matching, "game/game_fn_8016927C.c"),
            Object(Matching, "game/game_fn_801692D4.c"),
            Object(Matching, "game/game_fn_8016938C.c"),
            Object(NonMatching, "game/game_fn_801694A8.c"),
            Object(
                Matching,
                "game/game_fn_80169650.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_80169740.c"),
            Object(NonMatching, "game/game_fn_801697AC.c"),
            Object(Matching, "game/game_fn_8016A444.c"),
            Object(Matching, "game/game_fn_8016A44C.c"),
            Object(Matching, "game/game_fn_8016A480.c"),
            Object(Matching, "game/game_fn_8016A55C.c"),
            Object(Matching, "game/game_fn_8016A598.c"),
            Object(NonMatching, "game/game_fn_8016A5B0.c"),
            Object(Matching, "game/game_fn_8016A5F4.c"),
            Object(Matching, "game/game_fn_8016A628.c"),
            Object(Matching, "game/game_fn_8016A650.c"),
            Object(Matching, "game/game_fn_8016A694.c"),
            Object(Matching, "game/game_fn_8016A700.c"),
            Object(Matching, "game/game_fn_8016A784.c"),
            Object(Matching, "game/game_fn_8016A7D8.c"),
            Object(Matching, "game/game_fn_8016A830.c"),
            Object(Matching, "game/game_fn_8016A890.c"),
            Object(Matching, "game/game_fn_8016A8F8.c"),
            Object(Matching, "game/game_fn_8016A950.c"),
            Object(Matching, "game/game_fn_8016A970.c"),
            Object(Matching, "game/game_fn_8016AA34.c"),
            Object(Matching, "game/game_fn_8016AAB4.c"),
            Object(Matching, "game/game_fn_8016AB20.c"),
            Object(Matching, "game/game_fn_8016AB6C.c"),
            Object(Matching, "game/game_fn_8016AC68.c"),
            Object(Matching, "game/game_fn_8016ACAC.c"),
            Object(Matching, "game/game_fn_8016AD28.c"),
            Object(NonMatching, "game/game_fn_8016ADF0.c"),
            Object(Matching, "game/game_fn_8016AF2C.c"),
            Object(Matching, "game/game_fn_8016AFB0.c"),
            Object(Matching, "game/game_fn_8016B030.c"),
            Object(Matching, "game/game_fn_8016B0B4.c"),
            Object(Matching, "game/game_fn_8016B1D0.c"),
            Object(Matching, "game/game_fn_8016B21C.c"),
            Object(Matching, "game/game_fn_8016B26C.c"),
            Object(Matching, "game/game_fn_8016B29C.c"),
            Object(Matching, "game/game_fn_8016B3A4.c"),
            Object(Matching, "game/game_fn_8016B400.c"),
            Object(Matching, "game/game_fn_8016B4B4.c"),
            Object(NonMatching, "game/game_fn_8016B5CC.c"),
            Object(NonMatching, "game/game_fn_8016B914.c"),
            Object(Matching, "game/game_fn_8016BA38.c"),
            Object(NonMatching, "game/game_fn_8016BA4C.c"),
            Object(Matching, "game/game_fn_8016BD0C.c"),
            Object(Matching, "game/game_fn_8016BDD8.c"),
            Object(Matching, "game/game_fn_8016BE1C.c"),
            Object(Matching, "game/game_fn_8016BEC8.c"),
            Object(Matching, "game/game_fn_8016BF60.c"),
            Object(Matching, "game/game_fn_8016C008.c"),
            Object(Matching, "game/game_fn_8016C0BC.c"),
            Object(Matching, "game/game_fn_8016C164.c"),
            Object(Matching, "game/game_fn_8016C238.c"),
            Object(Matching, "game/game_fn_8016C3B4.c"),
            Object(Matching, "game/game_fn_8016C4BC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8016C668.c"),
            Object(Matching, "game/game_fn_8016C6EC.c"),
            Object(Matching, "game/game_fn_8016C774.c"),
            Object(Matching, "game/game_fn_8016C7C4.c"),
            Object(Matching, "game/game_fn_8016C890.c"),
            Object(Matching, "game/game_fn_8016C96C.c"),
            Object(Matching, "game/game_fn_8016CA2C.c"),
            Object(Matching, "game/game_fn_8016CB24.c"),
            Object(Matching, "game/game_fn_8016CBFC.c"),
            Object(Matching, "game/game_fn_8016CDA0.c"),
            Object(Matching, "game/game_fn_8016CE48.c"),
            # Behavior-complete object-property copy wrapper; MWCC reverses
            # retail's r30/r31 handle allocation and removes its r0 shuttle.
            Object(NonMatching, "game/game_fn_8016CEF0.c"),
            Object(Matching, "game/game_fn_8016D040.c"),
            Object(Matching, "game/game_fn_8016D0D4.c"),
            Object(Matching, "game/game_fn_8016D144.c"),
            Object(Matching, "game/game_fn_8016D1F8.c"),
            Object(Matching, "game/game_fn_8016D2B8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8016D480.c"),
            Object(Matching, "game/game_fn_8016D574.c"),
            Object(Matching, "game/game_fn_8016D680.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8016D7AC.c"),
            Object(Matching, "game/game_fn_8016D8A4.c"),
            Object(Matching, "game/game_fn_8016D92C.c"),
            Object(Matching, "game/game_fn_8016D9C0.c"),
            Object(Matching, "game/game_fn_8016DA80.c"),
            Object(Matching, "game/game_fn_8016DB38.c"),
            Object(Matching, "game/game_fn_8016DBF0.c"),
            Object(Matching, "game/game_fn_8016DCB0.c"),
            Object(Matching, "game/game_fn_8016DD70.c"),
            Object(Matching, "game/game_fn_8016DD94.c"),
            Object(Matching, "game/game_fn_8016DE30.c"),
            Object(Matching, "game/game_fn_8016DECC.c"),
            Object(Matching, "game/game_fn_8016DF4C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8016E254.c"),
            Object(Matching, "game/game_fn_8016E294.c"),
            Object(Matching, "game/game_fn_8016E3F0.c"),
            Object(NonMatching, "game/game_fn_8016E514.c"),
            Object(Matching, "game/game_fn_8016E5A8.c"),
            Object(Matching, "game/game_fn_8016E634.c"),
            Object(Matching, "game/game_fn_8016E6D4.c"),
            Object(Matching, "game/game_fn_8016E7B8.c"),
            Object(Matching, "game/game_fn_8016E854.c"),
            Object(Matching, "game/game_fn_8016E8C4.c"),
            Object(Matching, "game/game_fn_8016E8F8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8016EACC.c"),
            Object(Matching, "game/game_fn_8016EAF4.c"),
            Object(Matching, "game/game_fn_8016EB1C.c"),
            Object(Matching, "game/game_fn_8016EC50.c"),
            Object(Matching, "game/game_fn_8016ED78.c"),
            Object(Matching, "game/game_fn_8016EEE4.c"),
            Object(Matching, "game/game_fn_8016EFC4.c"),
            Object(Matching, "game/game_fn_8016F088.c"),
            Object(Matching, "game/game_fn_8016F128.c"),
            Object(Matching, "game/game_fn_8016F1D0.c"),
            Object(Matching, "game/game_fn_8016F2AC.c"),
            Object(Matching, "game/game_fn_8016F400.c"),
            Object(Matching, "game/game_fn_8016F4CC.c"),
            Object(Matching, "game/game_fn_8016F580.c"),
            Object(Matching, "game/game_fn_8016F678.c"),
            Object(NonMatching, "game/game_fn_8016F78C.c"),
            Object(Matching, "game/game_fn_8016F8F8.c"),
            Object(NonMatching, "game/game_fn_8016FA08.c"),
            Object(Matching, "game/game_fn_8016FB94.c"),
            Object(Matching, "game/game_fn_8016FC68.c"),
            Object(Matching, "game/game_fn_8016FD3C.c"),
            Object(Matching, "game/game_fn_8016FE4C.c"),
            Object(Matching, "game/game_fn_8016FEF8.c"),
            Object(Matching, "game/game_fn_8016FFA8.c"),
            Object(Matching, "game/game_fn_8016FFDC.c"),
            Object(Matching, "game/game_fn_80170090.c"),
            Object(Matching, "game/game_fn_80170144.c"),
            Object(Matching, "game/game_fn_801701D4.c"),
            Object(Matching, "game/game_fn_8017026C.c"),
            Object(Matching, "game/game_fn_801702FC.c"),
            Object(Matching, "game/game_fn_8017038C.c"),
            Object(Matching, "game/game_fn_80170438.c"),
            Object(Matching, "game/game_fn_801704F8.c"),
            Object(Matching, "game/game_fn_801705D4.c"),
            Object(Matching, "game/game_fn_80170658.c"),
            Object(Matching, "game/game_fn_801706DC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80170814.c"),
            Object(Matching, "game/game_fn_80170880.c"),
            Object(Matching, "game/game_fn_80170980.c"),
            Object(Matching, "game/game_fn_80170A40.c"),
            Object(Matching, "game/game_fn_80170B5C.c"),
            Object(Matching, "game/game_fn_80170C18.c"),
            Object(Matching, "game/game_fn_80170C84.c"),
            Object(Matching, "game/game_fn_80170D04.c"),
            Object(Matching, "game/game_fn_80170DF4.c"),
            Object(Matching, "game/game_fn_80170E9C.c"),
            Object(Matching, "game/game_fn_80170F44.c"),
            Object(Matching, "game/game_fn_80171020.c"),
            Object(Matching, "game/game_fn_801710FC.c"),
            Object(NonMatching, "game/game_fn_801711D0.c"),
            Object(Matching, "game/game_fn_8017138C.c"),
            Object(Matching, "game/game_fn_80171418.c"),
            Object(Matching, "game/game_fn_801714BC.c"),
            Object(NonMatching, "game/game_fn_80171560.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80171664.c"),
            Object(Matching, "game/game_fn_80171780.c"),
            Object(Matching, "game/game_fn_8017187C.c"),
            Object(Matching, "game/game_fn_801718F4.c"),
            Object(Matching, "game/game_fn_801719B4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80171AF0.c"),
            Object(NonMatching, "game/game_fn_80171BB4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80171D6C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80171F30.c"),
            Object(Matching, "game/game_fn_80171FBC.c"),
            Object(Matching, "game/game_fn_80172058.c"),
            Object(Matching, "game/game_fn_801720E8.c"),
            Object(Matching, "game/game_fn_80172150.c"),
            Object(Matching, "game/game_fn_80172204.c"),
            Object(Matching, "game/game_fn_8017230C.c"),
            Object(Matching, "game/game_fn_801723B8.c"),
            Object(Matching, "game/game_fn_80172470.c"),
            Object(Matching, "game/game_fn_8017250C.c"),
            Object(Matching, "game/game_fn_801725A8.c"),
            Object(Matching, "game/game_fn_80172610.c"),
            Object(Matching, "game/game_fn_801726EC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017288C.c"),
            Object(Matching, "game/game_fn_80172944.c"),
            Object(Matching, "game/game_fn_801729CC.c"),
            Object(Matching, "game/game_fn_80172A4C.c"),
            Object(Matching, "game/game_fn_80172ACC.c"),
            Object(Matching, "game/game_fn_80172BB0.c"),
            Object(Matching, "game/game_fn_80172C78.c"),
            Object(Matching, "game/game_fn_80172D04.c"),
            Object(Matching, "game/game_fn_80172DB8.c"),
            Object(Matching, "game/game_fn_80172E78.c"),
            Object(Matching, "game/game_fn_80172E80.c"),
            Object(Matching, "game/game_fn_80172EEC.c"),
            Object(Matching, "game/game_fn_80172FF0.c"),
            Object(Matching, "game/game_fn_80173104.c"),
            Object(Matching, "game/game_fn_8017320C.c"),
            Object(Matching, "game/game_fn_80173270.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801734B4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80173770.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801739E8.c"),
            Object(Matching, "game/game_fn_80173B6C.c"),
            Object(Matching, "game/game_fn_80173B78.c"),
            # 87.977776%: exact-size honest C; the packed rotation initializer
            # and Vec3 aggregate copy remain scheduled differently from retail.
            Object(NonMatching, "game/game_fn_80173BDC.c"),
            # 90.660710%: exact-size honest C; initializer/prologue scheduling
            # and later value/register lifetimes remain different from retail.
            Object(NonMatching, "game/game_fn_80173D44.c"),
            # 95.675000%: honest C; removing a load-bearing volatile exposes an
            # eight-byte size and broad stack/register scheduling divergence.
            Object(NonMatching, "game/game_fn_80173F04.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80174184.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80174358.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80174610.c"),
            Object(Matching, "game/game_fn_80174694.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801748EC.c"),
            # 99.830505%: exact-size honest C; only fcmpu operand order differs.
            Object(Matching, "game/game_fn_801749A8.c"),
            Object(Matching, "game/game_fn_80174A94.c"),
            Object(Matching, "game/game_fn_80174B14.c"),
            Object(Matching, "game/game_fn_80174B94.c"),
            Object(Matching, "game/game_fn_80174C34.c"),
            Object(Matching, "game/game_fn_80174CD4.c"),
            Object(Matching, "game/game_fn_80174DB8.c"),
            Object(Matching, "game/game_fn_80174EB4.c"),
            # 90.112680% exact-size honest C; callback/constant setup retains
            # five scheduling differences and one local-constant relocation.
            Object(NonMatching, "game/game_fn_80174F2C.c"),
            Object(Matching, "game/game_fn_80175164.c"),
            Object(Matching, "game/game_fn_801751DC.c"),
            Object(Matching, "game/game_fn_80175244.c"),
            # 95.642204% exact-size honest C; callback address materialization
            # and descriptor-pointer scheduling differ across 19 instructions.
            Object(NonMatching, "game/game_fn_801752B0.c"),
            Object(Matching, "game/game_fn_80175464.c"),
            Object(Matching, "game/game_fn_801754D0.c"),
            Object(Matching, "game/game_fn_80175534.c"),
            Object(Matching, "game/game_fn_8017553C.c"),
            Object(NonMatching, "game/game_fn_801755FC.c"),
            Object(Matching, "game/game_fn_8017583C.c"),
            Object(Matching, "game/game_fn_801758F8.c"),
            Object(Matching, "game/game_fn_80175964.c"),
            Object(NonMatching, "game/game_fn_80175A08.c", extra_cflags=["-sdata 0"]),
            Object(NonMatching, "game/game_fn_80175BB8.c"),
            Object(Matching, "game/game_fn_80175E64.c"),
            Object(Matching, "game/game_fn_80175F0C.c"),
            Object(Matching, "game/game_fn_80175FD4.c"),
            Object(Matching, "game/game_fn_80176098.c"),
            Object(Matching, "game/game_fn_80176160.c"),
            Object(Matching, "game/game_fn_80176220.c"),
            Object(Matching, "game/game_fn_801762E8.c"),
            Object(Matching, "game/game_fn_801763D8.c"),
            Object(Matching, "game/game_fn_80176488.c"),
            Object(Matching, "game/game_fn_8017652C.c"),
            Object(Matching, "game/game_fn_801765C4.c"),
            Object(Matching, "game/game_fn_80176644.c"),
            Object(Matching, "game/game_fn_801766F0.c"),
            Object(Matching, "game/game_fn_80176770.c"),
            Object(Matching, "game/game_fn_801767F0.c"),
            Object(Matching, "game/game_fn_80176870.c"),
            Object(Matching, "game/game_fn_80176914.c"),
            Object(Matching, "game/game_fn_80176994.c"),
            Object(Matching, "game/game_fn_80176A14.c"),
            Object(NonMatching, "game/game_fn_80176A94.c"),
            Object(Matching, "game/game_fn_80176BA4.c"),
            Object(Matching, "game/game_fn_80176C64.c"),
            Object(Matching, "game/game_fn_80176D14.c"),
            Object(Matching, "game/game_fn_80176DF4.c"),
            Object(Matching, "game/game_fn_80176E98.c"),
            Object(Matching, "game/game_fn_80176F34.c"),
            Object(Matching, "game/game_fn_80176FA0.c"),
            Object(Matching, "game/game_fn_80177034.c"),
            Object(Matching, "game/game_fn_801770F8.c"),
            Object(Matching, "game/game_fn_8017718C.c"),
            Object(Matching, "game/game_fn_80177244.c"),
            Object(Matching, "game/game_fn_801772C8.c"),
            Object(Matching, "game/game_fn_80177388.c"),
            Object(Matching, "game/game_fn_80177408.c"),
            Object(Matching, "game/game_fn_80177434.c", mw_version="GC/1.3.2"),
            Object(Matching, "game/game_fn_80178E94.c"),
            Object(NonMatching, "game/game_fn_80178F14.c"),
            Object(NonMatching, "game/game_fn_80178F88.c"),
            Object(Matching, "game/game_fn_80179004.c"),
            Object(Matching, "game/game_fn_80179064.c"),
            Object(NonMatching, "game/game_fn_801790A4.c"),
            Object(Matching, "game/game_fn_80179398.c"),
            Object(Matching, "game/game_fn_801794A0.c"),
            Object(Matching, "game/game_fn_80179570.c"),
            Object(Matching, "game/game_fn_801795A4.c"),
            Object(Matching, "game/game_fn_801795D8.c"),
            Object(Matching, "game/game_fn_8017960C.c"),
            Object(Matching, "game/game_fn_8017968C.c"),
            Object(Matching, "game/game_fn_801796D4.c"),
            Object(Matching, "game/game_fn_8017970C.c"),
            Object(Matching, "game/game_fn_8017974C.c"),
            Object(Matching, "game/game_fn_80179814.c"),
            Object(Matching, "game/game_fn_801798DC.c"),
            Object(Matching, "game/game_fn_80179904.c"),
            Object(Matching, "game/game_fn_80179A18.c"),
            Object(Matching, "game/game_fn_80179A74.c"),
            Object(Matching, "game/game_fn_80179AEC.c"),
            Object(Matching, "game/game_fn_80179B08.c"),
            Object(Matching, "game/game_fn_80179B58.c"),
            Object(Matching, "game/game_fn_80179B64.c"),
            Object(Matching, "game/game_fn_80179BB4.c"),
            Object(Matching, "game/game_fn_80179BC0.c"),
            Object(Matching, "game/game_fn_80179C10.c"),
            Object(Matching, "game/game_fn_80179CD4.c"),
            Object(Matching, "game/game_fn_80179D38.c"),
            Object(Matching, "game/game_fn_80179D78.c"),
            Object(Matching, "game/game_fn_80179DB0.c"),
            Object(Matching, "game/game_fn_80179E08.c"),
            Object(Matching, "game/game_fn_80179E60.c"),
            Object(Matching, "game/game_fn_80179EB8.c"),
            Object(Matching, "game/game_fn_80179F20.c"),
            Object(Matching, "game/game_fn_80179F48.c"),
            Object(Matching, "game/game_fn_80179FE4.c"),
            Object(Matching, "game/game_fn_8017A010.c"),
            Object(NonMatching, "game/game_fn_8017A12C.c"),
            Object(Matching, "game/game_fn_8017A1C0.c"),
            Object(Matching, "game/game_fn_8017A244.c"),
            Object(Matching, "game/game_fn_8017A284.c"),
            Object(Matching, "game/game_fn_8017A34C.c"),
            Object(
                Matching,
                "game/game_fn_8017A470.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_data_806506A8.c"),
            Object(NonMatching, "game/game_fn_8012356C.c"),
            Object(Matching, "game/game_fn_80008B38.c"),
            Object(Matching, "game/game_fn_80008B6C.c"),
            Object(Matching, "game/game_fn_80008BD8.c"),
            Object(Matching, "game/game_fn_80008C14.c"),
            Object(Matching, "game/game_fn_80008C48.c"),
            Object(Matching, "game/game_fn_80008C8C.c"),
            Object(Matching, "game/game_fn_80008CA0.c"),
            Object(Matching, "game/game_fn_80008D0C.c"),
            Object(Matching, "game/game_fn_80008D24.c"),
            Object(Matching, "game/game_fn_80008EA4.c"),
            Object(Matching, "game/game_fn_80008F80.c"),
            Object(Matching, "game/game_fn_80008FE8.c"),
            Object(Matching, "game/game_fn_80009060.c"),
            Object(Matching, "game/game_fn_800090DC.c"),
            Object(Matching, "game/game_fn_80009158.c"),
            Object(Matching, "game/game_fn_800091D0.c"),
            Object(Matching, "game/game_fn_80009248.c"),
            Object(Matching, "game/game_fn_80009314.c"),
            Object(Matching, "game/game_fn_8000937C.c"),
            Object(Matching, "game/game_fn_80009400.c"),
            Object(Matching, "game/game_fn_800094C0.c"),
            Object(Matching, "game/game_fn_800096E0.c"),
            Object(Matching, "game/game_fn_800098C0.c"),
            Object(Matching, "game/game_fn_800099D8.c"),
            Object(Matching, "game/game_fn_80009AB4.c"),
            Object(Matching, "game/game_fn_80009BE8.c"),
            Object(Matching, "game/game_fn_80009CE4.c"),
            Object(Matching, "game/game_fn_80009D54.c"),
            Object(Matching, "game/game_fn_80009DF0.c"),
            Object(Matching, "game/game_fn_80009E70.c"),
            Object(Matching, "game/game_fn_80009F64.c"),
            Object(Matching, "game/game_fn_80009FE4.c"),
            Object(Matching, "game/game_fn_8000A0A0.c"),
            Object(Matching, "game/game_fn_8000A26C.c"),
            Object(Matching, "game/game_fn_8000A2F8.c"),
            Object(Matching, "game/game_fn_8000A37C.c"),
            Object(Matching, "game/game_fn_8000A400.c"),
            Object(Matching, "game/game_fn_8000A4FC.c"),
            Object(Matching, "game/game_fn_8000A5A8.c"),
            Object(
                Matching,
                "game/game_fn_8000A668.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_8017A574.c"),
            Object(NonMatching, "game/game_fn_8017A5A8.c"),
            Object(Matching, "game/game_fn_8017A630.c"),
            Object(NonMatching, "game/game_fn_8017A65C.c"),
            Object(Matching, "game/game_fn_8017A694.c"),
            Object(Matching, "game/game_fn_8017A6D8.c"),
            Object(Matching, "game/game_fn_8017A71C.c"),
            Object(Matching, "game/game_fn_8017A750.c"),
            Object(NonMatching, "game/game_fn_8017A7D4.c"),
            Object(Matching, "game/game_fn_8017A9B8.c"),
            Object(Matching, "game/game_fn_8017AB08.c"),
            Object(Matching, "game/game_fn_8017ABA0.c"),
            Object(Matching, "game/game_fn_8017ABE0.c"),
            Object(NonMatching, "game/game_fn_8017AC20.c"),
            Object(Matching, "game/game_fn_8017ACE0.c"),
            Object(Matching, "game/game_fn_8017AD00.c"),
            Object(Matching, "game/game_fn_8017AD7C.c"),
            Object(Matching, "game/game_fn_8017AE0C.c"),
            Object(Matching, "game/game_fn_8017AE20.c"),
            Object(NonMatching, "game/game_fn_8017AE90.c"),
            Object(Matching, "game/game_fn_8017AF44.c"),
            Object(Matching, "game/game_fn_8017AF64.c"),
            Object(Matching, "game/game_fn_8017AF78.c"),
            Object(Matching, "game/game_fn_8017AF90.c"),
            Object(Matching, "game/game_fn_8017B074.c"),
            Object(Matching, "game/game_fn_8017B0C8.c"),
            Object(Matching, "game/game_fn_8017B1AC.c"),
            Object(NonMatching, "game/game_fn_8017B294.c"),
            Object(Matching, "game/game_fn_8017B31C.c"),
            Object(Matching, "game/game_fn_8017B32C.c"),
            Object(Matching, "game/game_fn_8017B344.c"),
            Object(Matching, "game/game_fn_8017B35C.c"),
            Object(Matching, "game/game_fn_8017B3C8.c"),
            Object(Matching, "game/game_fn_8017B440.c"),
            Object(Matching, "game/game_fn_8017B47C.c"),
            Object(NonMatching, "game/game_fn_8017B4F4.c"),
            Object(Matching, "game/game_fn_8017B7B8.c"),
            Object(Matching, "game/game_fn_8017B7C8.c"),
            Object(Matching, "game/game_fn_8017B7DC.c"),
            Object(Matching, "game/game_fn_8017B7EC.c"),
            Object(Matching, "game/game_fn_8017B7FC.c"),
            Object(Matching, "game/game_fn_8017B80C.c"),
            Object(Matching, "game/game_fn_8017B854.c"),
            Object(Matching, "game/game_fn_8017B864.c"),
            Object(Matching, "game/game_fn_8017B8AC.c"),
            Object(Matching, "game/game_fn_8017B8BC.c"),
            Object(Matching, "game/game_fn_8017B904.c"),
            Object(Matching, "game/game_fn_8017B914.c"),
            Object(Matching, "game/game_fn_8017B95C.c"),
            Object(Matching, "game/game_fn_8017B96C.c"),
            Object(Matching, "game/game_fn_8017B9B4.c"),
            Object(Matching, "game/game_fn_8017B9C4.c"),
            Object(Matching, "game/game_fn_8017B9F8.c"),
            Object(Matching, "game/game_fn_8017BA24.c"),
            Object(Matching, "game/game_fn_8017BA44.c"),
            Object(Matching, "game/game_fn_8017BA54.c"),
            Object(Matching, "game/game_fn_8017BA60.c"),
            Object(Matching, "game/game_fn_8017BA64.c"),
            Object(Matching, "game/game_fn_8017BAF4.c"),
            Object(Matching, "game/game_fn_8017BB24.c"),
            Object(Matching, "game/game_fn_8017BB44.c"),
            Object(Matching, "game/game_fn_8017BB60.c"),
            Object(Matching, "game/game_fn_8017BB98.c"),
            Object(NonMatching, "game/game_fn_8017BBD0.c"),
            Object(Matching, "game/game_fn_8017BCD0.c"),
            Object(Matching, "game/game_fn_8017BD3C.c"),
            Object(Matching, "game/game_fn_8017BD78.c"),
            Object(Matching, "game/game_fn_8017BDAC.c"),
            Object(Matching, "game/game_fn_8017C108.c"),
            Object(NonMatching, "game/game_fn_8017C1C8.c"),
            Object(Matching, "game/game_fn_8017C2B0.c"),
            Object(Matching, "game/game_fn_8017C32C.c"),
            Object(Matching, "game/game_fn_8017C3C0.c"),
            Object(Matching, "game/game_fn_8017C47C.c"),
            Object(Matching, "game/game_fn_8017C584.c"),
            Object(Matching, "game/game_fn_8017C67C.c"),
            Object(NonMatching, "game/game_fn_8017C724.c"),
            Object(NonMatching, "game/game_fn_8017C810.c"),
            Object(NonMatching, "game/game_fn_8017C8E0.c"),
            Object(NonMatching, "game/game_fn_8017C964.c"),
            Object(NonMatching, "game/game_fn_8017CA0C.c"),
            Object(NonMatching, "game/game_fn_8017CB20.c"),
            Object(Matching, "game/game_fn_8017CBCC.c"),
            Object(Matching, "game/game_fn_8017CC28.c"),
            Object(Matching, "game/game_fn_8017CC30.c"),
            Object(Matching, "game/game_fn_8017CC38.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017CCA8.c"),
            Object(NonMatching, "game/game_fn_8017CCD8.c"),
            Object(Matching, "game/game_fn_8017CDB4.c"),
            Object(Matching, "game/game_fn_8017CE74.c"),
            Object(Matching, "game/game_fn_8017CF0C.c"),
            Object(Matching, "game/game_fn_8017CF74.c"),
            Object(Matching, "game/game_fn_8017CFC0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017D064.c"),
            Object(Matching, "game/game_fn_8017D078.c"),
            Object(Matching, "game/game_fn_8017D098.c"),
            Object(Matching, "game/game_fn_8017D0D8.c"),
            Object(
                NonMatching,
                "game/game_fn_8017D144.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(NonMatching, "game/game_fn_8017D1E0.c"),
            Object(Matching, "game/game_fn_8017D2B4.c"),
            Object(NonMatching, "game/game_fn_8017D318.c"),
            Object(NonMatching, "game/game_fn_8017D508.c"),
            Object(NonMatching, "game/game_fn_8017D700.c"),
            Object(Matching, "game/game_fn_8017D908.c"),
            Object(Matching, "game/game_fn_8017DA60.c"),
            Object(Matching, "game/game_fn_8017DB70.c"),
            Object(Matching, "game/game_fn_8017DC88.c"),
            Object(Matching, "game/game_fn_8017DCA8.c"),
            Object(Matching, "game/game_fn_8017DCE8.c"),
            Object(Matching, "game/game_fn_8017DD28.c"),
            Object(Matching, "game/game_fn_8017E17C.c"),
            Object(Matching, "game/game_fn_8017E1B0.c"),
            Object(NonMatching, "game/game_fn_8017E1E4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017E2B0.c"),
            Object(Matching, "game/game_fn_8017E32C.c"),
            Object(Matching, "game/game_fn_8017E40C.c"),
            Object(Matching, "game/game_fn_8017E4E4.c"),
            Object(Matching, "game/game_fn_8017E734.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017E804.c"),
            Object(Matching, "game/game_fn_8017E850.c"),
            Object(Matching, "game/game_fn_8017E958.c"),
            Object(Matching, "game/game_fn_8017EA58.c"),
            Object(Matching, "game/game_fn_8017EAA8.c"),
            Object(Matching, "game/game_fn_8017EB4C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017ED50.c"),
            Object(Matching, "game/game_fn_8017ED64.c"),
            Object(Matching, "game/game_fn_8017EDB4.c"),
            Object(NonMatching, "game/game_fn_8017EE58.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8017F084.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8017F120.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8017F3B4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8017F700.c"),
            Object(Matching, "game/game_fn_8017F794.c"),
            Object(Matching, "game/game_fn_8017F7D8.c"),
            Object(Matching, "game/game_fn_8017F87C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8017FA14.c"),
            Object(Matching, "game/game_fn_8017FD34.c"),
            Object(Matching, "game/game_fn_8017FD6C.c"),
            Object(Matching, "game/game_fn_8017FD8C.c"),
            Object(Matching, "game/game_fn_8017FD98.c"),
            Object(Matching, "game/game_fn_8017FDA0.c"),
            Object(Matching, "game/game_fn_8017FDA8.c"),
            Object(Matching, "game/game_fn_8017FDDC.c"),
            Object(Matching, "game/game_fn_8017FDE4.c"),
            Object(Matching, "game/game_fn_8017FDEC.c"),
            Object(Matching, "game/game_fn_8017FDF4.c"),
            Object(Matching, "game/game_fn_8017FDFC.c"),
            Object(Matching, "game/game_fn_8017FE04.c"),
            Object(Matching, "game/game_fn_8017FE0C.c"),
            Object(Matching, "game/game_fn_8017FE14.c"),
            Object(Matching, "game/game_fn_8017FE1C.c"),
            Object(Matching, "game/game_fn_8017FE24.c"),
            Object(Matching, "game/game_fn_8017FEA4.c"),
            Object(Matching, "game/game_fn_8017FEAC.c"),
            Object(Matching, "game/game_fn_8017FED4.c"),
            Object(Matching, "game/game_fn_8017FEFC.c"),
            Object(Matching, "game/game_fn_8017FF04.c"),
            Object(Matching, "game/game_fn_8017FF0C.c"),
            Object(Matching, "game/game_fn_8017FF14.c"),
            Object(Matching, "game/game_fn_8017FF1C.c"),
            Object(Matching, "game/game_fn_8017FF24.c"),
            Object(Matching, "game/game_fn_8017FF40.c"),
            Object(Matching, "game/game_fn_8017FF68.c"),
            Object(NonMatching, "game/game_fn_8017FF7C.c"),
            Object(Matching, "game/game_fn_8017FF98.c"),
            Object(Matching, "game/game_fn_8017FFA0.c"),
            Object(Matching, "game/game_fn_8017FFA8.c"),
            Object(Matching, "game/game_fn_8017FFB0.c"),
            Object(Matching, "game/game_fn_8017FFB8.c"),
            Object(Matching, "game/game_fn_8017FFC0.c"),
            Object(Matching, "game/game_fn_80180014.c"),
            Object(Matching, "game/game_fn_801800F8.c"),
            Object(Matching, "game/game_fn_80180114.c"),
            Object(Matching, "game/game_fn_80180130.c"),
            Object(Matching, "game/game_fn_80180138.c"),
            Object(Matching, "game/game_fn_8018015C.c"),
            Object(Matching, "game/game_fn_80180170.c"),
            Object(Matching, "game/game_fn_801801A4.c"),
            Object(Matching, "game/game_fn_801801D0.c"),
            Object(Matching, "game/game_fn_801801D4.c"),
            Object(Matching, "game/game_fn_801801F4.c"),
            Object(Matching, "game/game_fn_80180214.c"),
            Object(Matching, "game/game_fn_80180234.c"),
            Object(Matching, "game/game_fn_80180254.c"),
            Object(NonMatching, "game/game_fn_80180274.c"),
            Object(Matching, "game/game_fn_80180374.c"),
            Object(Matching, "game/game_fn_8018037C.c"),
            Object(Matching, "game/game_fn_80180384.c"),
            Object(Matching, "game/game_fn_8018038C.c"),
            Object(NonMatching, "game/game_fn_80180430.c"),
            Object(Matching, "game/game_fn_80180454.c"),
            Object(Matching, "game/game_fn_801804AC.c"),
            Object(Matching, "game/game_fn_80180518.c"),
            Object(Matching, "game/game_fn_80180554.c"),
            Object(Matching, "game/game_fn_801805A0.c"),
            Object(Matching, "game/game_fn_801805E0.c"),
            Object(Matching, "game/game_fn_801806D4.c"),
            Object(Matching, "game/game_fn_801806E8.c"),
            Object(NonMatching, "game/game_fn_801807B0.c"),
            Object(Matching, "game/game_fn_8018094C.c"),
            Object(Matching, "game/game_fn_8018095C.c"),
            Object(Matching, "game/game_fn_801809A0.c"),
            Object(Matching, "game/game_fn_801809B8.c"),
            Object(Matching, "game/game_fn_80180A38.c"),
            Object(Matching, "game/game_fn_80180A9C.c"),
            Object(Matching, "game/game_fn_80180AC8.c"),
            Object(Matching, "game/game_fn_80180AD0.c"),
            Object(Matching, "game/game_fn_80180B5C.c"),
            Object(Matching, "game/game_fn_80180BE4.c"),
            Object(Matching, "game/game_fn_80180C4C.c"),
            Object(Matching, "game/game_fn_80180C54.c"),
            Object(Matching, "game/game_fn_80180C94.c"),
            Object(Matching, "game/game_fn_80180CC8.c"),
            Object(Matching, "game/game_fn_80180CE4.c"),
            Object(NonMatching, "game/game_fn_80180D0C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80180DDC.c"),
            Object(NonMatching, "game/game_fn_80180E14.c"),
            Object(Matching, "game/game_fn_80180ED8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801810A0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801813E4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80181530.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018163C.c"),
            Object(NonMatching, "game/game_fn_8018168C.c"),
            Object(NonMatching, "game/game_fn_801816D4.c"),
            Object(Matching, "game/game_fn_80181808.c"),
            Object(Matching, "game/game_fn_8018183C.c"),
            Object(NonMatching, "game/game_fn_80181870.c"),
            Object(Matching, "game/game_fn_80181924.c"),
            Object(Matching, "game/game_fn_8018199C.c"),
            Object(Matching, "game/game_fn_80181A00.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80181BD8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80181E30.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80181F5C.c"),
            Object(Matching, "game/game_fn_80181FD8.c"),
            Object(Matching, "game/game_fn_80182014.c"),
            Object(Matching, "game/game_fn_801820B0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80182274.c"),
            Object(Matching, "game/game_fn_80182290.c"),
            Object(Matching, "game/game_fn_80182370.c"),
            Object(Matching, "game/game_fn_80182380.c"),
            Object(Matching, "game/game_fn_80182428.c"),
            Object(Matching, "game/game_fn_80182430.c"),
            Object(Matching, "game/game_fn_80182440.c"),
            Object(Matching, "game/game_fn_80182448.c"),
            Object(NonMatching, "game/game_fn_80182514.c"),
            Object(Matching, "game/game_fn_80182798.c"),
            Object(NonMatching, "game/game_fn_8018284C.c"),
            Object(NonMatching, "game/game_fn_80182984.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80182B84.c"),
            Object(Matching, "game/game_fn_80182BCC.c"),
            Object(Matching, "game/game_fn_80182C68.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80182E64.c"),
            Object(Matching, "game/game_fn_80182E90.c"),
            Object(Matching, "game/game_fn_80182FA8.c"),
            Object(Matching, "game/game_fn_80182FCC.c"),
            Object(Matching, "game/game_fn_80183068.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80183208.c"),
            Object(Matching, "game/game_fn_8018322C.c"),
            Object(Matching, "game/game_fn_801833B8.c"),
            Object(Matching, "game/game_fn_80183454.c"),
            Object(Matching, "game/game_fn_801834F0.c"),
            Object(Matching, "game/game_fn_8018358C.c"),
            Object(Matching, "game/game_fn_801835F4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801837AC.c"),
            Object(Matching, "game/game_fn_801837D8.c"),
            Object(Matching, "game/game_fn_8018385C.c"),
            Object(Matching, "game/game_fn_8018391C.c"),
            Object(Matching, "game/game_fn_801839A4.c"),
            Object(Matching, "game/game_fn_801839D8.c"),
            Object(Matching, "game/game_fn_80183A68.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80183C54.c"),
            Object(Matching, "game/game_fn_80183D94.c"),
            Object(Matching, "game/game_fn_80183DD4.c"),
            Object(Matching, "game/game_fn_80183E44.c"),
            Object(Matching, "game/game_fn_80183EE0.c"),
            Object(NonMatching, "game/game_fn_80183F70.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80184094.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018422C.c"),
            Object(Matching, "game/game_fn_8018424C.c"),
            Object(Matching, "game/game_fn_801842A8.c"),
            Object(NonMatching, "game/game_fn_8018437C.c"),
            Object(Matching, "game/game_fn_80184740.c"),
            Object(Matching, "game/game_fn_801847AC.c"),
            Object(Matching, "game/game_fn_80184818.c"),
            Object(Matching, "game/game_fn_80184884.c"),
            Object(Matching, "game/game_fn_801848AC.c"),
            Object(Matching, "game/game_fn_80184950.c"),
            Object(Matching, "game/game_fn_80184990.c"),
            Object(Matching, "game/game_fn_801849E0.c"),
            Object(Matching, "game/game_fn_80184A68.c"),
            Object(Matching, "game/game_fn_80184C1C.c"),
            Object(Matching, "game/game_fn_80184C7C.c"),
            Object(Matching, "game/game_fn_80184C98.c"),
            Object(Matching, "game/game_fn_80184CC4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80184E3C.c"),
            Object(Matching, "game/game_fn_80185000.c"),
            Object(Matching, "game/game_fn_80185008.c"),
            Object(Matching, "game/game_fn_8018504C.c"),
            Object(Matching, "game/game_fn_80185078.c"),
            Object(Matching, "game/game_fn_801850CC.c"),
            Object(Matching, "game/game_fn_801850E4.c"),
            Object(Matching, "game/game_fn_801850FC.c"),
            Object(NonMatching, "game/game_fn_80185108.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801851A0.c"),
            Object(NonMatching, "game/game_fn_8018524C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801853F0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80185494.c"),
            Object(Matching, "game/game_fn_8018549C.c"),
            Object(Matching, "game/game_fn_801854A8.c"),
            Object(Matching, "game/game_fn_801854B4.c"),
            Object(Matching, "game/game_fn_8018560C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801857B4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801858E0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801859FC.c"),
            Object(Matching, "game/game_fn_80185A44.c"),
            Object(Matching, "game/game_fn_80185AE8.c"),
            Object(Matching, "game/game_fn_80185C64.c"),
            Object(NonMatching, "game/game_fn_80185CA4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80185E0C.c"),
            Object(NonMatching, "game/game_fn_80185F10.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80185FD0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801861C4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801865EC.c"),
            Object(NonMatching, "game/game_fn_8018666C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018680C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80186954.c"),
            Object(Matching, "game/game_fn_801869DC.c"),
            Object(Matching, "game/game_fn_801869E4.c"),
            Object(NonMatching, "game/game_fn_801869F8.c"),
            Object(Matching, "game/game_fn_80186A58.c"),
            Object(Matching, "game/game_fn_80186A80.c"),
            Object(NonMatching, "game/game_fn_80186A88.c"),
            Object(Matching, "game/game_fn_80186C88.c"),
            Object(Matching, "game/game_fn_80186D74.c"),
            Object(Matching, "game/game_fn_80186E10.c"),
            Object(NonMatching, "game/game_fn_80186F70.c"),
            Object(Matching, "game/game_fn_801870D0.c"),
            Object(Matching, "game/game_fn_80187120.c"),
            Object(NonMatching, "game/game_fn_801871F0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80187320.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80187488.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801875FC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018782C.c"),
            Object(Matching, "game/game_fn_801878D0.c"),
            Object(Matching, "game/game_fn_801878D8.c"),
            Object(Matching, "game/game_fn_801878E0.c"),
            Object(NonMatching, "game/game_fn_80187968.c"),
            Object(Matching, "game/game_fn_801879E8.c"),
            Object(Matching, "game/game_fn_80187A34.c"),
            Object(Matching, "game/game_fn_80187A3C.c"),
            Object(Matching, "game/game_fn_80187A44.c"),
            Object(NonMatching, "game/game_fn_80187A4C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80187BB4.c"),
            Object(Matching, "game/game_fn_80187DF4.c"),
            Object(NonMatching, "game/game_fn_80187E40.c"),
            Object(Matching, "game/game_fn_8018807C.c"),
            Object(Matching, "game/game_fn_8018812C.c"),
            Object(Matching, "game/game_fn_80188268.c"),
            Object(Matching, "game/game_fn_80188288.c"),
            Object(Matching, "game/game_fn_801882C4.c"),
            Object(NonMatching, "game/game_fn_801882D0.c"),
            Object(NonMatching, "game/game_fn_80188384.c"),
            Object(Matching, "game/game_fn_8018855C.c"),
            Object(Matching, "game/game_fn_80188560.c"),
            Object(Matching, "game/game_fn_8018856C.c"),
            Object(Matching, "game/game_fn_80188578.c"),
            Object(Matching, "game/game_fn_80188584.c"),
            Object(Matching, "game/game_fn_80188648.c"),
            Object(Matching, "game/game_fn_8018865C.c"),
            Object(Matching, "game/game_fn_80188710.c"),
            Object(Matching, "game/game_fn_801887C4.c"),
            Object(Matching, "game/game_fn_80188868.c"),
            Object(Matching, "game/game_fn_80188930.c"),
            Object(Matching, "game/game_fn_801889D8.c"),
            Object(Matching, "game/game_fn_80188A7C.c"),
            Object(Matching, "game/game_fn_80188B44.c"),
            Object(Matching, "game/game_fn_80188C1C.c"),
            Object(Matching, "game/game_fn_80188E28.c"),
            Object(Matching, "game/game_fn_80189028.c"),
            Object(Matching, "game/game_fn_801891D8.c"),
            Object(Matching, "game/game_fn_80189390.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801895E8.c"),
            Object(Matching, "game/game_fn_801896A0.c"),
            Object(Matching, "game/game_fn_80189760.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80189968.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80189B70.c"),
            Object(NonMatching, "game/game_fn_80189C14.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80189E7C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018A060.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018A1C8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018A310.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018A3D8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018A574.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018A88C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018AA30.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018ABD4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018AD14.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018AEB0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018B058.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018B210.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018B3C8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018B580.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018B770.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018B928.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018BAE0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018BC68.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018BD94.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018BEC0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018BFEC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018C118.c"),
            Object(NonMatching, "game/game_fn_8018C2D0.c"),
            Object(Matching, "game/game_fn_8018C540.c"),
            Object(NonMatching, "game/game_fn_8018C6EC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018C79C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018C84C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018C8FC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018CB70.c"),
            Object(NonMatching, "game/game_fn_8018CD18.c"),
            Object(NonMatching, "game/game_fn_8018CEC0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018CFB4.c"),
            Object(NonMatching, "game/game_fn_8018D020.c"),
            Object(Matching, "game/game_fn_8018D0D0.c"),
            Object(Matching, "game/game_fn_8018D160.c"),
            Object(Matching, "game/game_fn_8018D1F0.c"),
            Object(Matching, "game/game_fn_8018D2E0.c"),
            Object(NonMatching, "game/game_fn_8018D400.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018D688.c"),
            Object(Matching, "game/game_fn_8018D724.c"),
            Object(Matching, "game/game_fn_8018D788.c"),
            Object(NonMatching, "game/game_fn_8018D7DC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018D998.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018DC24.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018DE9C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8018E0D8.c"),
            Object(Matching, "game/game_fn_8018E1C4.c"),
            Object(Matching, "game/game_fn_8018E230.c"),
            Object(Matching, "game/game_fn_8018E24C.c"),
            Object(Matching, "game/game_fn_8018E260.c"),
            Object(Matching, "game/game_fn_8018E26C.c"),
            Object(NonMatching, "game/game_fn_8018E504.c"),
            Object(Matching, "game/game_fn_8018E8B8.c"),
            Object(Matching, "game/game_fn_8018E8DC.c"),
            Object(Matching, "game/game_fn_8018E8E4.c"),
            Object(Matching, "game/game_fn_8018E934.c"),
            Object(Matching, "game/game_fn_8018EA58.c"),
            Object(Matching, "game/game_fn_8018EACC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018EC8C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018EDE4.c"),
            Object(Matching, "game/game_fn_8018EEEC.c"),
            Object(Matching, "game/game_fn_8018EF9C.c"),
            Object(Matching, "game/game_fn_8018EFB0.c"),
            Object(Matching, "game/game_fn_8018F014.c"),
            Object(Matching, "game/game_fn_8018F0A0.c"),
            Object(Matching, "game/game_fn_8018F134.c"),
            Object(Matching, "game/game_fn_8018F1D0.c"),
            Object(Matching, "game/game_fn_8018F31C.c"),
            Object(NonMatching, "game/game_fn_8018F378.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018F6F4.c"),
            Object(Matching, "game/game_fn_8018F764.c"),
            Object(NonMatching, "game/game_fn_8018F76C.c"),
            Object(Matching, "game/game_fn_8018F808.c"),
            Object(Matching, "game/game_fn_8018F81C.c"),
            Object(Matching, "game/game_fn_8018F864.c"),
            Object(Matching, "game/game_fn_8018F8A4.c"),
            Object(NonMatching, "game/game_fn_8018F948.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018FAC8.c"),
            Object(Matching, "game/game_fn_8018FB74.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8018FC6C.c"),
            Object(Matching, "game/game_fn_8018FD70.c"),
            Object(Matching, "game/game_fn_8018FEDC.c"),
            Object(NonMatching, "game/game_fn_8018FFBC.c"),
            Object(Matching, "game/game_fn_80190280.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80190320.c"),
            Object(Matching, "game/game_fn_801903C4.c"),
            Object(Matching, "game/game_fn_8019045C.c"),
            Object(Matching, "game/game_fn_80190500.c"),
            Object(Matching, "game/game_fn_80190508.c"),
            Object(Matching, "game/game_fn_80190558.c"),
            Object(Matching, "game/game_fn_801905CC.c"),
            Object(Matching, "game/game_fn_80190638.c"),
            Object(Matching, "game/game_fn_80190680.c"),
            Object(Matching, "game/game_fn_80190794.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801908EC.c"),
            Object(Matching, "game/game_fn_80190930.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80190A90.c"),
            Object(Matching, "game/game_fn_80190BD0.c"),
            Object(Matching, "game/game_fn_80190C58.c"),
            Object(Matching, "game/game_fn_80190D0C.c"),
            Object(Matching, "game/game_fn_80190D7C.c"),
            Object(Matching, "game/game_fn_80190E60.c"),
            Object(Matching, "game/game_fn_80190EEC.c"),
            Object(NonMatching, "game/game_fn_80191034.c"),
            Object(Matching, "game/game_fn_801911B0.c"),
            Object(Matching, "game/game_fn_801911C8.c"),
            Object(Matching, "game/game_fn_801911D0.c"),
            Object(Matching, "game/game_fn_801911D8.c"),
            Object(Matching, "game/game_fn_801911F4.c"),
            Object(Matching, "game/game_fn_801911FC.c"),
            Object(Matching, "game/game_fn_80191204.c"),
            Object(NonMatching, "game/game_fn_8019120C.c"),
            Object(Matching, "game/game_fn_80191360.c"),
            Object(NonMatching, "game/game_fn_801913F4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801914D8.c"),
            Object(Matching, "game/game_fn_80191568.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801916D0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019197C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80191BA8.c"),
            Object(Matching, "game/game_fn_80191C8C.c"),
            Object(Matching, "game/game_fn_80191E84.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80191F04.c"),
            Object(Matching, "game/game_fn_80191F58.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80192318.c"),
            Object(Matching, "game/game_fn_801925F0.c"),
            Object(NonMatching, "game/game_fn_801926EC.c"),
            Object(NonMatching, "game/game_fn_801929A4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80192E8C.c"),
            Object(NonMatching, "game/game_fn_80192F54.c"),
            Object(NonMatching, "game/game_fn_801931C4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801936FC.c"),
            Object(Matching, "game/game_fn_80193838.c"),
            Object(Matching, "game/game_fn_80193840.c"),
            Object(Matching, "game/game_fn_80193848.c"),
            Object(Matching, "game/game_fn_80193850.c"),
            Object(Matching, "game/game_fn_80193858.c"),
            Object(Matching, "game/game_fn_80193860.c"),
            Object(Matching, "game/game_fn_80193868.c"),
            Object(Matching, "game/game_fn_80193870.c"),
            Object(Matching, "game/game_fn_80193878.c"),
            Object(Matching, "game/game_fn_80193880.c"),
            Object(Matching, "game/game_fn_80193888.c"),
            Object(Matching, "game/game_fn_80193890.c"),
            Object(Matching, "game/game_fn_80193898.c"),
            Object(Matching, "game/game_fn_801938A0.c"),
            Object(Matching, "game/game_fn_801938A8.c"),
            Object(Matching, "game/game_fn_801938B0.c"),
            Object(Matching, "game/game_fn_801938B8.c"),
            Object(Matching, "game/game_fn_801938C0.c"),
            Object(Matching, "game/game_fn_801938C8.c"),
            Object(Matching, "game/game_fn_801938D0.c"),
            Object(Matching, "game/game_fn_801938D8.c"),
            Object(NonMatching, "game/game_fn_801938E0.c"),
            Object(Matching, "game/game_fn_801938FC.c"),
            Object(Matching, "game/game_fn_801939A8.c"),
            Object(Matching, "game/game_fn_801939DC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80193AB8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80193B94.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80193CB4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80193D64.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80193E1C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80193F3C.c"),
            Object(NonMatching, "game/game_fn_801941EC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801944C0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019453C.c"),
            Object(NonMatching, "game/game_fn_801945D4.c"),
            Object(Matching, "game/game_fn_8019475C.c"),
            Object(NonMatching, "game/game_fn_801947F4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80194998.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80194AC4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80194E80.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80194F80.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801950D4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801952E8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801957EC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80195960.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80195AEC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801964E8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80196578.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019663C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801966E0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80196784.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80196918.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80196B10.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80196DE4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019753C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801978F8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80197900.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80197910.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80197D20.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198154.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80198318.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198420.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198724.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80198850.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801989CC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198A2C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198AAC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198BF4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_80198C8C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80198F78.c"),
            Object(Matching, "game/game_fn_8019901C.c"),
            Object(Matching, "game/game_fn_801990E0.c"),
            Object(Matching, "game/game_fn_801990E8.c"),
            Object(Matching, "game/game_fn_801990F0.c"),
            Object(Matching, "game/game_fn_801990F8.c"),
            Object(Matching, "game/game_fn_80199100.c"),
            Object(Matching, "game/game_fn_80199108.c"),
            Object(Matching, "game/game_fn_80199110.c"),
            Object(Matching, "game/game_fn_80199118.c"),
            Object(Matching, "game/game_fn_80199120.c"),
            Object(Matching, "game/game_fn_80199128.c"),
            Object(Matching, "game/game_fn_80199130.c"),
            Object(Matching, "game/game_fn_80199138.c"),
            Object(Matching, "game/game_fn_80199154.c"),
            Object(Matching, "game/game_fn_8019915C.c"),
            Object(Matching, "game/game_fn_80199164.c"),
            Object(Matching, "game/game_fn_8019916C.c"),
            Object(Matching, "game/game_fn_80199174.c"),
            Object(Matching, "game/game_fn_8019917C.c"),
            Object(Matching, "game/game_fn_801991E0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80199358.c"),
            Object(Matching, "game/game_fn_80199428.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80199598.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801997E8.c"),
            Object(NonMatching, "game/game_fn_80199868.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_80199ABC.c"),
            Object(Matching, "game/game_fn_80199B84.c"),
            Object(Matching, "game/game_fn_80199E18.c"),
            Object(Matching, "game/game_fn_80199EBC.c"),
            Object(NonMatching, "game/game_fn_80199F10.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019A0DC.c"),
            Object(Matching, "game/game_fn_8019A150.c"),
            Object(Matching, "game/game_fn_8019A300.c"),
            Object(Matching, "game/game_fn_8019A3A4.c"),
            Object(Matching, "game/game_fn_8019A3E0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019A5C8.c"),
            Object(NonMatching, "game/game_fn_8019A5DC.c"),
            Object(Matching, "game/game_fn_8019A7C4.c"),
            Object(Matching, "game/game_fn_8019A868.c"),
            Object(NonMatching, "game/game_fn_8019A8C4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019AAB4.c"),
            Object(Matching, "game/game_fn_8019AAF0.c"),
            Object(Matching, "game/game_fn_8019AD40.c"),
            Object(Matching, "game/game_fn_8019ADE4.c"),
            Object(Matching, "game/game_fn_8019AE88.c"),
            Object(Matching, "game/game_fn_8019AF2C.c"),
            Object(Matching, "game/game_fn_8019AFEC.c"),
            Object(Matching, "game/game_fn_8019B090.c"),
            Object(Matching, "game/game_fn_8019B134.c"),
            Object(Matching, "game/game_fn_8019B13C.c"),
            Object(NonMatching, "game/game_fn_8019B1BC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019B4D4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019B6F0.c"),
            Object(Matching, "game/game_fn_8019B73C.c"),
            Object(Matching, "game/game_fn_8019B7C4.c"),
            Object(Matching, "game/game_fn_8019B8B4.c"),
            Object(Matching, "game/game_fn_8019B914.c"),
            Object(Matching, "game/game_fn_8019B970.c"),
            Object(Matching, "game/game_fn_8019B9F4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019BAA8.c"),
            Object(Matching, "game/game_fn_8019BB00.c"),
            Object(Matching, "game/game_fn_8019BB78.c"),
            Object(Matching, "game/game_fn_8019BB9C.c"),
            Object(Matching, "game/game_fn_8019BBB4.c"),
            Object(Matching, "game/game_fn_8019BBCC.c"),
            Object(Matching, "game/game_fn_8019BBF0.c"),
            Object(Matching, "game/game_fn_8019BC48.c"),
            Object(Matching, "game/game_fn_8019BCEC.c"),
            Object(Matching, "game/game_fn_8019BD44.c"),
            Object(NonMatching, "game/game_fn_8019BDE8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019BFA0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019C06C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019C26C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019C3B8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019C4E4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019C648.c"),
            Object(NonMatching, "game/game_fn_8019C7A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019CC28.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019CE08.c"),
            Object(Matching, "game/game_fn_8019CE1C.c"),
            Object(NonMatching, "game/game_fn_8019CE34.c"),
            Object(Matching, "game/game_fn_8019CE64.c"),
            Object(Matching, "game/game_fn_8019CE6C.c"),
            Object(Matching, "game/game_fn_8019CE74.c"),
            Object(Matching, "game/game_fn_8019CE7C.c"),
            Object(Matching, "game/game_fn_8019CEF8.c"),
            Object(Matching, "game/game_fn_8019CFBC.c"),
            Object(Matching, "game/game_fn_8019CFC4.c"),
            Object(NonMatching, "game/game_fn_8019D030.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019D34C.c"),
            Object(Matching, "game/game_fn_8019D390.c"),
            Object(Matching, "game/game_fn_8019D50C.c"),
            Object(NonMatching, "game/game_fn_8019D560.c"),
            Object(Matching, "game/game_fn_8019D620.c"),
            Object(Matching, "game/game_fn_8019D66C.c"),
            Object(Matching, "game/game_fn_8019D714.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019D92C.c"),
            Object(NonMatching, "game/game_fn_8019DA3C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019DCF4.c"),
            Object(Matching, "game/game_fn_8019DD64.c"),
            Object(Matching, "game/game_fn_8019DDBC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019DEFC.c"),
            Object(Matching, "game/game_fn_8019DF5C.c"),
            Object(Matching, "game/game_fn_8019DF98.c"),
            Object(Matching, "game/game_fn_8019DFA0.c"),
            Object(Matching, "game/game_fn_8019DFF8.c"),
            Object(NonMatching, "game/game_fn_8019E0B0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019E580.c"),
            Object(Matching, "game/game_fn_8019E5E4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019E8C8.c"),
            Object(NonMatching, "game/game_fn_8019ECA0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019EF50.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019EFAC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019F00C.c"),
            Object(Matching, "game/game_fn_8019F1B0.c"),
            Object(Matching, "game/game_fn_8019F1B4.c"),
            Object(Matching, "game/game_fn_8019F1C0.c"),
            Object(Matching, "game/game_fn_8019F1CC.c"),
            Object(Matching, "game/game_fn_8019F1D8.c"),
            Object(Matching, "game/game_fn_8019F1EC.c"),
            Object(Matching, "game/game_fn_8019F228.c"),
            Object(Matching, "game/game_fn_8019F284.c"),
            Object(NonMatching, "game/game_fn_8019F320.c"),
            Object(Matching, "game/game_fn_8019F508.c"),
            Object(Matching, "game/game_fn_8019F5AC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019F6F0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019F800.c"),
            Object(NonMatching, "game/game_fn_8019F8A8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019FA94.c"),
            Object(NonMatching, "game/game_fn_8019FAB8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_8019FCB4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_8019FEBC.c"),
            Object(Matching, "game/game_fn_8019FEC0.c"),
            Object(Matching, "game/game_fn_8019FECC.c"),
            Object(Matching, "game/game_fn_8019FED8.c"),
            Object(Matching, "game/game_fn_8019FEE4.c"),
            Object(Matching, "game/game_fn_8019FF5C.c"),
            Object(Matching, "game/game_fn_801A0008.c"),
            Object(Matching, "game/game_fn_801A00B8.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A0268.c"),
            Object(NonMatching, "game/game_fn_801A0284.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A0450.c"),
            Object(Matching, "game/game_fn_801A19BC.c"),
            Object(Matching, "game/game_fn_801A1A04.c"),
            Object(Matching, "game/game_fn_801A1A4C.c"),
            Object(Matching, "game/game_fn_801A1AB0.c"),
            Object(Matching, "game/game_fn_801A1AF4.c"),
            Object(Matching, "game/game_fn_801A1B34.c"),
            Object(Matching, "game/game_fn_801A1BD0.c"),
            Object(Matching, "game/game_fn_801A1C78.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A1E14.c"),
            Object(Matching, "game/game_fn_801A1F18.c"),
            Object(NonMatching, "game/game_fn_801A1F8C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A2540.c"),
            Object(NonMatching, "game/game_fn_801A260C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A29E0.c"),
            Object(NonMatching, "game/game_fn_801A2A54.c"),
            Object(Matching, "game/game_fn_801A2AB4.c"),
            Object(NonMatching, "game/game_fn_801A2BCC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A2D64.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A2FB4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A318C.c"),
            Object(Matching, "game/game_fn_801A3200.c"),
            Object(NonMatching, "game/game_fn_801A329C.c"),
            Object(Matching, "game/game_fn_801A3420.c"),
            Object(NonMatching, "game/game_fn_801A34BC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A35F4.c"),
            Object(NonMatching, "game/game_fn_801A36C0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A38D0.c"),
            Object(Matching, "game/game_fn_801A3998.c"),
            Object(Matching, "game/game_fn_801A39A0.c"),
            Object(Matching, "game/game_fn_801A39A8.c"),
            Object(Matching, "game/game_fn_801A39B0.c"),
            Object(Matching, "game/game_fn_801A39B8.c"),
            Object(Matching, "game/game_fn_801A39D4.c"),
            Object(Matching, "game/game_fn_801A39DC.c"),
            Object(NonMatching, "game/game_fn_801A3A78.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A3D18.c"),
            Object(NonMatching, "game/game_fn_801A3DF8.c"),
            Object(Matching, "game/game_fn_801A42A0.c"),
            Object(Matching, "game/game_fn_801A438C.c"),
            Object(Matching, "game/game_fn_801A4410.c"),
            Object(Matching, "game/game_fn_801A4418.c"),
            Object(Matching, "game/game_fn_801A4420.c"),
            Object(NonMatching, "game/game_fn_801A4430.c"),
            Object(Matching, "game/game_fn_801A4874.s"),
            Object(Matching, "game/game_fn_801A4880.c"),
            Object(Matching, "game/game_fn_801A48EC.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A4AA0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A4CE0.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A4F74.c"),
            Object(Matching, "game/game_fn_801A4FCC.c"),
            Object(Matching, "game/game_fn_801A5068.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A5224.c"),
            Object(Matching, "game/game_fn_801A5290.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A53C4.c"),
            Object(Matching, "game/game_fn_801A5620.c"),
            Object(NonMatching, "game/game_fn_801A5684.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A5838.c"),
            Object(Matching, "game/game_fn_801A583C.c"),
            Object(Matching, "game/game_fn_801A5848.c"),
            Object(Matching, "game/game_fn_801A5854.c"),
            Object(NonMatching, "game/game_fn_801A5860.c"),
            Object(Matching, "game/game_fn_801A58FC.c"),
            Object(NonMatching, "game/game_fn_801A5910.c"),
            Object(NonMatching, "game/game_fn_801A59CC.c"),
            Object(Matching, "game/game_fn_801A5AA0.c"),
            Object(Matching, "game/game_fn_801A5B70.c"),
            Object(Matching, "game/game_fn_801A5BA0.c"),
            Object(Matching, "game/game_fn_801A5BD0.c"),
            Object(Matching, "game/game_fn_801A5C00.c"),
            Object(Matching, "game/game_fn_801A5C30.c"),
            Object(Matching, "game/game_fn_801A5CE0.c"),
            Object(Matching, "game/game_fn_801A5D04.c"),
            Object(Matching, "game/game_fn_801A5D28.c"),
            Object(Matching, "game/game_fn_801A5D5C.c"),
            Object(Matching, "game/game_fn_801A5DBC.c"),
            Object(Matching, "game/game_fn_801A5E10.c"),
            Object(Matching, "game/game_fn_801A5E20.c"),
            Object(Matching, "game/game_fn_801A5E30.c"),
            Object(Matching, "game/game_fn_801A5E68.c"),
            Object(Matching, "game/game_fn_801A5EB4.c"),
            Object(Matching, "game/game_fn_801A5EC4.c"),
            Object(Matching, "game/game_fn_801A5ED4.c"),
            Object(Matching, "game/game_fn_801A5F20.c"),
            Object(Matching, "game/game_fn_801A5F30.c"),
            Object(Matching, "game/game_fn_801A5F40.c"),
            Object(Matching, "game/game_fn_801A5F54.c"),
            Object(Matching, "game/game_fn_801A5F90.c"),
            Object(Matching, "game/game_fn_801A5FA0.c"),
            Object(Matching, "game/game_fn_801A5FB0.c"),
            Object(NonMatching, "game/game_fn_801A6350.c"),
            Object(NonMatching, "game/game_fn_801A63A0.c"),
            Object(Matching, "game/game_fn_801A6410.c"),
            Object(Matching, "game/game_fn_801A64F8.c"),
            Object(NonMatching, "game/game_fn_801A657C.c"),
            Object(Matching, "game/game_fn_801A65C0.c"),
            Object(Matching, "game/game_fn_801A65E0.c"),
            Object(Matching, "game/game_fn_801A664C.c"),
            Object(Matching, "game/game_fn_801A6654.c"),
            Object(Matching, "game/game_fn_801A665C.c"),
            Object(Matching, "game/game_fn_801A66C4.c"),
            Object(Matching, "game/game_fn_801A67C4.c"),
            Object(NonMatching, "game/game_fn_801A68C4.c"),
            Object(NonMatching, "game/game_fn_801A69F0.c"),
            Object(Matching, "game/game_fn_801A6ADC.c"),
            Object(Matching, "game/game_fn_801A6C58.c"),
            Object(Matching, "game/game_fn_801A6CB4.c"),
            Object(Matching, "game/game_fn_801A6D10.c"),
            Object(Matching, "game/game_fn_801A6D40.c"),
            Object(Matching, "game/game_fn_801A6D94.c"),
            Object(Matching, "game/game_fn_801A6D9C.c"),
            Object(Matching, "game/game_fn_801A6DA4.c"),
            Object(Matching, "game/game_fn_801A6DAC.c"),
            Object(Matching, "game/game_fn_801A6DB4.c"),
            Object(Matching, "game/game_fn_801A6DBC.c"),
            Object(Matching, "game/game_fn_801A6DC4.c"),
            Object(Matching, "game/game_fn_801A6DCC.c"),
            Object(Matching, "game/game_fn_801A6DD4.c"),
            Object(Matching, "game/game_fn_801A6DDC.c"),
            Object(Matching, "game/game_fn_801A6DE4.c"),
            Object(Matching, "game/game_fn_801A6DEC.c"),
            Object(Matching, "game/game_fn_801A6DF4.c"),
            Object(Matching, "game/game_fn_801A6DFC.c"),
            Object(Matching, "game/game_fn_801A6E04.c"),
            Object(Matching, "game/game_fn_801A6E14.c"),
            Object(Matching, "game/game_fn_801A6E24.c"),
            Object(Matching, "game/game_fn_801A6E2C.c"),
            Object(Matching, "game/game_fn_801A6E34.c"),
            Object(Matching, "game/game_fn_801A6E5C.c"),
            Object(Matching, "game/game_fn_801A6E90.c"),
            Object(Matching, "game/game_fn_801A6EB0.c"),
            Object(Matching, "game/game_fn_801A6EC4.c"),
            Object(Matching, "game/game_fn_801A6EE0.c"),
            Object(Matching, "game/game_fn_801A6EFC.c"),
            Object(Matching, "game/game_fn_801A6F64.c"),
            Object(Matching, "game/game_fn_801A6F94.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A7098.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A717C.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801A7228.c"),
            Object(Matching, "game/game_fn_801A7324.c"),
            Object(Matching, "game/game_fn_801A7354.c"),
            Object(Matching, "game/game_fn_801A742C.c"),
            Object(Matching, "game/game_fn_801A7434.c"),
            Object(Matching, "game/game_fn_801A743C.c"),
            Object(Matching, "game/game_fn_801A7460.c"),
            Object(Matching, "game/game_fn_801A7468.c"),
            Object(Matching, "game/game_fn_801A7470.c"),
            Object(Matching, "game/game_fn_801A7478.c"),
            Object(Matching, "game/game_fn_801A7480.c"),
            Object(Matching, "game/game_fn_801A7488.c"),
            Object(Matching, "game/game_fn_801A7490.c"),
            Object(Matching, "game/game_fn_801A7498.c"),
            Object(Matching, "game/game_fn_801A74A0.c"),
            Object(Matching, "game/game_fn_801A74A8.c"),
            Object(Matching, "game/game_fn_801A74B0.c"),
            Object(Matching, "game/game_fn_801A74B8.c"),
            Object(Matching, "game/game_fn_801A74C0.c"),
            Object(Matching, "game/game_fn_801A74C8.c"),
            Object(Matching, "game/game_fn_801A74D8.c"),
            Object(Matching, "game/game_fn_801A74E8.c"),
            Object(Matching, "game/game_fn_801A74F8.c"),
            Object(Matching, "game/game_fn_801A7500.c"),
            Object(Matching, "game/game_fn_801A7508.c"),
            Object(Matching, "game/game_fn_801A7510.c"),
            Object(Matching, "game/game_fn_801A7518.c"),
            Object(Matching, "game/game_fn_801A7520.c"),
            Object(Matching, "game/game_fn_801A7528.c"),
            Object(Matching, "game/game_fn_801A7530.c"),
            Object(Matching, "game/game_fn_801A7538.c"),
            Object(Matching, "game/game_fn_801A7540.c"),
            Object(Matching, "game/game_fn_801A7548.c"),
            Object(Matching, "game/game_fn_801A7550.c"),
            Object(Matching, "game/game_fn_801A7558.c"),
            Object(Matching, "game/game_fn_801A7560.c"),
            Object(Matching, "game/game_fn_801A7570.c"),
            Object(Matching, "game/game_fn_801A7578.c"),
            Object(Matching, "game/game_fn_801A7580.c"),
            Object(Matching, "game/game_fn_801A7588.c"),
            Object(Matching, "game/game_fn_801A7590.c"),
            Object(Matching, "game/game_fn_801A7598.c"),
            Object(Matching, "game/game_fn_801A75A0.c"),
            Object(Matching, "game/game_fn_801A75A8.c"),
            Object(Matching, "game/game_fn_801A75B0.c"),
            Object(Matching, "game/game_fn_801A75B8.c"),
            Object(Matching, "game/game_fn_801A75C0.c"),
            Object(Matching, "game/game_fn_801A7610.c"),
            Object(Matching, "game/game_fn_801A7644.c"),
            Object(Matching, "game/game_fn_801A764C.c"),
            Object(Matching, "game/game_fn_801A7668.c"),
            Object(Matching, "game/game_fn_801A7670.c"),
            Object(Matching, "game/game_fn_801A7678.c"),
            Object(Matching, "game/game_fn_801A7680.c"),
            Object(Matching, "game/game_fn_801A7688.c"),
            Object(Matching, "game/game_fn_801A76B0.c"),
            Object(Matching, "game/game_fn_801A76B8.c"),
            Object(Matching, "game/game_fn_801A76C0.c"),
            Object(Matching, "game/game_fn_801A76D4.c"),
            Object(Matching, "game/game_fn_801A76DC.c"),
            Object(Matching, "game/game_fn_801A76E4.c"),
            Object(Matching, "game/game_fn_801A76EC.c"),
            Object(Matching, "game/game_fn_801A76F4.c"),
            Object(Matching, "game/game_fn_801A7728.c"),
            Object(Matching, "game/game_fn_801A7744.c"),
            Object(Matching, "game/game_fn_801A7760.c"),
            Object(Matching, "game/game_fn_801A7768.c"),
            Object(Matching, "game/game_fn_801A7770.c"),
            Object(Matching, "game/game_fn_801A7778.c"),
            Object(Matching, "game/game_fn_801A7780.c"),
            Object(Matching, "game/game_fn_801A77B0.c"),
            Object(Matching, "game/game_fn_801A77D4.c"),
            Object(Matching, "game/game_fn_801A77F8.c"),
            Object(Matching, "game/game_fn_801A781C.c"),
            Object(Matching, "game/game_fn_801A7840.c"),
            Object(Matching, "game/game_fn_801A7864.c"),
            Object(Matching, "game/game_fn_801A78C0.c"),
            Object(Matching, "game/game_fn_801A78EC.c"),
            Object(Matching, "game/game_fn_801A7910.c"),
            Object(Matching, "game/game_fn_801A7934.c"),
            Object(NonMatching, "game/game_fn_801A7958.c"),
            Object(NonMatching, "game/game_fn_801A7BA0.c"),
            Object(Matching, "game/game_fn_801A7D20.c"),
            Object(NonMatching, "game/game_fn_801A7D44.c"),
            Object(Matching, "game/game_fn_801A7DEC.c"),
            Object(Matching, "game/game_fn_801A7DFC.c"),
            Object(Matching, "game/game_fn_801A7E04.c"),
            Object(Matching, "game/game_fn_801A7EA8.c"),
            Object(Matching, "game/game_fn_801A7F40.c"),
            Object(Matching, "game/game_fn_801A7F94.c"),
            Object(NonMatching, "game/game_fn_801A8024.c"),
            Object(Matching, "game/game_fn_801A8070.c"),
            Object(
                NonMatching,
                "game/game_fn_801A80FC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801A8168.c"),
            Object(
                NonMatching,
                "game/game_fn_801A81FC.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801A8268.c"),
            Object(NonMatching, "game/game_fn_801A82FC.c"),
            Object(Matching, "game/game_fn_801A83A4.c"),
            Object(Matching, "game/game_fn_801A8408.c"),
            Object(Matching, "game/game_fn_801A8478.c"),
            Object(Matching, "game/game_fn_801A84C8.c"),
            Object(NonMatching, "game/game_fn_801A852C.c"),
            Object(NonMatching, "game/game_fn_801A85D4.c"),
            Object(
                Matching,
                "game/game_fn_801A8660.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                NonMatching,
                "game/game_fn_801A872C.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_801A88D0.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_801A8974.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801A8A18.c"),
            Object(Matching, "game/game_fn_801A8B40.c"),
            Object(NonMatching, "game/game_fn_801A8C60.c"),
            Object(NonMatching, "game/game_fn_801A8CCC.c"),
            Object(Matching, "game/game_fn_801A8D38.c"),
            Object(
                Matching,
                "game/game_fn_801A8DE8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801A8EDC.c"),
            Object(
                Matching,
                "game/game_fn_801A8F08.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(
                Matching,
                "game/game_fn_801A8FE8.c",
                extra_cflags=["-use_lmw_stmw on"],
            ),
            Object(Matching, "game/game_fn_801A90BC.c"),
            Object(Matching, "game/game_fn_801A9118.c"),
            Object(NonMatching, "game/game_fn_801A91D4.c"),
            Object(NonMatching, "game/game_fn_801A9250.c"),
            Object(Matching, "game/game_fn_801A92D0.c"),
            Object(Matching, "game/game_fn_801A9384.c"),
            Object(Matching, "game/game_fn_801A93E8.c"),
            Object(Matching, "game/game_fn_801A9450.c"),
            Object(Matching, "game/game_fn_801A9454.c"),
            Object(Matching, "game/game_fn_801A9468.c"),
            Object(Matching, "game/game_fn_801A9474.c"),
            Object(Matching, "game/game_fn_801A9480.c"),
            Object(NonMatching, "game/game_fn_801A9488.c"),
            Object(Matching, "game/game_fn_801A94B8.c", extra_cflags=["-schedule off"]),
            Object(NonMatching, "game/game_fn_801A94E4.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801A96A8.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801A9758.c"),
            Object(Matching, "game/game_fn_801A977C.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801A98F4.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801A9964.c"),
            Object(Matching, "game/game_fn_801A9984.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801A99B4.c", cflags=cflags_with_optimization("-O1,p")),
            Object(Matching, "game/game_fn_801A9A00.c"),
            Object(Matching, "game/game_fn_801A9A20.c"),
            Object(NonMatching, "game/game_fn_801A9A40.c"),
            Object(Matching, "game/game_fn_801A9B28.c"),
            Object(Matching, "game/game_fn_801A9B30.c"),
            Object(NonMatching, "game/game_fn_801A9B38.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801A9B94.c", cflags=cflags_with_optimization("-O1,p")),
            Object(Matching, "game/game_fn_801A9C78.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801A9CDC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801A9DCC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801A9E40.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801A9EF4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801A9F44.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801A9FA4.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AA388.c"),
            Object(Matching, "game/game_fn_801AA398.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AA4A0.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801AA550.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801AA618.c", extra_cflags=["-schedule off"]),
            Object(NonMatching, "game/game_fn_801AA6D0.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AA9F8.c"),
            Object(Matching, "game/game_fn_801AA9FC.c", extra_cflags=["-schedule off"]),
            Object(NonMatching, "game/game_fn_801AAA28.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801AAAD8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AAB38.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AAC10.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801AAD48.c"),
            Object(Matching, "game/game_fn_801AAD58.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AAE68.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AB048.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AB0C4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AB154.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AB2EC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AB3CC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AB50C.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801ABCA8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ABD3C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ABF34.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AC030.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC0FC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC194.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC2E8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC350.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AC59C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC5E4.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AC7BC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC8AC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC908.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC980.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC9C0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AC9F4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACA40.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACACC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801ACB0C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACC10.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACC94.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACCA0.c", extra_cflags=["-schedule off"]),
            Object(Matching, "game/game_fn_801ACD08.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACD8C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801ACDC4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACDD4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACE30.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACF80.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ACFB0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801ACFE8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD08C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD404.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD46C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD490.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD4B4.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801AD528.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD5FC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD6F4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD72C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD734.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD770.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD7C0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD848.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD898.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD8B4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD8E8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD8F8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AD928.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD95C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AD9F4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADAF8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADB70.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADBC0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADC08.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801ADC50.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801ADCF8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADD5C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADE0C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801ADEEC.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801ADFC4.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AE140.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE1D0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE284.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE2F4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE368.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AE3C8.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AE530.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE5DC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AE6B0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AE91C.c", cflags=cflags_with_optimization("-O3,p")),
            Object(Matching, "game/game_fn_801AEA78.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AEAE0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AEB74.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AECAC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AED2C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AEE64.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801AEF18.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AEF3C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF000.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF0E4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF180.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801AF37C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF760.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF824.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF85C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF8A4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF8E4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF924.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF96C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AF9B0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801AFA74.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801AFCC8.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801B002C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0138.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B01F8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B02F0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B05B0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B05E8.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801B08BC.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801B097C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B09DC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B09F0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0A28.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0A6C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0B30.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0B64.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0BB4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0C08.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0CA4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0D30.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801B0DD4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0E68.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B0E6C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801B1028.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1070.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B10A4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B10EC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B110C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1150.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1194.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B11CC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1204.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1344.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B138C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1410.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1440.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B14B8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B151C.c", extra_cflags=["-schedule off", "-opt nopeephole", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801B1610.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1740.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B17A4.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B17A8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B17B0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B191C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1924.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B192C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B196C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B19BC.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B19D8.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1A1C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B1B0C.c", cflags=cflags_with_optimization("-O3")),
            Object(NonMatching, "game/game_fn_801B1BA0.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2348.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2380.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2410.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2428.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B243C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2444.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801B244C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2528.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B261C.c", extra_cflags=["-schedule off", "-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2748.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B2818.c", extra_cflags=["-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B2878.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B2914.c", extra_cflags=["-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801B2980.c", extra_cflags=["-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B3470.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B3558.c", mw_version="GC/1.2.5n", extra_cflags=["-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801B35BC.c", mw_version="GC/1.2.5n", extra_cflags=["-opt nopeephole"]),
            Object(NonMatching, "game/game_fn_801B3770.c", mw_version="GC/1.2.5n", extra_cflags=["-opt nopeephole"]),
            Object(Matching, "game/game_fn_801B3940.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B399C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            # Honest C; the remaining divergence is even-path r3 versus r5 allocation.
            Object(NonMatching, "game/game_fn_801B3A2C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B3B08.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B3C14.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B3CC8.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B3E64.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B4398.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B443C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B4654.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B46C8.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B4E48.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B4EF0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B4FB4.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B5228.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B58F0.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B5B20.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B5B68.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801B5B9C.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B5C14.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B5E9C.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801B6270.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B64D0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B6768.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B6F1C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B75CC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B775C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B78AC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B7910.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B7954.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B797C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B7A10.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B7A7C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B7D94.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B7DC8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B7E84.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B7F6C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8054.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B80D8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8164.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8574.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B85C8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B85F0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B86C0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8C04.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8C28.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8C70.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8CA8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8D00.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8D68.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8D88.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8DE8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8E48.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8E88.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8F0C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B8F50.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8F84.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B8FE4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B9078.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9170.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B9220.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9310.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9330.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B9350.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9418.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B941C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9C94.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9C98.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801B9D1C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801B9E7C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BA128.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BA15C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BA2A4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BA6C4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BA708.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BA94C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BACE8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BAF90.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BB1A0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BB3A0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BB5D0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BB7C0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BB944.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BBB8C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BBD58.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BBF50.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BC0D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BC240.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BC500.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BC5D8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BC670.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BC798.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BC8F4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BCC04.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BCEA0.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801BCEB0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BCF44.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801BCF54.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD07C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801BD08C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD0EC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD14C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801BD15C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD1DC.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801BD1EC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BD294.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD378.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD398.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD6A0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BD7F8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BD990.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BDB6C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BDCEC.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801BDE7C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BE0D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BE354.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BE3F4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BE474.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BE5A0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BE740.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BE874.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BE9D8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BEA3C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801BEAA4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BEB08.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BEC38.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BEE6C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801BEF40.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C044C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0594.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0644.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0738.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0844.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C08E8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C09C4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0ACC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C0BC8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C0ED8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C0F40.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C1038.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C106C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C13C0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C13D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C14D0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C1520.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C1600.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C1790.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C1BCC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C1CB0.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C1FE0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C20C8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C2148.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C21E8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C22F8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C242C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C267C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C26F8.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C2754.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C27D0.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C2980.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801C29BC.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C2AAC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C2B00.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C2D74.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C2D9C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C2EF0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C2F34.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C30D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C3158.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801C3278.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C3460.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C350C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C36FC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C38C0.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801C38CC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C3B30.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C3BCC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C3CBC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C3E2C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C3F6C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C40AC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C40D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C4478.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C44B0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C458C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C4694.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C46B4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C47A8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C4A60.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C4B5C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C753C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C7580.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C7624.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C7684.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/game_fn_801C773C.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C77E4.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801C7868.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/game_fn_801C79C8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C8160.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C8224.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C8600.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C87DC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/game_fn_801C8CC0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C8EE0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C8F50.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C9078.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C90A4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off", "-use_lmw_stmw on"]),
            Object(Matching, "game/game_fn_801C92F4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C934C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C93F4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C9460.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C9510.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C970C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C9914.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C9938.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C9A08.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801C9B1C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C9C4C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801C9E74.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA240.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA284.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CA288.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CA484.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA3A4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA3D8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA538.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CA59C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CA798.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CA7C0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CAD90.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CAEB8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CAFAC.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB238.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB274.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB2B8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CB354.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB470.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB4B4.c", mw_version="GC/1.2.5n"),
            Object(NonMatching, "game/game_fn_801CB4F8.c", mw_version="GC/1.2.5n"),
            Object(Matching, "game/game_fn_801CB980.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CB9C8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBA10.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBA58.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBAA0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBAE8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBB30.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBB78.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBBC0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBC08.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBC50.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBC98.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBCE0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CBD9C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CBE58.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC13C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC1AC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CC24C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC2E4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC304.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CC370.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC408.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC418.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC460.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CC468.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC5D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC698.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC6CC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC6D4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC6DC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC6FC.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC704.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CC718.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC8C4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CC914.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCAC4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCAE4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCAF8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCB0C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCB20.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCB34.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCB70.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCB98.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCC10.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCC3C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCC68.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCCC4.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCF94.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCFC0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CCFE0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD000.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD034.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD068.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CD094.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CD138.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD1C0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD1E0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD200.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD224.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CD228.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD284.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD2A8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD2C8.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD35C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD3E0.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD400.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CD404.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD418.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD424.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD44C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD46C.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(Matching, "game/game_fn_801CD504.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
            Object(NonMatching, "game/game_fn_801CD538.c", mw_version="GC/1.2.5n", extra_cflags=["-Cpp_exceptions on", "-fp_contract off"]),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": LIBRARY_MW_VERSIONS["Runtime.PPCEABI.H"],
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(Matching, "Runtime.PPCEABI.H/__save_fpr.s"),
            Object(Matching, "Runtime.PPCEABI.H/__restore_fpr.s"),
            Object(Matching, "Runtime.PPCEABI.H/__save_gpr.s"),
            Object(Matching, "Runtime.PPCEABI.H/__restore_gpr.s"),
        ],
    },
    {
        "lib": "NdevExi2A",
        "mw_version": LIBRARY_MW_VERSIONS["NdevExi2A"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/db/DebuggerDriver.c")],
    },
    {
        "lib": "amcstubs",
        "mw_version": LIBRARY_MW_VERSIONS["amcstubs"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/amc/AmcExi2Stubs.c")],
    },
    {
        "lib": "os",
        "mw_version": LIBRARY_MW_VERSIONS["os"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(Matching, "dolphin/os/OSMessage.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
            Object(Matching, "dolphin/os/OSGetSystemTime.c"),
            Object(Matching, "dolphin/os/OSTimeToSystemTime.c"),
        ],
    },
    {
        "lib": "dvd",
        "mw_version": LIBRARY_MW_VERSIONS["dvd"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/dvd/dvdqueue.c")],
    },
    {
        "lib": "si",
        "mw_version": LIBRARY_MW_VERSIONS["si"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/si/SISamplingRate.c")],
    },
    {
        "lib": "exi",
        "mw_version": LIBRARY_MW_VERSIONS["exi"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/exi/EXIUart.c")],
    },
    {
        "lib": "base",
        "mw_version": LIBRARY_MW_VERSIONS["base"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/base/PPCArch.s")],
    },
    {
        "lib": "gx",
        "mw_version": LIBRARY_MW_VERSIONS["gx"],
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [Object(Matching, "dolphin/gx/GXStubs.c")],
    },
]
config.progress_categories = [ProgressCategory("game", "Game Code"), ProgressCategory("sdk", "SDK/Runtime")]
config.progress_each_module = args.verbose
config.progress_report_args = []
config.reconfig_deps = [Path("config") / VERSION / "toolchain.yml"]

if args.mode == "configure":
    # project.py snapshots argv for Ninja reruns; omit the mode so the progress
    # rule can append its own positional mode without producing two modes.
    if len(sys.argv) > 1 and sys.argv[1] == "configure":
        del sys.argv[1]
    generate_build(config)
elif args.mode == "progress":
    calculate_progress(config)
else:
    sys.exit("unknown mode")
