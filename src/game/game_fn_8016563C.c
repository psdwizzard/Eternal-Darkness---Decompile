int getbinopr(int token)
{
    switch (token) {
    case 0x2B:
        return 0;
    case 0x2D:
        return 1;
    case 0x2A:
        return 2;
    case 0x2F:
        return 3;
    case 0x5E:
        return 4;
    case 0x114:
        return 5;
    case 0x119:
        return 6;
    case 0x116:
        return 7;
    case 0x3C:
        return 8;
    case 0x118:
        return 9;
    case 0x3E:
        return 10;
    case 0x117:
        return 11;
    case 0x101:
        return 12;
    case 0x10D:
        return 13;
    default:
        return 14;
    }
}
