typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target {
    Vec3 testPosition;
    Vec3 effectPosition;
    s16 direction[3];
    u8 pad1E[2];
} Target;
typedef struct RuntimeState {
    void *model;
    void *effect;
    u32 pad08;
    Target targets[3];
} RuntimeState;
typedef struct GameState {
    float zAngle, xAngle;
    int actions[3];
    s16 countdown;
    u16 sound;
    s8 active, selected, progress;
    u8 pad1B[0x195];
    Vec3 position;
} GameState;
typedef struct Color { u8 r, g, b, a; } Color;

extern GameState lbl_8031CBA0;
extern RuntimeState lbl_8031CD84;
extern s8 lbl_8064B598[3];
extern Color lbl_8064EA8C;
extern const float lbl_8064EA90;
extern int lbl_8064D18C;
extern void *lbl_8064C8EC;
extern char lbl_80244F44[];

extern u32 fn_80178E94(const float *, const float *);
extern void fn_80153050(void *, void *, u8, u8, u16, u16, u8 *, u8,
                       u16, s16, u8, u8);
extern void fn_80153104(void *);
extern int fn_801AAE68(u16, u8, u8, float, Vec3 *, s8, u8, u8, u16, u32);
extern void fn_801AC5E4(u16, u8, u8, int, s8, int, int);
extern int fn_801B05E8(int, u8, u8, u8, Vec3 *, u8, int, int);
extern void fn_8016B400(int, void *, void *);
extern void fn_801E7FDC(const char *, ...);
extern void fn_8007D744(int);
extern void fn_801E5FB0(void *);
extern int fn_800460EC(void);
extern int fn_8011E310(int, int, int, int, int, int, int);

/* Advance the interaction with the first target within range. */
void fn_800813D0(int unused, int event)
{
    int i;
    s8 selected;

    if (event == 1) {
        lbl_8031CBA0.selected = -1;
        for (i = 0; i < 3; i++) {
            if (fn_80178E94(&lbl_8031CD84.targets[i].testPosition.x,
                           &lbl_8031CBA0.position.x) < 30U) {
                lbl_8031CBA0.selected = i;
                break;
            }
        }
        selected = lbl_8031CBA0.selected;
        if (selected > -1) {
            lbl_8031CBA0.progress++;
            if (lbl_8031CBA0.progress <= lbl_8064B598[selected] &&
                lbl_8031CBA0.actions[selected] != 0) {
                /* The validated selection also indexes the target effect data. */
                int targetIndex = selected;
                Color color = lbl_8064EA8C;
                /* The third target becomes available after the first two actions. */
                if (targetIndex != 2 ||
                    (lbl_8031CBA0.actions[0] == 0 && lbl_8031CBA0.actions[1] == 0)) {
                    if (lbl_8031CBA0.progress == lbl_8064B598[targetIndex]) {
                        if (targetIndex != 2) {
                            color.r = 230;
                            color.g = 230;
                            color.b = 230;
                            if (lbl_8031CBA0.sound != 0xFFFF) {
                                fn_801AC5E4(246, 0, 0, 1, 30, 1, 0);
                                lbl_8031CBA0.sound = 0xFFFF;
                            }
                            if (lbl_8031CD84.effect != 0) {
                                fn_80153104(lbl_8031CD84.effect);
                                lbl_8031CD84.effect = 0;
                            }
                            fn_80153050(&lbl_8031CD84.targets[targetIndex].effectPosition,
                                        lbl_8031CD84.targets[targetIndex].direction,
                                        32, 64, 30, 24, &color.r, 3, 100, -1, 1, 250);
                            fn_801B05E8(38, 100, 3, 1, 0, 5, 0, 0);
                        }
                        fn_8016B400(lbl_8031CBA0.actions[selected], 0, 0);
                        lbl_8031CBA0.actions[selected] = 0;
                    } else if (targetIndex != 2) {
                        if (lbl_8031CD84.effect == 0) {
                            register RuntimeState *runtime = &lbl_8031CD84;
                            fn_80153050(&lbl_8031CD84.targets[targetIndex].effectPosition,
                                        lbl_8031CD84.targets[targetIndex].direction,
                                        32, 16, 0xFFFF, 0xFFFF, &color.r, 3, 100, -1, 1, 250);
                            /* ASM: stw saves the effect pointer returned in r3. The callee
                             * is defined as void, so C cannot access its return register. */
                            asm { stw r3, 4(runtime) }
                        }
                        if (lbl_8031CBA0.sound == 0xFFFF) {
                            fn_801E7FDC(lbl_80244F44);
                            lbl_8031CBA0.sound = fn_801AAE68(246, 100, 0, lbl_8064EA90,
                                &lbl_8031CD84.targets[targetIndex].effectPosition,
                                1, 1, 0, (u16)lbl_8064D18C, 0);
                        }
                        if (lbl_8031CBA0.sound != 0xFFFF) {
                            fn_801AC5E4(246, 0, lbl_8031CBA0.progress * 50 / 100 + 50,
                                        0, 0, 1, 0);
                        }
                        /* Retail repeats the update, rechecking the handle after the call. */
                        if (lbl_8031CBA0.sound != 0xFFFF) {
                            fn_801AC5E4(246, 0, lbl_8031CBA0.progress * 50 / 100 + 50,
                                        0, 0, 1, 0);
                        }
                    }
                }
            }
            if (lbl_8031CBA0.selected == -1 && lbl_8031CBA0.sound != 0xFFFF) {
                fn_801AC5E4(246, 0, 0, 1, 30, 1, 0);
                lbl_8031CBA0.sound = 0xFFFF;
            }
        }
        fn_8007D744(0);
        if (lbl_8031CBA0.selected == -1) {
            if (lbl_8031CD84.effect != 0) {
                fn_80153104(lbl_8031CD84.effect);
                lbl_8031CD84.effect = 0;
            }
        } else if (lbl_8031CBA0.active == 0) {
            fn_801E5FB0(lbl_8064C8EC);
            lbl_8064C8EC = 0;
        }
        if (lbl_8031CBA0.active != 0 && fn_800460EC() == 0) {
            fn_8011E310(6, 53, 0, 0, 50, 0, 0);
        }
    }
}
