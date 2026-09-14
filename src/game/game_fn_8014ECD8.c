typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;

typedef struct Coord3 {
    s16 x, y, z;
} Coord3;

typedef struct Vec3Words {
    unsigned int x, y, z;
} Vec3Words;

extern Coord3 lbl_80650544;
extern float lbl_8065054C;
extern int lbl_802FC5BC[];

extern void fn_80180D0C(void*);
extern void fn_80180DDC(void*, u8);
extern void fn_80180E14(void);
extern void* fn_80149E04(void);
extern void fn_80147E88(void*);
extern void fn_801489B4(void*, void*);
extern void fn_80184740(void*);
extern void fn_80149B38(void*);
extern int fn_801E8328();
extern void* memcpy(void*, const void*, unsigned int);

/* NonMatching: behavior- and size-exact entry/resource initializer at
 * 98.10185% (432/432 bytes). One equivalent relocation names
 * lbl_80650544+4 instead of lbl_80650548, and li 9 is scheduled after the
 * adjacent float load instead of before it. */
void fn_8014ECD8(u8* object, int index, u8 variant)
{
    u8 object_id;
    u8* entry;
    void* resource;
    u8* embedded;
    Coord3 config;
    u16 extent;
    float scale;

    index *= 0x174;
    entry = object + 0xEBC + index;
    config = lbl_80650544;
    object_id = *(volatile u8*)object;

    fn_80180D0C(entry);
    entry[0] = object_id;
    entry[1] = 4;
    *(s16*)(entry + 4) = *(s16*)(object + 0x2A);
    entry[2] = 250;
    *(s8*)(entry + 3) = -25;
    fn_80180DDC(entry, object_id);

    extent = *(volatile u16*)(object + 0x28);
    scale = lbl_8065054C;
    *(u16*)(entry + 0x1C) = extent;
    entry[0x14] = 6;
    *(u16*)(entry + 0x20) = 9;
    entry[0x18] &= ~0x20;
    *(float*)(entry + 0x50) = scale;
    *(u16*)(entry + 8) =
        (*(u16*)(entry + 0x1C) - 1) / (s8)entry[0x14] - 10;
    if (*(int*)(object + 4) != 0)
        *(u16*)(entry + 6) = *(u16*)(entry + 8) + 15;
    else
        *(u16*)(entry + 6) = *(u16*)(entry + 8) + 10;

    *(void (**)(void))(entry + 0x90) = fn_80180E14;
    *(Vec3Words*)(entry + 0x98) = *(Vec3Words*)(object + 0x34);
    memcpy(entry + 0xA4, &config, 6);
    entry[0xAA] = variant;

    resource = fn_80149E04();
    if (resource != 0) {
        embedded = entry + 0xB0;
        *(void**)(entry + 0x170) = resource;
        fn_80147E88(embedded);
        fn_801489B4(embedded, resource);
        embedded[0xBC] = variant;
        *(unsigned int*)(embedded + 0x94) = 0;
        fn_80184740(embedded);
        embedded[1] = 6;
        *(s8*)(embedded + 3) = -25;
        *(s16*)(embedded + 4) = *(s16*)(object + 0x30);
        *(int*)(embedded + 0x2C) = lbl_802FC5BC[3];
        embedded[0x2F] = 0xE0;
        *(u8*)resource = object_id;
        fn_80149B38(resource);
        fn_801E8328(25, entry);
    }
}
