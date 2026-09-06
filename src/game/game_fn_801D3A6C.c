extern int fn_801D38E8(int);

int fn_801D3A6C(int value, int mask)
{
    int result = -1;
    int type = fn_801D38E8(value);

    switch (mask) {
    case 0x10:
        result = 14;
        if (type == 4) result = 15;
        break;
    case 0x20:
        result = 16;
        if (type == 4) result = 17;
        break;
    case 0x40:
        result = 18;
        if (type == 4) result = 19;
        break;
    case 0x80:
        result = 20;
        if (type == 4) result = 21;
        break;
    case 0x100:
        result = 22;
        if (type == 4) result = 23;
        break;
    case 0x2000:
        result = 36;
        if (type == 4) result = 37;
        break;
    case 0x200:
        result = 28;
        if (type == 4) result = 29;
        break;
    case 0x400:
        result = 30;
        if (type == 4) result = 31;
        break;
    case 0x800:
        result = 32;
        if (type == 4) result = 33;
        break;
    case 0x1000:
        result = 34;
        if (type == 4) result = 35;
        break;
    }

    return result;
}
