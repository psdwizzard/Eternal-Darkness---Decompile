typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SpawnedEffect {
    u8 pad00[8];
    int resource;
    u8 pad0C[0x3C];
    int lifetime;
} SpawnedEffect;

typedef struct EffectSlot {
    u8 kind;
    u8 alpha;
    u8 intensity;
    s8 priority;
    u16 mode;
    u16 duration;
    u8 pad08[0xE];
    u8 variant;
    u8 strength;
    u8 pad18[4];
    int field1C;
    int field20;
    u8 pad24[0x10];
    float scale;
    u8 pad38[0x70];
    int owner;
    u8 padAC[0x14];
    SpawnedEffect *spawned;
} EffectSlot;

typedef struct ResourceIds {
    int ids[4];
} ResourceIds;

extern ResourceIds lbl_80239968;
extern EffectSlot lbl_80325540[4];
extern float lbl_8064F454;
extern int fn_80201B54(int *);
extern void *fn_80149E04(void);
extern void fn_80147E88(void *);
extern void fn_8014F4CC(u8 *, u8 *);
extern void fn_8019B13C(u8 *);
extern int fn_801E8328(u32, u32);
extern void fn_800D9064(void *, void *, void *);

int fn_800D96E0(void *unused, int *object)
{
    int owner;
    int resources[4];
    EffectSlot *slot;
    int *resource;
    int i;

    owner = fn_80201B54(object);
    resources[0] = lbl_80239968.ids[0];
    resources[1] = lbl_80239968.ids[1];
    resources[2] = lbl_80239968.ids[2];
    resources[3] = lbl_80239968.ids[3];
    resource = resources;
    for (i = 0; i < 4; i++, resource++) {
        slot = &lbl_80325540[i];
        slot->spawned = fn_80149E04();
        if (slot->spawned != 0) {
            fn_80147E88(slot);
            fn_8014F4CC((u8 *)slot, (u8 *)slot->spawned);
            slot->owner = owner;
            slot->spawned->resource = *resource;
            slot->spawned->lifetime = -1;
            fn_8019B13C((u8 *)slot);
            slot->alpha = 0xFF;
            slot->duration = 100;
            slot->mode = 0x33;
            slot->intensity = 0x82;
            slot->priority = -5;
            slot->field1C = 0;
            slot->field20 = 0;
            slot->variant = 5;
            slot->strength = 0x82;
            slot->scale = lbl_8064F454;
            fn_801E8328(0x11, (u32)slot);
        }
    }
    fn_800D9064(object, 0, (void *)1);
    return 1;
}
