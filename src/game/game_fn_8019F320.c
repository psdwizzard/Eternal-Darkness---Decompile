#pragma use_lmw_stmw on
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 lbl_80607120[];
extern u32 lbl_8064D18C;
extern u32 lbl_8064D224;
extern const float lbl_80650C80;
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);

extern void fn_801804AC(u8*, void*, void*, void*);
extern int fn_8018F0A0(void);
extern void fn_80180518(u8*, int, int);
extern void fn_80179904(void*, u8);
extern void fn_80180554(u8*, u8*, void*, u8*, u16, int);
extern void fn_801805E0(u8*, int, u8, u32, u8*, float);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, u8*, u8, int, u16);
extern void fn_801F5A04(u8*, s16, u8*, u8*);

extern u32 lbl_80651E40;
extern u16 lbl_80651E44;

void fn_8019F320(u8* object, u8* source, u8* value, u8* config)
{
    u8 key[6];
    u8 key2[6];
    u8 channel[4];
    u8* entry;
    u8 count;
    u32 i;

    *(u32*)&key[0] = lbl_80651E40;
    *(u16*)&key[4] = lbl_80651E44;
    entry = *(u8**)(object + 0x4C);
    count = config[0];
    fn_801804AC(object, source, value, key);
    object[0] = 0x80;
    object[1] = config[0];
    object[2] = config[2];
    object[4] = config[3];
    *(u16*)(object + 0xC) = *(u16*)(config + 6);
    *(s16*)(object + 0xE) = *(s16*)(config + 4);
    *(u16*)(object + 0xA) = 0;
    *(u32*)(object + 0x44) = 0;
    *(u32*)(object + 0x38) = lbl_8064D18C;
    *(u32*)(object + 0x68) = lbl_8064D224;
    object[3] |= 0x81;
    object[6] = 5;
    object[7] = 5;
    if (fn_8018F0A0()) {
        *(s16*)(object + 0x1A) = -*(s16*)(object + 0x1A);
        *(s16*)(value + 4) = -*(s16*)(value + 4);
    }
    memset(object + 0x24, 0, 0x10);
    channel[0] = config[0x10];
    channel[1] = config[0x11];
    channel[2] = config[0x12];
    channel[3] = config[0x13];
    fn_80180518(object + 0x24, 0, 1);
    for (i = 0; (u8)i < count; i++) {
        memcpy(key2, source, 6);
        fn_80179904(value, config[0x18]);
        fn_80180554(entry, key2, value, key, *(u16*)(config + 8), 0);
        fn_801805E0(entry + 0x20, 4, config[1], (i & 0x3F) * 4, channel, lbl_80650C80);
        entry += 0x38;
    }
    fn_8018CB70(*(void**)(object + 0x54), count, *(u16*)(lbl_80607120 + 2));
    fn_8018C540(*(void**)(object + 0x58), channel, count, 4, *(u16*)(lbl_80607120 + 2));
    *(u16*)(object + 0x22) = 4;
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6C, *(s16*)(config + 4), lbl_80606328, lbl_80606318);
    }
}
#pragma use_lmw_stmw off
