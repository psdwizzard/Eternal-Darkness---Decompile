typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Resource {
    u8 pad00[8];
    u32 mode;
    u8 pad0C[0x3C];
    u32 alternateMode;
} Resource;

typedef struct Effect {
    u8 pad00[0x14];
    u8 type;
    u8 pad15;
    u8 active;
    u8 pad17;
    u32 enabled;
    u32 state;
    u8 pad20[0x88];
    int owner;
    u8 padAC[0x11];
    u8 ready;
    u8 padBE[2];
    Resource *resource;
} Effect;

typedef union Color {
    void *value;
    u8 components[4];
} Color;

extern void *fn_8004910C();
extern void *fn_80201BD0(void *object);
extern u32 fn_801A7480(void *object);
extern void *fn_80149E04(void);
extern void *fn_80201C24(void *object);
extern void fn_80147E88(void *effect);
extern void fn_80148B18(void *effect, u8 *resource);
extern void fn_80149220();
extern u32 fn_801A74C0(void *object);
extern u8 fn_80157AB8(void *object);
extern void *fn_801D3974(int index);
extern int fn_80201B54(int *object);
extern int fn_801E8328(u32 type, u32 object);
extern void *lbl_8064F1C0;

int fn_800C3ADC(void *object, void *alternate)
{
    Color color;
    void *linked;
    void *entry = 0;
    Effect *effect = 0;
    u32 flags;
    u8 index;

    if (alternate != 0) {
        entry = fn_8004910C(alternate);
        if (entry == 0) {
            entry = fn_80201BD0(object);
        }
        effect = (Effect *)fn_801A7480(alternate);
    }
    if (entry != 0 && effect != 0) {
        effect->resource = fn_80149E04();
        if (effect->resource != 0) {
            linked = fn_80201C24(entry);
            color.value = lbl_8064F1C0;
            fn_80147E88(effect);
            fn_80148B18(effect, (u8 *)effect->resource);
            fn_80149220(effect, &color);
            flags = fn_801A74C0(alternate);
            if (flags & 0x4000) {
                effect->active = 1;
                effect->state = 1;
            }
            effect->type = 2;
            effect->enabled = 1;
            effect->resource->mode = 3;
            effect->resource->alternateMode = 2;
            if (flags & 0x10000) {
                effect->resource->mode = 0x1C;
                effect->resource->alternateMode = 0x1D;
                effect->enabled = 0;
            }
            if (linked != 0) {
                index = fn_80157AB8(linked);
                if (index != 0) {
                    color.value = fn_801D3974(index);
                    color.components[3] = 0x9C;
                    fn_80149220(effect, &color);
                }
            }
            effect->ready = 1;
            effect->owner = fn_80201B54(entry);
            fn_801E8328(0x11, (u32)effect);
        }
    }
    return 1;
}
