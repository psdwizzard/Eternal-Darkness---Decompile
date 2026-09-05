typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Config {
    u8 pad[0x3C];
    void* effects[1];
} Config;

extern void* memcpy(void*, const void*, u32);
extern void fn_8018EFB0(Vec3s*, u16, int);
extern unsigned int fn_800FBFB0(void);
extern void fn_80180554(void*, void*, Vec3s*, void*, u16, int);
extern void fn_8018E230(void*, void*, int, int, s8, u8);
extern void fn_80185108(void*);
extern void fn_801851A0(void*, void*);

void fn_8018284C(u8* self, int index)
{
    u8* config2;
    u8* config = self + 0x8C;
    u8* item = *(u8**)(self + 0x4C) + index * 0x38;
    Vec3s position;
    void* effect;

    memcpy(&position, self + 0x16, 6);
    fn_8018EFB0(&position, *(u16*)(config + 4), 0);
    fn_8018EFB0(&position, *(u16*)(config + 4), 1);
    position.z *= config[6];
    position.z += config[7] & fn_800FBFB0();
    fn_80180554(item, self + 0x10, &position, self + 0x1C,
                *(u16*)(item + 8), 0);

    if (config[0x30] == config[0x31]) {
        item[0x2B] = config[0x31];
    } else {
        fn_8018E230(item, item + 0x2B, 1, 0, (s8)config[0x30], config[0x31]);
    }
    config[index + 0xA] = 0;
    item[0x21] = config[0x34];

    if (config[0x38] != 0) {
        config2 = config;
        config2 = config2 + index * 4;
        effect = *(void**)(config2 + 0x3C);
        fn_80185108(effect);
        fn_801851A0(effect, self + 0x10);
    }
}
