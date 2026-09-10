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

extern u32 lbl_80651DE8;
extern u16 lbl_80651DEC;
extern void* lbl_8064D224;
extern const float lbl_80650BEC;
extern const float lbl_80650BF0;
extern const float lbl_80650BF4;
extern const float lbl_80650BF8;
extern u8 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_801804AC(void*, void*, void*, void*);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern void fn_801805E0(void*, int, u8, int, void*, float);
extern void fn_8018E230(void*, void*, int, u8, signed char, int);
extern void fn_8018E260(void*, u8, u8);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern u32 fn_8018EF9C(void*);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8019B1BC(u8* object, ShortCoord3* first, void* second, u8* config)
{
    u8 count;
    u8* entry;
    SixBytes setup;
    ShortCoord3 position;
    u32 texture;
    u32 i;
    float angle;

    setup.word = lbl_80651DE8;
    setup.half = lbl_80651DEC;
    count = config[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = count;
    object[2] = config[2];
    object[4] = config[3];
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(float*)(object + 0x3C) = lbl_80650BEC;
    *(float*)(object + 0x40) = *(float*)(config + 0x34);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    for (i = 0; (u8)i < count; i++) {
        angle = lbl_80650BF0 * (float)(u8)i / (float)count;
        position.x = first->x + lbl_80650BF4 * fn_80048C2C(angle);
        position.y = first->y + lbl_80650BF4 * fn_80048C50(angle);
        position.z = first->z;
        fn_80180554(entry, &position, second, &setup, 0, 0);
        fn_801805E0(entry + 0x20, 4, config[1], 0,
                    lbl_802FC5BC + 0xC, lbl_80650BF8);

        if (config[0x16] != 0) {
            fn_8018E230(entry, entry + 0x2B, 1, 0,
                        config[0x16], config[0x17]);
        } else if (*(u16*)(config + 6) == 0 &&
                   *(int*)(config + 0x1C) == 0) {
            if (config[0x14] != config[0x15]) {
                fn_8018E230(entry, entry + 0x2B, 3, config[0x14],
                            ((signed char*)config)[0x19], config[0x15]);
                fn_8018E260(entry, config[0x14], config[0x15]);
            } else {
                fn_8018E230(entry, entry + 0x2B, 1, config[2],
                            ((signed char*)config)[3], 0);
            }
        } else {
            entry[0x2B] = config[0x17];
        }
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                *(u16*)(lbl_80607120 + 2));
    texture = fn_8018EF9C(*(void**)(config + 0x38));
    fn_8018C540(*(void**)(object + 0x58), &texture, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
