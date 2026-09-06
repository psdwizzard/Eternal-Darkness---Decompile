typedef unsigned int u32;

int fn_801DA0A0(u32 value)
{
    switch (value & 0x70000) {
    case 0x10000:
        return 5;
    case 0x20000:
        return 7;
    case 0x40000:
        return 10;
    }
}
