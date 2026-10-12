typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef union Color {
    u32 value;
    struct { u8 r, g, b, a; } channel;
} Color;

typedef struct RangeControl {
    int minimum, maximum, window, value;
} RangeControl;

typedef struct NamePair {
    const char *top;
    const char *bottom;
} NamePair;

/* View of the menu data pool, including the adjacent name tables and title. */
typedef struct MenuData {
    u8 textures[0x310];
    u8 textureList[0xAF8];
    const char *upperNames[3]; /* 0xE08 */
    u8 reserved[0x174];
    NamePair slotNames[14];   /* 0xF88 */
    u8 reserved2[0x40C];
    char upperTitle[0x10];      /* 0x1404 */
} MenuData;

extern MenuData lbl_8024CE40[];
extern RangeControl *lbl_80331A08[];
extern Color lbl_8064B8D8;
extern Color lbl_8064B8DC;
extern char lbl_8064B95C[4];
extern char lbl_8064B960[4];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern Color lbl_8064C2B8;
extern u32 lbl_8064CD2C;
extern u32 lbl_8064CD48;
extern u32 lbl_8064CD4C;
extern u32 lbl_8064CD80;
extern const float lbl_8064FF78;
extern const float lbl_8064FF7C;

extern int fn_801E8D34(RangeControl *);
extern void fn_801A90BC(void *, void *);
extern void fn_801A852C(u32 *, int, u16, u32);
extern void fn_801A9118(int, int, void *);
extern void fn_801A8974(int, int, int, int, int, int);
extern void fn_801A8D38(int);
extern void fn_801E3AA4(int);
extern u32 fn_801E3A34(Color *);
extern s8 fn_801E5AD0(s8);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(float, const char *, ...);
extern u32 fn_801ED3F4(u32);
extern void fn_801ED5F4(int, int, s16, float *, float (*)[4], float);
typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern u32 fn_8020216C(Object8020216C *);

