typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma pack(push, 1)
typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;
#pragma pack(pop)

extern u32 lbl_80651D10;
extern u16 lbl_80651D14;
extern void* lbl_8064D224;
extern float lbl_806509D4;
extern u32 lbl_806509D0;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern unsigned int rand(void);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u8, void*, float);
extern void fn_80180518(void*, u8, int);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);
extern void* memset(void*, int, u32);

void fn_80183A68(u8* self, void* arg1, s16* arg2, u8* desc)
{
    s16 x;
    s16 y;
    u8 i;
    u8* entry;
    u8 count;
    SixBytes setup;
    s16 position[3];
    u32 color;
    u8 random_count;

    setup.word = lbl_80651D10;
    setup.half = lbl_80651D14;
    color = lbl_806509D0;
    entry = *(u8**)(self + 0x4C);
    count = desc[0];
    fn_801804AC(self, arg1, arg2, &setup);
    self[0] = 0x80;
    self[1] = desc[0];
    *(s16*)(self + 0xE) = *(s16*)(desc + 4);
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    *(void**)(self + 0x68) = lbl_8064D224;
    memset(self + 0x24, 0, 0x10);
    position[2] = arg2[2];
    x = arg2[0] * 2;
    y = arg2[1] * 2;
    for (i = 0; i < count; entry += 0x38, i++) {
        s16 rx = x + (rand() & 3);
        s16 ry = y + (rand() & 3);
        if (desc[0x14] == 0) {
            position[1] = rx;
            position[0] = -ry;
        } else {
            position[0] = ry;
            position[1] = -rx;
        }
        fn_80180554(entry, arg1, position, &setup, *(u16*)(desc + 8), 0);
        random_count = desc[1] - ((desc[1] - 1) & rand());
        fn_801805E0(entry + 0x20, 4, random_count, i * 4,
                    &color, lbl_806509D4);
        fn_80180518(self + 0x24, i, 1);
        fn_8018E230(entry, entry + 0x2B, 1, desc[2], desc[3], 0);
    }
    fn_8018CEC0(*(void**)(self + 0x54), count);
    fn_8018C540(*(void**)(self + 0x58), &color, count, 4,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(self + 0x22) = 4;
    if (*(s16*)(desc + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(desc + 4), lbl_80606328,
                    lbl_80606318);
    }
}
