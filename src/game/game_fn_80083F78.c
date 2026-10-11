typedef unsigned char u8;
typedef signed char s8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;
typedef struct ObjectState {
    u8 pad[0x6c];
    void (*update)(void *);
    u8 pad70[4];
    struct ObjectState *child;
} ObjectState;
typedef struct GameState {
    u8 pad[0x1cb];
    s8 screen;
    s8 selectionState;
    s8 selectedItem;
} GameState;
typedef struct MenuState {
    u8 pad[0x430];
    void *model430;
    ObjectState *object;
    void *value438;
    int value43C;
    int value440;
} MenuState;

extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern char lbl_80244DB8[];
extern void *lbl_8064C8E8, *lbl_8064C8EC;
extern void fn_80083B10(int, int);
extern void fn_8011E310(int, int, int, int, int, int, int);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_80144680(void *);
extern void fn_80144C40(void);
extern Vec3s *fn_80158ABC(int, int, void *);
extern int fn_8015C4A4(void *, int);
extern void fn_8016B400(int, int, int);
extern void fn_801A9964(void *);
extern void fn_801E5FB0(void *);
extern unsigned int fn_801E741C(const char *);
extern void fn_801F85A4(void);

void fn_80083F78(int unused, int event)
{
    int selection = 0x39;
    Vec3 copy;
    Vec3 position;
    Vec3s *limit;

    if (event == 1) {
        if (lbl_8031CD84.value43C != 0) {
            limit = fn_80158ABC(fn_8015C4A4((void *)fn_801E741C(lbl_80244DB8), 2), 2, 0);
            fn_8011F114(&position, lbl_8031CD84.model430);
            copy = position;
            if (copy.x > (float)limit->x) {
                fn_80083B10(-1, 0);
            } else {
                fn_80083B10(1, 0);
            }
        }
        if (lbl_8031CD84.value440 == 2) {
            fn_80144680(lbl_8064C8E8);
            lbl_8031CBA0.screen = -1;
            lbl_8064C8E8 = 0;
            fn_801E5FB0(lbl_8064C8EC);
            lbl_8064C8EC = 0;
            fn_801F85A4();
            lbl_8031CD84.object->update = 0;
            lbl_8031CD84.object->child->update = 0;
            if (lbl_8031CD84.value438 != 0) {
                fn_801A9964(lbl_8031CD84.value438);
                lbl_8031CD84.value438 = 0;
            }
            fn_8016B400(0xbc, 0, 0);
            fn_80144C40();
        } else {
            if (lbl_8031CBA0.selectedItem != -1) {
                selection = 0x19;
            }
            if (lbl_8031CD84.value440 == 0 && lbl_8031CD84.value438 != 0) {
                fn_801A9964(lbl_8031CD84.value438);
                lbl_8031CD84.value438 = 0;
            }
            lbl_8031CD84.value440 = 0;
        }
        fn_8011E310(2, selection, 0, 0, 0x32, 0, 0);
    }
}
