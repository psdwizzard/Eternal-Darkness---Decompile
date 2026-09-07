typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

extern u32 lbl_80651DD0;
extern u16 lbl_80651DD4;
extern u32 lbl_80650BD4;
extern const float lbl_80650BC4;
extern const float lbl_80650BD8;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern char lbl_80606318[];
extern char lbl_80606328[];
extern void fn_801804AC(void*, void*, void*, void*);
extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_8018F014(void*, u16);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern u32 fn_800FBFB0(void);
extern void fn_801805E0(void*, int, u8, u8, void*, float);
extern void fn_8018E230(void*, void*, int, int, u8, int);
extern void fn_80180518(void*, u8, int);
extern void fn_8018CB70(void*, u8, u16);
extern void* fn_8018EF9C(void*);
extern void fn_8018C540(void*, void**, u8, int, u16);
extern void fn_801F5A04(void*, s16, char*, char*);

extern const float lbl_80650BCC;

void fn_80199F10(u8* object, void* owner, void* source, u8* config)
{
    struct {
        u32 word;
        u16 half;
    } point;
    u8 packet[6];
    u32 seed;
    void* handle;
    u8 count;
    u8 limit;
    u8* entry;
    u8 index;
    u8 adjusted;

    point.word = lbl_80651DD0;
    point.half = lbl_80651DD4;
    seed = lbl_80650BD4;
    count = config[0];
    fn_801804AC(object, config + 0x20, source, &point);
    object[0] = 0x80;
    object[1] = count;
    object[4] = config[3];
    *(u16*)(object + 0xc) = *(u16*)(config + 6);
    *(s16*)(object + 0xe) = *(s16*)(config + 4);
    *(u16*)(object + 0xa) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3c) = lbl_80650BC4;
    *(float*)(object + 0x40) = lbl_80650BD8;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    index = 0;
    entry = *(u8**)(object + 0x4c);
    limit = config[1] - 1;
    while (index < count) {
        memcpy(packet, config + 0x20, 6);
        fn_8018F014(packet, *(u16*)(config + 0x1e));
        fn_80180554(entry, packet, source, &point, 0, 0);
        adjusted = config[1] - (limit & fn_800FBFB0());
        fn_801805E0(entry + 0x20, 4, adjusted, index << 2, &seed, lbl_80650BCC);
        fn_8018E230(entry, entry + 0x2b, 1, 0, object[4], 0xcc);
        fn_80180518(object + 0x24, index, 1);
        entry += 0x38;
        index++;
    }
    fn_8018CB70(*(void**)(object + 0x54), count, *(u16*)(lbl_80607120 + 2));
    handle = fn_8018EF9C(*(void**)(config + 0x2c));
    fn_8018C540(*(void**)(object + 0x58), &handle, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(object + 0x6c, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
