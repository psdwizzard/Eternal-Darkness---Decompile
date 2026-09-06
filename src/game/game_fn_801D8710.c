typedef unsigned int u32;

int fn_801D8710(u32 value)
{
    int result = 0;

    switch (value & 0x70000) {
    case 0x10000:
        result = 50;
        break;
    case 0x20000:
        result = 100;
        break;
    case 0x40000:
        result = 200;
        break;
    }
    return result;
}
