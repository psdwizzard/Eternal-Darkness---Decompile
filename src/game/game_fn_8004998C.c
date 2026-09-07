typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int fn_8011EB04(void *);
extern u16 fn_8012A244(int value);
extern int fn_801A9EF4(int minimum, int maximum);

extern float lbl_8064E3C0;
extern float lbl_8064E3C4;
extern float lbl_8064E3C8;
extern float lbl_8064E3CC;

u16 fn_8004998C(int value, u8* intensity, u32* flags)
{
    int type = fn_8011EB04((void*)value);
    int state = fn_8012A244(value);
    u16 result = 0xFFFF;
    float scale = lbl_8064E3C0;

    if (state >= 21 || state < 0) {
        state = 0;
    }

    switch (type) {
    case 0:
    case 0x56:
    case 0x7E:
        result = fn_801A9EF4(5, 10);
        break;
    case 9:
        switch (state) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            result = fn_801A9EF4(0x53, 0x56);
            scale = lbl_8064E3C4;
            break;
        case 12:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            break;
        case 13:
            result = fn_801A9EF4(0x1A7, 0x1AB);
            break;
        case 10:
        case 11:
            result = fn_801A9EF4(0x57, 0x5D);
            scale = lbl_8064E3C4;
            break;
        case 0:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        default:
            result = fn_801A9EF4(0x57, 0x5D);
            scale = lbl_8064E3C4;
            break;
        }
        break;
    case 0x4C:
    case 0x90:
    case 0x93:
    case 0x96:
        switch (state) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            result = fn_801A9EF4(0x1BA, 0x1BF);
            break;
        case 10:
        case 11:
            result = fn_801A9EF4(0x1C0, 0x1C7);
            break;
        case 12:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            break;
        case 13:
            result = fn_801A9EF4(0x1A7, 0x1AB);
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
            result = fn_801A9EF4(0x1A4, 0x1A6);
            break;
        }
        break;
    case 0x12:
    case 0x91:
        switch (state) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            result = fn_801A9EF4(0x1BA, 0x1BF);
            break;
        case 10:
        case 11:
            result = fn_801A9EF4(0x1C0, 0x1C7);
            break;
        case 12:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            break;
        case 13:
            result = fn_801A9EF4(0x1A7, 0x1AB);
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
            result = fn_801A9EF4(0x1B3, 0x1B9);
            scale = lbl_8064E3C8;
            break;
        default:
            result = fn_801A9EF4(0x1C0, 0x1C7);
            break;
        }
        break;
    case 0x4A:
    case 0x55:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x8F:
    case 0x92:
        switch (state) {
        case 12:
        case 13:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        default:
            result = fn_801A9EF4(0x1A4, 0x1A6);
            break;
        }
        break;
    case 0x45:
    case 0x49:
    case 0x4B:
        switch (state) {
        case 16:
        case 17:
            result = fn_801A9EF4(0x1BA, 0x1BF);
            break;
        case 12:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            scale = lbl_8064E3CC;
            break;
        case 13:
            result = fn_801A9EF4(0x1A7, 0x1AB);
            break;
        case 10:
        case 11:
        case 19:
            result = fn_801A9EF4(0x1C0, 0x1C7);
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
        case 15:
        case 18:
        default:
            result = fn_801A9EF4(0x1B3, 0x1B9);
            break;
        }
        break;
    case 0x46:
    case 0x8E:
        result = fn_801A9EF4(0x161, 0x166);
        break;
    case 0x51:
        switch (state) {
        case 15:
        case 16:
        case 17:
        case 18:
            result = fn_801A9EF4(0xE5, 0xEA);
            break;
        case 19:
        default:
            result = fn_801A9EF4(0x1AC, 0x1B2);
            break;
        }
        break;
    case 0x57:
    case 0x58:
    case 0x66:
    case 0x67:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x7C:
    case 0x83:
    case 0x85:
    case 0x86:
    case 0x9A:
    case 0x9D:
    case 0x9E:
    case 0x9F:
        switch (state) {
        case 16:
        case 17:
            result = fn_801A9EF4(0x1BA, 0x1BF);
            break;
        case 12:
        case 14:
            result = fn_801A9EF4(0x4F, 0x52);
            break;
        case 13:
            result = fn_801A9EF4(0x1A7, 0x1AB);
            break;
        case 10:
        case 11:
        case 19:
            result = fn_801A9EF4(0x1C0, 0x1C7);
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
        case 15:
        case 18:
        default:
            result = fn_801A9EF4(0x1A4, 0x1A6);
            break;
        }
        break;
    case 1:
    case 6:
    case 7:
    case 8:
    case 0x89:
        result = fn_801A9EF4(0x1D, 0x20);
        break;
    case 2:
    case 15:
    case 16:
        result = 0xB5;
        break;
    case 0x1C:
    case 0x4F:
    case 0x50:
        result = 0x12E;
        break;
    }

    if (intensity != 0 && lbl_8064E3C0 != scale) {
        int adjusted = (int)(scale * *intensity);
        *intensity = (adjusted > 0 ? adjusted : 0) > 0x7F
                         ? 0x7F
                         : (adjusted > 0 ? adjusted : 0);
    }
    if (flags != 0) {
        *flags |= 0x20;
    }
    return result;
}
