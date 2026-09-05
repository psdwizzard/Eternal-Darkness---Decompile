typedef signed int s32;
typedef unsigned int u32;

s32 fn_8006B620(u32 value)
{
    switch (value) {
    case 10:
        return 0x123;
    case 9:
    case 11:
    case 16:
    case 17:
    case 18:
    case 19:
    case 29:
    case 32:
    case 33:
    case 35:
        return 0x80103;
    case 22:
        return 0x102;
    case 12:
        return 0x801C2;
    case 15:
        return 0x801CB;
    case 7:
        return 0x810E3;
    case 13:
        return 2;
    case 25:
    case 26:
    case 28:
        return 0x4C3;
    case 23:
        return 0x800C3;
    case 30:
        return 8;
    case 34:
        return 0x50B;
    case 36:
        return 0x805CB;
    case 4:
        return 0x80521;
    case 24:
    case 31:
        return 0x421;
    case 1:
    case 5:
    case 6:
    case 38:
        return 0x20;
    case 14:
        return 0x823;
    case 20:
        return 3;
    case 21:
        return 2;
    case 8:
        return 0x21;
    case 27:
        return 0x421;
    case 0:
    case 2:
        return 0;
    case 3:
    case 37:
    default:
        return 8;
    }
}
