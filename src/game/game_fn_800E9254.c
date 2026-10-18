typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct Matrix34 { float m[3][4]; } Matrix34;
typedef struct JointQuery {
    int field0, field4;
    Vec3 pos, dir;
    int field20, field24, field28, field2C;
} JointQuery;
typedef struct ImpactEffect {
    u8 pad[0x2E];
    u16 flags;
} ImpactEffect;

/* State shared by the throw setup, flight, and attachment handlers. */
typedef struct ThrowState {
    void *owner;
    int handle;
    void *hitModel;
    int hitHandle;
    void *resource;
    Vec3 start;
    Matrix34 attachment;
    Vec4 rotation;
    Vec3 axis, spin, velocity;
    float angle;
    Vec3 target;
    float distance, travelled, spinRate;
    int hitJoint, fieldA4;
    float step;
    u16 surface;
    u8 flags, soundTimer;
    ImpactEffect impactEffect;
} ThrowState;
typedef struct ActorInfo { u8 pad[0x84]; ThrowState *state; } ActorInfo;
typedef struct EffectInfo { u8 pad[0xC0]; void *resource; } EffectInfo;

extern Vec3 lbl_80239B74;
extern u8 lbl_80325E58[0xC4];
extern float lbl_8064F830, lbl_8064F834, lbl_8064F838, lbl_8064F83C;
extern int fn_80200C10(void *);
extern ActorInfo *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(void *);
extern Vec3 *fn_8011F130(void *);
extern u32 fn_801A7480(void *);
extern void *fn_80149D48(void *, int);
extern int fn_8011EB04(void *);
extern u16 fn_80050B08(int, int, int, u8 *, signed char *, u16 *, int *);
extern int fn_801AC9F4(u16, u8, Vec3 *, u8);
extern void *memset(void *, int, unsigned long);
extern void *fn_80201C24(void *);
extern void fn_801A7680(void *, u32);
extern void fn_801A7934(void *);
extern void fn_801A78EC(void *);
extern void fn_801A7910(void *);
extern u32 fn_801A7570(void *);
extern void fn_801A74D8(void *, u32);
extern u32 fn_801A7560(void *, u32);
extern void fn_801A7478(void *, u32);
extern void fn_800C3ADC(void *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, u8);
extern void fn_800E9DE0(ThrowState *);
extern void fn_801A7228(void *);
extern int fn_802006D4(int, int, int, int, void (*)(int));
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, u8);
extern int fn_801E8328(u32, u32);
extern u64 fn_8020123C(int, int, int, int);
extern u32 fn_801A74C0(void *);
extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);
extern void PSVECSubtract(Vec3 *, Vec3 *, Vec3 *);
extern Vec3 fn_801A75C0(void *, int, Vec3 *);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_8012CDF0(void *, int, Vec4, int);
extern u32 fn_801A7490(void *);
extern void *fn_80201814(int);
extern int fn_8003AD00(void *, void *, void *, int *, int *);
extern void *fn_80201890(int);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern u8 fn_80157AB8(void *);
extern void fn_800337C8(Vec3 *, const Vec3 *, int, ImpactEffect *, int, int);
extern void fn_800E9C5C(void *, ThrowState *, Vec3 *);
extern int fn_8012FDA0(void *, int);
extern void fn_80127FD8(void *, int, Matrix34 *);
extern void PSMTXInverse(Matrix34 *, Matrix34 *);
extern void PSMTXConcat(Matrix34 *, Matrix34 *, Matrix34 *);
extern void *fn_80155DB4(u32);
extern int fn_80156F80(void *, void *);
extern void fn_80039FF0(void *, Vec3 *);
extern int fn_80204028(void *, u32, int, int);
extern void fn_800890F4(Vec3 *);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_800E9E44(void *, void *, int);
extern void fn_80127DF8(void *, int, Matrix34 *);
extern void C_QUATMtx(Vec4 *, Matrix34 *);
extern void fn_8012CCF0(void *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern Vec4 *fn_8011FE34(void *);

/* The joint API consumes copies of its three vector arguments. */
static inline void setJointVectors(void *model, int joint, Vec3 position,
                                  Vec3 second, Vec3 third, int alternate)
{
    fn_8012CCF0(model, joint, &position, &second, &third, alternate);
}

int fn_800E9254(void *object, int stateId, void *event)
{
    JointQuery hit;
    Matrix34 hitMatrix, inverse, ownMatrix, attachedMatrix, worldMatrix;
    Vec3 end, beginning;
    Vec4 spinRotation, rotation;
    Vec3 translation;
    Vec4 attachedRotation;
    Vec3 zero;
    int hitHandle, hitJoint;
    u16 soundExtra;
    u8 initialVolume, volume;
    int eventId;
    ThrowState *state;
    void *model;
    int handle;
    void *owner;
    Vec3 *position;

    eventId = fn_80200C10(event);
    state = fn_80201B8C(object)->state;
    model = fn_80201BC8(object);
    handle = fn_80201B54(object);
    owner = state->owner;
    position = fn_8011F130(model);
    if (eventId == 3) {
        if (!(state->flags & 4) && owner != 0) {
            EffectInfo *info = (EffectInfo *)fn_801A7480(owner);
            if (info != 0 && info->resource != 0) {
                void *resource = fn_80149D48(info->resource, 0);
                if (resource != 0) {
                    state->resource = resource;
                    state->flags |= 4;
                }
            }
        }
        if (!(state->flags & 0x10)) {
            state->flags |= 0x10;
        }
    }
    if (stateId == 0) {
        if (eventId == 1) {
            if (!(state->flags & 2) && fn_8011EB04(model) != 0x100) {
                u16 sound = fn_80050B08(0, (int)model, 0x39, &initialVolume, 0, 0, 0);
                fn_801AC9F4(sound, initialVolume, position, 2);
            }
            memset(lbl_80325E58, 0, 0xC4);
            {
                void *link = fn_80201C24(object);
                fn_801A7680(owner, (u32)link);
            }
            fn_801A7934(owner);
            fn_801A78EC(owner);
            fn_801A7910(owner);
            {
                u32 value = fn_801A7570(owner);
                fn_801A74D8(owner, 1);
                fn_801A7560(owner, value);
            }
            fn_801A74D8(owner, 0x4000);
            fn_801A7478(owner, (u32)lbl_80325E58);
            fn_800C3ADC(model, owner);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (eventId == 0x39) {
            fn_800E9DE0(state);
            if (state->owner != 0) {
                fn_801A7228(state->owner);
                state->owner = 0;
            }
            fn_802006D4(handle, handle, -1, 0x11, 0);
            fn_802006D4(handle, handle, -1, 0x39, 0);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            state->flags |= 0x40;
            fn_801E8328(2, (u32)object);
            return 1;
        } else if (eventId == 0x3D) {
            fn_8020123C(0x39, handle, handle, 0);
            return 1;
        }
    } else if (stateId == 1) {
        if (eventId == 3) {
            int collision;
            u32 flying;
            u32 reached;
            u32 expired;
            int stopped = 0;
            flying = fn_801A74C0(owner) & 0x2000;
            reached = state->travelled + state->step >= state->distance;
            expired = state->travelled + state->step >= lbl_8064F830;
            if (!(state->flags & 1) && !(state->flags & 0x20)) {
                PSVECAdd(position, &state->spin, &end);
                fn_801A75C0(owner, 0, &end);
                PSVECSubtract(position, &state->spin, &beginning);
                fn_801A75C0(owner, 1, &beginning);
                state->flags |= 1;
            }
            if (state->flags & 2) {
                state->angle += lbl_8064F834;
                fn_8017A244(&state->axis, &spinRotation, state->angle);
                fn_8017A34C(&spinRotation, &state->rotation, &rotation);
                fn_8012CDF0(model, 15, rotation, 0);
            }
            PSVECAdd(position, &state->velocity, position);
            state->travelled += state->step;
            if (state->flags & 2) {
                state->soundTimer++;
                if (state->soundTimer > 10) {
                    u16 sound = fn_80050B08(0, (int)model, 0x41, &volume, 0, &soundExtra, 0);
                    fn_801AC9F4(sound, 100, position, 2);
                    state->soundTimer = 0;
                }
            }
            PSVECAdd(position, &state->spin, &end);
            fn_801A75C0(owner, 2, &end);
            PSVECSubtract(position, &state->spin, &beginning);
            fn_801A75C0(owner, 3, &beginning);
            if (!(state->flags & 0x20)) {
                void *source = fn_80201814(fn_801A7490(owner));
                collision = fn_8003AD00(object, source, owner, &hitHandle, &hitJoint);
            }
            if (state->flags & 0x20) {
                if ((!flying && reached) || expired) {
                    stopped = 1;
                }
            } else if (collision & 3) {
                void *hitModel = fn_80201890(hitHandle);
                int color;
                state->hitModel = hitModel;
                state->hitHandle = hitHandle;
                state->hitJoint = hitJoint;
                fn_8011F6A4(hitModel, 0, hitJoint, -1, &hit, 1);
                color = fn_80157AB8(fn_80201C24(object));
                if (color != 0) {
                    fn_800337C8(position, 0, color, &state->impactEffect, 0x50, 1);
                }
                fn_800E9C5C(model, state, &hit.pos);
                {
                    int joint = fn_8012FDA0(model, 15);
                    fn_80127FD8(model, joint, &ownMatrix);
                }
                {
                    int joint = fn_8012FDA0(hitModel, hitJoint);
                    fn_80127FD8(hitModel, joint, &hitMatrix);
                }
                PSMTXInverse(&hitMatrix, &inverse);
                PSMTXConcat(&inverse, &ownMatrix, &state->attachment);
                fn_80156F80(fn_80155DB4((u32)object),
                            fn_80155DB4((u32)fn_80201814(state->hitHandle)));
                fn_800E9DE0(state);
                fn_801A7228(state->owner);
                state->owner = 0;
                fn_80201D2C(object, 0x6B);
                fn_80201D14(object, 1);
            } else if (collision & 0x20) {
                fn_801AC9F4(0x29, 100, position, 2);
                fn_8020123C(0x39, handle, handle, 0);
            } else if ((!flying && reached) || expired) {
                stopped = 1;
            }
            if (stopped) {
                if (expired) {
                    fn_8020123C(0x39, handle, handle, 0);
                } else {
                    u16 sound;
                    int color = fn_80157AB8(fn_80201C24(object));
                    if (color != 0) {
                        fn_800337C8(position, 0, color, &state->impactEffect, 0x50, 1);
                    }
                    fn_800E9C5C(model, state, &state->target);
                    state->travelled = state->distance;
                    fn_80039FF0(model, position);
                    if (state->surface == 0x14) {
                        sound = 0x2CA;
                    } else {
                        sound = fn_80050B08(0, (int)model, 0x1C, &volume, 0, 0, 0);
                    }
                    fn_801AC9F4(sound, 100, position, 2);
                    fn_80204028(object, 10000, 0, 0);
                    fn_800E9DE0(state);
                    fn_801A7228(state->owner);
                    state->owner = 0;
                    if (state->flags & 0x20) {
                        fn_800890F4(&state->target);
                        fn_8020123C(0x39, handle, handle, 0);
                    }
                    fn_80201D2C(object, 0x6A);
                    fn_80201D14(object, 1);
                }
            }
            fn_801A75C0(owner, 0, &end);
            fn_801A75C0(owner, 1, &beginning);
            return 1;
        }
    } else if (stateId == 0x6A) {
        if (eventId == 1) {
            fn_8020104C(0x11, handle, handle, 0, lbl_8064F838);
            return 1;
        }
        if (eventId == 0x11) {
            fn_800E9E44(object, model, handle);
            return 1;
        }
    } else if (stateId == 0x6B) {
        if (eventId == 1) {
            if (!((u32)(fn_8020123C(0xF3, handle, state->hitHandle, state->hitJoint) & 0xFFFFFFFF))) {
                fn_8020104C(0x39, handle, handle, 0, lbl_8064F83C);
            }
            return 1;
        } else if (eventId == 3) {
            zero = lbl_80239B74;
            {
                int joint = fn_8012FDA0(state->hitModel, state->hitJoint);
                fn_80127DF8(state->hitModel, joint, &attachedMatrix);
            }
            PSMTXConcat(&attachedMatrix, &state->attachment, &worldMatrix);
            translation.x = worldMatrix.m[0][3];
            translation.y = worldMatrix.m[1][3];
            translation.z = worldMatrix.m[2][3];
            C_QUATMtx(&attachedRotation, &worldMatrix);
            fn_8012CDF0(model, 15, attachedRotation, 0);
            setJointVectors(model, 15, translation, zero, zero, 1);
            {
                Vec4 *orientation = fn_8011FE34(state->hitModel);
                *fn_8011FE34(model) = *orientation;
            }
            *position = *fn_8011F130(state->hitModel);
            return 1;
        } else if (eventId == 0x11) {
            fn_800E9E44(object, model, handle);
            return 1;
        } else if (eventId == 0x3D) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