void fn_801157B4(void)
{
    register MenuData *menu;
    register u32 poolHigh;
    register RangeControl *rowControl;
    register void *image;
    int row;
    int selected;
    int i;
    s16 upperX;
    const char **names;
    s16 x, y;
    int position;
    int texture;
    u32 available;
    int mode;
    Color upperBackground;
    Color upperText;
    Color upperIcon;
    Color background;
    Color icon;
    Color frame;
    Color knownIcon;
    Color knownFrame;
    Color unknownIcon;
    Color unknownFrame;
    Color text;

    /* ASM: lis, lis, addi, addi and lwz keep the control lookup and pooled
     * address setup interleaved; C initializes the pointers separately. */
    asm {
        lis rowControl, lbl_80331A08@ha
        lis poolHigh, lbl_8024CE40@ha
        addi rowControl, rowControl, lbl_80331A08@l
        addi menu, poolHigh, lbl_8024CE40@l
        lwz rowControl, 0x20(rowControl)
    }
    row = fn_801E8D34(rowControl) * 5;
    selected = fn_801E8D34(lbl_80331A08[7]) + ((0 > row - 2) ? 0 : row - 2);
    if (selected > 7) {
        selected--;
    }
    /* ASM: addi preserves the zero-offset pooled array address;
     * MWCC replaces the equivalent C address expression with mr. */
    asm { addi image, menu, 0 }
    fn_801A90BC(image, menu->textureList);

    for (i = 0, upperX = 0x114, names = menu->upperNames;
         i < 3; i++, upperX += 0x37, names++) {
        upperBackground = lbl_8064C2A8;
        fn_801A852C(&upperBackground.value, 0, 6, 0x80000000);
        fn_801A9118(0, ((i + 0x1E) * 4) & 0xFFFF, (void *)5);
        if (!(lbl_8064CD2C & 1)) {
            if (i == selected) {
                fn_801A8974(upperX, 0x86, 0x2E, 0x2E, -0x7698, 2);
                fn_801E3AA4(0);
                upperText = lbl_8064C2B0;
                fn_801E3A34(&upperText);
                fn_801E5AD0(99);
                if ((fn_8020216C((Object8020216C *)
                        fn_80201814(fn_80201B44())) & 0x4000) ||
                    ((0x10000 << i) & lbl_8064CD48)) {
                    fn_801E5430(upperX + 0x1A, 0x68);
                    fn_801E56AC(lbl_8064FF78, menu->upperTitle);
                    fn_801E5430(upperX + 0x1A, 0xB8);
                    fn_801E56AC(lbl_8064FF78, *names);
                }
                fn_801ED3F4(lbl_8064CD80);
                /* ASM: addi preserves the zero-offset pooled array address;
                 * MWCC replaces the equivalent C address expression with mr. */
                asm { addi image, menu, 0 }
                fn_801A90BC(image, menu->textureList);
            }
            if ((fn_8020216C((Object8020216C *)
                        fn_80201814(fn_80201B44())) & 0x4000) ||
                ((0x10000 << i) & lbl_8064CD48)) {
                upperIcon = lbl_8064C2A8;
                fn_801A852C(&upperIcon.value, 0, i + 0x58, 0x80000000);
                fn_801A9118(0, ((i + 0x72) * 4) & 0xFFFF, (void *)5);
            }
        }
    }

    for (i = 0, names = (const char **)menu->slotNames; i < 14; i++, names += 2) {
        position = i;
        if (i >= 4) {
            position = i + 1;
        }
        x = (position % 5) * 0x37 + 0x114;
        y = (position / 5) * 0x4D + 0xD8;
        lbl_8064B8DC.channel.a = 0xFF;
        background = lbl_8064C2A8;
        fn_801A852C(&background.value, 0, 6, 0x80000000);
        texture = (i + 0x21) * 4;
        fn_801A9118(0, ((i + 0x21) * 4) & 0xFFFC, (void *)5);
        if (!(lbl_8064CD2C & 2)) {
            if ((fn_8020216C((Object8020216C *)
                        fn_80201814(fn_80201B44())) & 0x4000) ||
                ((available = lbl_8064CD4C & (0x10000 << i)) &&
                 (lbl_8064CD4C & (1 << i)))) {
                int source;
                icon = lbl_8064B8D8;
                fn_801A852C(&icon.value, 5, 0xE, 0x80000000);
                source = (i + 1) * 4;
                fn_801A9118(((i + 1) * 4) & 0xFFFC, (u16)texture, (void *)5);
                if (i < 4) {
                    mode = 0x40;
                    switch (i) {
                    case 0:
                        mode = 0x20;
                        break;
                    case 1:
                        mode = 8;
                        break;
                    case 2:
                        mode = 0x10;
                        break;
                    }
                    fn_801ED5F4(1, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
                } else {
                    fn_801ED5F4(1, 0x8500, 1, 0, 0, lbl_8064FF7C);
                }
                frame = lbl_8064C2B8;
                fn_801A852C(&frame.value, 0, 0xF, 0x80000000);
                fn_801A9118(source & 0xFFFF, texture & 0xFFFF, (void *)5);
                fn_801ED5F4(0, 0x8000, 1, 0, 0, lbl_8064FF7C);
                fn_801A8D38(5);
            } else if (lbl_8064CD4C & (1 << i)) {
                int source;
                knownIcon = lbl_8064B8D8;
                fn_801A852C(&knownIcon.value, 5, 0xE, 0x80000000);
                source = (i + 1) * 4;
                fn_801A9118(((i + 1) * 4) & 0xFFFC, (u16)texture, (void *)5);
                knownFrame = lbl_8064B8DC;
                fn_801A852C(&knownFrame.value, 0, 0xF, 0x80000000);
                fn_801A9118(source & 0xFFFF, texture & 0xFFFF, (void *)5);
            } else if (available != 0) {
                unknownIcon = lbl_8064C2A8;
                fn_801A852C(&unknownIcon.value, 0, 0x10, 0x80000000);
                fn_801A9118(0, (u16)texture, (void *)5);
                unknownFrame = lbl_8064C2B8;
                fn_801A852C(&unknownFrame.value, 0, 0xF, 0x80000000);
                fn_801A9118(((i + 1) * 4) & 0xFFFF, ((i + 0x2F) * 4) & 0xFFFF, (void *)5);
            }
            if (i + 3 == selected) {
                fn_801A8974(x, y, 0x2E, 0x2E, -0x7698, 2);
                fn_801E3AA4(0);
                text = lbl_8064C2B0;
                fn_801E3A34(&text);
                fn_801E5AD0(99);
                fn_801E5430(x + 0x17, y + 0x32);
                if (lbl_8064CD4C & (0x10000 << i)) {
                    fn_801E56AC(lbl_8064FF78, names[1]);
                    fn_801E5430(x + 0x17, y - 0x1E);
                    fn_801E56AC(lbl_8064FF78, names[0]);
                } else if (lbl_8064CD4C & (1 << i)) {
                    if (i >= 4) {
                        fn_801E56AC(lbl_8064FF78, lbl_8064B95C);
                    }
                    fn_801E5430(x + 0x17, y - 0x1E);
                    fn_801E56AC(lbl_8064FF78, lbl_8064B960);
                }
                fn_801ED3F4(lbl_8064CD80);
                /* ASM: addi preserves the zero-offset pooled array address;
                 * MWCC replaces the equivalent C address expression with mr. */
                asm { addi image, menu, 0 }
                fn_801A90BC(image, menu->textureList);
            }
        }
    }
}
