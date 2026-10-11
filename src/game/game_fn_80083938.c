typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct MenuState {
    unsigned char pad[0x430];
    Vec3 *model;
    unsigned char pad434[8];
    int active;
} MenuState;
typedef struct GameState {
    unsigned char pad[0x1CD];
    signed char selectedItem;
} GameState;
typedef struct ShortVec3 { short x, y, z; } ShortVec3;

extern char lbl_80244870[];
extern MenuState lbl_8031CD84;
extern GameState lbl_8031CBA0;
extern float lbl_8064D7A0;
extern float lbl_8064EAC4, lbl_8064EAC8;
extern void fn_8011F114(Vec3 *, Vec3 *);
extern unsigned int fn_801E741C(const char *);
extern int fn_8015C4A4(void *, int);
extern void *fn_80158ABC(int, int, float *);
extern unsigned int fn_80178E94(const float *, const float *);
extern void fn_8007D744(int);
extern void fn_80083C18(int, int);
extern void fn_80144C40(void);

/* Select the first menu item within range of the current model. */
void fn_80083938(void)
{
    Vec3 position;
    Vec3 target;
    int item;
    int resource;
    ShortVec3 *point;
    char *names = lbl_80244870;

    fn_8011F114(&position, lbl_8031CD84.model);
    lbl_8064D7A0 = (lbl_8064EAC4 + position.x) / lbl_8064EAC8;
    for (item = 1; item <= 4; item++) {
        resource = -1;
        switch (item) {
        case 4:
            resource = fn_8015C4A4((void *)fn_801E741C(names + 0x548), 2);
            break;
        case 1:
            resource = fn_8015C4A4((void *)fn_801E741C(names + 0x554), 2);
            break;
        case 3:
            resource = fn_8015C4A4((void *)fn_801E741C(names + 0x6F4), 2);
            break;
        case 2:
            resource = fn_8015C4A4((void *)fn_801E741C(names + 0x700), 2);
            break;
        }
        if (resource != -1) {
            point = fn_80158ABC(resource, 2, 0);
            target.x = point->x;
            target.y = point->y;
            target.z = point->z;
            if (fn_80178E94(&position.x, &target.x) < 10U) {
                lbl_8031CBA0.selectedItem = item;
                fn_8007D744(3);
                if (lbl_8031CD84.active != 0 && item == 4) {
                    fn_80083C18(2, 0);
                }
                return;
            }
        }
    }
    if (lbl_8031CD84.active != 0) {
        fn_80144C40();
    }
    lbl_8031CBA0.selectedItem = -1;
    fn_8007D744(3);
}
