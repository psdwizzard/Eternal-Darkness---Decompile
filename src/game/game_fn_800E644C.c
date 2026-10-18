typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct RuntimeState {
    u32 first;
    u32 second;
    Vec3 anchor;
    u32 owner;
    u8 active;
    u8 pending;
} RuntimeState;

typedef struct ActorData {
    u8 pad0[0x6C];
    RuntimeState *state;
    u8 pad70[0x1C];
    u8 *extra;
} ActorData;

typedef struct SoundParams {
    u8 data[0xC4];
} SoundParams;

extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern int fn_80200C38(void *);
extern void *fn_80201B3C(void);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern ActorData *fn_80201B8C(void *);
extern int fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201C48(int);
extern void *fn_80201814(int);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201DD8(int, int);
extern void fn_80201E78(Vec3 *, void *);
extern void fn_802006D4(int, int, int, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8020123C(int, int, int, int);
extern void fn_802045AC(void *, Vec3 *);
extern void fn_80204FDC(void *);
extern void PSVECSubtract(Vec3 *, Vec3 *, Vec3 *);
extern void fn_8011F114(Vec3 *, void *);
extern Vec3 *fn_8011F130(void *);
extern void fn_8011F778(void *, float);
extern void fn_8011FA8C(void *, int, int);
extern void fn_8011FADC(void *, u32);
extern u32 fn_8011FAEC(void *);
extern void fn_8011FB5C(void *, int);
extern Vec4 *fn_8011FE34(void *);
extern void fn_801294DC(void *, int, int, int);
extern void fn_8012B324(void *);
extern void fn_8012B344(void *);
extern void fn_8012B6FC(void *, Vec3 *, Vec3 *);
extern void fn_8012C62C(void *, int, Color *, Color *, Color *, int);
extern void fn_80149220(SoundParams *, u32 *);
extern u32 fn_80149D48(u32, int);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern u32 fn_80179004(Vec3 *, Vec3 *);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_8017A470(Vec3 *, Vec3 *, Vec3 *, Vec4 *);
extern float fn_8017A5A8(const Vec4 *, const Vec4 *, float);
extern void fn_8017A7D4(const Vec4 *, const Vec4 *, float, Vec4 *);
extern void fn_801850CC(u32);
extern u32 fn_801A717C(void);
extern void fn_801A7228(u32);
extern void fn_801A7478(u32, SoundParams *);
extern u8 *fn_801A7480(u32);
extern void fn_801A74A0(u32, int);
extern void fn_801A74D8(u32, int);
extern void fn_801A7518(u32, int);
extern void fn_801A7538(u32, int);
extern void fn_801A7588(u32, int);
extern u32 fn_801AC8AC(int, int, int, Vec3 *);
extern int fn_801AC908(u32, Vec3 *, int);
extern void fn_801AC980(u32, int);
extern void fn_801AC9F4(int, int, Vec3 *, int);
extern u32 fn_801D3974(int);
extern void fn_801E8328(int, void *);
extern void fn_800C3ADC(void *, u32);
extern void fn_800C91F8(void *, void *);
extern void fn_800C92E8(void *);
extern int fn_800C9450(void *, int);
extern void fn_800CA2C8(void *);
extern void fn_800CC4DC(void *);
extern int fn_800E6E04(void *, void *);
extern void *memset(void *, int, u32);

extern Vec3 lbl_80239B24;
extern Vec3 lbl_80239B30;
extern SoundParams lbl_80325CF0;
extern u32 lbl_8064D5A8;
extern const float lbl_8064F780;
extern Color lbl_8064F784;
extern Color lbl_8064F788;
extern const float lbl_8064F78C;
extern const float lbl_8064F790;
extern const float lbl_8064F794;
extern const float lbl_8064F798;
extern const float lbl_8064F79C;
extern const float lbl_8064F7A0;
extern const float lbl_8064F7A4;
extern const float lbl_8064F7A8;
extern const float lbl_8064F7AC;
extern const float lbl_8064F7B0;
extern Color lbl_80651B58;

int fn_800E644C(void *context, int phase, void *message, int *result)
{
    int flag;
    int kind;
    void *targetObject;
    void *target;
    RuntimeState *state;
    ActorData *data;
    u8 *extra;
    int link;
    void *object;
    int id;
    int partner;
    Vec3 position;
    Vec3 targetPosition;
    Vec3 start;
    Vec3 targetPos;
    Vec3 lower;
    Vec3 lowerWorld;
    Vec3 offset;
    Vec3 upper;
    Vec4 rotation;
    Vec4 combined;
    Vec4 final;
    Vec3 origin;
    u32 info;
    Color a;
    Color b;
    Color c;

    kind = fn_80200C10(message);
    targetObject = 0;
    target = fn_80201B3C();
    object = fn_80201BC8(context);
    data = fn_80201B8C(context);
    extra = data->extra;
    link = fn_80201B94(context);
    id = fn_80201B54(context);
    fn_8011F114(&position, object);
    state = data->state;
    if ((partner = fn_80201B44()) != 0) {
        targetObject = fn_80201BC8(fn_80201814(partner));
        fn_8011F114(&targetPosition, targetObject);
        fn_80201DD8(link, partner);
    }

    if (kind == 3) {
        fn_800CC4DC(context);
        fn_800C92E8(context);
        if (targetObject != (void *)0) {
            fn_800C91F8(object, targetObject);
        }
        if (!(lbl_8064D5A8 & 3) && fn_800E6E04(context, target) != 0) {
            fn_8020104C(0x39, id, id, 1, lbl_8064F78C);
        }
        if (!(state->pending & 2)) {
            float limit = lbl_8064F790;
            u32 distance = fn_80179004(&targetPosition, &state->anchor);
            if (distance < 0xC1C) {
                if (distance < 0x4B0) {
                    limit = lbl_8064F780;
                } else if (distance < 0x8FC) {
                    limit -= lbl_8064F794;
                } else {
                    limit -= lbl_8064F798;
                }
            }
            if ((float)fn_80179004(&position, &state->anchor) / (float)distance > limit) {
                state->pending |= 2;
            }
        }
        if (fn_801AC908(state->owner, &position, 0xFF) == 0) {
            state->owner = fn_801AC8AC(0x23E, 0x6E, 0x1388, &position);
        }
        if (!(state->pending & 1) && state->first != 0) {
            u8 *sound = fn_801A7480(state->first);
            if (sound != 0 && *(u32 *)(sound + 0xC0) != 0) {
                u32 voice = fn_80149D48(*(u32 *)(sound + 0xC0), 0);
                if (voice != 0) {
                    state->second = voice;
                    state->pending |= 1;
                }
            }
        }
    }

    if (phase == 0) {
        if (kind == 1) {
            void *self = fn_80201B3C();
            fn_80201E78(&origin, self);
            start = origin;
            state->active = 1;
            state->owner = 0;
            state->pending = 0;
            state->first = 0;
            state->second = 0;
            fn_8011FB5C(object, 0x20000);
            fn_8011F778(object, lbl_8064F79C);
            fn_8011FA8C(object, 0, 0x802);
            fn_801294DC(object, 2, 0x121, 1);
            state->first = fn_801A717C();
            fn_801A74A0(state->first, id);
            fn_801A7538(state->first, 5);
            fn_801A7518(state->first, 5);
            fn_801A7588(state->first, 0x8000);
            memset(&lbl_80325CF0, 0, sizeof(SoundParams));
            fn_801A74D8(state->first, 0x4000);
            fn_801A7478(state->first, &lbl_80325CF0);
            fn_800C3ADC(object, state->first);
            info = fn_801D3974(1);
            ((u8 *)&info)[3] = 0xBE;
            fn_80149220(&lbl_80325CF0, &info);
            fn_801AC9F4(0x2B7, 0x7F, &start, 2);
            fn_80201D2C(context, 3);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 0x65) {
            fn_80200C38(message);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x3B) {
            fn_80200C38(message);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xEF) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x27) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        }
        if (kind == 8) {
            fn_8012B324(object);
            fn_8020104C(0x39, id, id, 1, lbl_8064F7A0);
            return 1;
        }
        if (kind == 0x82) {
            return 1;
        }
        if (kind == 0xED) {
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(message), fn_80200C28(message), fn_80200C38(message));
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 0xB) {
            fn_8012B344(object);
            fn_8020104C(0x39, id, id, 1, lbl_8064F7A0);
            if (result != 0) {
                *result = 0;
            }
            return 1;
        }
        if (kind == 0x35) {
            return 1;
        }
        if (kind == 0x39) {
            flag = fn_80200C38(message) & 1;
            fn_801AC980(state->owner, 1);
            state->owner = 0;
            if (*(int *)(extra + 0xBC) != 0) {
                fn_8020123C(0x91, id, *(int *)(extra + 0xBC), 0);
            }
            if (flag != 0) {
                fn_800C9450(context, 0xD2);
            }
            fn_8012B324(object);
            if (state->second != 0) {
                fn_801850CC(state->second);
                state->second = 0;
                fn_801A7478(state->first, 0);
            }
            fn_801A7228(state->first);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
        if (kind == 0xD5) {
            *(int *)(extra + 0xBC) = fn_80200C38(message);
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 3) {
            int linked;
            if ((linked = fn_80201C48(link)) != 0 && fn_80201814(linked) != 0) {
                fn_80201D2C(context, 3);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (phase == 3) {
        if (kind == 1) {
            fn_801294DC(object, 2, 0x121, 1);
            return 1;
        }
        if (kind == 3) {
            int linked;
            lower = lbl_80239B24;
            upper = lbl_80239B30;
            if ((linked = fn_80201C48(link)) != 0 && fn_80201814(linked) != 0) {
                Vec4 *orientation;
                Vec3 *origin2;
                u32 distance;
                u32 anchorDistance;
                float blend;
                fn_802045AC(context, &targetPos);
                distance = fn_80178E94(&position, &targetPos);
                if (distance <= 100 && fn_800C9450(context, 0xD2) != 0) {
                    fn_8020123C(0x39, id, id, 0);
                }
                anchorDistance = fn_80179004(&targetPos, &state->anchor);
                if ((distance > 0x28A || anchorDistance < 0x8FC) && (state->pending & 2)) {
                    blend = lbl_8064F7A4;
                    fn_8012B6FC(object, &lower, &lowerWorld);
                    fn_8012B6FC(object, &upper, &upper);
                    origin2 = fn_8011F130(object);
                    PSVECSubtract(&targetPos, origin2, &offset);
                    fn_8017A470(&lowerWorld, &offset, &upper, &rotation);
                    orientation = fn_8011FE34(object);
                    fn_8017A34C(&rotation, orientation, &combined);
                    if (anchorDistance < 0xC1C) {
                        if (anchorDistance < 0x4B0) {
                            blend += lbl_8064F7A8;
                        } else if (anchorDistance < 0x8FC) {
                            blend += lbl_8064F7AC;
                        } else {
                            blend += lbl_8064F7B0;
                        }
                    }
                    fn_8017A7D4(orientation, &combined, fn_8017A5A8(orientation, &combined, blend), &final);
                    *orientation = final;
                }
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x66) {
            fn_8012B344(object);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (phase == 8) {
        if (kind == 1) {
            if (object != 0) {
                u32 flags = fn_8011FAEC(object);
                fn_8011FADC(object, flags & ~0xC0);
            }
            fn_800CA2C8(context);
            fn_80204FDC(context);
            return 1;
        }
        if (kind == 0x3D) {
            fn_8020123C(0x39, id, id, 0);
            return 1;
        }
        if (kind == 0x11) {
            c = lbl_80651B58;
            b = lbl_8064F788;
            a = lbl_8064F784;
            fn_8012C62C(object, 0xF, &a, &b, &c, 0x14);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(id, id, 8, 0x11, 0);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
