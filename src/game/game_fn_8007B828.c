typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object {
    Vec3 origin;
    Vec3 position;
    unsigned char pad18[0x10];
    void *link;
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
extern void fn_80211A6C();
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern void fn_80211C78(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern void fn_801AAE68(float, s32, s32, s32, Vec3 *, s32, s32, s32,
                        u16, s32);
extern void fn_8018358C(EffectParams *);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern s32 fn_8007BC44(Vec3 *);
extern void* fn_80148008(Vec3 *, void *, EffectParams *, void (*)(void));
extern void fn_801834F0(void);
extern void fn_80179B64(Vec3 *, void *);
extern void fn_8019FF5C(EffectParams *);
extern void fn_801A0008(void);

void fn_8007B828(Object *object)
{
    void (*callback)(void) = fn_801834F0;
    unsigned char descriptor[6] = { 0, 0, 0, 0, 0, 1 };
    Vec3 linked_direction;
    Vec3 direction;
    Vec3 effect_position;
    Vec3 follow_position;
    EffectParams params;
    Vec3 *position = &object->position;

    fn_80211A6C(position, object, &direction);
    fn_80211AAC(&direction, &direction);
    if (object->link != 0) {
        fn_80211C78(&direction, (Vec3 *)((char *)object->link + 0x14),
                     &linked_direction);
        fn_80211AAC(&linked_direction, &linked_direction);
    } else {
        fn_80211A6C(object, position, &linked_direction);
    }
    fn_80211A90(&linked_direction, &linked_direction, lbl_8064E9BC);

    fn_801AAE68(lbl_8064E998, 0xC3, 127, 0, position, 2, 2, 0,
                (u16)lbl_8064D18C, 0);
    fn_801AAE68(lbl_8064E998, 0x142, 50, 0, position, 2, 2, 0,
                (u16)lbl_8064D18C, 0);

    fn_8018358C(&params);
    params.value2 = 100;
    params.value3 = -10;
    params.value6 = (fn_800FBFB0() + 10) & 0x1F;
    params.value17 = 2;
    params.value18 = 1;
    params.value14 = 100;
    params.value15 = 100;
    params.value19 = (fn_800FBFB0() & 7) + 1;
    params.value16 = (fn_800FBFB0() & 0xF) + 1;

    if (fn_8007BC44(position) == 0) {
        effect_position = *position;
        fn_80148008(&effect_position, descriptor, &params, callback);
    }
    fn_80179B64(&linked_direction, descriptor);
    fn_8019FF5C(&params);
    params.value0 = 3;
    follow_position = *position;
    fn_80148008(&follow_position, descriptor, &params, fn_801A0008);
}
