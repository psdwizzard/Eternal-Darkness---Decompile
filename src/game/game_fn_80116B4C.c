typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef union Color { u32 value; struct { u8 r, g, b, a; } channel; } Color;
typedef struct Pos { short x, y; } Pos;
typedef struct PosList { Pos p[5]; } PosList;
typedef struct Glyphs { signed char c[4]; } Glyphs;

extern unsigned int lbl_80331748[];
extern char *lbl_8024DCF0[];
extern char lbl_8024E260[];
extern char lbl_8064B978[8];
extern char lbl_8064B980[8];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern const Glyphs lbl_8064FF94;
extern const float lbl_8064FF7C;
extern const float lbl_8064FF8C;
extern const float lbl_8064FF98;

extern void fn_801A852C(u32 *, int, u16, u32);
extern void fn_801A9118(int, int, void *);
extern void fn_801E3AA4(int);
extern signed char fn_801E5AD0(signed char);
extern u32 fn_801E3A34(Color *);
extern void fn_801E5430(short, short);
extern void fn_801E56AC(float, const char *, ...);
extern int fn_801E75A4(unsigned int, int);
extern void fn_801ED5F4(int, int, short, float *, float (*)[4], float);
extern int fn_80113E48(unsigned int);
typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern unsigned int fn_8020216C(Object8020216C *);

void fn_80116B4C(void)
{
    /* Screen positions for the five assigned spells. */
    PosList pos = {{
        {0x20F, 0xB7},
        {0x176, 0xBB},
        {0x176, 0x13B},
        {0x136, 0xFC},
        {0x1B3, 0xFC}
    }};
    Glyphs glyphs;
    Color icon0, icon1, icon2, icon3, text;
    unsigned int *slot;
    Pos *p;
    int i;
    int index;
    char *name;
    int type;
    int flags;

    icon0 = lbl_8064C2A8;
    fn_801A852C(&icon0.value, 0, 0xD, 0x80000000);
    fn_801A9118(0, 0x13C, (void *)5);
    icon1 = lbl_8064C2A8;
    fn_801A852C(&icon1.value, 0, 0x37, 0x80000000);
    fn_801A9118(0, 0x1A0, (void *)5);
    icon2 = lbl_8064C2A8;
    fn_801A852C(&icon2.value, 0, 0x38, 0x80000000);
    fn_801A9118(0, 0x1A4, (void *)5);
    icon3 = lbl_8064C2A8;
    fn_801A852C(&icon3.value, 0, 0x36, 0x80000000);
    fn_801A9118(0, 0x1A8, (void *)5);
    fn_801A9118(0, 0x1AC, (void *)5);
    fn_801A9118(0, 0x1B0, (void *)5);
    fn_801A9118(0, 0x1B4, (void *)5);
    fn_801A9118(0, 0x1B8, (void *)5);
    fn_801E3AA4(0);
    fn_801E5AD0(0x63);

    for (i = 0; i < 5; i++) {
        slot = &lbl_80331748[i];
        p = &pos.p[i];
        text = lbl_8064C2B0;
        fn_801E3A34(&text);
        if (slot[0x26] != 0) {
            index = fn_80113E48(slot[0x26]);
            if (index != -1) {
                glyphs = lbl_8064FF94;
                name = (char *)fn_801E75A4(slot[0x26] & 0x70000, 0) + 0x2C;
                type = fn_801E75A4(slot[0x26] & 0xF, 0);
                flags = 0x40;
                fn_801E5430(p->x, p->y);
                if ((lbl_80331748[index + 2] & 0x08000000) || (fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000)) {
                    fn_801E56AC(lbl_8064FF8C, lbl_8024DCF0[index]);
                } else {
                    fn_801E56AC(lbl_8064FF8C, lbl_8024E260, index + 1);
                }
                fn_801E5430(p->x, p->y + 0x28);
                switch (type) {
                case 0:
                    flags = 0x20;
                    break;
                case 1:
                    flags = 8;
                    break;
                case 2:
                    flags = 0x10;
                    break;
                }
                fn_801ED5F4(1, flags | 0x402, 1, 0, 0, lbl_8064FF7C);
                fn_801E56AC(lbl_8064FF98, lbl_8064B978, glyphs.c[type], name);
                fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064FF7C);
            } else {
                fn_801E5430(p->x, p->y + 0x28);
                fn_801E56AC(lbl_8064FF8C, lbl_8064B980);
            }
        } else {
            fn_801E5430(p->x, p->y + 0x28);
            fn_801E56AC(lbl_8064FF8C, lbl_8064B980);
        }
    }
}
