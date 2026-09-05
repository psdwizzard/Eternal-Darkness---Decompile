typedef signed int s32;
typedef unsigned char u8;

extern void *lbl_8064C4E0;
extern int fn_801E79FC(void*, int);
extern s32 fn_8006B96C(s32 value, s32 mode);

s32 fn_8006B70C(u8 *object, s32 value)
{
    s32 input = value;
    s32 result = 0;
    s32 initial_mask;
    s32 mask;

    switch (input) {
    case 0xFF:
        if (fn_801E79FC(lbl_8064C4E0, 0x373) != 0) {
            result = 0;
        } else if (object[0x15] == 3) {
            initial_mask = *(s32 *)(*(u8 **)(object + 0xC4) + 0x1C);
            input = fn_8006B96C(input, 1);
            if (input >= 0 && input < 10 &&
                (initial_mask & (1 << input)) == 0) {
                result = 1;
            }
        }
        break;
    default:
        if (object[0x15] == 3) {
            mask = *(s32 *)(*(u8 **)(object + 0xC4) + 0x1C);
            input = fn_8006B96C(input, 1);
            if (input >= 0 && input < 10 && (mask & (1 << input)) == 0) {
                result = 1;
            }
        }
        break;
    }
    return result;
}
