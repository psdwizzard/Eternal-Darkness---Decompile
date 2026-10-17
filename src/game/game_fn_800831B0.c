typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Position { u32 x, y, z; } Position;
typedef struct Object Object;
typedef struct Entry Entry;
typedef struct RangeControl RangeControl;
typedef struct GameState {
    u8 pad0[0x1CB];
    s8 screen; /* 0x1CB */
    u8 pad1[0x1DC - 0x1CC];
    s8 lastRune; /* 0x1DC */
} GameState;
typedef struct MenuState {
    u8 pad0[0x610];
    RangeControl *range; /* 0x610 */
    void *models[5]; /* 0x614 */
    u32 mask; /* 0x628 */
    u32 firstBit; /* 0x62C */
} MenuState;

extern Vec3 lbl_8023945C;
extern char lbl_80244870[];
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern unsigned char lbl_8064B59C[8];
extern unsigned char lbl_8064B5A4[8];
extern Entry *lbl_8064C8E8;
extern void *lbl_8064C8EC;
extern int lbl_8064C904;
extern int lbl_8064C908;
extern int lbl_8064C90C;
extern float lbl_8064EA08;
extern float lbl_8064EABC;

extern void fn_80008C14(unsigned char *, int, int, int);
extern int fn_800835CC(int);
extern void fn_8011F0E8(Vec3 *, Vec3 *);
extern void fn_80120AD0(Object *, const Position *, u16, u32, float, float);
extern void fn_8012CBE8(u8 *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_80144680(Entry *);
extern void fn_80144C40(void);
extern void *fn_80158CC8(int, int, void *);
extern int fn_8015C4A4(void *, int);
extern void fn_8016B400(int, void *, void *);
extern int fn_801B05E8(int, u8, u8, u8, Vec3 *, u8, int, int);
extern void fn_801E5FB0(void *);
extern u32 fn_801E741C(const char *);
extern int fn_801E75A4(u32, int);
extern void fn_801E8AC4(void *);
extern int fn_801E8D34(RangeControl *);
extern int fn_801F6228(u32, u16, u16);
extern void fn_801F63E4(u32, u16);

static inline void applyTransition(void **model, register u32 flags)
{
    register float rate;
    register u32 masked;
    /* ASM: lfs and clrlwi preserve the load and flag truncation order;
     * C removes the redundant truncation for the 32-bit callee. */
    asm {
        lfs rate, lbl_8064EA08
        clrlwi masked, flags, 16
    }
    fn_80120AD0(*model, 0, 100, masked, rate, rate);
}

/* Rune selection screen update: once a rune has been picked, apply it to
 * the rune models; otherwise play the matching narration. */
void fn_800831B0(void)
{
    u8 buffer[8];
    Vec3 position;
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 zero;
    short *source;
    s8 chosen;
    u16 level;
    u32 sound;
    u16 flags;
    u32 j;
    char *strings = lbl_80244870;

    chosen = fn_801E75A4(lbl_8031CD84.mask, fn_801E8D34(lbl_8031CD84.range));
    if (lbl_8064C908 == 1)
        return;

    if (chosen == 4) {
        level = 0;
        sound = fn_801E741C(strings + 0x4DC);
        flags = 0x100;
        source = fn_80158CC8(fn_8015C4A4((void *)fn_801E741C(strings + 0x6E4), 2), 2, buffer);
        position.x = source[0];
        position.y = source[1];
        position.z = source[2];
        fn_80144680(lbl_8064C8E8);
        lbl_8031CBA0.screen = -1;
        fn_801E5FB0(lbl_8064C8EC);
        lbl_8064C8E8 = 0;
        lbl_8064C8EC = 0;
        fn_80144C40();
        lbl_8031CBA0.lastRune = chosen;
        switch (fn_800835CC(4)) {
        case 0:
            flags = 0x20;
            level = 1;
            break;
        case 1:
            flags = 0x8;
            level = 3;
            break;
        case 2:
            flags = 0x10;
            level = 2;
            break;
        }
        fn_801F63E4(sound, level);
        fn_801F6228(sound, 0, 2);
        for (j = 0; (int)j < 5; j++) {
            if (lbl_8031CD84.models[j] != 0) {
                if (chosen >= 0 && j == chosen - lbl_8031CD84.firstBit) {
                    zero = lbl_8023945C;
                    position.x += lbl_8064EABC;
                    third = zero;
                    second = zero;
                    first = zero;
                    fn_8012CBE8(lbl_8031CD84.models[j], 15, &first, &second, &third, 0);
                    fn_8011F0E8(lbl_8031CD84.models[j], &position);
                    position.x -= lbl_8064EABC;
                } else {
                    fn_8011F0E8(lbl_8031CD84.models[j], &position);
                }
                fn_80120AD0(lbl_8031CD84.models[j], 0, 100, 0, lbl_8064EA08, lbl_8064EA08);
                applyTransition(&lbl_8031CD84.models[j], flags | 0x202);
            }
        }
        fn_8016B400(0x89C, 0, 0);
        fn_801E8AC4(lbl_8031CD84.range);
        lbl_8031CD84.range = 0;
        return;
    }

    lbl_8064C908 = 1;
    if (chosen == 5) {
        lbl_8064C904 = fn_801B05E8(0x2D, 100, 4, 1, 0, 5, 0, 0);
        fn_80008C14((unsigned char *)strings + 0x78, 7, 2, 0x2D);
        return;
    }
    if (lbl_8064C90C == 0) {
        lbl_8064C904 = fn_801B05E8(0x2A, 100, 4, 1, 0, 5, 0, 0);
        fn_80008C14(lbl_8064B59C, 7, 1, 0x2A);
    } else if (lbl_8064C90C == 1) {
        lbl_8064C904 = fn_801B05E8(0x2B, 100, 4, 1, 0, 5, 0, 0);
        fn_80008C14((unsigned char *)strings + 0x58, 7, 4, 0x2B);
    } else if (lbl_8064C90C == 2) {
        lbl_8064C904 = fn_801B05E8(0x2C, 100, 4, 1, 0, 5, 0, 0);
        fn_80008C14(lbl_8064B5A4, 7, 1, 0x2C);
    }
    lbl_8064C90C = (lbl_8064C90C == 2) ? 0 : lbl_8064C90C + 1;
}
