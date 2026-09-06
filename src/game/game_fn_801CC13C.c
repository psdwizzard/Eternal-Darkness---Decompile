typedef unsigned char u8;

u8 fn_801CC13C(u8 value)
{
    switch ((u8)value) {
    case 0x80:
        return 0x80;
    case 0x81:
        return 0x82;
    case 0x82:
        return 0xA0;
    case 0x83:
        return 0xA1;
    case 0x84:
        return 0x83;
    case 0x85:
        return 0x84;
    case 0x86:
        return 0xA2;
    case 0x87:
        return 0xA3;
    case 0x88:
        return 0xA4;
    default:
        return value;
    }
}
