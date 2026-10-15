typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct QueryResult {
    u8 pad00[8];
    Vec3 position;
    Vec3 direction;
    u8 pad20[8];
} QueryResult;

typedef struct GrabState {
    int bone;
    int model;
    Vec3 target;
    Vec3 step;
    float angle;
    int flags;
    int partner;
    short frames;
} GrabState;

typedef struct ActorData {
    u8 pad0[0x80];
    GrabState *grab;
    u8 pad84[0x8];
    u8 *unk8C;
    u8 pad90[0x4];
    int unk94;
    u8 pad98[0x7];
    u8 unk9F;
} ActorData;

typedef struct AnimPair {
    int first;
    int second;
} AnimPair;

extern int fn_80200C10(void *);
extern int fn_80200C38(void *);
extern ActorData *fn_80201B8C(void *);
extern int fn_80201B54(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);
extern void *fn_80201814(int);
extern void *fn_80201B3C(void);
extern void *fn_80201C2C(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201E78(Vec3 *, void *);
extern void fn_802020B4(void *, int);
extern void *fn_80204C2C(void *);
extern void fn_80204E0C(void *, void *);
extern void fn_80205318(void *, int);
extern void fn_802006D4(int, int, int, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8020123C(int, int, int, int);
extern void fn_800C1B50(int, int, int, float, float);
extern void fn_8016B400(int, int, int);
extern void fn_801E8328(int, void *);
extern void fn_800E13EC(u8 *, int, int, int);
extern void fn_8011FE3C(void *, void *);
extern void *fn_80155DB4(void *);
extern void fn_80156F80(void *, void *);
extern int fn_801261F4(void *);
extern void fn_80045CE0(void *);
extern int fn_8011F6A4(void *, int, int, int, QueryResult *, int);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern float fn_80211B08(Vec3 *);
extern float fn_80211B44(Vec3 *, Vec3 *);
extern void fn_80211B64(Vec3 *, Vec3 *, Vec3 *);
extern void fn_801AAE68(int, int, int, Vec3 *, int, int, int, u16, float, int);
extern int fn_801D3A24(int, int);
extern void fn_8015295C(Vec3 *, Vec3 *, int, int, int);
extern int fn_80066D04(void *, int);
extern int fn_800E05BC(int, int);
extern void *fn_8011FE34(void *);
extern float fn_800490E8(float, float);
extern void fn_8017A244(Vec3 *, Vec4 *, float);
extern void fn_8017A34C(Vec4 *, Vec4 *, void *);
extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_8011F114(Vec3 *, void *);
extern float fn_8012B750(void *);
extern void fn_8012B7A0(void *, float);

extern Vec3 lbl_802399C8;
extern AnimPair lbl_80248CF8[];
extern AnimPair lbl_80248D28[];
extern int lbl_8064C58C;
extern int lbl_8064D18C;
extern int lbl_8064D1BC;
extern const float lbl_8064F5A0;
extern const float lbl_8064F5A4;
extern const float lbl_8064F5A8;
extern const float lbl_8064F5AC;
extern const double lbl_8064F5B0;
extern const float lbl_8064F5BC;
extern const float lbl_8064F5C0;
extern const float lbl_8064F5C4;
extern const float lbl_8064F5C8;

static inline Vec3 GetObjectPosition(void *object)
{
    Vec3 pos;
    fn_8011F114(&pos, object);
    return pos;
}

static inline Vec3 GetActorPosition(void *actor)
{
    Vec3 pos;
    fn_80201E78(&pos, actor);
    return pos;
}

int fn_800E0814(void *context, int phase, void *message, int *result)
{
    int kind;
    ActorData *data;
    int id;
    GrabState *grab;
    void *object;
    int handle;

    kind = fn_80200C10(message);
    data = fn_80201B8C(context);
    id = fn_80201B54(context);
    object = fn_80201BC8(context);
    grab = data->grab;
    handle = fn_80201EB8(context);

    if (phase == 0) {
        if (kind == 1) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            grab->model = 0x1F;
            grab->bone = 1;
            return 1;
        }
        if (kind == 240) {
            int next = fn_80200C38(message);
            fn_800C1B50(id, 15, 0, lbl_8064F5A0, lbl_8064F5A4);
            fn_80201D34(context, next);
            fn_80201D1C(context, 1);
            if (lbl_8064D1BC == 0)
                fn_8016B400(0x578, id, 0);
            lbl_8064C58C = 0;
            fn_802006D4(id, id, -1, 240, 0);
            if (result != 0)
                *result = 1;
            return 1;
        }
        if (kind == 8) {
            fn_80201D2C(context, 8);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 57) {
            fn_801E8328(2, context);
            return 1;
        }
        if (kind == 16) {
            int partner = fn_80200C38(message);
            void *other = fn_80201814(partner);
            void *otherObject = other != 0 ? fn_80201BC8(other) : 0;
            grab->partner = partner;
            if (other != 0 && otherObject != 0) {
                ActorData *otherData = fn_80201B8C(other);
                *(int *)(otherData->unk8C + 0x6C) = id;
                fn_800E13EC(otherObject, otherData->unk9F == 4, handle, 1);
                fn_8011FE3C(otherObject, object);
            }
            return 1;
        }
        if (kind == 213) {
            int partner = fn_80200C38(message);
            void *other = fn_80201814(partner);
            void *otherObject;
            if (other != 0)
                otherObject = fn_80201BC8(other);
            else
                otherObject = 0;
            grab->partner = partner;
            if (other != 0 && otherObject != 0) {
                ActorData *otherData;
                void *link;
                void *otherLink = fn_80155DB4(other);
                void *selfLink = fn_80155DB4(context);
                if (otherLink != 0 && selfLink != 0)
                    fn_80156F80(selfLink, otherLink);
                otherData = fn_80201B8C(other);
                link = fn_80201C2C(other);
                if (link == 0)
                    link = fn_80204C2C(other);
                *(int *)(otherData->unk8C + 0x6C) = id;
                fn_800E13EC(otherObject, otherData->unk9F == 4, handle, 0);
                fn_8011FE3C(otherObject, object);
                fn_80204E0C(context, link);
            }
            return 1;
        }
        if (kind == 62) {
            void *other = fn_80201814(grab->partner);
            void *otherObject = other != 0 ? fn_80201BC8(other) : 0;
            if (other != 0 && otherObject != 0) {
                fn_800E13EC(otherObject, fn_80201B8C(other)->unk9F == 4, lbl_8064D18C, 0);
                fn_801261F4(object);
                fn_80045CE0(object);
            }
            return 1;
        }
        if (kind == 241) {
            void *other = fn_80201814(grab->partner);
            void *otherObject;
            ActorData *otherData;
            int index;
            if (other != 0)
                otherObject = fn_80201BC8(other);
            else
                otherObject = 0;
            if (other != 0)
                otherData = fn_80201B8C(other);
            else
                otherData = 0;
            index = fn_80200C38(message);
            if (other != 0 && otherObject != 0 && otherData != 0) {
                QueryResult from;
                QueryResult to;
                if (fn_8011F6A4(otherObject, lbl_80248D28[index].first, lbl_80248CF8[index].first, -1, &from, 1) != -1 &&
                    fn_8011F6A4(otherObject, lbl_80248D28[index].second, lbl_80248CF8[index].second, -1, &to, 1) != -1) {
                    Vec3 pos;
                    Vec3 dir;
                    pos = from.position;
                    fn_80211A6C(&to.position, &from.position, &dir);
                    fn_80211AAC(&dir, &dir);
                    fn_80211A90(&dir, &dir, lbl_8064F5A8);
                    fn_80211A48(&to.position, &dir, &pos);
                    fn_801AAE68(0x289, 90, 0, &from.position, 2, 2, 0, lbl_8064D18C, lbl_8064F5AC, 0);
                    fn_8015295C(&to.position, &pos, fn_801D3A24(otherData->unk94, 0x31), 4, 2);
                }
            }
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 3) {
            void *other = fn_80201814(grab->partner);
            void *otherObject;
            ActorData *otherData;
            if (other != 0)
                otherObject = fn_80201BC8(other);
            else
                otherObject = 0;
            if (other != 0)
                otherData = fn_80201B8C(other);
            else
                otherData = 0;
            if (other != 0 && otherObject != 0 && otherData != 0) {
                QueryResult query;
                int flagA = fn_80066D04(other, 2);
                fn_800E05BC(fn_80066D04(other, 3) == 0, flagA == 0);
                if (fn_8011F6A4(otherObject, grab->model, grab->bone, -1, &query, 1) != -1) {
                    void *matrix = fn_8011FE34(object);
                    Vec4 spin;
                    Vec4 tilt;
                    Vec3 up;
                    Vec3 axis;
                    float length;
                    float dot;
                    float tiltAngle;
                    up = lbl_802399C8;
                    fn_80211B64(&up, &query.direction, &axis);
                    length = fn_80211B08(&axis);
                    fn_80211AAC(&axis, &axis);
                    dot = fn_80211B44(&up, &query.direction);
                    tiltAngle = fn_800490E8(length, dot);
                    grab->angle = grab->angle + lbl_8064F5B0;
                    if (grab->angle > 6.2831855f)
                        grab->angle -= 6.2831855f;
                    fn_8017A244(&up, &spin, grab->angle);
                    fn_8017A244(&axis, &tilt, tiltAngle);
                    fn_8017A34C(&tilt, &spin, matrix);
                    fn_8011F0E8(object, &query.position);
                }
            }
            return 1;
        }
    } else if (phase == 3) {
        if (kind == 1) {
            GetObjectPosition(object);
            if (grab->flags & 1) {
                fn_8020104C(240, id, id, 30, lbl_8064F5A4);
                fn_8020104C(22, id, id, 0, lbl_8064F5A4);
            } else {
                fn_8020104C(240, id, id, 30, lbl_8064F5BC);
                fn_8020104C(22, id, id, 0, lbl_8064F5C0);
            }
            return 1;
        }
        if (kind == 3) {
            Vec3 next = GetObjectPosition(object);
            float angle = fn_8012B750(object);
            fn_80211A48(&next, &grab->step, &next);
            fn_8011F0E8(object, &next);
            angle += lbl_8064F5C4;
            fn_8012B7A0(object, angle > 6.2831855f ? angle - 6.2831855f : angle);
            return 1;
        }
        if (kind == 22) {
            Vec3 effectPos = GetObjectPosition(object);
            fn_801AAE68(0x28B, 100, 0, &effectPos, 2, 2, 0, lbl_8064D18C, lbl_8064F5AC, 0);
            return 1;
        }
        if (kind == 240) {
            int next = fn_80200C38(message);
            fn_80201D34(context, next);
            fn_80201D1C(context, 1);
            fn_80205318(fn_80201B3C(), 1);
            fn_800C1B50(id, 15, 0, lbl_8064F5A0, lbl_8064F5A4);
            if (lbl_8064D1BC == 0)
                fn_8016B400(0x578, id, 0);
            lbl_8064C58C = 0;
            fn_802006D4(id, id, -1, 240, 0);
            if (result != 0)
                *result = 1;
            return 1;
        }
        if (kind == 61) {
            fn_8011F0E8(object, &grab->target);
            fn_8020123C(240, id, id, 30);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(id, id, -1, 6, 0);
            return 1;
        }
    } else if (phase == 8) {
        if (kind == 1) {
            void *other = fn_80201814(grab->partner);
            ActorData *otherData;
            if (other != 0)
                otherData = fn_80201B8C(other);
            else
                otherData = 0;
            if (other != 0 && otherData != 0)
                grab->target = GetActorPosition(other);
            else
                grab->target = GetActorPosition(context);
            fn_8016B400(0x578, id, 0);
            fn_802020B4(other, 0);
            fn_8020104C(6, id, id, 0, grab->frames);
            return 1;
        }
        if (kind == 3) {
            void *other = fn_80201814(grab->partner);
            void *otherObject;
            ActorData *otherData;
            QueryResult query;
            if (other != 0)
                otherObject = fn_80201BC8(other);
            else
                otherObject = 0;
            if (other != 0)
                otherData = fn_80201B8C(other);
            else
                otherData = 0;
            if (other != 0 && otherObject != 0 && otherData != 0 &&
                fn_8011F6A4(otherObject, grab->model, grab->bone, -1, &query, 1) != -1)
                fn_8011F0E8(object, &query.position);
            return 1;
        }
        if (kind == 6) {
            Vec3 start = GetActorPosition(context);
            grab->target.z = lbl_8064F5BC + start.z;
            grab->step.x = (grab->target.x - start.x) / lbl_8064F5BC;
            grab->step.y = (grab->target.y - start.y) / lbl_8064F5BC;
            grab->step.z = (grab->target.z - start.z) / lbl_8064F5BC;
            fn_8020104C(240, id, id, 30, lbl_8064F5C8);
            fn_8020104C(22, id, id, 0, lbl_8064F5C8);
            fn_80201D2C(context, 3);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 61) {
            grab->target.z = grab->target.z + lbl_8064F5BC;
            fn_8011F0E8(object, &grab->target);
            fn_8020123C(240, id, id, 30);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(id, id, -1, 6, 0);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
