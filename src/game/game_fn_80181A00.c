typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern u32 lbl_80650988;
extern const float lbl_8065098C;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);
extern unsigned int rand(void);
extern void fn_80179904(ShortCoord3*, s16);
extern void fn_801804AC(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*);
extern void fn_80180518(void*, u32, int);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        int);
extern void fn_801805E0(void*, int, u8, u32, u32*, float);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, u32*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80181A00(u8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    u32 effect;
    ShortCoord3 base;
    ShortCoord3 work;
    u32 i;
    u8 count;
    u8* entry;

    effect = lbl_80650988;
    count = config[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, first, second, (ShortCoord3*)(config + 0x24));

    object[0] = 0x80;
    object[1] = config[0];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    memcpy(&base, second, sizeof(base));
    fn_80179904(&base, *(s16*)(config + 0x20));

    for (i = 0; (u8)i < count; i++) {
        memcpy(&work, config + 0x24, sizeof(work));
        work.z *= (rand() & 7) + 1;
        fn_80180554(entry, first, &base, &work,
                    *(u16*)(config + 8) + (rand() & 0x1F) +
                        *(u16*)(config + 0x1A) * (u8)i,
                    0);
        fn_801805E0(entry + 0x20, 4, config[1], ((u8)i & 0x3F) * 4,
                    &effect, lbl_8065098C);
        entry += 0x38;
    }

    entry = *(u8**)(object + 0x4C);
    fn_80180518(object + 0x24, 0, 1);
    fn_8018E230(entry, entry + 0x2B, 1, object[2], object[4], 0);
    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), &effect, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
