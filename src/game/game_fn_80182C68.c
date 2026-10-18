typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u32 lbl_80651CF8;
extern u16 lbl_80651CFC;
extern void* lbl_8064D224;
extern float lbl_806509C8;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern unsigned int rand(void);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u8, void*, float);
extern void fn_80180518(void*, u8, int);
extern void fn_8018EFB0(void*, u8, int);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80182C68(u8* self, const void* position, void* arg2, u8* desc)
{
    u8 initial[6];
    u8 copy[6];
    u8 color[4];
    u8* item;
    u8 count;
    u8 mode;
    u8 alpha;
    u8 i;

    *(u32*)initial = lbl_80651CF8;
    *(u16*)(initial + 4) = lbl_80651CFC;
    item = *(u8**)(self + 0x4C);
    count = desc[0];
    mode = desc[0x16];
    alpha = desc[0x17];
    fn_801804AC(self, (void*)position, arg2, initial);
    self[0] = 0x80;
    self[1] = desc[0];
    self[2] = desc[2];
    self[4] = desc[3];
    *(u16*)(self + 0xC) = *(u16*)(desc + 6);
    *(s16*)(self + 0xE) = *(s16*)(desc + 4);
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    *(void**)(self + 0x68) = lbl_8064D224;
    memset(self + 0x24, 0, 0x10);
    color[3] = desc[2];
    if (alpha < 0xFF) {
        alpha = (u8)(alpha + ((u8)(0xFF - alpha) & rand()));
    } else {
        alpha = 0xFF;
    }
    color[2] = alpha;
    color[1] = alpha;
    color[0] = alpha;
    for (i = 0; i < count; i++) {
        memcpy(copy, position, 6);
        if (mode >= 2) {
            fn_8018EFB0(copy, mode, 0);
            fn_8018EFB0(copy, mode, 1);
        }
        fn_80180554(item, copy, arg2, initial, *(u16*)(desc + 8), 0);
        alpha = desc[1];
        fn_801805E0(item + 0x20, 4, (u8)(alpha - (rand() & (alpha - 1)) + 2), i * 4, color, lbl_806509C8);
        fn_80180518(self + 0x24, i, 1);
        item += 0x38;
    }
    fn_8018CB70(*(void**)(self + 0x54), count, *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(self + 0x58), color, count, 4, *(u16*)(lbl_80607120 + 2));
    *(u16*)(self + 0x22) = 4;
    if (*(s16*)(desc + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(desc + 4), lbl_80606328, lbl_80606318);
    }
}
