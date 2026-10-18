typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectParams {
    unsigned char pad0[2];
    unsigned char value2;
    signed char value3;
    unsigned char pad4[2];
    u16 value6;
    unsigned char pad8[0xC];
    unsigned char value14;
    unsigned char value15;
    unsigned char value16;
    unsigned char value17;
    unsigned char value18;
    unsigned char value19;
    unsigned char pad1A[0x76];
} EffectParams;

extern volatile s32 lbl_8064D18C;
extern const float lbl_8064E998;
extern void fn_801AAE68(float intensity, s32 effect_type, s32 value, s32 arg3,
                        const Vec3 *position, s32 arg5, s32 arg6, s32 arg7,
                        u16 owner, s32 arg9);
extern void fn_8018358C(EffectParams *params);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void* fn_80148008(Vec3 *position, void *descriptor,
                       EffectParams *params, void (*callback)(void));
extern void fn_801834F0(void);

/* NonMatching: honest reconstruction of the randomized effect descriptor and
 * sound dispatch. */
void fn_8007B540(const Vec3 *source, void *object)
{
    unsigned char descriptor[6] = { 0, 0, 0, 0, 0, 1 };
    Vec3 position;
    EffectParams params;

    fn_801AAE68(lbl_8064E998, 0x141, 100, 0, source, 2, 2, 0,
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
    position = *source;
    fn_80148008(&position, descriptor, &params, fn_801834F0);
}
