typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_80651E00;
extern u16 lbl_80651E04;
extern u32 lbl_80651E08;
extern u16 lbl_80651E0C;
extern void* lbl_8064D224;
extern const float lbl_80650C10;
extern u8 lbl_80607120[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];

extern void fn_801804AC(void*, void*, void*, void*);
extern void* memset(void*, int, unsigned long);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019C4E4(u8* object, void* first, void* second, u8* config)
{
    register u8 count;
    register u8* entry;
    u8* cfg;
    void* base;
    u8* self;
    int i;
    struct { u32 word; u16 half; } setup;
    struct { u32 word; u16 half; } value;

    cfg = config;
    base = first;
    self = object;
    setup.word = lbl_80651E00;
    setup.half = lbl_80651E04;
    value.word = lbl_80651E08;
    value.half = lbl_80651E0C;
    count = cfg[0];
    entry = *(u8**)(self + 0x4C);
    fn_801804AC(self, base, &setup, &value);

    self[0] = 0x80;
    self[1] = cfg[0];
    self[2] = cfg[2];
    self[4] = cfg[3];
    *(u16*)(self + 0xC) = *(u16*)(cfg + 6);
    *(s16*)(self + 0xE) = *(s16*)(cfg + 4);
    *(u16*)(self + 0xA) = 0;
    *(u32*)(self + 0x44) = 0;
    *(void**)(self + 0x68) = lbl_8064D224;
    memset(self + 0x24, 0, 0x10);
    cfg[0x1B] = 0;

    i = 0;
    for (; (u8)i < count; entry += 0x38, i++) {
        fn_80180554(entry, base, &setup, &value, *(u16*)(cfg + 8), 0);
        fn_801805E0(entry + 0x20, 4, cfg[1], (u32)((i & 0x3F) * 4),
                    cfg + 0x18, lbl_80650C10);
    }

    fn_8018CEC0(*(void**)(self + 0x54), count);
    fn_8018C540(*(void**)(self + 0x58), cfg + 0x18, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(cfg + 4) >= 0) {
        fn_801F5A04(self + 0x6C, *(s16*)(cfg + 4),
                    lbl_80606328, lbl_80606318);
    }
}
