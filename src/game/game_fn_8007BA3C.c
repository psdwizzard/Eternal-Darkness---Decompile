typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object {
    Vec3 origin;
    Vec3 position;
    unsigned char pad18[0x10];
    void *link;
    unsigned char active;
    unsigned char pad2D[3];
} Object;
typedef struct EffectParams {
    unsigned char value0;
    unsigned char pad1;
    unsigned char value2;
    signed char value3;
    unsigned char pad4[2];
    u16 value6;
    unsigned char pad8[0xC];
    unsigned char value14, value15, value16, value17, value18, value19;
    unsigned char pad1A[0x76];
} EffectParams;

extern volatile s32 lbl_8064D18C;
extern const float lbl_8064E998;
extern const float lbl_8064E9BC;
extern void fn_801AAE68(float, s32, s32, s32, Vec3 *, s32, s32, s32,
                        u16, s32);
extern void fn_8018358C(EffectParams *);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8019FF5C(EffectParams *);
extern s32 fn_8007BC44(Vec3 *);
extern void* fn_80148008(Vec3 *, void *, EffectParams *, void (*)(void));
extern void fn_801834F0(void);
extern void PSVECSubtract();
extern void PSVECNormalize(Vec3 *, Vec3 *);
extern void C_VECReflect(Vec3 *, Vec3 *, Vec3 *);
extern void PSVECScale(Vec3 *, Vec3 *, float);
extern void fn_80179B64(Vec3 *, void *);
extern void fn_801A0008(void);

/* NonMatching: honest reconstruction of the per-object effect loop. */
void fn_8007BA3C(Object *object, s32 count)
{
    unsigned char descriptor[6] = { 0, 0, 0, 0, 0, 1 };
    unsigned char follow_descriptor[6] = { 0, 0, 0, 0, 0, 1 };
    Vec3 linked_direction;
    Vec3 direction;
    Vec3 effect_position;
    Vec3 follow_position;
    EffectParams params;
    EffectParams follow_params;
    Vec3 *position;
    s32 i;
    void (*callback)(void);

    fn_801AAE68(lbl_8064E998, 0xC2, 50, 0, &object->position, 2, 2, 0,
                (u16)lbl_8064D18C, 0);
    fn_8018358C(&params);
    params.value2 = 100;
    params.value3 = -10;
    params.value6 = (rand() + 1) & 0x1F;
    params.value17 = 5;
    params.value18 = 1;
    params.value14 = 100;
    params.value15 = 100;
    params.value19 = (rand() & 7) + 1;
    params.value16 = (rand() & 0xF) + 10;
    fn_8019FF5C(&follow_params);
    follow_params.value0 = 3;

    for (i = 0; i < count; object++, i++) {
        if (object->active != 0) {
            callback = fn_801834F0;
            position = &object->position;
            if (fn_8007BC44(position) == 0) {
                effect_position = *position;
                fn_80148008(&effect_position, descriptor, &params, callback);
            }
            PSVECSubtract(position, object, &direction);
            PSVECNormalize(&direction, &direction);
            if (object->link != 0) {
                C_VECReflect(&direction,
                            (Vec3 *)((char *)object->link + 0x14),
                            &linked_direction);
                PSVECNormalize(&linked_direction, &linked_direction);
            } else {
                PSVECSubtract(object, position, &linked_direction);
            }
            PSVECScale(&linked_direction, &linked_direction, lbl_8064E9BC);
            fn_80179B64(&linked_direction, follow_descriptor);
            follow_position = *position;
            fn_80148008(&follow_position, follow_descriptor, &follow_params,
                        fn_801A0008);
        }
    }
}
