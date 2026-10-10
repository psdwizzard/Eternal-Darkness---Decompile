typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ModeState { u8 pad[8]; int mode; } ModeState;
typedef struct GameState {
    u8 pad0[0x1CB];
    s8 screen; /* 0x1CB */
    s8 selectionState; /* 0x1CC */
    s8 selectedItem; /* 0x1CD */
    s8 selections[18]; /* 0x1CE */
} GameState;
typedef struct MenuState {
    u8 pad0[0x610];
    void *range; /* 0x610 */
    void *models[5]; /* 0x614 */
    u32 mask; /* 0x628 */
    u32 firstBit; /* 0x62C */
} MenuState;

extern Vec3 lbl_80239450;
extern int lbl_80244880[];
extern char lbl_80244F54[];
extern ModeState lbl_803003C8;
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern void *lbl_8064C8E8, *lbl_8064C8EC;
extern int lbl_8064D18C;
extern float lbl_8064EABC;

extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_8012CBE8(void *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_80144680(void *);
extern void fn_80144C40(void);
extern void *fn_80158CC8(int, int, void *);
extern int fn_8015C4A4(void *, int);
extern void fn_8016B400(int, int, int);
extern void fn_801E5FB0(void *);
extern u32 fn_801E741C(const char *);
extern int fn_801E75A4(u32, int);
extern void fn_801E8AC4(void *);
extern int fn_801E8D34(void *);

/* Close the rune selection screen: store the chosen rune for the current
 * chapter, redraw the rune models and release the selection range. */
void fn_80082EDC(short confirmed)
{
    u8 buffer[8];
    Vec3 position;
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 zero;
    short *source;
    s8 chosen;
    s8 selection;
    int alternate;
    int *chapters;
    GameState *saved;
    int chapter;
    int i;
    u32 j;

    chosen = fn_801E75A4(lbl_8031CD84.mask, fn_801E8D34(lbl_8031CD84.range));
    selection = -1;
    alternate = 0;
    if (lbl_803003C8.mode == 9) alternate = 1;
    source = fn_80158CC8(fn_8015C4A4((void *)fn_801E741C(lbl_80244F54), 2), 2, buffer);
    position.x = source[0];
    position.y = source[1];
    position.z = source[2];
    fn_80144680(lbl_8064C8E8);
    lbl_8031CBA0.screen = -1;
    fn_801E5FB0(lbl_8064C8EC);
    lbl_8064C8E8 = 0;
    lbl_8064C8EC = 0;
    fn_80144C40();
    chapters = lbl_80244880 + alternate;
    saved = (GameState *)((u8 *)&lbl_8031CBA0 + alternate);
    chapter = lbl_8064D18C;
    for (i = 0; i < 9; i++) {
        if (chapter == *chapters) {
            if (confirmed == 0)
                saved->selections[0] = chosen;
            selection = saved->selections[0];
        }
        chapters += 2;
        saved = (GameState *)((u8 *)saved + 2);
    }
    for (j = 0; (int)j < 5; j++) {
        if (lbl_8031CD84.models[j] != 0) {
            if (selection >= 0 && j == selection - lbl_8031CD84.firstBit) {
                zero = lbl_80239450;
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
        }
    }
    if (confirmed == 0) {
        fn_8016B400(0x89C, 0, 0);
    } else if (confirmed == 1) {
        fn_8016B400(0x822, 0, 0);
    }
    fn_801E8AC4(lbl_8031CD84.range);
    lbl_8031CD84.range = 0;
}
