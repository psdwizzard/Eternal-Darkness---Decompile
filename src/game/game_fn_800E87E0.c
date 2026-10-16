typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Matrix34 { float m[3][4]; } Matrix34;

typedef struct Segment {
    Vec3 start;
    Vec3 dir;
} Segment;

typedef struct JointQuery {
    int unk0;
    int unk4;
    Vec3 pos;
    Vec3 dir;
    int unk20;
    int unk24;
} JointQuery;

typedef struct SpawnInfo {
    Vec3 position;
    float scale;
    int field_10;
    int field_14;
    int field_18;
    u8 pad1C[0x28 - 0x1C];
    int field_28;
    void *field_2C;
    u8 pad30[0x34 - 0x30];
    s16 field_34;
    u8 pad36[0x38 - 0x36];
} SpawnInfo;

typedef struct HitInfo {
    u8 pad0[0xC];
    Vec3 pos;
    u8 pad18[0x24 - 0x18];
    u32 count;
    u8 pad28[0x30 - 0x28];
} HitInfo;

typedef struct ThrowState {
    void *owner;
    int unk4;
    u8 pad8[0x14 - 0x8];
    Vec3 start;
    u8 pad20[0x50 - 0x20];
    Vec4 rotation;
    Vec3 axis;
    Vec3 spin;
    Vec3 velocity;
    float unk84;
    Vec3 target;
    float distance;
    float speed;
    float spinRate;
    u8 padA0[0xA4 - 0xA0];
    int unkA4;
    float scale;
    u16 surface;
    u8 flags;
} ThrowState;

typedef struct ActorInfo {
    u8 pad0[0x84];
    ThrowState *state;
    u8 pad88[0x98 - 0x88];
    s16 kind;
} ActorInfo;

extern const Vec3 lbl_80239B50[3];
extern int lbl_8064D5A8;
extern u32 lbl_8064F808;
extern u32 lbl_8064F80C;
extern u32 lbl_8064F810;
extern const float lbl_8064F814;
extern float lbl_8064F818;
extern const float lbl_8064F81C;
extern const float lbl_8064F820;
extern Color lbl_80651B60;
extern Color lbl_80651B64;

