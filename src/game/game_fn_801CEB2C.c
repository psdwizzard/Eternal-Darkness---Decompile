typedef unsigned int u32;

int fn_801CEB2C(u32 value)
{
    int result = 0;

    switch (value & 0xF0000) {
    case 0x10000:
        result = 3;
        break;
    case 0x20000:
        result = 5;
        break;
    case 0x40000:
        result = 7;
        break;
    case 0x80000:
        result = 9;
        break;
    }
    return result;
}
