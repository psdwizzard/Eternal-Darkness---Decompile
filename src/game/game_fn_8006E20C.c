typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union Color {
    struct { u8 r, g, b, a; } channels;
    u32 packed;
} Color;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Effect {
    u8 pad00[6];
    u16 value06;
    u16 value08;
    u8 pad0A[0x1E];
    u8 value28;
    u8 pad29[0x67];
    void *(*callback)(void *, void *, void *);
    u8 *child;
    Vec3 position;
    u16 rotation[3];
    u8 enabled;
} Effect;

typedef struct State {
    u8 pad00[0x15C];
    Effect *effect;
} State;

typedef struct Owner {
    u8 pad00[0xC4];
    State *state;
} Owner;

typedef struct Object {
    u8 pad00[0x18];
    void *value18;
} Object;

extern void fn_8018F76C(Effect *);
extern void fn_8018F808(u32 *, const u32 *, const u32 *);
extern void *fn_8018F864(void *, void *, void *);
extern void *memcpy(void *, const void *, unsigned long);
extern Object *fn_80147EC4(Effect *);
extern void fn_801568B8(Object *, void *);
extern void fn_80180AC8(u8 *, u8);
extern int fn_801A98F4(int, void *);
extern void fn_800AF2D4(void);
extern int fn_800AE380(u16, u32, void *, u16, u16, u16, u8, u16);
extern void fn_800AE3FC(u16, u32, void *, u16, u16, u16, u8, u16);
extern void *fn_8006ED98(Owner *);
extern void fn_801FA748(int, Vec3 *);
extern const float lbl_8064E810, lbl_8064E814, lbl_8064E818;

int fn_8006E20C(Owner *owner)
{
    Vec3 position;
    Color firstColor = {{230, 230, 255, 254}};
    Color secondColor = {{230, 230, 255, 254}};
    Vec3 direction = {0.0f, 0.0f, 1.0f};
    u16 rotation[3] = {0, 0, 0};
    Effect *effect;
    Object *object;
    int *kind;

    position.x = lbl_8064E810;
    position.y = lbl_8064E814;
    position.z = lbl_8064E818;
    effect = owner->state->effect;
    fn_8018F76C(effect);
    fn_8018F808((u32 *)effect, &firstColor.packed, &secondColor.packed);
    effect->callback = fn_8018F864;
    effect->position = position;
    memcpy(effect->rotation, rotation, sizeof(rotation));
    effect->child = 0;
    effect->enabled = 1;
    effect->value28 = 0;
    effect->value08 = 20;
    effect->value06 = effect->value08 + 255;
    object = fn_80147EC4(effect);
    if (object != 0) {
        fn_801568B8(object, 0);
        if (effect->child != 0) {
            fn_80180AC8(effect->child, 1);
        }
        fn_801A98F4(0x218, (void *)100);
        fn_800AF2D4();
        if (fn_800AE380(0xFFFF, 3, 0, 2, 360, 2, 0, 0) == 0) {
            fn_800AE3FC(0xFFFF, 3, 0, 2, 360, 2, 0, 0);
        }
    }
    kind = fn_8006ED98(owner);
    if (kind != 0 && *kind != 24 && *kind != 31) {
        fn_801FA748(2, &direction);
    }
    return 1;
}
