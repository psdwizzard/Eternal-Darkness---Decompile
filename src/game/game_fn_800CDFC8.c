#include "src/game/types.h"

typedef float f32;

#define NULL ((void *)0)

typedef struct LinkedTable {
    u8 pad[0x36];
    u16 values[1];
} LinkedTable;

typedef struct LinkedInfo {
    u32 unk0;
    LinkedTable *table;
} LinkedInfo;

extern s32 fn_80071D84(void);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(void *);
extern int fn_8003565C(void *, int *);
extern void *fn_80201B9C();
extern void *fn_80204844(void *, s32);
extern int fn_8006D444();
extern int fn_80038308(void *, int, s16 *);
extern int fn_80049220();
extern void *fn_80049304(void *, int);
extern int fn_8006D344(void *, int, int);
extern int fn_800CE3BC(int);
extern void fn_8011FB44(void *, void *);
extern void fn_8011EB0C(void *, int);
extern LinkedInfo *fn_80201C24(void *);
extern void fn_8011FC38(void *, int, int);
extern void *fn_80201814(int);
extern int fn_80201B64(void *);
extern int fn_80126070(void *);
extern int fn_80201B5C(void *);
extern void fn_8012FE10(void *, int, f32 *);
extern void fn_800CE24C(void *, f32 *, int, int, int);

extern s32 lbl_8064B818;
extern s32 lbl_8064CAA8;
extern s32 lbl_8064CAAC;
extern s32 lbl_8064D5A8;

void fn_800CDFC8(void *object) {
    f32 pos[3];
    int linkedId;
    s16 health;
    s16 sanity;
    void *runtime;
    int state;
    void *link;
    void *ctx;
    int kind;
    int match;
    void *other;
    void *otherRuntime;
    int isSpecial;

    if ((lbl_8064D5A8 & 0xF) != 0) {
        return;
    }
    if (fn_80071D84() != 0) {
        return;
    }

    runtime = fn_80201BC8(object);
    linkedId = 0;
    fn_80201B54(object);
    state = fn_8003565C(object, &linkedId);
    health = 0;
    sanity = 0;
    ctx = (void *)fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
    fn_80038308(object, 0, &health);
    fn_80038308(object, 3, &sanity);
    kind = fn_80049220(object, 1);
    link = fn_80049304(object, kind);

    if (fn_8006D344(ctx, 0x40800, 0) != 0) {
        state = 1;
    } else if (state != 0 && health <= 40) {
        state = 2;
    } else if (health <= 40) {
        state = 1;
    } else if (sanity < 3333) {
        state = 5;
    } else if (state != 0) {
        state = 4;
    } else {
        if (sanity < 5000) {
            void *scale = (void *)fn_800CE3BC(sanity);
            fn_8011FB44(runtime, scale);
        } else {
            fn_8011FB44(runtime, (void *)0x10000);
        }
        state = 0;
    }

    lbl_8064CAA8 = state;
    if (lbl_8064B818 != -1) {
        state = lbl_8064B818;
    }
    fn_8011EB0C(runtime, state);
    if (link != NULL) {
        fn_8011FC38(runtime, fn_80201C24(link)->table->values[state], 0);
    } else {
        fn_8011FC38(runtime, state, 0);
    }

    if (linkedId != 0) {
        other = fn_80201814(linkedId);
        isSpecial = fn_80201B64(object) == 0x52;
        if (other != NULL) {
            otherRuntime = fn_80201BC8(other);
            if (otherRuntime != NULL && fn_80126070(otherRuntime) != 0 && !isSpecial) {
                kind = fn_80201B5C(other);
                match = 0;
                if (kind == 0x2F || kind == 0x39) {
                    match = 1;
                }
                lbl_8064CAAC = match != 0;
                fn_8012FE10(otherRuntime,lbl_8064CAAC, pos);
                fn_800CE24C(runtime, pos, 200, 20, 17);
            }
        }
    }
}
