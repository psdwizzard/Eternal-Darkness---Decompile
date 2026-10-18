typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern u32 lbl_80651E18;
extern u16 lbl_80651E1C;
extern void* lbl_8064D18C;
extern void* lbl_8064D224;
extern const float lbl_80650C50;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern u32 rand(void);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180518(void*, u8, int);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern int fn_8018F0A0(void);
extern void fn_8018EFB0(void*, u8, int);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C8FC(void*, void*, u8, int, u16, int);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019D714(u8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    u8 effect[4];
    struct {
        u32 word;
        u16 half;
    } setup;
    ShortCoord3 base;
    u32 i;
    u8* entry;
    u8 count;
    u8 variant;

    setup.word = lbl_80651E18;
    setup.half = lbl_80651E1C;
    entry = *(u8**)(object + 0x4C);
    count = config[0];
    variant = config[0x1E];
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = config[0];
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x38) = lbl_8064D18C;
    *(void**)(object + 0x68) = lbl_8064D224;
    object[3] |= 0x80;

    if (fn_8018F0A0() != 0) {
        *(s16*)(object + 0x1A) = -*(s16*)(object + 0x1A);
        second->z = -second->z;
    }

    memset(object + 0x24, 0, 0x10);
    effect[0] = config[0x18];
    effect[1] = config[0x19];
    effect[2] = config[0x1A];
    effect[3] = 0;
    fn_80180518(object + 0x24, 0, 1);

    for (i = 0; (u8)i < count; i++) {
        memcpy(&base, first, sizeof(base));
        if (variant >= 2) {
            fn_8018EFB0(&base, variant, 0);
            fn_8018EFB0(&base, variant, 1);
        }
        fn_80180554(entry, &base, second, &setup, *(u16*)(config + 8), 0);
        fn_801805E0(entry + 0x20, 4,
                    (u8)(config[1] - ((config[1] - 1) & rand()) + 2),
                    ((u8)i & 0x3F) * 4, effect, lbl_80650C50);
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                 *(u16*)(lbl_80607120 + 2));
    fn_8018C8FC(*(void**)(object + 0x58), effect, count, 4,
                 *(u16*)(lbl_80607120 + 2), 4);
    *(u16*)(object + 0x22) = 4;
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
