typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long ulong;
typedef float Matrix34[3][4];
typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;

/* Qualifiers agree with game_data_8023A414.c. */
extern const volatile u32 lbl_8023A414[12];
extern ulong lbl_8064B8D8;
extern ulong lbl_8064C2B8;
extern int lbl_8064CD34;
extern int lbl_8064CD44;
extern u32 lbl_8064CD4C;
extern const float lbl_8064FF7C;
extern const ulong lbl_8064FF90;

extern void fn_801A852C(ulong *, int, u16, ulong);
extern void fn_801A8D38(int);
/* Match game_fn_801A9118.c: the third argument is void *, despite
 * integer declarations in some callers. Selector 5 is forwarded to
 * fn_80226AB4 without being dereferenced. */
extern void fn_801A9118(long, long, void *);
extern int fn_801E75A4(u32, int);
extern void fn_801ED5F4(int, int, short, float *, Matrix34, float);
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern u32 fn_8020216C(Object8020216C *);

void fn_801168EC(u32 excluded, int first, int count)
{
    int i;
    int index;
    int row;
    int next;
    ulong color;
    ulong specialColor;
    ulong normalColor;

    for (i = 0; i < count; i++) {
        index = fn_801E75A4(lbl_8064CD4C & ~excluded, i);
        if (index == -1 || index >= 14)
            break;
        row = i - first;
        if (row >= 0) {
            color = lbl_8064B8D8;
            fn_801A852C(&color, 5, 14, 0x80000000);
            next = index + 1;
            /* All three draws truncate coordinates to 16 bits. Using a mask
             * here and u16 casts below keeps the full products available
             * across calls in MWCC, matching the retail register allocation. */
            fn_801A9118((next * 4) & 0xFFFF, (row * 4) & 0xFFFF, (void *)5);
            if ((fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000) ||
                (lbl_8064CD4C & (0x10000 << index))) {
                if (index < 4) {
                    switch (index) {
                    case 0:
                        fn_801ED5F4(1, 0x8420, 1, 0, 0, lbl_8064FF7C);
                        break;
                    case 1:
                        fn_801ED5F4(1, 0x8408, 1, 0, 0, lbl_8064FF7C);
                        break;
                    case 2:
                        fn_801ED5F4(1, 0x8410, 1, 0, 0, lbl_8064FF7C);
                        break;
                    case 3:
                        if (lbl_8064CD44 == 2 ||
                            (lbl_8023A414[lbl_8064CD34] & 0x1FF0) != 0x820) {
                            fn_801ED5F4(1, 0x8440, 1, 0, 0, lbl_8064FF7C);
                        } else {
                            specialColor = lbl_8064FF90;
                            fn_801A852C(&specialColor, 0, 15, 0x80000000);
                            fn_801A9118((u16)(next * 4), (u16)(row * 4), (void *)5);
                            return;
                        }
                        break;
                    }
                } else {
                    fn_801ED5F4(1, 0x8500, 1, 0, 0, lbl_8064FF7C);
                }
            }
            normalColor = lbl_8064C2B8;
            fn_801A852C(&normalColor, 0, 15, 0x80000000);
            fn_801A9118((u16)(next * 4), (u16)(row * 4), (void *)5);
            fn_801ED5F4(0, 0x8000, 1, 0, 0, lbl_8064FF7C);
            fn_801A8D38(5);
        }
    }
}
