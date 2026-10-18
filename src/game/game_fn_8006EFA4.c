typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Config {
    u8 pad_00[4];
    int value;
    u8 pad_08[4];
    u8 object_count;
    u8 slot_count;
    u8 cleared;
    u8 pad_0F;
    int arg2;
    int arg3;
    u8 pad_18[0x5C];
    void *slots[16];
    int expected[16];
} Config;

typedef struct State {
    u8 pad_00[4];
    u8 done;
    u8 flags[0x43];
    Config config;
} State;

typedef struct Context {
    int kind;
    u8 pad_04[0x14];
    u32 flags;
} Context;

typedef struct Owner {
    u8 pad_00[0x38];
    void *resource;
    u8 pad_3C[0x88];
    State *state;
} Owner;

typedef struct Actor {
    u8 pad_00[0x9E];
    u8 type;
    u8 subtype;
} Actor;

extern void fn_80036060(void *object, u16 flags);
extern int fn_800360B0(void *object, u16 *flags);
extern int fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, int flags);
extern int fn_800467F0(int id, int mode);
extern void fn_80046F28(void *resource, int id);
extern void fn_80046FC4(int id, int mode);
extern void fn_80047700(void *object, int mode);
extern Context *fn_8006ED98(Owner *owner);
extern void *fn_8007091C(int kind, int subtype, int count, int owner,
                         const Vec3 *position, float scale);
extern int fn_80071620(int mode, int id, int event, int *outX, int *outType,
                       int *outY, u8 *flags);
extern void fn_800720C8(void *object);
extern int fn_80072618(Vec3 *base, Vec3 *out, int range, int mode);
extern void fn_800C1B50(int id, int a, int b, float c, float d);
extern u8 rand(void);
extern int fn_8011EB1C(void);
extern void fn_8011F114(Vec3 *pos, void *object);
extern void fn_8011FA8C(void *object, int a, int b);
extern void fn_8011FB54(void *object, int value);
extern int fn_801207F0(void *object);
extern int fn_80128328(void);
extern void fn_8012B750(void *object);
extern void fn_8012B7A0(void *object, float value);
extern float fn_8012B7D0(void *object, Vec3 pos);
extern void fn_8013B83C(void *object);
extern void fn_80157BA0(void *object, int mode);
extern void fn_8017A12C(float *out, float a, float b);
extern void *fn_80201814(void *resource);
extern int fn_80201AE4(void);
extern int fn_80201B4C(void *object);
extern int fn_80201B54(void *object);
extern int fn_80201B5C(void *object);
extern Actor *fn_80201B8C(void *object);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *object);
extern void *fn_80201BC8(void *object);
extern void *fn_80201C24(void *object);
extern void fn_80201CE8(void *object, int flags, int mode);
extern int fn_80201EB8(void *object);
extern void *memset(void *dest, int value, unsigned int size);

extern void *lbl_803127F8[32];
extern const Vec3 lbl_802390E0;
extern void *lbl_8064C4E4;
extern int lbl_8064D18C;
extern const float lbl_8064E7FC;
extern const float lbl_8064E824;
extern const float lbl_8064E828;
extern const float lbl_8064E82C;
extern const float lbl_8064E830;

/* Declaration order mirrors the original register allocation (first declared
 * gets the highest saved register); `event` is a differently-typed copy of
 * `kind` so MWCC keeps it in its own register. */
