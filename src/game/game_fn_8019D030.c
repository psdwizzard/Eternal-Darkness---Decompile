typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

extern u32 lbl_80651E10;
extern u16 lbl_80651E14;
extern void* lbl_8064D224;
extern const float lbl_80650C3C;
extern const float lbl_80650C40;
extern const float lbl_80650C44;
extern const float lbl_80650C48;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern int fn_800FBFB0(void);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180518(void*, u8, int);
extern void fn_801805E0(void*, int, u8, u8, float, void*);
extern void fn_8017E958(void*, void*, s16, float);
extern void fn_8017E734(void*, void*, void*, void*, void*);
extern void fn_8018E230(void*, void*, int, int, s8, u8);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019D030(u8* object, void* first, void* second, u8* config)
{
    SixBytes setup;
    int x_negative;
    int bits;
    int value;
    int y_negative;
    int z_negative;
    void* texture;
    u8 count;
    u8* entry;
    int i;
    s16 magnitude;

    setup.word = lbl_80651E10;
    setup.half = lbl_80651E14;
    count = config[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = count;
    object[2] = config[2];
    object[4] = config[3];
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(void**)(object + 0x68) = lbl_8064D224;
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3C) = lbl_80650C3C;
    *(float*)(object + 0x40) = lbl_80650C40;
    memset(object + 0x24, 0, 0x10);

    fn_8017E958(entry + 0xA, object + 0x10, *(s16*)(config + 0x16),
                lbl_80650C3C);
    texture = lbl_802FC5BC + 0xC;
    value = config[1];
    fn_801805E0(entry + 0x20, 4, value, 0, lbl_80650C44, texture);
    fn_80180518(object + 0x24, 0, 1);
    fn_8018E230(entry, entry + 0x2B, 1, 0, (s8)config[0x14], config[0x15]);

    fn_8017E958(entry + 0x42, object + 0x10, *(s16*)(config + 0x16),
                lbl_80650C48);
    fn_801805E0(entry + 0x58, 4, config[1], 0, lbl_80650C44, texture);
    fn_80180518(object + 0x24, 1, 1);
    fn_8018E230(entry + 0x38, entry + 0x63, 1, 0, (s8)config[0x14],
                config[0x15]);

    entry += 0x70;
    bits = fn_800FBFB0();
    x_negative = bits & 1;
    y_negative = bits & 2;
    z_negative = bits & 4;
    i = 2;
    for (; i < 5; i++, entry += 0x38) {
        int random;
        int sign;

        random = (fn_800FBFB0() & 7) + 1;
        sign = x_negative ? -1 : 1;
        *(s16*)(entry + 0x10) = sign * random;

        random = (fn_800FBFB0() & 7) + 1;
        sign = y_negative ? -1 : 1;
        *(s16*)(entry + 0x12) = sign * random;

        random = (fn_800FBFB0() & 7) + 1;
        sign = z_negative ? -1 : 1;
        *(s16*)(entry + 0x14) = sign * random;

        magnitude = *(s16*)(config + 0x18);
        *(s16*)(entry + 0x16) = fn_800FBFB0() % (magnitude * 2) - magnitude;
        magnitude = *(s16*)(config + 0x1A);
        *(s16*)(entry + 0x18) = fn_800FBFB0() % (magnitude * 2) - magnitude;
        magnitude = *(s16*)(config + 0x1C);
        *(s16*)(entry + 0x1A) = fn_800FBFB0() % (magnitude * 2) - magnitude;

        fn_8017E734(entry + 0xA, first, entry + 0x10, config + 0x18,
                    entry + 0x16);
        fn_801805E0(entry + 0x20, 4, config[1], 0, lbl_80650C44,
                    texture);
        fn_80180518(object + 0x24, (u8)i, 1);
        fn_8018E230(entry, entry + 0x2B, 1, 0, (s8)config[0x14],
                    config[0x15]);
    }

    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), config + 0x10, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
