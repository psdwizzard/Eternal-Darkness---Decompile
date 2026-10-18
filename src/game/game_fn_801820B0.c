typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma pack(push, 1)
typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;
#pragma pack(pop)

extern u32 lbl_80651CE8;
extern u16 lbl_80651CEC;
extern void* lbl_8064D224;
extern float lbl_806509B0;
extern u32 lbl_802FC5BC[];
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void fn_801804AC(void*, void*, void*, SixBytes*);
extern void fn_80180554(void*, void*, void*, SixBytes*, u16, s16);
extern void fn_801805E0(void*, int, u8, int, float, void*);
extern void fn_80180518(void*, u8, int);
extern void fn_8018F014(void*, u8);
extern unsigned int rand(void);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);
extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);

void fn_801820B0(u8* object, void* arg1, void* arg2, u8* descriptor)
{
    void* table;
    u8 i;
    u8 count;
    u8* entry;
    u8 random_count;
    SixBytes setup;
    SixBytes position;
    int variant;

    setup.word = lbl_80651CE8;
    setup.half = lbl_80651CEC;
    count = descriptor[0];
    entry = *(u8**)(object + 0x4C);
    fn_801804AC(object, arg1, arg2, &setup);
    object[0] = 0x80;
    object[1] = descriptor[0];
    object[2] = descriptor[2];
    object[4] = descriptor[3];
    *(u16*)(object + 0xC) = *(u16*)(descriptor + 6);
    *(s16*)(object + 0xE) = *(s16*)(descriptor + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    table = &lbl_802FC5BC[3];
    for (i = 0; i < count; entry += 0x38, i++) {
        memcpy(&position, arg2, 6);
        fn_8018F014(&position, descriptor[0x14]);
        if (*(int*)(descriptor + 0x1C) != 0) {
            variant = (s16)((rand() & 3) + 1);
        } else {
            variant = 0;
        }
        fn_80180554(entry, arg1, &position, &setup,
                    *(u16*)(descriptor + 8), variant);
        random_count = descriptor[1] - ((descriptor[1] - 1) & rand());
        fn_801805E0(entry + 0x20, 4, random_count, (i & 0x3F) << 2,
                    lbl_806509B0, table);
        fn_80180518(object + 0x24, i, 1);
    }

    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), table, count, 4,
                *(u16*)(lbl_80607120 + 2));
    *(u16*)(object + 0x22) = 4;
    if (*(s16*)(descriptor + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(descriptor + 4),
                    lbl_80606328, lbl_80606318);
    }
}
