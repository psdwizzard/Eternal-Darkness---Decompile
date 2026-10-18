typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

extern u32 lbl_80651E60;
extern u16 lbl_80651E64;
extern u32 lbl_8064D224;
extern u32 lbl_8064D18C;
extern float lbl_80650D10;
extern u8 lbl_80607120[];
extern u32 lbl_80607440[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void fn_801804AC(void*, ShortCoord3*, ShortCoord3*, SixBytes*);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, SixBytes*, u16, int);
extern unsigned int rand(void);
extern void fn_801805E0(void*, int, u8, u32, u32*, float);
extern void fn_80180518(void*, u32, int);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_801A1C78(u8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    SixBytes setup;
    ShortCoord3 position;
    u8* entry;
    u8 count;
    u8 random_value;
    u32 i;

    setup.word = lbl_80651E60;
    setup.half = lbl_80651E64;
    position.x = first->x;
    position.y = first->y;
    position.z = first->z;
    entry = *(u8**)(object + 0x4C);
    count = config[0];
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = config[0];
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    object[5] = 0;
    *(u32*)(object + 0x44) = 0;
    *(u32*)(object + 0x68) = lbl_8064D224;
    *(u32*)(object + 0x38) = lbl_8064D18C;
    object[3] |= 0x81;
    memset(object + 0x24, 0, 0x10);

    for (i = 0; (u8)i < count; i++) {
        fn_80180554(entry, &position, second, &setup, *(u16*)(config + 8), 0);
        random_value = config[1];
        fn_801805E0(entry + 0x20, 4,
                    random_value - ((random_value - 1) & rand()) + 4,
                    (i & 0x3F) * 4,
                    lbl_80607440, lbl_80650D10);
        fn_80180518(object + 0x24, i, 1);
        entry += 0x38;
    }

    fn_8018CB70(*(void**)(object + 0x54), count,
                 *(u16*)(lbl_80607120 + 2));
    *(u16*)(object + 0x22) = 4;
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
