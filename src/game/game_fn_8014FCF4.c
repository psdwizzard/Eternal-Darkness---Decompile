typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3Words { u32 x, y, z; } Vec3Words;

extern u32 lbl_80651C18;
extern u16 lbl_80651C1C;
extern const float lbl_80650580;
extern void fn_8014B738(void);
extern u8* fn_80149D98(void*);
extern void fn_80149D64(void*);
extern void fn_801857B4(void*);
extern void fn_80185A44(void);
extern int fn_801E8328();
extern void* memcpy(void*, const void*, unsigned int);

void fn_8014FCF4(Vec3Words* position, u16 value, u16 target,
                 int enabled, u32* source)
{
    u8* instance = fn_80149D98(fn_8014B738);
    struct { u32 word; u16 half; } config;

    if (instance != 0) {
        u8* embedded;
        Vec3Words adjusted;

        config.word = lbl_80651C18;
        config.half = lbl_80651C1C;
        instance[0x1328] = 4;
        fn_80149D64(instance);
        embedded = instance + 8;
        fn_801857B4(embedded);
        *(u32*)(embedded + 0x78) = *source;
        embedded[0x7B] = 0xFF;
        *(u16*)(embedded + 4) = value;
        embedded[1] = 50;
        *(u16*)(embedded + 8) = 30;
        *(u16*)(embedded + 6) = *(u16*)(embedded + 8) + 25;
        *(s8*)(embedded + 3) = -10;
        embedded[0x14] = (u16)target / 30;
        *(u16*)(embedded + 0x1C) = 5;
        embedded[0x18] |= 2;
        if (enabled != 0)
            embedded[0x18] |= 8;
        embedded[0x19] = 8;
        *(void**)(embedded + 0x90) = fn_80185A44;
        adjusted = *position;
        *(float*)&adjusted.z += lbl_80650580;
        *(Vec3Words*)(embedded + 0x98) = adjusted;
        memcpy(embedded + 0xA4, &config, 6);
        *(u32*)(embedded + 0x94) = 0;
        embedded[0xAA] = 4;
        fn_801E8328(0x10, embedded);
    }
}
