typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Segment {
    Vec3 start;
    Vec3 dir;
} Segment;

typedef struct Entry {
    s32 packed;
    s32 kind;
    s32 unused;
} Entry;

typedef struct ObjectInfo {
    u8 pad00[0x38];
    Vec3 pos;
    Vec3 target;
    float yaw;
    s32 layer;
    u8 pad58[0x74 - 0x58];
    s32 link;
} ObjectInfo;

typedef struct OwnerState {
    u8 pad00[0x1C];
    s32 value;
} OwnerState;

typedef struct OwnerData {
    ObjectInfo *info;
    u8 pad04[0x8C - 0x04];
    OwnerState *state;
} OwnerData;

extern const float lbl_8064F110;
extern const float lbl_8064F140;
extern const float lbl_8064F164;
extern const float lbl_8064F1E4;
extern const float lbl_8064F1E8;
extern Vec3 lbl_803251F0;

extern void fn_80047494(s32);
extern float fn_800490E8(float, float);
extern void *fn_8004918C(void);
extern void fn_8004948C(void *, void *, s32);
extern s32 fn_80049694(void *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128B8C(void *, Vec3 *);
extern void fn_80128C28(void *, void *, void *);
extern void fn_80128C44(void *, void *, void *);
extern void fn_801292E0(void *, s32 *, Entry **);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80129BA4(void *, float, float);
extern int fn_8012A1BC(void *, int);
extern int fn_8012A1FC(void *, int);
extern float fn_8012B7D0(void *, Vec3);
extern s32 fn_8015793C(void *);
extern void fn_80157C0C(void *, Vec3 *);
extern float fn_80179F20(float);
extern void *fn_801A717C(void);
extern void fn_801A7324(void *, void *);
extern void fn_801A7460(void *, s32);
extern void fn_801A74A8(void *, s32);
extern void fn_801A74D8(void *, s32);
extern void fn_801A7518(void *, s32);
extern void fn_801A7538(void *, s32);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern void fn_801A7560(void *, s32);
extern u32 fn_801A7570(void *);
extern void fn_801A7588(void *, s32);
extern void fn_801A7610(void *, Segment);
extern void fn_801A7678(void *, s32);
extern void *fn_801A7778(void *);
extern s32 fn_801A7780(void *);
extern s32 fn_801A77D4(void *);
extern void fn_8020123C(int, int, int, void *);
extern void *fn_80201814(s32);
extern int fn_80201B54(void *);
extern OwnerData *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern float fn_80211B08(Vec3 *);

static inline Vec3 get_position(void *resource)
{
    Vec3 result;
    fn_8011F114(&result, resource);
    return result;
}

static inline float get_height(void *resource, Vec3 *pos)
{
    return fn_8012B7D0(resource, *pos);
}

extern void fn_80036104(void);
extern void fn_80036198(void);
extern void fn_800C5258(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);

void fn_800C52B8(void *object)
{
    OwnerState *state;
    int start;
    int end;
    OwnerData *owner;
    void *resource;
    void *anim;
    int id;
    Segment seg;
    Vec3 pos;
    Vec3 linked_pos;
    Vec3 facing;
    Vec3 delta;
    Vec3 dir;
    Vec3 step;
    Vec3 dest;
    Vec3 res_pos;
    Entry *entries;
    s32 count;
    s32 offset;
    void *gfx;
    void *draw;
    ObjectInfo *owner_info;
    s32 first;
    ObjectInfo *info;
    s32 layer;
    s32 i;
    void *linked;
    void *model;
    s32 frame;
    void *linked_res;
    float len;
    float dist;
    float neg_dist;
    float height;
    float angle;
    s32 span;

    owner = fn_80201B8C(object);
    state = owner != 0 ? owner->state : 0;
    resource = fn_80201BC8(object);
    id = fn_80201B54(object);
    gfx = fn_8004918C();
    info = owner->info;
    fn_801A7570(gfx);
    linked = fn_80201814(info->link);
    pos = info->pos;
    layer = info->layer;
    if (linked == 0) {
        return;
    }

    fn_8004948C(object, gfx, 0);
    state->value = fn_80201B54(linked);
    if (fn_80049694(gfx) != 0 || (fn_801A7780(gfx) & 0x20)) {
        fn_801A7460(gfx, fn_801A77D4(gfx));
        fn_801A74D8(gfx, 0x2420);
        fn_801A7560(gfx, fn_801A7780(gfx));
        fn_801A74A8(gfx, state->value);
        fn_801A7678(gfx, layer);
        fn_8020123C(0x28, id, id, gfx);
        return;
    }

    linked_res = fn_80201BC8(linked);
    linked_pos = get_position(linked_res);
    owner_info = owner->info;
    anim = fn_801294DC(resource, 0x41, 0x100, 6);
    if (anim == 0) {
        return;
    }

    first = 1;
    height = get_height(resource, &linked_pos);
    end = fn_8012A1BC(resource, 0x41);
    start = fn_8012A1FC(resource, 0x41);
    res_pos = get_position(resource);
    model = fn_801A7778(gfx);
    fn_80157C0C(model, &facing);
    facing.z = lbl_8064F110;
    dist = fn_80211B08(&facing);

    draw = fn_801A717C();
    fn_801A7324(gfx, draw);
    fn_801A7550(draw, 0xC);
    fn_801A7558(draw, 0xC);
    fn_801A74D8(draw, 0x2000);
    fn_801A74A8(draw, state->value);
    fn_801A7678(draw, layer);
    fn_801A7588(draw, 1 << layer);
    fn_801A7538(draw, 1);
    fn_801A7518(draw, (u8)fn_8015793C(model));
    seg.dir.x = lbl_8064F110;
    seg.dir.y = lbl_8064F110;
    seg.dir.z = lbl_8064F164;
    seg.start = pos;
    fn_801A7610(draw, seg);

    fn_801292E0(resource, &count, &entries);
    neg_dist = -dist;
    for (i = 0, offset = 0; i < count; offset += sizeof(Entry), i++) {
        Entry *entry = (Entry *)((u8 *)entries + offset);
        if (entry->kind != 1) {
            continue;
        }
        frame = entry->packed >> 17;
        fn_801287C4(anim, fn_80036198, draw, frame);
        if (first == 0) {
            continue;
        }
        first = 0;
        fn_801287C4(anim, fn_80036104, draw, frame);
        if (dist > lbl_8064F140) {
            height = get_height(resource, &pos);
            angle = -(lbl_8064F1E4 + fn_800490E8(facing.y, facing.x));
            height = height + angle;
            fn_80211A6C(&pos, &res_pos, &delta);
            len = fn_80211B08(&delta);
            fn_80211AAC(&delta, &dir);
            fn_80211A90(&dir, &step, neg_dist);
            fn_80211A48(&pos, &step, &dest);
            owner_info->target = dest;
            owner_info->yaw = height;
            fn_80211A90(&dir, &lbl_803251F0,
                        (len - dist) / (float)((frame - (start + 1)) * 2 + 8));
            fn_80128B8C(resource, &lbl_803251F0);
        }
    }

    if (first == 0) {
        fn_801287C4(anim, fn_800C5258, draw, end - 2);
    }
    fn_80128C28(anim, fn_80204230, draw);
    fn_80128C44(anim, fn_802042A4, draw);
    fn_80201D2C(object, 0x1E);
    fn_80201D14(object, 1);
    fn_80129BA4(anim, fn_80179F20(height), lbl_8064F1E8);
    span = (end - start) * 2;
    if (span > 0 && span < 600) {
        fn_80047494(span);
    }
}
