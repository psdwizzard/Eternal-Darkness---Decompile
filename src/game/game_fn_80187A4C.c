typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

extern u32 lbl_80651D60;
extern u16 lbl_80651D64;
extern void* lbl_8064D224;
extern float lbl_80650A54;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607130[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern void fn_801805E0(void*, int, u8, int, void*, float);
extern void fn_8018E230(void*, void*, int, int, s8, u8);
extern void fn_8018CB70(void*, int, u16);
extern void fn_8018C540(void*, void*, int, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80187A4C(u8* self, void* arg1, void* arg2, u8* desc)
{
    SixBytes setup;
    u8* entry;
    int value;

    setup.word = lbl_80651D60;
    setup.half = lbl_80651D64;
    entry = *(u8**)(self + 0x4C);
    fn_801804AC(self, arg1, arg2, &setup);

    self[0] = 0x80;
    self[2] = desc[2];
    self[4] = desc[3];
    *(s16*)(self + 0xE) = *(s16*)(desc + 4);
    *(void**)(self + 0x68) = lbl_8064D224;
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    memset(self + 0x24, 0, 0x10);

    fn_80180554(entry, arg1, arg2, &setup, 0, 0);
    if (*(int*)(desc + 0x20) != 0) {
        value = (u8)(desc[1] >> 1);
    } else {
        value = desc[1];
    }
    fn_801805E0(entry + 0x20, 4, value, 0, lbl_802FC5BC,
                lbl_80650A54);
    fn_8018E230(entry, entry + 0x2B, 1, 0, (s8)desc[0x24], desc[0x25]);
    fn_8018CB70(*(void**)(self + 0x54), 1, *(u16*)(lbl_80607130 + 2));
    fn_8018C540(*(void**)(self + 0x58), lbl_802FC5BC, 1, 4,
                *(u16*)(lbl_80607130 + 2));
    if (*(s16*)(desc + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(desc + 4), lbl_80606328,
                    lbl_80606318);
    }
}
