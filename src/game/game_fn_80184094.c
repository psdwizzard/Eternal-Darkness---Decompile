typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes { u32 word; u16 half; } SixBytes;

extern u32 lbl_80651D20;
extern u16 lbl_80651D24;
extern void* lbl_8064D224;
extern float lbl_806509D8;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];
extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_80180518(void*, u8, int);
extern void fn_8018F014(void*, u8);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80184094(u8* self, void* arg1, void* arg2, u8* desc)
{
    u8* entry;
    u8 count;
    SixBytes setup;
    SixBytes position;
    u32 color;
    u8 transform;
    u8 shift;
    int i;

    setup.word = lbl_80651D20;
    setup.half = lbl_80651D24;
    entry = *(u8**)(self + 0x4C);
    transform = desc[0x16];
    shift = desc[0x17];
    fn_801804AC(self, arg1, arg2, &setup);
    count = self[1] = desc[0];
    self[0] = 0x80;
    self[2] = desc[2];
    self[4] = desc[3];
    *(s16*)(self + 0xE) = *(s16*)(desc + 4);
    *(void**)(self + 0x68) = lbl_8064D224;
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    memset(self + 0x24, 0, 0x10);
    color = *(u32*)(desc + 0x1C);
    ((u8*)&color)[3] = 0;
    for (i = 0; i < count; entry += 0x38, i++) {
        memcpy(&position, arg1, 6);
        fn_8018F014(&position, transform);
        fn_80180554(entry, &position, self + 0x16, &setup,
                    *(u16*)(desc + 8) + (i << shift), 0);
        fn_801805E0(entry + 0x20, 4, desc[1], 0, &color, lbl_806509D8);
    }
    fn_80180518(self + 0x24, 0, 1);
    fn_8018CEC0(*(void**)(self + 0x54), count);
    fn_8018C540(*(void**)(self + 0x58), desc + 0x1C, count, 4,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(self + 0x22) = 4;
    if (*(s16*)(desc + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(desc + 4), lbl_80606328,
                    lbl_80606318);
    }
}
