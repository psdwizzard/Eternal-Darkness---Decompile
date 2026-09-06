typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_80651DF8;
extern u16 lbl_80651DFC;
extern const float lbl_80650C10;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];

extern void* memcpy(void*, const void*, u32);
extern void* memset(void*, int, u32);
extern void fn_80179904(void*, s16);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_8018EFB0(void*, u16, int);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019BDE8(u8* object, void* first, void* second, u8* config)
{
    u8 count;
    u8* entry;
    s16 mode;
    int i;
    u8 base[8];
    struct {
        u32 word;
        u16 half;
    } setup;
    u8 current[8];
    u8 work[8];

    setup.word = lbl_80651DF8;
    setup.half = lbl_80651DFC;
    count = config[0];
    entry = *(u8**)(object + 0x4c);
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = config[0];
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xc) = *(u16*)(config + 6);
    *(s16*)(object + 0xe) = *(s16*)(config + 4);
    *(u16*)(object + 0xa) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    memcpy(base, second, 6);
    fn_80179904(base, *(s16*)(config + 0x14));
    config[0x1b] = 0;

    i = 0;
    for (; (u8)i < count; entry += 0x38, i++) {
        memcpy(current, base, 6);
        memcpy(work, first, 6);
        *(s16*)(current + 4) = -32;
        mode = *(u16*)(config + 0x16);
        fn_8018EFB0(work, mode, 0);
        fn_8018EFB0(work, *(u16*)(config + 0x16), 1);
        fn_80180554(entry, work, current, &setup,
                    *(u16*)(config + 8), 1);
        fn_801805E0(entry + 0x20, 4, config[1], ((u8)i & 0x3f) * 4,
                    config + 0x18, lbl_80650C10);
    }

    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), config + 0x18, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6c, *(s16*)(config + 4),
                    lbl_80606328, lbl_80606318);
    }
}
