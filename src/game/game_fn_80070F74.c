typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Context {
    int state;
    char pad_04[0x14];
    u32 flags;
} Context;

typedef struct Flags {
    char pad_00[0x20];
    u32 bits;
} Flags;

typedef struct Actor {
    char pad_00[0x44];
    int id;
} Actor;

typedef struct Owner {
    char pad_00[4];
    Context *context;
    char pad_08[0x30];
    int id;
    char pad_3C[0x2C];
    u8 slot;
    char pad_69[0x5B];
    Flags *flags;
} Owner;

typedef struct GlobalState {
    char pad_00[8];
    int level;
} GlobalState;

extern GlobalState lbl_803003C8;
extern const Vec3 lbl_80239110;
extern void *lbl_8064C4E0;
extern void *lbl_8064C824;
extern int lbl_8064C8C4;
extern void *lbl_8064C8C8;
extern int lbl_8064C9DC;
extern int lbl_8064C9E0;
extern const float lbl_8064E7FC;

extern void fn_8006CAC4(Context *, int);
extern void fn_8006C9E4(Context *, int);
extern void fn_8006BEE4(Context *, void (*)(void));
extern void fn_8006DE98(void);
extern void fn_8006EA4C(void);
extern void fn_8006DEF8(Owner *, u32, u32, u32, unsigned short);
extern void fn_801E7974(void *, int);
extern void fn_801E79A0(void *, int);
extern void *fn_80201814(int);
extern void fn_802020B4(void *, int);
extern Actor *fn_80036D38(void *);
extern int fn_801A6D9C(void *);
extern void fn_801A6E04(void *);
extern void fn_801A5C30(int);
extern void fn_801B08BC(int, int, int);
extern void fn_801FA748(int, Vec3 *);
extern void fn_801FA66C(int, int, float);
extern void fn_801A9A40(int, int, int);
extern void fn_801E5FB0(void *);
extern void fn_8011E174(int, int);

int fn_80070F74(Owner *owner)
{
    int result = 0;
    Context *ctx = owner->context;
    Actor *actor;
    Vec3 dir;
    int i;

    if (ctx == 0) {
        goto end;
    }

    if (ctx->flags & 0x20) {
        fn_8006CAC4(ctx, 0);
        fn_8006C9E4(ctx, 1);
        fn_8006BEE4(ctx, fn_8006DE98);
        result = 1;
        switch (ctx->state) {
        case 0x1B:
            fn_801E7974(lbl_8064C4E0, 0x1DB);
            break;
        case 7:
            actor = fn_80036D38(fn_80201814(owner->id));
            if (fn_801A6D9C(lbl_8064C824) & 2) {
                fn_801A6E04(lbl_8064C824);
            }
            if (actor != 0) {
                fn_802020B4(fn_80201814(actor->id), 1);
            }
            fn_801A5C30(1);
            fn_801B08BC(-1, 0x1B, 0);
            lbl_8064C8C4 = 0;
            break;
        case 10:
            dir = lbl_80239110;
            fn_801FA748(2, &dir);
            break;
        case 6:
            if (fn_801A6D9C(lbl_8064C824) & 2) {
                fn_801A6E04(lbl_8064C824);
                fn_801A5C30(1);
            }
            break;
        case 2:
            fn_801FA66C(2, 0, lbl_8064E7FC);
            break;
        case 4:
        case 0x17:
        case 0x1F:
            lbl_8064C8C4 = 0;
            fn_8006BEE4(ctx, fn_8006EA4C);
            for (i = 0; i < 4; i++) {
                owner->slot = i;
                fn_8006DEF8(owner, ctx->state, 0, 0, 1);
            }
            fn_801A9A40(5, lbl_8064C9E0, lbl_8064C9DC);
            if (ctx->state == 4) {
                actor = fn_80036D38(fn_80201814(owner->id));
                fn_801A5C30(1);
                if (actor != 0) {
                    fn_802020B4(fn_80201814(actor->id), 1);
                }
            }
            break;
        }
        if (lbl_8064C8C8 != 0) {
            fn_801E5FB0(lbl_8064C8C8);
            lbl_8064C8C8 = 0;
        }
        fn_8011E174(0x100, 0);
    }

    if (ctx->state == 0xD && (owner->flags->bits & 4)) {
        owner->flags->bits &= ~4u;
        fn_8006CAC4(ctx, 0);
        fn_8006C9E4(ctx, 1);
        fn_8006BEE4(ctx, fn_8006DE98);
        result = 1;
        if (lbl_8064C8C8 != 0) {
            fn_801E5FB0(lbl_8064C8C8);
            lbl_8064C8C8 = 0;
        }
        fn_8011E174(0x100, 0);
        if (lbl_803003C8.level == 0) {
            fn_801E79A0(lbl_8064C4E0, 0x463);
        } else {
            fn_801E79A0(lbl_8064C4E0, 0x464);
        }
    }
end:
    return result;
}
