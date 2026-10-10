typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct ObjData {
    /* 0x00 */ char unk0[0x41];
    /* 0x41 */ u8 state;
} ObjData;

typedef struct Context {
    /* 0x00 */ char unk0[0xC];
    /* 0x0C */ ObjData *data;
} Context;

extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern void fn_801A7590(void *);
extern u32 fn_801A7570(void *);
extern void fn_801A7588(void *, u32);
extern int fn_800654F8(void *);
extern void *fn_80201814(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201B5C(void *);
extern Context *fn_80201B8C(void *);
extern u8 fn_80204508(void *, void *);
extern int fn_80079008(void *, void *);
extern Vec3 fn_8011F114(void *);
extern int fn_80128EAC(void *);
extern int fn_80128F40(void *);
extern f32 fn_8012B750(void *);
extern f32 fn_8012B7D0(void *, Vec3);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_8020104C(int, void *, void *, int, f32);

extern const Vec3 lbl_802391E8;
extern f32 lbl_8064E91C;
extern f32 lbl_8064E920;
extern f32 lbl_8064E924;

static inline Vec3 getZero(void) {
    Vec3 v = lbl_802391E8;
    return v;
}

int fn_80078D44(void *actor) {
    void *targetObj;
    void *targetEvent;
    void *ownerEvent;
    void *targetId;
    int result = 0;
    void *ownerObj;
    void *ownerId;
    Vec3 pos;
    int blocked;
    int inRange;
    int kind;
    int dist;
    int handled;
    f32 heading;
    f32 angle;
    f32 turn;
    f32 absAngle;

    ownerId = fn_801A7498(actor);
    targetId = fn_801A7490(actor);
    fn_801A7590(actor);
    ownerEvent = fn_80201814(ownerId);
    targetEvent = fn_80201814(targetId);
    targetObj = targetEvent != 0 ? fn_80201BC8(targetEvent) : 0;
    ownerObj = ownerEvent != 0 ? fn_80201BC8(ownerEvent) : 0;

    if ((ownerEvent != 0 ? fn_80201B5C(ownerEvent) : 0) != 0x19 && ownerEvent != 0 &&
        targetEvent != 0) {
        pos = ownerObj != 0 ? fn_8011F114(ownerObj) : getZero();

        if (ownerObj != 0) {
            blocked = fn_80204508(targetEvent, ownerEvent) == 0;
        } else {
            blocked = 0;
        }

        inRange = 0;
        kind = fn_80128EAC(targetObj);
        if (blocked == 0) {
            handled = fn_80079008(targetEvent, targetObj);
            dist = fn_80128F40(targetObj) >> 17;
            if (handled == 0) {
                if (kind == 0x7C) {
                    inRange = dist > 10;
                } else if (kind == 0x81) {
                    inRange = dist < 10;
                } else {
                    inRange = 1;
                }
            }
        }

        if (blocked != 0 || inRange != 0) {
            fn_801A7588(actor, 0x8000);
            result = fn_800654F8(actor);
        } else {
            if (fn_801A7570(actor) & 0x10018) {
                fn_8020104C(0x97, targetId, targetId, 0x13A, lbl_8064E91C);
            }
            result = 0x20;
        }

        heading = fn_8012B750(targetObj);
        turn = fn_8012B7D0(targetObj, pos);
        fn_8017A12C(&angle, heading, turn);
        absAngle = angle;
        if (absAngle < lbl_8064E920) {
            absAngle = -absAngle;
        }
        if (absAngle > lbl_8064E924) {
            ObjData *data = fn_80201B8C(targetEvent)->data;
            data->state = 0x2D;
        }
    }
    return result;
}
