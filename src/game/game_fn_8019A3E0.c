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

extern u32 lbl_80651DD8;
extern u16 lbl_80651DDC;
extern void* lbl_8064D224;
extern const float lbl_80650BC4;
extern const float lbl_80650BCC;
extern const float lbl_80650BD8;
extern u32 lbl_80650BDC;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern u32 rand(void);
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void fn_801805E0(void*, int, u8, u32, void*, float);
extern void fn_80180518(void*, u32, int);
extern void fn_8018E230(void*, void*, int, int, u8, u8);
extern void fn_8018CB70(void*, u8, u16);
extern void* fn_8018EF9C(void*);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019A3E0(u8* object, void* first, void* second, u8* config)
{
    SixBytes setup;
    ShortCoord3 random;
    u32 effect;
    u8 count;
    u8* entry;
    u32 i;
    u8 random_mask;
    void* table;
    float initial_b = lbl_80650BD8;
    float initial_a = lbl_80650BC4;

    setup.word = lbl_80651DD8;
    setup.half = lbl_80651DDC;
    effect = lbl_80650BDC;
    count = config[0];

    object[0] = 0x80;
    object[1] = count;
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3C) = initial_a;
    *(float*)(object + 0x40) = initial_b;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    random_mask = config[1] - 1;
    entry = *(u8**)(object + 0x4C);
    for (i = 0; (u8)i < count; i++) {
        random.x = 4 - (rand() & 7);
        random.y = 4 - (rand() & 7);
        random.z = 4 - (rand() & 3);
        fn_80180554(entry, first, &random, &setup,
                    (rand() & 7) + 7, 0);
        fn_801805E0(entry + 0x20, 4,
                    config[1] - (random_mask & rand()),
                    (i & 0x3F) * 4, &effect, lbl_80650BCC);
        fn_8018E230(entry, entry + 0x2B, 1, 0, 0x33, 0xFF);
        fn_80180518(object + 0x24, i, 1);
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                *(u16*)(lbl_80607120 + 2));
    table = fn_8018EF9C(*(void**)(config + 0x18));
    fn_8018C540(*(void**)(object + 0x58), &table, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
