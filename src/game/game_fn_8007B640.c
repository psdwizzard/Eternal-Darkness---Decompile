typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Object {
    Vec3 origin;
    Vec3 position;
    unsigned char pad18[0xC];
    u32 value24;
    void *link;
    unsigned char active;
} Object;

typedef struct EffectParams {
    unsigned char data[0x90];
} EffectParams;

extern volatile s32 lbl_8064D18C;
extern const float lbl_8064E9A4;
extern const float lbl_8064E9A8;
extern const float lbl_8064E9AC;
extern const float lbl_8064E9B0;
extern void fn_801F74C8(s32, s32, s32);
extern void fn_801441C0(s32, s32, s32);
extern void PSVECSubtract();
extern void PSVECNormalize(Vec3 *, Vec3 *);
extern void PSVECScale(Vec3 *, Vec3 *, float);
extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);
extern void fn_801AAE68(float intensity, s32 effect_type, s32 value, s32 arg3,
                        Vec3 *position, s32 arg5, s32 arg6, s32 arg7,
                        u16 owner, s32 arg9);
extern void fn_801A318C(EffectParams *params);
extern void fn_80154F10(Vec3 *, void *, EffectParams *);
extern void fn_8007B374(Vec3 *);
extern void fn_8007B2F4(Vec3 *);

/* NonMatching: honest reconstruction of tiered feedback, vector adjustment,
 * sound, and effect dispatch. */
void fn_8007B640(Object *object, s32 flags)
{
    unsigned char descriptor[6] = { 0, 0, 0, 0, 0, 1 };
    Vec3 vector;
    EffectParams params;
    Vec3 *position = &object->position;


    if (object->active != 0) {
        if (object->value24 < 500) {
            fn_801F74C8(30, 1, 6);
            fn_801441C0(4, 2, 35);
        } else if (object->value24 < 1000) {
            fn_801F74C8(30, 1, 5);
            fn_801441C0(3, 3, 35);
        } else if (object->value24 < 1500) {
            fn_801F74C8(30, 1, 4);
            fn_801441C0(2, 4, 35);
        } else if (object->value24 < 2000) {
            fn_801F74C8(35, 1, 3);
            fn_801441C0(1, 4, 35);
        } else {
            fn_801F74C8(35, 1, 1);
            fn_801441C0(5, 8, 35);
        }

        PSVECSubtract(object, position, &vector);
        PSVECNormalize(&vector, &vector);
        PSVECScale(&vector, &vector,
                    (flags & 1) ? lbl_8064E9A4 : lbl_8064E9A8);
        PSVECAdd(&vector, position, position);
    }

    fn_801AAE68(lbl_8064E9AC, 0x2A1, 100, 0, position, 2, 1, 0,
                (u16)lbl_8064D18C, 0);
    fn_801A318C(&params);
    fn_80154F10(position, descriptor, &params);
    position->z -= lbl_8064E9B0;
    fn_8007B374(position);
    fn_8007B2F4(position);
}
