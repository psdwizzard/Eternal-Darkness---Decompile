typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

extern u8 lbl_802FC5BC[];
extern void* fn_80201B94();
extern s16 fn_80201C8C(s32 value);

s32 fn_80066E78(u32 flags, s16 divisor, u8 kind, s32 value,
                s32 *amount, s32 *level, s32 *resource, s8 *variant)
{
    s32 result;
    s32 scaled;
    s16 base;

    base = fn_80201C8C((s32)fn_80201B94(value));
    scaled = divisor != 0 ? (s16)(base / divisor) : 0;
    if (flags & 1) {
        switch (kind) {
        case 0:
            *resource = *(s32 *)(lbl_802FC5BC + 0x18);
            result = 0;
            *level = 0;
            *amount = 0;
            *variant = 0;
            break;
        case 1:
            *resource = *(s32 *)(lbl_802FC5BC + 0x18);
            result = 3;
            if ((s16)scaled > 20) {
                *level = 1;
                *amount = 5;
                *variant = 0;
            } else if ((s16)scaled > 10) {
                *level = 2;
                *amount = 10;
                *variant = 0;
            } else if ((s16)scaled > 5) {
                *level = 3;
                *amount = 15;
                *variant = 1;
            } else {
                *level = 4;
                *amount = 20;
                *variant = 1;
            }
            break;
        case 8:
        case 16:
        case 32:
            *resource = *(s32 *)(lbl_802FC5BC + 0x18);
            *level = 0;
            result = 2;
            if ((s16)scaled > 20) {
                *amount = 10;
                *variant = 0;
            } else if ((s16)scaled > 10) {
                *amount = 15;
                *variant = 1;
            } else if ((s16)scaled > 5) {
                *amount = 20;
                *variant = 2;
            } else {
                *amount = 25;
                *variant = 3;
            }
            break;
        case 4:
            *resource = *(s32 *)(lbl_802FC5BC + 0x18);
            result = 3;
            if ((s16)scaled > 20) {
                *level = 1;
                *amount = 2;
                *variant = 0;
            } else if ((s16)scaled > 10) {
                *level = 2;
                *amount = 4;
                *variant = 1;
            } else if ((s16)scaled > 5) {
                *level = 3;
                *amount = 8;
                *variant = 2;
            } else {
                *level = 4;
                *amount = 12;
                *variant = 3;
            }
            break;
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        default:
            *resource = *(s32 *)(lbl_802FC5BC + 0x18);
            result = 3;
            if ((s16)scaled > 20) {
                *level = 1;
                *amount = 1;
            } else if ((s16)scaled > 10) {
                *level = 1;
                *amount = 4;
            } else if ((s16)scaled > 5) {
                *level = 1;
                *amount = 8;
            } else {
                *level = 1;
                *amount = 10;
            }
            *variant = 0;
            break;
        }
    }
    return result;
}
