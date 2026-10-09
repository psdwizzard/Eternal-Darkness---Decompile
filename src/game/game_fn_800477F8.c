typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ResourceKey {
    u32 word;
    u16 half;
} ResourceKey;

typedef struct EffectDesc {
    u8 kind;
    u8 width;
    u8 alpha;
    signed char mode;
    u8 pad04[2];
    u16 count;
    u16 height;
    u8 pad0A[0x0A];
    u16 lifetime;
    u16 fade;
    u8 color[4];
    u8 pad1C;
    u8 flags;
    u8 pad1E[2];
    u8 variant;
    u8 pad21;
    u8 enabled;
    u8 owner;
    u8 pad24[0x6C];
} EffectDesc;

typedef struct SpawnPoint {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[0x0A];
    int id;
    u8 pad14[4];
} SpawnPoint;

typedef struct Room {
    u8 pad000[0xB8];
    u16 spawnCount;
    u8 pad0BA[2];
    SpawnPoint *spawns;
    u8 pad0C0[0x8142 - 0xC0];
    signed char loaded;
    signed char active;
} Room;

extern Color lbl_8064E378;
extern u32 lbl_8064E37C;
extern u16 lbl_8064E380;
extern int lbl_8064D18C;
extern void *lbl_8064C4E0;

extern u16 fn_80050730(int type, int mode, u8 *out_level, u8 *out_flags,
                       u16 *out_time, u32 *out_value);
extern void *fn_80201B3C(void);
extern Room *fn_8015C28C(int);
extern void *memset(void *, int, u32);
extern void fn_8019D560(EffectDesc *);
extern void fn_801A0450(void);
extern int fn_8018F0A0(void);
extern void *fn_80152F90(Vec3 *, void *, u8 *, u8);
extern void fn_80154F74(SpawnPoint *, u16, u16, int, int);
extern void *fn_80201C2C(void *);
extern void fn_80047D90(void);
extern void *fn_80201B9C(void);
extern int fn_80201EB8(void *);
extern void *fn_80201BC8(void *);
extern int fn_8011EB04(void);
extern int fn_80047CB4(void);
extern int fn_80047C2C(void *);
extern int fn_80036E50(void *);
extern void *fn_80204A94(void *, void *);
extern void fn_801E79A0(void *, int);
extern int fn_80047D78(void);
extern void fn_80047DF8(void *, int, int);
extern void *fn_80201BC0(void *);

void fn_800477F8(int skipSpawns, int owner)
{
    int z;
    u8 level;
    u8 flags;
    u16 time;
    Color color;
    ResourceKey key;
    Vec3 pos;
    EffectDesc effect;
    u16 type;
    SpawnPoint *spawn;
    u16 count;
    void *group;
    void *player;
    SpawnPoint *spawns;
    Room *room;
    int i;
    void *object;
    void *runtime;
    int result;
    void *member;

    type = fn_80050730(0x50, 0, &level, &flags, &time, 0);
    group = 0;
    player = fn_80201B3C();
    room = fn_8015C28C(2);
    if (room->active != 0 && room->loaded != 0) {
        count = room->spawnCount;
        if (count != 0 && skipSpawns == 0) {
            spawns = room->spawns;
            color = lbl_8064E378;
            memset(&effect, 0, sizeof(effect));
            fn_8019D560(&effect);
            effect.kind = 0x10;
            effect.width = 0x10;
            effect.count = 0xFFFF;
            effect.height = 0x18;
            effect.mode = -2;
            effect.alpha = color.a;
            effect.lifetime = 0xC;
            effect.color[0] = color.r;
            effect.color[1] = color.g;
            effect.color[2] = color.b;
            effect.color[3] = color.a;
            effect.variant = 5;
            effect.enabled = 0;
            effect.flags = 0x40;
            effect.owner = owner;
            fn_801A0450();
            spawn = spawns;
            for (i = 0; i < count; i++) {
                if (type == spawn->id) {
                    key.word = lbl_8064E37C;
                    key.half = lbl_8064E380;
                    pos.x = spawn->x;
                    pos.y = spawn->y;
                    pos.z = spawn->z;
                    if (fn_8018F0A0() != 0) {
                        z = spawn->z - 30;
                    } else {
                        z = spawn->z + 30;
                    }
                    pos.z = z;
                    fn_80152F90(&pos, &key, (u8 *)&effect, 0x20);
                }
                spawn++;
            }
            fn_80154F74(spawns, 0, count, type, owner);
        }
        if (player != 0) {
            group = fn_80201C2C(player);
        }
        fn_80047D90();
        for (object = fn_80201B9C(); object != 0; object = fn_80201BC0(object)) {
            result = fn_80201EB8(object);
            if (result == lbl_8064D18C && result != -1) {
                runtime = fn_80201BC8(object);
                if (runtime != 0) {
                    result = fn_8011EB04();
                    if (result == fn_80047CB4() && fn_80047C2C(runtime) != 0) {
                        result = fn_80036E50(player);
                        member = fn_80204A94(group, object);
                        if (result == 1 && member == 0) {
                            fn_801E79A0(lbl_8064C4E0, 0x467);
                            fn_80047DF8(runtime, fn_80047D78(), 1);
                        }
                        return;
                    }
                }
            }
        }
    }
}
