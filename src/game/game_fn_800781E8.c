typedef signed int s32;

extern s32 fn_80128EAC(void *object);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern s32 fn_800460EC(void);
extern void fn_8012965C(void *object, s32 a, s32 b, s32 c);

#pragma opt_propagation off
s32 fn_800781E8(void *object, s32 enabled)
{
    void *target;
    s32 result;

    target = object;
    result = 1;

    if (enabled != 0) {
        if (fn_80128EAC(target) == 0xF && (fn_800FBFB0() & 0xFF) < 25 &&
            fn_800460EC() == 0) {
            fn_8012965C(target, 0x10, 0x20, 1);
            result = 0;
        }
    } else {
        fn_8012965C(target, 0xF, 0x21, 1);
    }
    return result;
}
#pragma opt_propagation reset
