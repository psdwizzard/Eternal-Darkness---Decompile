typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 lbl_80607120[];
extern u8 lbl_802FC5BC[];
extern int lbl_8064D738;
extern float lbl_80650D34;

extern void fn_8018D020(void);
extern void fn_80188C1C(void*, void*, void*);
extern void DCFlushRange(void*, u32);
extern int fn_801ED57C(int);
extern void fn_801ECF50(int);
extern void fn_8018D0D0(void*, void*, s16);
extern int fn_801EF384(void);
extern void fn_801ED494(int, int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_801ED510(int, int, int);
extern void fn_8018865C(void*, void*, void*);

static inline void generate_object(u8* object, int* saved)
{
    u32* output2;
    void* output1;
    void* output0;
    u16 size2;
    u16 size1;
    u16 size0;
    u16 offset;

    offset = *(u16*)(lbl_80607120 + 2);
    size0 = *(u16*)(lbl_80607120 + 0xA);
    size1 = *(u16*)(lbl_80607120 + 0xE);
    size2 = *(u16*)(lbl_80607120 + 0xC);
    output0 = *(void**)(object + 0x50);
    output1 = *(void**)(object + 0x54);
    output2 = *(u32**)(object + 0x58);

    if (lbl_8064D738 != 0) {
        output1 = (u8*)output1 + (u32)offset * 4;
        output0 = (u8*)output0 + (u32)offset * 6;
        output2 = (u32*)((u8*)output2 + (u32)offset * 4);
    }

    {
        u32* output2_cursor;
        u8* input;
        int i;

        input = *(u8**)(object + 0x4C);
        output2_cursor = output2;
        input[0x21] = (u8)(lbl_80650D34 * *(float*)(object + 0x94));
        fn_80188C1C(input, output0, fn_8018D020);

        for (i = 0; i < input[0x20]; i++) {
            *output2_cursor++ = *(u32*)(lbl_802FC5BC + 0xC);
        }
    }

    DCFlushRange(output0, size0);
    DCFlushRange(output1, size1);
    DCFlushRange(output2, size2);

    *saved = fn_801ED57C(0);
    fn_801ECF50(3);
    fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
    if (fn_801EF384()) {
        fn_801ED494(3, 0, 0, 0, 3);
        fn_80229C0C(0, 0, 1, 2, 1, 0);
        fn_801ED510(0, 3, 3);
    }
    fn_8018865C(output0, output1, output2);
    if (fn_801EF384()) {
        fn_80229C0C(0, 0, 0, 0, 1, 0);
        fn_801ED510(0, 0, 0);
        fn_80229C0C(0, 0, 1, 2, 1, 0);
    }
}

void fn_801A2FB4(u8* object)
{
    int saved;

    generate_object(object, &saved);
    fn_801ED57C(saved);
}
