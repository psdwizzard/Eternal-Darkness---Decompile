typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed long s32;
typedef signed char s8;
typedef union Color { u32 value; struct { u8 r, g, b, a; } channel; } Color;
typedef struct RangeControl RangeControl;
typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;

extern unsigned int lbl_80331748[];
extern RangeControl *lbl_80331A08[];
extern char *lbl_8024DCF0[];
extern char lbl_8024E254[];
extern char lbl_8064B964[8];
extern char lbl_8064B96C[8];
extern char lbl_8064B974[8];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern Color lbl_8064C2BC;
extern const Color lbl_8064FF84;
extern const Color lbl_8064FF88;
extern const float lbl_8064FF7C;
extern const float lbl_8064FF8C;

extern int fn_801E8D3C(RangeControl *);
extern int fn_801E8D34(RangeControl *);
extern void fn_801A852C(u32 *, int, u16, u32);
extern void fn_801A9118(s32, s32, void *);
extern void fn_801A8974(s32, s32, s32, s32, s32, s32);
extern void fn_801A872C(s32, s32, s32, s32, s32, s32, const u32 *);
extern void fn_801E3AA4(int);
extern s8 fn_801E5AD0(s8);
extern u32 fn_801E3A34(Color *);
extern void fn_801E5430(short, short);
extern void fn_801E56AC(float, const char *, ...);
extern int fn_801E76E0(unsigned int);
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern unsigned int fn_8020216C(Object8020216C *);

static inline u32 CurrentObjectFlags(void)
{
    /* The manager returns the intrusive-list entry at the start of the object. */
    return fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44()));
}

static inline void SetDescriptorColor(Color color, int index, u16 replacement, u32 word6)
{
    fn_801A852C(&color.value, index, replacement, word6);
}

static inline void SetTextColor(Color color)
{
    fn_801E3A34(&color);
}

static inline void DrawColoredFrame(s32 x, s32 y, s32 width, s32 height,
                                    s32 depth, s32 inset, Color color)
{
    fn_801A872C(x, y, width, height, depth, inset, &color.value);
}

static inline Color WithAlpha(Color color, u8 alpha)
{
    color.channel.a = alpha;
    return color;
}

void fn_80116490(int compact, int showLabel, u8 alpha)
{
    int limit;
    int i;
    int base;
    int index;

    base = fn_801E8D3C(lbl_80331A08[5]) * 3;
    index = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);

    SetDescriptorColor(lbl_8064C2A8, 0, 5, 0x80000000);
    fn_801A9118(0, 0x68, (void *)5);
    SetDescriptorColor(lbl_8064C2A8, 0, 2, 0x80000000);

    if ((lbl_80331748[index + 2] & 0x04000000) || (CurrentObjectFlags() & 0x4000)) {
        fn_801A9118(0x3C, 0x6C, (void *)5);
        fn_801A9118(0x40, 0x70, (void *)5);
    }
    if ((lbl_80331748[index + 2] & 0x0C000000) || (CurrentObjectFlags() & 0x4000)) {
        fn_801A9118(0x44, 0x74, (void *)5);
    }
    SetDescriptorColor(lbl_8064FF84, 5, 3, 0x80000000);

    limit = 12 - base;
    for (i = 0; i < (limit > 9 ? 9 : limit); i++) {
        u16 coordinate = i + 0x3D;
        coordinate *= 4;
        fn_801A9118(0, coordinate, (void *)5);
    }

    if (compact) {
        fn_801A8974((short)((index - base) % 3 * 75 + 0x130), (short)((index - base) / 3 * 75 + 0x8C), 0x40, 0x40, -0x7698, 2);
    } else {
        DrawColoredFrame((short)((index - base) % 3 * 75 + 0x130), (short)((index - base) / 3 * 75 + 0x8C), 0x40, 0x40, -0x7698, 2, lbl_8064C2BC);
        fn_801E3AA4(0);
        fn_801E5AD0(0x63);
    }
    fn_801E3AA4(0);
    fn_801E5AD0(0x63);

    SetTextColor(WithAlpha(lbl_8064FF88, alpha));

    if (fn_801E8D3C(lbl_80331A08[5]) != 0) {
        fn_801E5430(0x225, 0xD7);
        fn_801E56AC(lbl_8064FF7C, lbl_8064B964);
    }
    if (fn_801E8D3C(lbl_80331A08[5]) * 3 + 9 < 12) {
        fn_801E5430(0x225, 0x100);
        fn_801E56AC(lbl_8064FF7C, lbl_8064B96C);
    }

    if (showLabel) {
        fn_801E76E0(lbl_80331748[index + 2] & 0x70000);
        SetTextColor(lbl_8064C2B0);
        fn_801E5430((short)((index - base) % 3 * 75 + 0x150), (short)((index - base) / 3 * 75 + 0x64));
        if (lbl_80331748[index + 2] == 0) {
            if ((CurrentObjectFlags() & 0x4000) == 0) {
                return;
            }
        }
        if ((lbl_80331748[index + 2] & 0x08000000) || (CurrentObjectFlags() & 0x4000)) {
            fn_801E56AC(lbl_8064FF8C, lbl_8064B974, lbl_8024DCF0[index]);
        } else {
            fn_801E56AC(lbl_8064FF8C, lbl_8024E254, index + 1);
        }
    }
}