extern void *fn_80034708(SpawnInfo *);
extern void fn_8003B630(void *, Vec3 *, Vec3 *, HitInfo *, u16 **);
extern void fn_80043F44(SpawnInfo *);
extern float fn_800490E8(float, float);
extern int fn_8006D344(void *, int, int);
extern void *fn_8006D444(void *);
extern int fn_80088528(void *, Vec3 *);
extern int fn_800C44C0(void *, void *, void *, Vec3 *, int *);
extern int fn_8011EB04(void *);
extern Vec3 *fn_8011F130(void *);
extern int fn_8011F598(void *, int, int, int, JointQuery *, int);
extern int fn_8011F6A4(void *, int, int, int, JointQuery *, int);
extern void fn_8011FA8C(void *, int, int);
extern void *fn_8011FB4C(void *);
extern void *fn_8011FE34(void *);
extern int fn_801261F4(void *);
extern void fn_80127DF8(void *, int, Matrix34 *);
extern void fn_8012A24C(void *, u16);
extern void fn_8012B690(void *, Vec3 *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8012B7A0(void *, float);
extern void *fn_8012C62C(void *, int, void *, void *, void *, int);
extern void fn_8012CCF0(void *, int, Vec3, Vec3, Vec3, int);
extern void fn_8012CDF0(void *, int, Vec4, int);
extern void fn_8012F604(void *, int, int, int);
extern int fn_8012FDA0(void *, int);
extern u32 fn_80157888(void *);
extern int fn_80157894(void *);
extern u8 fn_80157918(void *);
extern u8 fn_80157AB8(void *);
extern void fn_80157B3C(void *, u8);
extern void fn_80157B60(void *, u8);
extern void fn_80157B80(void *, int);
extern int fn_8015821C(void *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern int fn_80179004(const Vec3 *, const Vec3 *);
extern void fn_8017A244(Vec3 *, Vec4 *, float);
extern void fn_8017AD00(Matrix34 *, Vec3 *, Vec3 *);
extern u32 fn_801A7490(void *);
extern u32 fn_801A7498(void *);
extern void fn_801A74D8(void *, u32);
extern void fn_801A7610(void *, Segment);
extern void *fn_801A7778(void *);
extern u32 fn_801D3974(int);
extern void fn_801E8328(int, void *);
extern void fn_802015A4(void *);
extern void *fn_80201814(u32);
extern int fn_80201B54(void *);
extern ActorInfo *fn_80201B8C(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern void *fn_80201C24(void *);
extern void fn_80201DD0(void *, void *);
extern void *fn_80204844(void *, int);
extern void *fn_8020499C(void *);
extern void fn_802110A8(Matrix34 *, Matrix34 *);
extern void fn_802114E0(Matrix34 *, void *);
extern void fn_80211710(Matrix34 *, Vec3 *, Vec3 *);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern float fn_80211B08(Vec3 *);
extern float fn_80211B44(Vec3 *, Vec3 *);
extern void fn_80211B64(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211EFC(Vec4 *, Matrix34 *);

void *fn_800E87E0(void *owner, int flagged, int fromHand, int arg3, int arg4, int arg5, float scale)
{
    Vec3 *handPosition;
    Vec3 *position;
    void *model;
    void *handle;
    void *targetObject;
    u32 hits;
    void *targetModel;
    void *thrower;
    void *holder;
    const Vec3 *defaults;
    void *target;
    void *link;
    int tint;
    void *source;
    int value;
    void *object;
    ActorInfo *info;
    ThrowState *state;
    Matrix34 handMatrix;
    Matrix34 inverse;
    SpawnInfo spawn;
    JointQuery tip;
    JointQuery jointA;
    JointQuery jointB;
    JointQuery jointC;
    JointQuery jointD;
    JointQuery grip;
    HitInfo hit;
    Matrix34 rotation;
    Segment segment;
    Vec3 handPos;
    Vec3 local;
    Vec3 offset;
    Vec4 quat;
    Vec3 zero;
    Vec3 flip;
    Vec3 tipPos;
    Vec3 delta;
    Vec3 cross;
    Vec3 aim;
    Vec3 diff;
    Vec3 dir;
    Vec3 spin;
    Vec3 step;
    Vec3 end;
    Vec3 up;
    Vec3 forward;
    Vec3 normal;
    Vec4 orient;
    Vec3 travel;
    int hitObject;
    u16 *surface;
    Color colorA;
    Color colorB;
    void *handModel;
    int found;

    defaults = lbl_80239B50;
    zero = defaults[0];
    found = 0;
    surface = 0;
    colorA = lbl_80651B60;
    colorB = lbl_80651B64;
    thrower = fn_801A7778(owner);
    holder = fn_8020499C(thrower);
    handModel = fn_80201BC8(holder);
    info = fn_80201B8C(holder);
    handPosition = fn_8011F130(handModel);
    fn_80043F44(&spawn);
    if (fromHand != 0) {
        spawn.field_10 = info->kind;
        spawn.field_14 = fn_8011EB04(handModel);
        spawn.field_18 = fn_8015821C(thrower);
        spawn.scale = fn_8012B750(handModel);
    } else {
        spawn.field_10 = arg4;
        spawn.field_14 = arg3;
        spawn.field_18 = arg5;
        spawn.scale = lbl_8064F814;
    }
    spawn.field_28 = 0x53;
    spawn.position = *handPosition;
    spawn.field_2C = fn_8011FB4C(handModel);
    spawn.field_34 = 0;
    object = fn_80034708(&spawn);
    state = fn_80201B8C(object)->state;
    state->owner = owner;
    state->unkA4 = lbl_8064D5A8;
    state->unk4 = fn_80201B54(object);
    state->scale = scale;
    if (flagged != 0) {
        state->flags |= 2;
    }
    model = fn_80201BC8(object);
    if (model != 0) {
        fn_801261F4(model);
    }
    fn_8012B7A0(model, spawn.scale);
    target = fn_80201814(fn_801A7490(owner));
    fn_8011FA8C(model, 0x10100, 0);
    link = fn_80201C24(object);
    tint = fn_80157AB8(thrower);
    fn_80157B60(link, tint);
    fn_80157B3C(link, fn_80157918(thrower));
    fn_80157888(link);
    value = fn_80157894(thrower);
    fn_80157B80(link, value);
    if (tint != 0) {
        u32 c0;
        Color c1;
        Color c2;
        c2 = colorA;
        c1 = colorB;
        c0 = fn_801D3974(tint);
        fn_8012C62C(model, 0xF, &c0, &c1, &c2, 0x16);
    }
    if (fromHand != 0) {
        int jointIndex = fn_8012FDA0(handModel, 0xF);
        fn_80127DF8(handModel, jointIndex, &handMatrix);
        handPos.x = handMatrix.m[0][3];
        handPos.y = handMatrix.m[1][3];
        handPos.z = handMatrix.m[2][3];
        fn_80211EFC(&quat, &handMatrix);
        fn_8012B690(handModel, &handPos, &local);
        fn_80211A6C(&local, handPosition, &offset);
        position = fn_8011F130(model);
        fn_80211A48(position, &offset, position);
        fn_8012CDF0(model, 0xF, quat, 0);
        fn_8011F598(handModel, 1, 0xF, -1, &tip, 2);
        fn_80211A6C(&tip.pos, &handPos, &delta);
        fn_802110A8(&handMatrix, &inverse);
        fn_8017AD00(&inverse, &delta, &flip);
        flip.x = -flip.x;
        flip.y = -flip.y;
        flip.z = -flip.z;
        fn_8012CCF0(model, 0xF, flip, zero, zero, 0);
        fn_8012B690(handModel, &tip.pos, &tipPos);
        fn_80211A6C(&tipPos, &local, &offset);
        fn_80211A48(position, &offset, position);
    } else {
        up = defaults[1];
        forward = defaults[2];
        if (arg3 == 0xE9) {
            up = forward;
        }
        fn_801A74D8(owner, 0x10000);
        fn_8011F598(handModel, 4, 0xF, -1, &grip, 1);
        position = fn_8011F130(model);
        *position = grip.pos;
        fn_8011F598(model, 1, 0xF, -1, &tip, 2);
        fn_80211B64(&up, &grip.dir, &normal);
        {
            float len;
            float dot;
            len = fn_80211B08(&normal);
            fn_80211AAC(&normal, &normal);
            dot = fn_80211B44(&up, &grip.dir);
            fn_8017A244(&normal, &orient, fn_800490E8(len, dot));
        }
        fn_8012CDF0(model, 0xF, orient, 0);
        delta.x = -tip.pos.x;
        delta.y = -tip.pos.y;
        delta.z = -tip.pos.z;
        fn_8012CCF0(model, 0xF, delta, zero, zero, 0);
    }
    state->start = *position;
    fn_8011F598(handModel, 0x13, 0xF, -1, &jointA, 2);
    state->axis = jointA.dir;
    state->unk84 = lbl_8064F814;
    state->rotation = quat;
    fn_8011F6A4(handModel, 2, 0xF, -1, &jointB, 1);
    fn_8011F6A4(handModel, 3, 0xF, -1, &jointC, 1);
    fn_80211A6C(&jointB.pos, &jointC.pos, &diff);
    {
        float length;
        length = fn_80211B08(&diff);
        length *= lbl_8064F818;
        state->spinRate = length;
    }
    targetObject = fn_80201814(fn_801A7498(owner));
    targetModel = fn_80201BC8(targetObject);
    fn_800C44C0(targetObject, target, owner, &aim, &hitObject);
    fn_80211A6C(&aim, position, &state->velocity);
    if (fn_80211B08(&state->velocity) <= lbl_8064F81C) {
        fn_800C44C0(targetObject, 0, owner, &aim, &hitObject);
    }
    fn_80211AAC(&state->velocity, &state->velocity);
    fn_80211A90(&state->velocity, &state->velocity, state->scale);
    fn_8011F6A4(handModel, 3, 0xF, -1, &jointD, 2);
    fn_80211B64(&state->axis, &tip.dir, &cross);
    if (fn_80211B44(&cross, &jointD.dir) < lbl_8064F814) {
        state->axis.x = -state->axis.x;
        state->axis.y = -state->axis.y;
        state->axis.z = -state->axis.z;
    }
    source = fn_8011FE34(handModel);
    fn_802114E0(&rotation, source);
    fn_80211710(&rotation, &state->axis, &dir);
    fn_80211B64(&dir, &state->velocity, &spin);
    fn_80211AAC(&spin, &spin);
    fn_80211A90(&spin, &spin, state->spinRate);
    state->spin = spin;
    handle = fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
    if (fn_8006D344(handle, 0x80, 0) != 0 && fn_80088528(handle, &step) != 0) {
        found = 1;
    }
    if (found != 0) {
        state->target = step;
        state->distance = fn_80178E94(&state->start, &step);
        state->flags |= 0x20;
        state->speed = lbl_8064F814;
    } else {
        hits = fn_80179004(fn_8011F130(targetModel), position);
        travel = state->velocity;
        fn_80211AAC(&travel, &travel);
        fn_80211A90(&travel, &travel, lbl_8064F820 * hits);
        fn_80211A48(position, &travel, &end);
        fn_8003B630(object, &state->velocity, &end, &hit, &surface);
        state->target = hit.pos;
        state->distance = hit.count;
        state->surface = surface != 0 ? *surface : 0;
        state->speed = fn_80211B08(&travel);
    }
    if (surface != 0) {
        fn_8012A24C(model, *surface);
    }
    segment.start = *position;
    segment.dir = state->velocity;
    fn_801A7610(owner, segment);
    if (fromHand != 0) {
        u32 c0;
        u32 c1;
        u32 c2;
        c2 = lbl_8064F810;
        c1 = lbl_8064F80C;
        c0 = lbl_8064F808;
        fn_8012C62C(handModel, 0xF, &c0, &c1, &c2, 4);
        fn_8012F604(handModel, 0xF, 0, 0x1E);
    }
    fn_80201DD0(object, model);
    fn_802015A4(object);
    fn_801E8328(3, object);
    return object;
}
