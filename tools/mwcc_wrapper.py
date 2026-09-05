#!/usr/bin/env python3
"""Run Metrowerks under wibo and normalize constructor subsection names."""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
WIBO = ROOT / ".tools" / "bin" / "wibo"
OBJCOPY = ROOT / "build" / "binutils" / "powerpc-eabi-objcopy"


def output_object(args: list[str]) -> Path | None:
    if "-c" not in args or "-o" not in args:
        return None
    source = next((Path(arg) for arg in args if arg.endswith((".c", ".cpp"))), None)
    if source is None:
        return None
    output = Path(args[args.index("-o") + 1])
    return output / source.with_suffix(".o").name if output.suffix.lower() != ".o" else output


def normalize_runtime_sections(path: Path) -> None:
    payload = path.read_bytes()
    replacements = {
        b".ctors$10\0": b".ctors\0\0\0\0",
        b".dtors$10\0": b".dtors\0\0\0\0",
        b".dtors$15\0": b".dtors\0\0\0\0",
    }
    for old, new in replacements.items():
        if old not in payload:
            raise SystemExit(f"expected MWCC section name {old[:-1].decode()} in {path}")
        payload = payload.replace(old, new)
    path.write_bytes(payload)


def set_section_alignment(path: Path, section_name: bytes, alignment: int) -> None:
    """Correct split-object alignment metadata without changing generated code/data."""
    payload = bytearray(path.read_bytes())
    shoff = int.from_bytes(payload[32:36], "big")
    shentsize = int.from_bytes(payload[46:48], "big")
    shnum = int.from_bytes(payload[48:50], "big")
    shstrndx = int.from_bytes(payload[50:52], "big")
    shstr = shoff + shstrndx * shentsize
    names_offset = int.from_bytes(payload[shstr + 16 : shstr + 20], "big")
    for index in range(shnum):
        header = shoff + index * shentsize
        name_offset = int.from_bytes(payload[header : header + 4], "big")
        name_start = names_offset + name_offset
        name_end = payload.index(0, name_start)
        if payload[name_start:name_end] == section_name:
            payload[header + 32 : header + 36] = alignment.to_bytes(4, "big")
            path.write_bytes(payload)
            return
    raise SystemExit(f"section {section_name.decode()} not found in {path}")


