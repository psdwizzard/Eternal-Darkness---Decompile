typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct SpawnInfo {
    s32 unk0;
    s32 unk4;
    u16 unk8;
} SpawnInfo;

typedef struct ColorEntry {
    u8 pad0[0x2];
    u8 unk2;
    u8 unk3;
    u8 pad4[0x4];
} ColorEntry;

typedef struct ColorTable {
    u8 pad0[0x28];
    ColorEntry entries[2];
} ColorTable;

typedef struct Spawner Spawner;
typedef struct SpawnerVtable {
    u8 pad0[0x40];
    void (*unk40)(Spawner *, void *, void *, void *, Vec3 *);
} SpawnerVtable;

struct Spawner {
    SpawnerVtable *vtable;
    u8 pad4[0x25C];
    u16 unk260;
};

typedef struct Manager {
    u8 pad0[0x64];
    Spawner *unk64;
    u8 pad68[0x28];
    s32 unk90;
} Manager;

typedef struct Ret4 { s32 unk0; } Ret4;

extern Manager *fn_80201B8C(void);
extern void *fn_80201B94(void *);
extern Vec3 fn_8011F114(void *);
extern u32 fn_80128EE4(void *);
extern void *fn_80201C48(void *);
extern void *fn_80201B54(void *);
extern u32 fn_80201814(void *);
extern void *fn_80201BC8(void);
extern s32 fn_800A2B04(void *, s32);
extern float fn_8012B7D0(void *, Vec3);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern s32 fn_8012AFC4(void *);
extern void *fn_80129A00(void *, s32, s32, float, float);
extern void *fn_801A717C(void);
extern void fn_80129190(void *, s32);
extern ColorTable *fn_80072354(s32);
extern void fn_801A7460(void *, s32);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern void fn_801A74C8(void *, s32);
extern void fn_801A7560(void *, s32);
extern void fn_801A7538(void *, u8);
extern void fn_801A7518(void *, u8);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern void fn_801A7598(void *, s32);
extern void fn_801A764C(void *, Vec3 *);
extern void fn_80128C28(void *, void *, void *);
extern void fn_80128C44(void *, void *, void *);
extern s32 fn_800A3240(Spawner *, s32, SpawnInfo *);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_800A2688();
extern void fn_80204230();
extern void fn_802042A4();

extern const SpawnInfo lbl_802396F0;
extern const float lbl_8064EE88;

s32 fn_800A2798(void *actor, void *object, s32 unused, s32 flags) {
    Manager *manager;
    void *owner;
    Vec3 objectPos;
    u32 objectFlags;
    void *target;
    void *group;
    s32 result;
    Spawner *spawner;
    Vec3 spawnPos;
    void *created;
    s32 kind;
    SpawnInfo info;
    float facing;
    float angle;
    Vec3 tmp;
    Vec3 tmp2;
    void *source;
    u32 ready;
    void *effect;
    ColorTable *colors;
    s32 alt;

    manager = fn_80201B8C();
    owner = fn_80201B94(actor);
    tmp = fn_8011F114(object);
    objectPos = tmp;
    objectFlags = fn_80128EE4(object);
    target = fn_80201C48(owner);
    group = fn_80201B54(actor);
    result = 0;
    if (!(objectFlags & 0x20)) {
        ready = fn_80201814(target);
        spawner = manager->unk64;
        if (ready != 0) {
            source = fn_80201BC8();
            tmp2 = fn_8011F114(source);
            spawnPos = tmp2;
            kind = fn_800A2B04(actor, 1);
            if (kind != -1) {
                info = lbl_802396F0;
                facing = fn_8012B7D0(object, spawnPos);
                fn_8017A12C(&angle, fn_8012B750(object), facing);
                if (fn_8012AFC4(object) == 0) {
                    created = fn_80129A00(object, kind, 0x100, facing, lbl_8064EE88);
                    if (created != 0) {
                        effect = fn_801A717C();
                        fn_80129190(object, 6);
                        colors = fn_80072354(manager->unk90);
                        fn_801A7460(effect, kind);
                        fn_801A74A0(effect, group);
                        fn_801A74A8(effect, target);
                        fn_801A74C8(effect, 1);
                        fn_801A7560(effect, 0x2000);
                        alt = kind != 4;
                        fn_801A7538(effect, colors->entries[alt].unk3);
                        fn_801A7518(effect, colors->entries[alt].unk2);
                        fn_801A7550(effect, 0xC);
                        fn_801A7558(effect, 7);
                        fn_801A7598(effect, 0x1130);
                        fn_801A764C(effect, &objectPos);
                        spawner->vtable->unk40(spawner, actor, created, effect, &spawnPos);
                        fn_80128C28(created, fn_80204230, effect);
                        fn_80128C44(created, fn_802042A4, effect);
                        flags &= fn_800A3240(spawner, kind, &info);
                        if (flags) {
                            spawner->unk260 = info.unk8;
                            spawner->unk260 = (spawner->unk260 << 1) & 0xFFFE;
                            fn_801287C4(created, fn_800A2688, actor, info.unk0);
                        }
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}
