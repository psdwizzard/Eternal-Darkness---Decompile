typedef unsigned short u16;

extern u16 fn_8012A244(int value);
extern int fn_8011EB04(void *);
extern int fn_801A9EF4(int minimum, int maximum);

u16 fn_80049818(int value)
{
    int state = fn_8012A244(value);
    u16 result = 0xFFFF;
    int type = fn_8011EB04((void*)value);

    if (state >= 21 || state < 0) {
        state = 0;
    }

    switch (type) {
    case 1:
    case 0x3D:
    case 0x3E:
    case 0x5B:
    case 0x62:
    case 0x6E:
    case 0x6F:
    case 0x75:
    case 0x79:
    case 0x7A:
    case 0xBA:
    case 0xD2:
    case 0xE4:
    case 0xE5:
    case 0xE6:
    case 0xE7:
        switch (state) {
        case 10:
        case 11:
            result = fn_801A9EF4(0x1E9, 0x1EE);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = fn_801A9EF4(0x28, 0x32);
            break;
        }
        break;
    case 0x70:
    case 0xE9:
        switch (state) {
        case 10:
        case 11:
            result = fn_801A9EF4(0x2A2, 0x2A3);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = 0x2A5;
            break;
        }
        break;
    }

    return result;
}
