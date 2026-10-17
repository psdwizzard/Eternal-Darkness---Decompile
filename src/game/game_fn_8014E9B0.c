typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3Words {
    u32 x, y, z;
} Vec3Words;

typedef struct ConfigBlock {
    u8 bytes[0x14];
} ConfigBlock;

typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct Entry Entry;
struct Entry {
    u8 unknown00[4];
    short type;
    u8 unknown06[0x8A];
    void* (*create)(Vec3s*, Vec3s*, Entry*);
    void* instance;
    Vec3f position;
    Vec3s rotation;
    u8 flags;
};

typedef struct Item Item;

typedef struct Effect {
    u8 type;
    u8 mode;
    u8 pad02[2];
    u16 value;
    u8 pad06[0xA];
    u32 resource;
    u8 state;
    u8 pad15[2];
    u8 size;
    u8 flags;
    u8 pad19[7];
    u16 count;
    u8 pad22[0x2E];
    float scale;
    u8 pad54[0x3C];
    void* (*update)(void*, void*, ConfigBlock*);
    u32 owner;
    Vec3Words position;
    u8 config[6];
    u8 variant;
} Effect;

typedef struct Config {
    u32 word;
    u16 half;
} Config;

extern u32 lbl_80650530;
extern u16 lbl_80650534;
extern const float lbl_80650538;

extern void fn_80180D0C(Effect*);
extern void fn_80180DDC(u8*, u8);
extern void* fn_80180E14(void*, void*, ConfigBlock*);
extern Item* fn_80147EC4(Entry*);
extern void* memcpy(void*, const void*, u32);

void fn_8014E9B0(Effect* effect, Vec3Words* position, u8 type, u16 value,
                 u32* resource, u8 mode, u8 variant, int enabled)
{
    Config config;

    config.word = lbl_80650530;
    config.half = lbl_80650534;
    fn_80180D0C(effect);
    effect->type = type;
    effect->mode = mode;
    effect->value = value;
    effect->resource = *resource;
    fn_80180DDC((u8*)effect, type);
    effect->state = 0;
    effect->count = 2;
    effect->size = 4;
    if (enabled == 0)
        effect->flags &= ~0x40;
    effect->scale = lbl_80650538;
    effect->update = fn_80180E14;
    effect->position = *position;
    memcpy(effect->config, &config, 6);
    effect->owner = 0;
    effect->variant = variant;
    /* Effect and Entry share the placement fields at offsets 0x90 through 0xAA. */
    fn_80147EC4((Entry*)effect);
}
