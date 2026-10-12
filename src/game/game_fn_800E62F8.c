typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct SpawnRequest {
    Vec3 position;
    float facing;
    u32 kind;
    u32 subtype;
    u32 param18;
    u32 param1C;
    u32 param20;
    u32 param24;
    u32 count;
    u32 owner;
    u32 enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

typedef struct RuntimeState {
    u32 first, second;
    Vec3 anchor;
} RuntimeState;

typedef struct ActorData {
    u8 pad[0x6C];
    RuntimeState *state;
} ActorData;

extern void fn_80043F44(SpawnRequest *);
extern int fn_80034708(void *);
extern void *fn_80201BC8(void *);
extern int fn_801261F4(void *);
extern Vec4 *fn_8011FE34(void *);
extern void fn_8017A470(const Vec3 *, const Vec3 *, const Vec3 *, Vec4 *);
extern u32 fn_8011FABC(void *, u32, u32);
extern ActorData *fn_80201B8C(void *);
extern int fn_800CCA44(void *);
extern void fn_802015A4(void *);
extern void fn_801E8328(int, void *);
extern int fn_80201B54(void *);
extern Vec3 lbl_80239B18;
extern u32 lbl_8064D18C;
extern const float lbl_8064F780;

int fn_800E62F8(Vec3 *position, Vec3 *direction)
{
    SpawnRequest request;
    Vec3 axis = lbl_80239B18;
    void *actor;
    void *model;
    RuntimeState *state;

    fn_80043F44(&request);
    request.kind = 0x63;
    request.subtype = 0x9C;
    request.facing = lbl_8064F780;
    request.count = 0x59;
    request.position = *position;
    request.owner = lbl_8064D18C;
    request.flags = 0;
    actor = (void *)fn_80034708(&request);
    model = fn_80201BC8(actor);
    if (model != 0) {
        fn_801261F4(model);
        fn_8017A470(&axis, direction, 0, fn_8011FE34(model));
        fn_8011FABC(model, 0, 0x6000);
        fn_8011FABC(model, 0, 0x2000);
    }
    state = fn_80201B8C(actor)->state;
    state->anchor = *position;
    fn_800CCA44(actor);
    fn_802015A4(actor);
    fn_801E8328(1, actor);
    return fn_80201B54(actor);
}
