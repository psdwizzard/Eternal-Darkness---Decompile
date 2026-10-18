typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

#pragma opt_strength_reduction off

extern u32 lbl_80651E58;
extern u16 lbl_80651E5C;
extern void* lbl_8064D224;
extern void* lbl_8064D18C;
extern float lbl_80650CA0;
extern u8 lbl_80607120[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_8018F014(void*, u8);
extern void fn_80180554(void*, void*, void*, void*, u16, u32);
extern int rand(void);
extern void fn_801805E0(void*, u32, u8, u32, void*, float);
extern void fn_80180518(void*, u32, u32);
extern void fn_8018CEC0(void*, u32);
extern void fn_8018C540(void*, void*, u32, u32, u16);
extern void fn_801F5A04(void*, s16, void*, void*);
extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);

void fn_801A00B8(u8* object, void* arg1, u8* arg2, u8* descriptor)
{
    struct { u32 word; u16 half; } stack_b;
    u8 stack_a[6];
    u32 count;
    u8* entry;
    u32 index;
    u8 divisor;

    stack_b.word = lbl_80651E58;
    stack_b.half = lbl_80651E5C;
    count = descriptor[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, arg1, arg2, &stack_b);
    object[0] = 0x80;
    object[1] = descriptor[0];
    object[2] = descriptor[2];
    object[4] = descriptor[3];
    *(u16*)(object + 0xC) = *(u16*)(descriptor + 6);
    *(s16*)(object + 0xE) = *(s16*)(descriptor + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    *(void**)(object + 0x38) = lbl_8064D18C;
    object[7] = 10;
    memset(object + 0x24, 0, 16);
    for (index = 0; (u8)index < count; index++) {
        memcpy(stack_a, arg2, 6);
        if (descriptor[0x20] != 0) fn_8018F014(stack_a, descriptor[0x20]);
        fn_80180554(entry, arg1, stack_a, &stack_b, *(u16*)(descriptor + 8), 0);
        divisor = descriptor[1];
        fn_801805E0(entry + 0x20, 4, (u8)(divisor - (rand() % divisor)),
                    (index << 2) & 0xFC, descriptor + 0x10, lbl_80650CA0);
        fn_80180518(object + 0x24, index, 1);
        entry += 0x38;
    }
    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), descriptor + 0x10, count, 4,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(object + 0x22) = 4;
    if (*(s16*)(descriptor + 4) >= 0)
        fn_801F5A04(object + 0x6C, *(s16*)(descriptor + 4), lbl_80606328, lbl_80606318);
}
