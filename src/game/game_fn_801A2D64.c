typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 lbl_80607120[];
extern u8 lbl_80607900[];
extern int lbl_8064D738;

extern void fn_801A2BCC(void*, void*, void*, int);
extern void DCFlushRange(void*, u32);
extern int fn_801ED57C(int);
extern void fn_801ECF50(int);
extern void fn_8018D0D0(void*, void*, s16);
extern int fn_801EF384(void);
extern void fn_801ED494(int, int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void fn_801ED510(int, int, int);
extern u32 fn_801F6D90(s16, s16, s16);
extern void fn_8018865C(void*, void*, void*);

void fn_801A2D64(u8* object)
{
    u16 size0;
    u16 size1;
    u16 size2;
    void* output0;
    void* output1;
    u32* output2;
    int old;
    u8* temp;
    u8 count;
    u8* input;
    u32* output2_cursor;
    int i;
    int j;

    temp = (u8*)(u32)*(u16*)(lbl_80607120 + 2);
    count = object[1];
    size0 = *(u16*)(lbl_80607120 + 0xA);
    size1 = *(u16*)(lbl_80607120 + 0xE);
    size2 = *(u16*)(lbl_80607120 + 0xC);
    output0 = *(void**)(object + 0x50);
    output1 = *(void**)(object + 0x54);
    output2 = *(u32**)(object + 0x58);

    if (lbl_8064D738 != 0) {
        u32 scale = ((u32)temp << 16) >> 14;
        output1 = (u8*)output1 + scale;
        output0 = (u8*)output0 + (u32)temp * 6;
        output2 = (u32*)((u8*)output2 + scale);
    }

    temp = lbl_80607900;
    input = *(u8**)(object + 0x4C);
    output2_cursor = output2;
    for (i = 0; i < count; i++) {
        *(u32*)temp = *(u32*)(input + 0xA);
        *(u16*)(temp + 4) = *(u16*)(input + 0xE);
        j = 0;
        while (j < input[0x20]) {
            *output2_cursor++ = *(u32*)(input + 0x28 + j * 4);
            j++;
        }
        input += 0x38;
        temp += 6;
    }

    fn_801A2BCC(*(void**)(object + 0x4C), lbl_80607900, output0, count);
    DCFlushRange(output0, size0);
    DCFlushRange(output1, size1);
    DCFlushRange(output2, size2);

    old = fn_801ED57C(0);
    fn_801ECF50(3);
    fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
    if (fn_801EF384()) {
        fn_801ED494(3, 0, 0, 0, 3);
        GXSetTevColorOp(0, 0, 1, 2, 1, 0);
        fn_801ED510(0, 3, 3);
    }
    if (object[0xBD] == 0) {
        if (object[0xBC] != 0) {
            if (fn_801F6D90(*(s16*)(object + 0x10), *(s16*)(object + 0x12), *(s16*)(object + 0x14)) > 300) {
                fn_8018865C(output0, output1, output2);
            }
        } else if (fn_801F6D90(*(s16*)(object + 0x10), *(s16*)(object + 0x12), *(s16*)(object + 0x14)) > 200) {
            fn_8018865C(output0, output1, output2);
        }
    }
    if (fn_801EF384()) {
        GXSetTevColorOp(0, 0, 0, 0, 1, 0);
        fn_801ED510(0, 0, 0);
        GXSetTevColorOp(0, 0, 1, 2, 1, 0);
    }
    fn_801ED57C(old);
}
