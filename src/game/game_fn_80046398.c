typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;

extern s32 lbl_8064B4B8;
extern s32 lbl_8064C4E4;

extern s32 fn_800FBFB0(void);
extern void fn_800AE5C4(s32, s32, s32, s32, u16 *, s8 *, s32);

u16 fn_80046398(s32 arg0, u16 value, s8 arg2, s32 chance)
{
    u16 result;
    s8 local;

    result = value;
    if (fn_800FBFB0() % 100 <= chance) {
        local = arg2;
        fn_800AE5C4(lbl_8064B4B8, lbl_8064C4E4, arg0, 0, &result, &local, 0);
    }
    return result;
}
