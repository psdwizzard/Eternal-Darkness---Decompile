typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;

typedef struct GameState {
    u8 pad0[0x14];
    s16 countdown; /* 0x14 */
    u8 pad16[0x1B5];
    s8 screen; /* 0x1CB */
} GameState;

/* Sound ids announcing the remaining hours: one, two and three hours left. */
typedef struct HourSounds { int ids[3]; } HourSounds;

extern HourSounds lbl_802393FC;
extern GameState lbl_8031CBA0;
extern void *lbl_8064C8E8, *lbl_8064C8EC;

extern void fn_80025A78(int);
extern void fn_80045A24(int, int);
extern void fn_80052580(int, int, int, int, int);
extern void fn_8007D744(int);
extern void fn_800A7F1C(int);
extern void fn_801441C0(int, int, int);
extern int fn_80144608(void *);
extern void fn_80144680(void *);
extern unsigned int fn_8015C910(void);
extern int fn_8015C9F0(void);
extern int fn_801A98F4(int, void *);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern void fn_801E5FB0(void *);
extern void *fn_80201B3C();
extern int fn_80201B64(void *);

void fn_80080FEC(int unused, int phase) {
    if (phase == 1) {
        if (fn_8015C910() == 0) {
            GameState *state = &lbl_8031CBA0;
            s16 t = state->countdown;

            if (t >= 0) {
                if (t % 3600 == 0 && t > 0) {
                    HourSounds sounds = lbl_802393FC;

                    fn_801A98F4(0x1E1, (void *)0x64);
                    /* Hours remaining (1..3) as an unsigned index: retail computes
                     * (hours - 1) * 4 explicitly; a signed index (inline or via a
                     * local) lets MWCC fold the -1 into the stack offset. */
                    fn_801B05E8(sounds.ids[t / 3600 - 1U], 0x64,6, 1, 0, 5, 0, 0);
                } else if (t % 60 == 0 && t < 3600) {
                    fn_801A98F4(0x1E1, (void *)0x64);
                } else if (t % 10 == 0) {
                    fn_801A98F4(0x1E0, (void *)0x64);
                }
            }
            state->countdown--;
        }

        if (lbl_8031CBA0.countdown == 0) {
            if (fn_8015C9F0() > 0 || fn_80201B64(fn_80201B3C()) == 8) {
                lbl_8031CBA0.countdown = 1;
            } else {
                fn_801E5FB0(lbl_8064C8EC);
                lbl_8064C8EC = 0;
                fn_800A7F1C(0);
                fn_80052580(2, 0x40, 1, 0, 0);
                fn_801441C0(1, 0, 60);
                fn_801441C0(1, 1, 120);
                fn_80144608(lbl_8064C8E8);
            }
        } else if (lbl_8031CBA0.countdown == -120) {
            fn_80144680(lbl_8064C8E8);
            lbl_8031CBA0.screen = -1;
            lbl_8064C8E8 = 0;
            fn_801E5FB0(lbl_8064C8EC);
            lbl_8064C8EC = 0;
            fn_80045A24(0, 0);
            fn_80025A78(3);
        }
        fn_8007D744(5);
    }
}
