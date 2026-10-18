typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

extern u32 lbl_80651D08;
extern u16 lbl_80651D0C;
extern float lbl_806509CC;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_8018E230(void*, void*, int, int, s8, u8);
extern void fn_8018CD18(void*, int, u16);
extern void fn_8018CB70(void*, int, u16);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern unsigned int rand(void);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_801835F4(u8* self, void* arg1, void* arg2, u8* desc)
{
    SixBytes position;
    SixBytes setup;
    u8* entry;

    setup.word = lbl_80651D08;
    setup.half = lbl_80651D0C;
    entry = *(u8**)(self + 0x4C);
    fn_801804AC(self, arg1, &position, &setup);
    self[1] = 1;
    self[0] = 0x80;
    self[2] = desc[2];
    self[4] = desc[3];
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    *(u16*)(self + 0xC) = *(u16*)(desc + 6);
    *(void**)(self + 0x68) = lbl_8064D224;
    *(void**)(self + 0x5C) = *(void**)(desc + 0x1C);
    memset(self + 0x24, 0, 0x10);
    fn_80180554(entry, arg1, arg2, &setup, 0, 0);
    fn_801805E0(entry + 0x20, 4, desc[1], 0, self + 0x5C,
                lbl_806509CC);
    entry[0x24] = desc[0x1A];
    fn_8018E230(self + 0x60, self + 0x5F, 1, 0, (s8)desc[0x14],
                desc[0x15]);
    if (desc[0x1A] == 2) {
        fn_8018CD18(*(void**)(self + 0x54), 1,
                    *(u16*)(lbl_80607120 + 2));
    } else {
        fn_8018CB70(*(void**)(self + 0x54), 1,
                    *(u16*)(lbl_80607120 + 2));
    }
    fn_8018C540(*(void**)(self + 0x58), self + 0x5C, self[1], 4,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(self + 0x22) = 4;
    *(s16*)(desc + 4) = (rand() & 1) + 9;
    *(s16*)(desc + 4) += rand() & 3;
    if (*(s16*)(desc + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(desc + 4), lbl_80606328,
                    lbl_80606318);
    }
}
