typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern u32 lbl_80651CC8;
extern u16 lbl_80651CCC;
extern void* lbl_8064D224;
extern float lbl_80650938;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);
extern void fn_80179904(ShortCoord3*, s16);
extern void fn_801804AC(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*);
extern void fn_8018EFB0(ShortCoord3*, u8, int);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        int);
extern void fn_801805E0(void*, int, u8, u32, u8*, float);
extern void fn_80180518(void*, u32, int);
extern void fn_8018CEC0(void*);
extern void fn_8017FA14(void*, u8*, u8*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_8017EE58(u8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    u32 i;
    ShortCoord3 work;
    ShortCoord3 base;
    ShortCoord3 current;
    ShortCoord3 zero;

    *(u32*)&zero = lbl_80651CC8;
    *(u16*)((u8*)&zero + 4) = lbl_80651CCC;
    object[0] = 0x80;
    object[1] = config[0];
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    memcpy(&base, second, sizeof(base));
    fn_80179904(&base, *(s16*)(config + 0x14));
    fn_801804AC(object, first, &base, &zero);

    i = 0;
    current.x = first->x + 10;
    current.y = first->y - 10;
    current.z = first->z;

    while ((u8)i < object[1] - 1) {
        u8* entry = *(u8**)(object + 0x4C) + (i & 0xFF) * 0x38;

        memcpy(&work, &base, sizeof(work));
        if (work.x != 0) {
            fn_8018EFB0(&work, config[0x16], 0);
        }
        if (work.y != 0) {
            fn_8018EFB0(&work, config[0x16], 1);
        }
        fn_80180554(entry, first, &work, &zero, *(u16*)(config + 8), 1);
        fn_801805E0(entry + 0x20, 4, config[1], 0, config + 0x1C,
                    lbl_80650938);
        fn_80180518(object + 0x24, i, 1);

        fn_80180554(entry + 0x38, &current, &work, &zero,
                    *(u16*)(config + 8), 1);
        fn_801805E0(entry + 0x58, 4, config[1], 0, config + 0x20,
                    lbl_80650938);
        fn_80180518(object + 0x24, (u8)((u8)i + 1), 1);
        i += 2;
    }

    fn_8018CEC0(*(void**)(object + 0x54));
    fn_8017FA14(*(void**)(object + 0x58), config + 0x1C, config + 0x20,
                object[1], 4, *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
