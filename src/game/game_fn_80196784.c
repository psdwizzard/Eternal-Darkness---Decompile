typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u32 lbl_80651DB0;
extern u16 lbl_80651DB4;
extern void* lbl_8064D224;
extern float lbl_80650B84;
extern char lbl_80606318[];
extern char lbl_80606328[];

void fn_801804AC(void* object, void* arg, int value, void* info);
void fn_80180554(void* entry, void* arg, int value, void* info, u16 kind, int zero);
void fn_801805E0(void* entry, int two, u8 count, u8 index, void* data, float scale);
void fn_801806D4(void* entry, void* data, int one);
void fn_8018C118(void* state, u8 count);
void fn_8019753C(void* state, void* first, void* second, u8 count);
void fn_801F5A04(void* state, s16 value, const char* a, const char* b);
void* memcpy(void* dst, const void* src, unsigned long size);

void fn_80196784(u8* object, void* arg, int value, u8* config)
{
    u8 count;
    u8 total;
    u8* data;
    u8 i;
    u8* entry;
    u32 first;
    u32 second;
    struct {
        u32 word;
        u16 half;
    } info;

    data = config + 0x14;
    info.word = lbl_80651DB0;
    info.half = lbl_80651DB4;
    count = config[0];
    entry = *(u8**)(object + 0x4c);
    total = count * 2;
    fn_801804AC(object, arg, value, &info);

    object[0] = 0x80;
    object[1] = total;
    *(u16*)(object + 0xc) = *(u16*)(config + 6);
    *(s16*)(object + 0xe) = *(s16*)(config + 4);
    *(u16*)(object + 0xa) = 0;
    *(u32*)(object + 0x44) = 0;
    object[4] = config[3];
    *(void**)(object + 0x68) = lbl_8064D224;
    memcpy(&first, data, 4);
    memcpy(&second, data + 4, 4);

    for (i = 0; i < total; i++) {
        fn_80180554(entry, arg, value, &info, *(u16*)(config + 8), 0);
        fn_801805E0(entry + 0x20, 2, config[1], i * 2, &first, lbl_80650B84);
        entry[2] = data[0xe];
        entry[3] = data[0xf];
        entry += 0x38;
    }

    i = count;
    entry = *(u8**)(object + 0x4c) + count * 0x38;
    while (i < total) {
        fn_801806D4(entry + 0x20, &second, 1);
        entry += 0x38;
        i++;
    }

    fn_8018C118(*(void**)(object + 0x54), total);
    fn_8019753C(*(void**)(object + 0x58), &first, &second, total);
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6c, *(s16*)(config + 4), lbl_80606328, lbl_80606318);
    }
}
