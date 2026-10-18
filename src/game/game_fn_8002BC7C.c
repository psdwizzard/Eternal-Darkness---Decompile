typedef int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

#pragma use_lmw_stmw on

extern float lbl_8064E048;
extern float lbl_8064E04C;
extern float lbl_8064E050;
extern float lbl_8064E054;
extern float lbl_8064E058;
extern float lbl_8064E05C;
extern float lbl_8064E060;

extern int fn_80200C10(void *);
extern int fn_80201B54();
extern void *fn_80201BC8();
extern unsigned int fn_8011FA8C(void*, int, int);
extern void fn_8011F788(void*, float);
extern void fn_8011F798(void*, float);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern unsigned long long fn_8020123C();
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_801E8328();
extern void fn_80201D34(void *, s32);
extern void fn_80201D1C(void *, s32);
extern void fn_8015424C(s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_8002BFE0(void*);
extern s32 fn_8015E4E8(void);
extern float fn_8012D01C(void*, s32);
extern void fn_8012D074(void*, s32, float);
extern s32 fn_8011F770(void*);
extern s32 fn_8011F130(void*);
extern void PSVECAdd(s32, s32, Vec3*);
extern s32 fn_8011F7D8(void*);
extern float fn_8011F6F8(void*);
extern s32 fn_8017E4E4(Vec3*, s32, float, float, float, float);
extern void PSVECSubtract();
extern void fn_800C8394(void*, s32);

s32 fn_8002BC7C(void* callback, s32 phase, void* event)
{
    s32 event_id = fn_80200C10(event);
    s32 object_id = fn_80201B54(callback);
    void* state = fn_80201BC8(callback);

    if (phase == 0) {
        if (event_id == 1) {
            fn_8011FA8C(state, 0x8C0, 2);
            fn_8011F788(state, lbl_8064E048);
            fn_8011F798(state, lbl_8064E048);
            fn_8020104C(8, object_id, object_id, 0, lbl_8064E04C);
            fn_80201D2C(callback, 1);
            fn_80201D14(callback, 1);
            return 1;
        }
        if (event_id == 0x39) {
            fn_801E8328(2, callback);
            fn_80201D34(callback, 0);
            fn_80201D1C(callback, 1);
            return 1;
        }
        if (event_id == 0x3D) {
            fn_8020123C(0x39, object_id, object_id, 0);
            return 1;
        }
        if (event_id == 8) {
            fn_80201D2C(callback, 0x26);
            fn_80201D14(callback, 1);
            return 1;
        }
        if (event_id == 0xDF) {
            fn_8015424C(object_id, 1, -1, 1, 0xA0, 0, 1, 0x20);
            return 1;
        }
        if (event_id == 0x59) {
            fn_8020123C(0x39, object_id, object_id, 0);
            return 1;
        }
        goto event_unhandled;
    }

    if (phase == 1) {
        if (event_id == 1) {
            fn_8002BFE0(state);
            return 1;
        }
        if (event_id == 3) {
            s32 first;
            s32 second;
            s32 target;
            s32 hit;
            Vec3 vector;

            if (fn_8015E4E8() != 0) {
                return 0;
            }
            fn_8012D074(state, 0xF, fn_8012D01C(state, 0xF) / lbl_8064E050);
            first = fn_8011F770(state);
            second = fn_8011F130(state);
            PSVECAdd(second, first, &vector);
            target = fn_8011F7D8(state);
            hit = fn_8017E4E4(&vector, target, lbl_8064E054,
                              fn_8011F6F8(state), lbl_8064E054,
                              lbl_8064E058);
            PSVECSubtract(&vector, first, second);
            if (hit & 1) {
                fn_80201D2C(callback, 0x26);
                fn_80201D14(callback, 1);
            }
            return 1;
        }
        if (event_id == 2) {
            return 1;
        }
        goto event_unhandled;
    }

    if (phase == 0x26) {
        if (event_id == 1) {
            fn_8020123C(0x11, object_id, object_id, 0);
            return 1;
        }
        if (event_id == 0x11) {
            fn_800C8394(state, -5);
            fn_8011FA8C(state, 0x800, 0);
            fn_8020104C(0x39, object_id, object_id, 0, lbl_8064E05C);
            return 1;
        }
        if (event_id == 3) {
            if (fn_8015E4E8() != 0) {
                return 0;
            }
            fn_8012D074(state, 0xF, fn_8012D01C(state, 0xF) / lbl_8064E060);
            return 1;
        }
        if (event_id == 2) {
            return 1;
        }
        goto event_unhandled;
    }

    return 0;

event_unhandled:
    return 0;
}
