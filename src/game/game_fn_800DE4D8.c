typedef unsigned int u32;

extern u32 lbl_8064F4FC;
extern u32 lbl_8064F500;
extern u32 lbl_802399A8[3];

extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8011EB04(void *);
extern unsigned int rand(void);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern int fn_801A98F4(int, int);

void fn_800DE4D8(void *object, int alternate)
{
    void *info = fn_80201814(object);
    void *data = info != 0 ? fn_80201BC8(info) : 0;

    if (info != 0 && data != 0) {
        int state = fn_8011EB04(data);

        if (state == 0x69) {
            if (alternate == 1) {
                u32 sounds[2];
                sounds[0] = lbl_8064F4FC;
                sounds[1] = lbl_8064F500;
                fn_801B05E8(sounds[rand() & 1], 80, 5, 1, 0, 5, 0, 0);
            } else if (alternate == 2) {
                fn_801B05E8(0x65, 80, 5, 1, 0, 5, 0, 0);
            }
        } else if (state == 0x6A) {
            if (alternate == 1) {
                u32 sounds[3];
                sounds[0] = lbl_802399A8[0];
                sounds[1] = lbl_802399A8[1];
                sounds[2] = lbl_802399A8[2];
                fn_801B05E8(sounds[rand() % 3], 80, 5, 1, 0, 5, 0, 0);
            } else if (alternate == 2) {
                fn_801A98F4(0x12A, 80);
            }
        }
    }
}
