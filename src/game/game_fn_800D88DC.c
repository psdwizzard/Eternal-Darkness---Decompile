#pragma use_lmw_stmw on
typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int fn_80201B54();
extern void *fn_801294DC(void *, int, int, int);
extern void fn_800D8B74(s32, void *);
extern void *fn_800A1D28(void *);
extern void fn_802045AC(void *, Vec3 *);
extern float fn_8012B7D0(void *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern void fn_80129BA4(void *, float, float);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128C44(void *, void *, s32);
extern void fn_80128C28();
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_800D93B4(void);
extern void fn_800DA0C4(void);
extern void fn_800DA05C(void);
extern void fn_800D9278(void);
extern void fn_800D96E0(void);
extern void fn_800D9814(void);
extern void fn_800D9D64(void);
extern void fn_80204810(void);
extern float lbl_8064F418;
extern float lbl_8064F41C;
extern float lbl_8064F420;

s32 fn_800D88DC(void *object, void *resource)
{
    s32 result = 1;
    void *created;
    void *state;
    s32 object_id;
    Vec3 local_position;
    Vec3 origin;
    Vec3 position;
    float angle;
    float value;
    float magnitude;

    object_id = ((s32)fn_80201B54(object));
    created = fn_801294DC(resource, 5, 0x100, 6);
    if (created != 0) {
        fn_800D8B74(5, &origin);
        state = fn_800A1D28(object);
        ((u16 *)state)[0x42] &= ~0x410;
        fn_802045AC(object, &local_position);
        position = local_position;
        angle = fn_8012B7D0(resource, &position);
        fn_8017A12C(&value, fn_8012B750(resource), angle);
        magnitude = value;
        if (magnitude < lbl_8064F418) {
            magnitude = -magnitude;
        }
        if (magnitude > lbl_8064F41C) {
            fn_80129BA4(created, angle, lbl_8064F420);
        }

        fn_801287C4(created, fn_800D93B4, object, 0x80);
        fn_801287C4(created, fn_800DA0C4, state, 2);
        fn_801287C4(created, fn_800DA05C, object, 0x78);
        fn_801287C4(created, fn_800D9278, object, 0x9E);
        fn_801287C4(created, fn_800D96E0, object, 0x76);
        fn_801287C4(created, fn_800D9814, object, 0xA4);
        fn_801287C4(created, fn_800D9D64, object, 0xC7);
        fn_80128C44(created, fn_80204810, (object_id << 8) | 7);
        fn_80128C28(created, fn_80204810, (object_id << 8) | 0xC);
        fn_80201D2C(object, 0x42);
        fn_80201D14(object, 1);
    } else {
        result = 0;
    }
    return result;
}
#pragma use_lmw_stmw off