def main() -> None:
    if not WIBO.is_file():
        raise SystemExit("wibo is missing; run: python3 tools/bootstrap.py")
    args = sys.argv[1:]
    result = subprocess.run([str(WIBO), *args], check=False)
    if result.returncode:
        raise SystemExit(result.returncode)
    output = output_object(args)
    local_symbol_names = {
        "game_data_80239BC0.o": ("lbl_80239BC0", "@62_80239BC0"),
        "game_data_80239C88.o": ("lbl_80239C88", "@154_80239C88"),
        "game_data_80239CAC.o": ("lbl_80239CAC", "@155_80239CAC"),
    }
    if output is not None and output.name in local_symbol_names:
        old, new = local_symbol_names[output.name]
        subprocess.run(
            [str(OBJCOPY), "--redefine-sym", f"{old}={new}", str(output)],
            check=True,
        )
    if output is not None and output.name == "__init_cpp_exceptions.o":
        normalize_runtime_sections(output)
    if output is not None and output.name in (
        "game_fn_8000EE9C.o",
        "game_fn_8000EFC4.o",
        "game_fn_800122F8.o",
        "game_fn_80015568.o",
        "game_fn_80015BE0.o",
        "game_fn_80015D40.o",
        "game_fn_8001C078.o",
        "game_fn_8001CC00.o",
        "game_fn_8001CE14.o",
        "game_fn_8001D3F8.o",
        "game_fn_8001D4C4.o",
        "game_data_8023D77C.o",
        "game_data_8023D884.o",
        "game_fn_8001E644.o",
        "game_fn_8005EE9C.o",
        "game_fn_8006B620.o",
        "game_fn_800B5F78.o",
        "game_fn_800B6024.o",
        "game_fn_800B611C.o",
        "game_fn_800B61B8.o",
        "game_fn_800B6234.o",
        "game_fn_800B63C0.o",
        "game_fn_800B64AC.o",
        "game_fn_800B6548.o",
        "game_fn_800B6C00.o",
        "game_fn_800B6C88.o",
        "game_fn_800B6D10.o",
        "game_data_8023DA2C.o",
        "game_fn_80020E94.o",
        "game_data_8023DAB4.o",
        "game_data_8023DD84.o",
        "game_data_8023DFAC.o",
        "game_data_8023E0E8.o",
        "game_data_8023E154.o",
        "game_data_8023E280.o",
        "game_data_8023E388.o",
        "game_data_8023E410.o",
        "game_data_8023E448.o",
        "game_data_8023E4E8.o",
        "game_data_8023ECBC.o",
        "game_data_8023EE94.o",
        "game_data_8023EEE4.o",
        "game_data_8023EF34.o",
        "game_data_8023EF84.o",
        "game_data_8023F204.o",
        "game_data_8023F350.o",
        "game_data_8023F49C.o",
        "game_data_8023F560.o",
        "game_data_8023F6AC.o",
        "game_data_8023F7C4.o",
        "game_data_8023F904.o",
        "game_data_8023FA44.o",
        "game_data_8023FB90.o",
        "game_data_8023FCD0.o",
        "game_data_8023FE1C.o",
        "game_data_8023FF7C.o",
        "game_data_802400DC.o",
        "game_data_8024023C.o",
        "game_data_8024039C.o",
        "game_data_802404FC.o",
        "game_data_80240648.o",
        "game_data_802407A8.o",
        "game_data_80240908.o",
        "game_fn_80050730.o",
        "game_fn_8006F6A4.o",
        "game_fn_800A1060.o",
        "game_fn_800A1580.o",
        "game_fn_80028E88.o",
        "game_fn_80037AF4.o",
    ):
        set_section_alignment(output, b".data", 4)
        payload = output.read_bytes().replace(b".comment\0", b".ignored\0")
        output.write_bytes(payload)
    if output is not None and output.name in (
        "game_fn_80050A7C.o",
        "game_fn_80057E3C.o",
        "game_data_80239044.o",
        "game_data_80239054.o",
        "game_data_80239060.o",
        "game_data_8023906C.o",
        "game_data_80239078.o",
        "game_data_80239084.o",
        "game_data_80239090.o",
        "game_data_802390A0.o",
        "game_data_802390B4.o",
        "game_data_802390C8.o",
        "game_data_802390D4.o",
        "game_data_802390E0.o",
        "game_data_802390EC.o",
        "game_data_802390F8.o",
        "game_data_80239110.o",
        "game_data_80239188.o",
        "game_data_80239194.o",
        "game_data_802391C4.o",
        "game_data_802391D0.o",
        "game_data_802391E8.o",
        "game_data_802393CC.o",
        "game_data_802393D8.o",
        "game_data_802393E4.o",
        "game_data_802393F0.o",
        "game_data_802393FC.o",
        "game_data_80239408.o",
        "game_data_80239414.o",
        "game_data_80239420.o",
        "game_data_80239450.o",
        "game_data_8023945C.o",
        "game_data_80239490.o",
        "game_data_80239530.o",
        "game_data_8023953C.o",
        "game_data_80239548.o",
        "game_data_80239554.o",
        "game_data_80239560.o",
        "game_data_80239620.o",
        "game_data_80239630.o",
        "game_data_8023963C.o",
        "game_data_80239648.o",
        "game_data_80239654.o",
        "game_data_80239660.o",
        "game_data_8023966C.o",
        "game_data_80239678.o",
        "game_data_80239688.o",
        "game_data_80239694.o",
        "game_data_802396A0.o",
        "game_data_802396B0.o",
        "game_data_802396BC.o",
        "game_data_802396C8.o",
        "game_data_802396D4.o",
        "game_data_802396E0.o",
        "game_data_802396F0.o",
        "game_data_8023972C.o",
        "game_data_80239750.o",
        "game_data_8023975C.o",
        "game_data_80239768.o",
        "game_data_80239778.o",
        "game_data_80239788.o",
        "game_data_8023979C.o",
        "game_data_802397B0.o",
        "game_data_802397BC.o",
        "game_data_802397C8.o",
        "game_data_802397D8.o",
        "game_data_802397F0.o",
        "game_data_80239800.o",
        "game_data_8023980C.o",
        "game_data_80239818.o",
        "game_data_80239824.o",
        "game_data_80239830.o",
        "game_data_8023983C.o",
        "game_data_80239854.o",
        "game_data_80239860.o",
        "game_data_8023986C.o",
        "game_data_80239878.o",
        "game_data_80239884.o",
        "game_data_80239890.o",
        "game_data_8023989C.o",
        "game_data_802398A8.o",
        "game_data_802398B8.o",
        "game_data_802398C8.o",
        "game_data_802398E0.o",
        "game_data_802398EC.o",
        "game_data_802398F8.o",
        "game_data_80239934.o",
        "game_data_80239940.o",
        "game_data_8023994C.o",
        "game_data_80239958.o",
        "game_data_80239968.o",
        "game_data_80239978.o",
        "game_data_80239988.o",
        "game_data_80239998.o",
        "game_data_802399A8.o",
        "game_data_802399B8.o",
        "game_data_802399C8.o",
        "game_data_802399D8.o",
        "game_data_80239A78.o",
        "game_data_80239B18.o",
        "game_data_80239B24.o",
        "game_data_80239B30.o",
        "game_data_80239B40.o",
        "game_data_80239B50.o",
        "game_data_80239B74.o",
        "game_data_80239B80.o",
        "game_data_80239B8C.o",
        "game_data_80239B98.o",
        "game_data_80239BC0.o",
        "game_data_80239BE0.o",
        "game_data_80239C00.o",
        "game_data_80239C10.o",
        "game_data_80239C38.o",
        "game_data_80239C60.o",
        "game_data_80239C88.o",
        "game_data_80239CAC.o",
        "game_data_8023A2A4.o",
        "game_data_8023A2E0.o",
        "game_data_8023A3B0.o",
        "game_data_8023A3C0.o",
        "game_data_8023A414.o",
        "game_data_8023A444.o",
        "game_data_8023A630.o",
        "game_data_8023A63C.o",
        "game_data_8023A650.o",
        "game_data_8023A660.o",
        "game_data_8023A670.o",
        "game_data_8023A680.o",
        "game_data_8023A690.o",
        "game_data_8023A69C.o",
        "game_data_8023A6B8.o",
        "game_data_8023A6C8.o",
        "game_data_8023A6D8.o",
        "game_data_8023A6E8.o",
        "game_data_8023A6F4.o",
        "game_data_8023A700.o",
        "game_data_8023A70C.o",
        "game_data_8023A718.o",
        "game_data_8023A728.o",
        "game_data_8023A738.o",
        "game_data_8023A744.o",
        "game_data_8023A750.o",
        "game_data_8023A760.o",
        "game_data_8023A76C.o",
        "game_data_8023A778.o",
        "game_data_8023A788.o",
        "game_data_8023A798.o",
        "game_data_8023A7F8.o",
        "game_data_8023A868.o",
        "game_data_8023A878.o",
        "game_data_8023A890.o",
        "game_data_8023A8B0.o",
        "game_data_8023A994.o",
        "game_data_8023B018.o",
        "game_data_8023B028.o",
        "game_data_8023B038.o",
        "game_data_8023B044.o",
        "game_data_8023B050.o",
        "game_data_8023B05C.o",
        "game_data_8023B068.o",
        "game_data_8023B078.o",
        "game_data_8023B088.o",
        "game_data_8023B094.o",
        "game_data_8023B0A0.o",
        "game_data_8023B0B0.o",
        "game_data_8023B190.o",
        "game_data_8023B2B0.o",
        "game_data_8023B2D0.o",
        "game_data_8023B2F0.o",
        "game_data_8023B330.o",
        "game_data_8023B348.o",
        "game_data_8023B3D0.o",
        "game_data_8023B458.o",
        "game_data_8023B558.o",
        "game_data_8023B564.o",
        "game_data_8023B570.o",
        "game_data_8023B5A8.o",
        "game_data_8023B5B4.o",
        "game_data_8023B5C0.o",
        "game_data_8023B6A8.o",
        "game_data_8023B6C8.o",
        "game_data_8023B768.o",
        "game_data_8023B78C.o",
        "game_data_8023B798.o",
        "game_data_8023B7A8.o",
        "game_data_8023B7B4.o",
        "game_data_8023B7C0.o",
        "game_data_8023B7CC.o",
        "game_data_8023B7D8.o",
        "game_data_8023B7E4.o",
        "game_data_8023B7F0.o",
        "game_data_8023B7FC.o",
        "game_data_8023B808.o",
        "game_data_8023B814.o",
        "game_data_8023B820.o",
    ):
        set_section_alignment(output, b".rodata", 4)
        payload = output.read_bytes().replace(b".comment\0", b".ignored\0")
        output.write_bytes(payload)
    if output is not None and output.name == "game_data_80060C28.o":
        set_section_alignment(output, b".sdata2", 4)
        payload = output.read_bytes().replace(b".comment\0", b".ignored\0")
        output.write_bytes(payload)


if __name__ == "__main__":
    main()
