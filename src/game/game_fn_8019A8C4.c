typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern u32 lbl_80651DE0;
extern u16 lbl_80651DE4;
extern void* lbl_8064D224;
extern const float lbl_80650BC4;
extern const float lbl_80650BCC;
extern const float lbl_80650BD8;
extern u32 lbl_80650BE0;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern u32 fn_800FBFB0(void);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019A8C4(u8* object, void* first, void* second, u8* config)
{
    SixBytes setup;
    ShortCoord3 random;
    ShortCoord3 table;
    u32 effect;
    u8 count;
    u8* entry;
    u32 i;
    u8 random_mask;
    u32 width;
    u32 mask;

    setup.word = lbl_80651DE0;
    setup.half = lbl_80651DE4;
    effect = lbl_80650BE0;
    count = config[0];
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = count;
    object[4] = config[3];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3C) = lbl_80650BC4;
    *(float*)(object + 0x40) = lbl_80650BD8;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    random_mask = config[1] - 1;
    width = *(u32*)(config + 0x14);
    entry = *(u8**)(object + 0x4C);
    mask = width * 2 - 1;
    memcpy(&table, second, 6);
    random.z = *(s16*)((u8*)first + 4);
    for (i = 0; (u8)i < count; i++) {
        random.x = *(s16*)first + width - (mask & fn_800FBFB0());
        random.y = *(s16*)((u8*)first + 2) + width - (mask & fn_800FBFB0());
        table.z = *(s16*)((u8*)second + 4) + (fn_800FBFB0() & 3);
        fn_80180554(entry, &random, &table, &setup,
                    *(u16*)(config + 8) + (fn_800FBFB0() & 7), 0);
        fn_801805E0(entry + 0x20, 4,
                    config[1] - (random_mask & fn_800FBFB0()),
                    (i & 0x3F) * 4, &effect, lbl_80650BCC);
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(object + 0x58), config + 0x10, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
