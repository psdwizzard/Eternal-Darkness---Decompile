typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3Words {
    u32 x, y, z;
} Vec3Words;

extern u32 lbl_80651C00;
extern u16 lbl_80651C04;
extern const float lbl_80650578;
extern const float lbl_8065057C;

extern void fn_80150158(void);
extern u8* fn_80149D98(void*);
extern void fn_80149D64(void*);
extern void fn_801858E0(void*);
extern void* fn_80185AE8(s16*, void*, u8*);
extern int fn_801E8328();
extern void* memcpy(void*, const void*, unsigned int);

void fn_8014F834(Vec3Words* position, u16 value, u16 target,
                 int enabled, u32* source, float scale)
{
    u8* instance = fn_80149D98(fn_80150158);
    struct {
        u32 word;
        u16 half;
    } config;

    if (instance != 0) {
        u8* embedded;
        u8 divisor;
        float delta;

        config.word = lbl_80651C00;
        config.half = lbl_80651C04;
        instance[0x1328] = 4;
        fn_80149D64(instance);
        delta = (lbl_80650578 + scale) / lbl_8065057C;
        *(u16*)(instance + 8) = 0;
        embedded = instance + 0x10;
        *(u16*)(instance + 0x0A) = 0;
        *(s16*)(instance + 0x0C) = -delta;
        divisor = (*(u8*)(instance + 0x0F) =
                       -(60 / *(s16*)(instance + 0x0C)));
        fn_801858E0(embedded);
        *(u32*)(embedded + 0x78) = *source;
        embedded[0x7B] = 0xFF;
        *(u16*)(embedded + 4) = value;
        embedded[1] = 0x20;
        *(u16*)(embedded + 8) = 0x1E;
        *(u16*)(embedded + 6) = *(u16*)(embedded + 8);
        embedded[0x14] = ((u16)target - embedded[1]) / divisor;
        *(u16*)(embedded + 0x1C) = embedded[1];
        embedded[0x18] |= 2;
        if (enabled != 0)
            embedded[0x18] |= 8;
        embedded[0x19] = 8;
        *(void**)(embedded + 0x90) = fn_80185AE8;
        *(Vec3Words*)(embedded + 0x98) = *position;
        *(float*)(embedded + 0xA0) += scale;
        memcpy(embedded + 0xA4, &config, 6);
        *(u32*)(embedded + 0x94) = 0;
        embedded[0xAA] = 4;
        fn_801E8328(0x10, embedded);
    }
}
