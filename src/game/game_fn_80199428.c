typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

extern u32 lbl_80651DC0;
extern u16 lbl_80651DC4;
extern u32 lbl_80650BC0;
extern const float lbl_80650BC4;
extern const float lbl_80650BC8;
extern const float lbl_80650BCC;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_802FC5BC[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];

extern void fn_801804AC(void*, void*, void*, void*);
extern void* memset(void*, int, unsigned long);
extern void fn_80180554(void*, void*, void*, void*, int, s16);
extern int rand(void);
extern void fn_801805E0(void*, int, u8, u8, float, void*);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80199428(u8* object, void* first, void* second, u8* config)
{
    u8 count;
    u8* entry;
    int i;
    struct {
        u32 word;
        u16 half;
    } setup;
    u32 value;

    setup.word = lbl_80651DC0;
    setup.half = lbl_80651DC4;
    value = lbl_80650BC0;
    count = config[0];
    fn_801804AC(object, first, second, &setup);

    object[0] = 0x80;
    object[1] = count;
    object[4] = config[3];
    *(s16*)(object + 0xe) = *(s16*)(config + 4);
    *(u16*)(object + 0xc) = *(u16*)(config + 6);
    *(u16*)(object + 0xa) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3c) = lbl_80650BC4;
    *(float*)(object + 0x40) = lbl_80650BC8;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    entry = *(u8**)(object + 0x4c);
    i = 0;
    for (; (u8)i < count; entry += 0x38, i++) {
        fn_80180554(entry, first, second, &setup, 0, *(s16*)(config + 0x20));
        fn_801805E0(entry + 0x20, 4,
                    (u8)(config[1] + (rand() & 3)),
                    (u32)((u8)i << 2), lbl_80650BCC, &value);
    }

    fn_8018CEC0(*(void**)(object + 0x54), count);
    fn_8018C540(*(void**)(object + 0x58), lbl_802FC5BC + 0xc, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6c, *(s16*)(config + 4),
                    lbl_80606328, lbl_80606318);
    }
}