void fn_8006EFA4(Owner *owner, int id, int arg2, int arg3)
{
    int i;
    Actor *actor;
    int max;
    void *runtime;
    void **list;
    State *state;
    void *object;
    Config *config;
    int kind;
    int found;
    int spawned;
    int special;
    u32 random;
    u32 flags;
    int range;
    u32 event;
    void *resource;
    Context *context;
    int x;
    int type;
    int y;
    int result;
    float scale;
    float out;
    Vec3 pos;
    Vec3 spawnPos;
    u16 bits;

    list = lbl_803127F8;
    object = fn_80201B9C();
    state = owner->state;
    config = &state->config;
    context = fn_8006ED98(owner);
    scale = lbl_8064E7FC;
    found = 0;
    spawned = 0;
    special = 0;
    random = 0;
    range = 200;
    memset(lbl_803127F8, 0, 0x80);
    flags = context->flags;
    kind = context->kind;
    resource = fn_80201814(owner->resource);
    if (flags & 0x10) {
        while (object != 0 && found < 32) {
            int owner_id = fn_80201EB8(object);
            if (owner_id == id) {
                int category = fn_80201B4C(object);
                void *target = fn_80201BC8(object);
                actor = fn_80201B8C(object);
                if (fn_80201B5C(object) != 0x45) {
                    switch (category) {
                    case 1:
                        if (actor != 0 && actor->type == 2) {
                            switch (actor->subtype) {
                            case 0x1F:
                            case 0x20:
                            case 0x21:
                            case 0x23:
                            case 0x24:
                            case 0x28:
                                break;
                            case 0x22:
                            default:
                                fn_8011FB54(target, 10000);
                                list[found] = object;
                                found++;
                                break;
                            }
                        }
                        break;
                    case 2:
                        if (actor != 0 && actor->type == 4) {
                            fn_800720C8(object);
                            fn_8011FB54(target, 10000);
                            list[found] = object;
                            found++;
                        }
                        break;
                    }
                }
            }
            object = fn_80201BC0(object);
        }
    }
    if (resource != 0) {
        fn_80046F28(resource, id);
        if ((int)owner->resource == fn_80201AE4()) {
            fn_80046FC4(id, 0);
        }
    }
    if (flags & 4) {
        pos = lbl_802390E0;
        if (resource != 0) {
            fn_8011F114(&pos, fn_80201BC8(resource));
        }
        switch (kind) {
        case 9:
            max = 16;
            special = 1;
            switch (id) {
            case 0x1B:
            case 0x45:
            case 0x7B:
            case 0xF5:
            case 0xFF:
                range = 500;
                break;
            }
            break;
        case 0x15:
            range = 500;
            max = 5;
            random = 1;
            break;
        default:
            max = 5;
            break;
        }
        if (flags & 0x2000) {
            result = fn_800467F0(id, 1);
            if (result >= 0 && result < 5) {
                max = 5 - result;
            } else if (result >= 5) {
                max = 0;
            }
        }
        event = kind;
        for (i = 0; i < max; i++) {
            int ok;
            int mode;

            ok = 1;
            if ((i > 0 && lbl_8064C4E4 != 0 && fn_801207F0(lbl_8064C4E4) == 0) ||
                fn_80128328() == 0) {
                ok = 0;
            }
            mode = fn_80071620(i, lbl_8064D18C, event, &x, &type, &y, &state->flags[0]);
            if (ok != 0 && fn_80072618(&pos, &spawnPos, range, 1) != 0) {
                if (random != 0) {
                    scale = lbl_8064E824 * (rand() + 1);
                }
                config->slots[i] = fn_8007091C(x, y, type, id, &spawnPos, scale);
                if (config->slots[i] != 0) {
                    runtime = fn_80201BC8(config->slots[i]);
                    if (runtime != 0) {
                        if (fn_8011EB1C() == 2) {
                            fn_8013B83C(runtime);
                            fn_80047700(config->slots[i], 2);
                        }
                        if (random == 0) {
                            float angle;
                            fn_8012B750(runtime);
                            angle = fn_8012B7D0(runtime, pos);
                            fn_8017A12C(&out, lbl_8064E7FC, angle);
                            fn_8012B7A0(runtime, out);
                        }
                    }
                    config->expected[i] = fn_80201B54(config->slots[i]);
                    spawned++;
                    if (mode != 0) {
                        bits = 0;
                        if (fn_800360B0(config->slots[i], &bits) != 0) {
                            fn_80036060(config->slots[i], bits | 0x83);
                        }
                    }
                    if (flags & 0x4000) {
                        fn_800C1B50(config->expected[i], 15, 0, lbl_8064E828, lbl_8064E82C);
                    } else if (flags & 0x8000) {
                        fn_800C1B50(config->expected[i], 15, 0, lbl_8064E830, lbl_8064E828);
                    }
                    if (special != 0) {
                        fn_8011FA8C(fn_80201BC8(config->slots[i]), 0, 0x4000);
                        if (kind == 9) {
                            void *ai = fn_80201C24(config->slots[i]);
                            if (ai != 0) {
                                fn_80157BA0(ai, 0);
                            }
                            fn_80201CE8(config->slots[i], 0x1000000, 0);
                        }
                    } else {
                        fn_80036DA4(config->slots[i], fn_80036D5C(config->slots[i]) | 0x1000);
                    }
                }
            }
        }
        if (kind == 0x15 && spawned > 0) {
            state->done = 1;
        }
    }
    config->cleared = 0;
    config->value = id;
    config->arg2 = arg2;
    config->arg3 = arg3;
    config->object_count = found;
    config->slot_count = spawned;
}
