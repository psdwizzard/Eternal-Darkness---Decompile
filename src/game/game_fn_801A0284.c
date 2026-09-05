typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern float lbl_80650CA4;
extern int lbl_8064D18C;
extern int fn_80180430(void*, u8);
extern void fn_80179B08(void*, void*);
extern void fn_80179B64(void*, void*);
extern u32 fn_8017E4E4(void*, void*, float, float, float, float);
extern u8 fn_8018E26C(void*, void*);
extern void fn_80180518(void*, u8, u32);
extern void fn_8018E230(void*, void*, u32, u8, u8, u32);
extern int fn_80180454(void*);

#pragma use_lmw_stmw on
#pragma opt_lifetimes off
int fn_801A0284(void* object_arg)
{
    float a[3];
    float b[3];
    u8* object = object_arg;
    u8* entry;
    int count;
    u8* entries;
    int index;

    index = 0;
    entries = *(u8**)(object + 0x4C);
    count = object[1];
    entry = entries;

    for (; (u32)index < (u32)count; entry += 0x38, index++) {
        u32 result;

        if (fn_80180430(object + 0x24, (u8)index)) {
            fn_80179B08(entry + 0xA, a);
            fn_80179B08(entry + 0x10, b);
            result = fn_8017E4E4(a, b, *(float*)(object + 0x90),
                                 lbl_80650CA4, *(float*)(object + 0x8C),
                                 *(float*)(object + 0x94));
            fn_80179B64(a, entry + 0xA);
            fn_80179B64(b, entry + 0x10);
            if (*(s16*)(entry + 0xE) < -5000) {
                *(u16*)(object + 0x22) = 8;
            }
            if (entry[0] != 0) {
                if (!fn_8018E26C(entry, entry + 0x2B)) {
                    fn_80180518(object + 0x24, (u8)index, 0);
                }
            } else if ((result & 1) && entry[0] == 0) {
                fn_8018E230(entry, entry + 0x2B, 1, entry[0x2B], object[4], 0);
            }
        }
    }
    if (*(u16*)(object + 0xA) >= *(u16*)(object + 0xC)) {
        entry = entries;
        index -= index;
        for (; index < count; entry += 0x38, index++) {
            if (fn_80180430(object + 0x24, (u8)index) && entry[0] == 0) {
                fn_8018E230(entry, entry + 0x2B, 1, entry[0x2B], object[4], 0);
            }
        }
    }
    *(u16*)(object + 0xA) = *(u16*)(object + 0xA) + 1;
    if (fn_80180454(object + 0x24)) {
        *(u16*)(object + 0x22) = 8;
    }
    if (lbl_8064D18C != *(int*)(object + 0x38)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
#pragma opt_lifetimes reset
#pragma use_lmw_stmw reset
