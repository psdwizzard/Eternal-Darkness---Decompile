typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern u32 lbl_80651DA8;
extern u16 lbl_80651DAC;
extern u32 lbl_80650B40;
extern u32 lbl_80650B44;
extern double lbl_80650B18;
extern float lbl_80650B20;
extern float lbl_80650B34;
extern float lbl_80650B48;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern s32 rand(void);
extern void fn_801804AC(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, int,
                        int);
extern void fn_801805E0(void*, int, u8, int, void*, float);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_8018C6EC(void*, void*, u8, int, u16);
extern void fn_8018C79C(void*, void*, u8, int, u16);
extern void fn_8018C84C(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019197C(u8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    ShortCoord3 zero;
    u32 value1;
    u32 value2;
    u8 count;
    u8* entry;
    u32 i;
    float initial;

    *(u32*)&zero = lbl_80651DA8;
    *(u16*)((u8*)&zero + 4) = lbl_80651DAC;
    value1 = lbl_80650B40;
    value2 = lbl_80650B44;
    entry = *(u8**)(object + 0x4C);
    count = config[0];
    fn_801804AC(object, first, second, &zero);

    object[0] = 0x80;
    initial = lbl_80650B20;
    object[1] = count;
    object[2] = config[2];
    object[4] = config[3];
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(void**)(object + 0x68) = lbl_8064D224;
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3C) = initial;
    *(float*)(object + 0x40) = lbl_80650B48 * (float)((rand() & 3) + 1);
    memset(object + 0x24, 0, 0x10);

    for (i = 0; (u8)i < count; i++) {
        fn_80180554(entry, first, second, &zero, 0,
                    *(signed char*)(config + 0x1D));
        fn_801805E0(entry + 0x20, 4, config[1], 0, &value1,
                    lbl_80650B34);
        entry += 0x38;
    }

    fn_8018CEC0(*(void**)(object + 0x54), count);
    switch (config[0x1C]) {
    case 1:
        fn_8018C84C(*(void**)(object + 0x58), config + 0x3C, count, 4,
                    *(u16*)(lbl_80607120 + 2));
        break;
    case 2:
        fn_8018C79C(*(void**)(object + 0x58), config + 0x3C, count, 4,
                    *(u16*)(lbl_80607120 + 2));
        break;
    case 3:
        fn_8018C6EC(*(void**)(object + 0x58), config + 0x3C, count, 4,
                    *(u16*)(lbl_80607120 + 2));
        break;
    default:
        fn_8018C540(*(void**)(object + 0x58), &value2, count, 4,
                    *(u16*)(lbl_80607120 + 2));
        break;
    }
    if (*(s16*)(object + 0xE) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(object + 0xE), lbl_80606328,
                    lbl_80606318);
    }
}
