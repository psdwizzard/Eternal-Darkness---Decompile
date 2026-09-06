typedef signed short s16;
typedef unsigned int u32;

extern void* fn_80201ADC(void);
extern u32 fn_8020216C(void);
extern void fn_801D3E0C(u32 value, s16* x, s16* y, s16* z);
extern void fn_80038308(void* object, int index, s16* value);
extern void fn_800389E0(void* object, int index, s16 value, int mode);

void fn_801D53F0(u32 value)
{
    void* object;
    u32 flags;
    s16 x;
    s16 z;
    s16 y;
    s16 current_x;
    s16 current_y;
    s16 current_z;

    object = fn_80201ADC();
    if (object != 0) {
        flags = fn_8020216C();
        fn_801D3E0C(value, &x, &y, &z);
        if (x != 0 && (flags & 0x800) == 0) {
            fn_80038308(object, 0, &current_x);
            fn_800389E0(object, 0, (s16)(current_x - x), 1);
        }
        if (y != 0 && (flags & 0x1000) == 0) {
            fn_80038308(object, 1, &current_y);
            fn_800389E0(object, 1, (s16)(current_y - y), 1);
        }
        if (z != 0 && (flags & 0x2000) == 0) {
            fn_80038308(object, 2, &current_z);
            fn_800389E0(object, 2, (s16)(current_z - z), 1);
        }
    }
}
