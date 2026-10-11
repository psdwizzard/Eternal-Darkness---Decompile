/* fn_800C5FF0 (0x800C5FF0, 520 bytes) */
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef float f32;
#define NULL ((void *)0)

typedef struct {
    f32 x, y, z;
} Vec3;

typedef struct {
    u8 pad00[0x16];
    s16 unk16;
    u8 pad18[0x1C - 0x18];
    u16 unk1C;
    u8 pad1E[0x2C - 0x1E];
    u8 unk2C[0x5F - 0x2C];
    u8 unk5F;
    u8 pad60[0x78 - 0x60];
    s32 unk78;
    u8 pad7C[0x8E - 0x7C];
    u16 unk8E;
    u8 pad90[0x94 - 0x90];
    u8 unk94;
} PlayerState;

extern void fn_800AE460(void *obj);
extern void fn_800BEB04(void *ctx);
extern void fn_800C5CA0(void *ctx);
extern void fn_800C61F8(void *ctx, void *arg);
extern void fn_800C6254(void *ctx, void *obj);
extern void fn_800C644C(void *ctx);
extern void fn_800C65FC(void *ctx);
extern void fn_800CB694(void *obj);
extern void fn_800CDFC8(void *ctx);
extern void fn_8011E174(s32 a, s32 b);
extern void *fn_8011F130(void *obj);
extern s32 fn_8012FF34(void *obj, Vec3 *pos, s32 a, s32 b);
extern void fn_801302BC(void *obj, s32 a);
extern u32 fn_80178E94(void *a, void *b);
extern void *fn_80201814(s32 id);
extern s32 fn_80201B64(void *ctx);
extern Vec3 fn_80201E78(void *actor);

extern s32 lbl_8064B4D8;
extern s32 lbl_8064C58C;
extern s32 lbl_8064C86C;
extern f32 lbl_8064F1B8;

void fn_800C5FF0(void *ctx, void *obj, PlayerState **statePtr, void *arg3) {
    PlayerState *state = *statePtr;
    void *actor;
    s32 t;

    fn_800C61F8(ctx, arg3);
    fn_800C5CA0(ctx);
    if (state->unk5F != 0) {
        fn_8011E174(8, 1);
    }
    if (state->unk1C != 0) {
        state->unk1C--;
    }
    fn_800CDFC8(ctx);
    fn_800BEB04(ctx);
    if (fn_80201B64(ctx) != 0x52) {
        fn_800CB694(obj);
    }
    fn_800C6254(ctx, obj);
    fn_800AE460(obj);
    fn_800C644C(ctx);
    fn_800C65FC(ctx);
    t = lbl_8064C86C;
    if (t > 0) {
        t--;
    }
    lbl_8064C86C = t;
    lbl_8064B4D8 = lbl_8064B4D8 > 0 ? lbl_8064B4D8 - 1 : 0;
    if (state->unk16 > 0) {
        state->unk16--;
    }
    if (state->unk94 != 0) {
        state->unk94--;
    }
    if (lbl_8064C58C != 0) {
        actor = fn_80201814(lbl_8064C58C);
        if (actor != NULL) {
            Vec3 pos = fn_80201E78(actor);
            if (fn_8012FF34(obj, &pos, 4, 4) != 0) {
                fn_801302BC(obj, 0xB4);
            }
        } else {
            lbl_8064C58C = 0;
        }
    }
    if (state->unk8E != 0) {
        state->unk8E--;
        if (state->unk8E == 0) {
            state->unk78 = 0;
        }
        if (state->unk8E != 0 &&
            (f32)fn_80178E94(state->unk2C, fn_8011F130(obj)) > lbl_8064F1B8) {
            state->unk78 = 0;
            state->unk8E = 0;
        }
    }
}
