typedef signed short s16;
typedef unsigned char u8;

typedef struct Entry {
    u8 pad0[8];
    void (*callback)(void);
    u8 padC[6];
    s16 value;
    u8 pad14[12];
} Entry;

extern Entry lbl_806079C0[];
extern void fn_801A5F40(void);
extern void fn_801A5F54(void);

void fn_801A5910(int enabled)
{
    int i;

    for (i = 0; i < 9; i++) {
        if (lbl_806079C0[i].callback == fn_801A5F40 ||
            lbl_806079C0[i].callback == fn_801A5F54) {
            if (enabled) {
                lbl_806079C0[i].value = -72;
            } else {
                lbl_806079C0[i].value = 72;
            }
        }
    }
}
