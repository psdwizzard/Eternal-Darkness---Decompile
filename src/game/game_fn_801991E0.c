typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned long u32;

extern int fn_80180430(void*, u8);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern int rand(void);
extern void fn_80179904(s16*, s16);
extern void fn_8018F014(s16*, int);
extern void fn_80199358(void);
extern void fn_8018ABD4(void);

void fn_801991E0(u8* object, float* offset, u8 bias)
{
    u8* entry = *(u8**)(object + 0x4c);
    int i = 0;
    u8 count = object[1];

    for (; i < count; i++) {
        if (fn_80180430(object + 0x24, (u8)i)) {
            ((s8*)object)[4] = -4;
            entry[0x2b] = ((u8)entry[0x2b] / (s8)object[4]) * (s8)object[4];
            fn_8018E230(entry, entry + 0x2b, 1, entry[0x2b], object[4], 0);
            *(s16*)(entry + 0x10) = (s16)(*(s16*)(entry + 0xa) - offset[0]);
            *(s16*)(entry + 0x12) = (s16)(*(s16*)(entry + 0xc) - offset[1]);
            *(s16*)(entry + 0x14) = (int)(*(s16*)(entry + 0xe) - offset[2]) >> 2;
            fn_80179904((s16*)(entry + 0x10), (s16)(bias + (rand() & 7)));
            fn_8018F014((s16*)(entry + 0x10), 2);
        }
        entry += 0x38;
    }
    *(void (**)(void))(object + 0x14c) = fn_80199358;
    *(void (**)(void))(object + 0x148) = fn_8018ABD4;
}
