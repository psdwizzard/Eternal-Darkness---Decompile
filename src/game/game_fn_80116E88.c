typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef union Color { u32 value; struct { u8 r, g, b, a; } channel; } Color;
typedef struct BoundsCamera {
    float min_x, min_y, unused_8;
    float max_x, max_y, unused_14;
    float eye[3];
    float unused_24[3];
    float projection;
} BoundsCamera;
typedef struct RangeControl { int minimum, maximum, window, value; } RangeControl;
typedef struct TextDescriptor TextDescriptor;

/* Menu data block at 0x8024CE40 (texture lists, name tables, format strings). */
typedef struct MenuData {
    u8 textures[0x310];        /* 0x000 */
    u8 textureList[0xAF8];     /* 0x310 */
    char *bitNames[3];         /* 0xE08: indexed by bit number - 16 */
    u8 padE14[0x9C];           /* 0xE14 */
    char *bookNames[12];       /* 0xEB0 */
    u8 padEE0[0x54C];          /* 0xEE0 */
    char bookNameFmt[0x28];    /* 0x142C */
    char bitFmt[0x18];         /* 0x1454 */
    char runeFmt[0x14];        /* 0x146C */
    char pageFmt[0xC];         /* 0x1480 */
    char bookIndexFmt[0x24];   /* 0x148C */
    char exitFmt[0x24];           /* 0x14B0 */
} MenuData;

extern MenuData lbl_8024CE40[];
/* Journal state block at 0x80331748. */
typedef struct JournalState {
    unsigned int header[2];          /* 0x00 */
    unsigned int chapterFlags[24];   /* 0x08 */
    unsigned int bookFlags[12];      /* 0x68 */
} JournalState;

extern JournalState lbl_80331748;
extern RangeControl *lbl_80331A08[];
extern const volatile unsigned int lbl_8023A414[12];
extern char lbl_8064B988[3];
extern char lbl_8064B98C[3];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern Color lbl_8064C2BC;
extern void *lbl_8064C508;
extern unsigned char lbl_8064CD28;
extern int lbl_8064CD44;
extern unsigned int lbl_8064CD48;
extern unsigned int lbl_8064CD4C;
extern unsigned int lbl_8064CD50;
extern unsigned int lbl_8064CD54;
extern unsigned int lbl_8064CD60;
extern int lbl_8064CD68;
extern int lbl_8064CD6C;
extern u32 lbl_8064CD80;
extern TextDescriptor *lbl_8064CDB0;
extern TextDescriptor *lbl_8064CDB4;
extern unsigned int lbl_8064CCD8;
extern const float lbl_8064FF78;
extern const float lbl_8064FF7C;

extern int fn_801E8D34(RangeControl *);
extern int fn_801E8D3C(RangeControl *);
extern int fn_801E8D44(RangeControl *);
extern int fn_801E8D24(RangeControl *);
extern int fn_801E75A4(unsigned int, int);
extern unsigned int fn_801E7578(unsigned int);
extern void fn_80119224(int, u8);
extern void fn_801F683C(BoundsCamera *);
extern void fn_801F03F0(BoundsCamera *, int);
extern void fn_80156C04(void);
extern void fn_801882C4(void);
extern void fn_80156CBC(void);
extern void fn_801882D0(void);
extern u32 fn_801ED3F4(u32);
extern void fn_801A8D38(int);
extern void fn_801A90BC(void *, void *);
extern void fn_801A872C(int, int, int, int, int, int, const u32 *);
extern void fn_801A8974(int, int, int, int, int, int);
extern void fn_801A852C(u32 *, int, int, u32);
extern void fn_801A9118(int, u16, void *);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void fn_80115D8C(u32, int, u8);
extern void fn_801E3AA4(int);
extern s8 fn_801E5AD0(s8);
extern u32 fn_801E3A34(Color *);
extern void fn_801E5430(short, short);
extern void fn_801E56AC(float, const char *, ...);
extern void fn_801156D0(int);
extern void fn_801157B4(void);
extern void fn_80116490(int, int, u8);
extern void fn_80116838(int, int);
extern void fn_801168EC(int, int, int);
extern void fn_80116B4C(void);
extern unsigned int fn_80113CF8(unsigned int);
extern int fn_80113E48(unsigned int);
typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern unsigned int fn_8020216C(Object8020216C *);

void fn_80116E88(u8 alpha)
{
    BoundsCamera copy;
    BoundsCamera source;
    Color highlight0, highlight1, highlight2, highlight3;
    Color bookText, powerIcon, powerText, alignmentText, runeText;
    Color discoveredText, chapterIcon, chapterPageIcon, assignedIcon, assignmentText;
    int runeCount;
    int symbolMask;
    unsigned int i;
    int count;
    int sel;
    int max;
    int page;
    int total;
    int idx;
    unsigned int mask;
    register MenuData *data = lbl_8024CE40;
    register void *textures;
    register void *textureList;
    register char **names;
    register int bookIndex;
    register u32 bitNameAddress;
    register u32 bitBase;
    register u32 bookBase;

    runeCount = fn_801E75A4(lbl_8064CD4C & 0xF, fn_801E8D34(lbl_80331A08[2]));
    symbolMask = fn_801E75A4(lbl_8064CD4C & 0x3FF0, fn_801E8D34(lbl_80331A08[3]));
    fn_80119224(3, alpha);
    fn_801F683C(&source);
    copy = source;
    fn_801F03F0(&copy, 0);
    fn_80156C04();
    fn_801882C4();
    fn_80156CBC();
    fn_801882D0();
    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(5);
    /* ASM: addi preserves the pooled zero-offset address; C reduces it to mr. */
    asm {
        addi textures, data, 0
        addi textureList, data, 0x310
    }
    fn_801A90BC(textures, textureList);

    if (lbl_8064CD44 != 0) {
        switch (fn_801E8D34(lbl_80331A08[0])) {
        case 0:
            highlight0 = lbl_8064C2BC;
            fn_801A872C(0xAE, 0xB4, 0x50, 0x2C, -0x7698, 2, &highlight0.value);
            break;
        case 1:
            highlight1 = lbl_8064C2BC;
            fn_801A872C(0xA7, 0xF8, 0x50, 0x2C, -0x7698, 2, &highlight1.value);
            break;
        case 2:
            highlight2 = lbl_8064C2BC;
            fn_801A872C(0xAD, 0x13B, 0x50, 0x2C, -0x7698, 2, &highlight2.value);
            break;
        case 3:
            highlight3 = lbl_8064C2BC;
            fn_801A872C(0xA7, 0x17F, 0x50, 0x2C, -0x7698, 2, &highlight3.value);
            break;
        }
    }

    switch (lbl_8064CD44) {
    case 17:
        max = ((lbl_80331748.bookFlags[lbl_8064CD6C] & 0xF) << 1) + 3;
        fn_80115D8C(lbl_80331748.bookFlags[lbl_8064CD6C],
                    (lbl_8064CD68 < max ? lbl_8064CD68 : max) > 0 ? (lbl_8064CD68 < max ? lbl_8064CD68 : max) : 0,
                    0xFF);
        fn_801E3AA4(0);
        fn_801E5AD0(0x63);
        bookText = lbl_8064C2B0;
        fn_801E3A34(&bookText);
        switch (max) {
        case 3:
            fn_801E5430(0x19D, 0x50);
            break;
        case 5:
            fn_801E5430(0x1A2, 0x32);
            break;
        case 7:
            fn_801E5430(0x1A2, 0x32);
            break;
        }
        /* ASM: lwz and addi retain the index-load order and separate table base;
         * C folds the table offset into the indexed load. */
        asm {
            lwz bookIndex, lbl_8064CD6C
            addi names, data, 0xEB0
        }
        fn_801E56AC(lbl_8064FF78, data->bookNameFmt, names[bookIndex]);
        break;
    case 0:
        sel = fn_801E8D34(lbl_80331A08[0]);
        if (lbl_8064CCD8 != 0) {
            sel = fn_801E75A4(lbl_8064CCD8, 0);
        }
        switch (sel) {
        case 0:
            fn_801A8974(0xAE, 0xB4, 0x50, 0x2C, -0x7698, 2);
            break;
        case 1:
            fn_801A8974(0xA7, 0xF8, 0x50, 0x2C, -0x7698, 2);
            break;
        case 2:
            fn_801A8974(0xAD, 0x13B, 0x50, 0x2C, -0x7698, 2);
            break;
        case 3:
            fn_801A8974(0xA7, 0x17F, 0x50, 0x2C, -0x7698, 2);
            break;
        }
        if (lbl_8064CCD8 == 0) {
            if (lbl_8064CDB4 == 0) {
                lbl_8064CDB4 = fn_801E6CA0(lbl_8064C508, 1, 8, 0, 1);
            }
            if (lbl_8064CDB0 == 0) {
                lbl_8064CDB0 = fn_801E6CA0(lbl_8064C508, 1, 5, 0, 1);
            }
        }
        break;
    case 1:
        lbl_8064CD60 = lbl_8064CD48;
    case 10:
    case 12:
    case 25:
        count = 0;
        idx = fn_801E8D34(lbl_80331A08[1]);
        if (lbl_8064CD44 == 10) {
            fn_80116490(0, 1, 100);
            fn_80116838(0, 0);
        } else if (lbl_8064CD44 == 12 || lbl_8064CD44 == 25) {
            fn_80116490(0, 1, 100);
            fn_80116838(1, 0);
        }
        fn_801ED3F4(lbl_8064CD80);
        /* ASM: addi preserves both pooled addresses; C reduces the first to mr. */
        asm {
            addi textures, data, 0
            addi textureList, data, 0x310
        }
        fn_801A90BC(textures, textureList);
        for (i = 0; i <= 3; i++) {
            if (lbl_8064CD60 & (0x10000 << i)) {
                powerIcon = lbl_8064C2A8;
                fn_801A852C(&powerIcon.value, 0, i + 0x58, 0x80000000);
                fn_801A9118(0, (count + 0x6F) * 4, (void *)5);
                count++;
            }
        }
        fn_801156D0(idx);
        fn_801E3AA4(0);
        powerText = lbl_8064C2B0;
        fn_801E3A34(&powerText);
        fn_801E5430(0xA8, 0x7A);
        bitNameAddress = fn_801E75A4(lbl_8064CD60, idx);
        /* ASM: slwi, addi and add preserve the separate pooled table base;
         * C combines its offset with the bit-number bias in the final load. */
        asm {
            slwi bitNameAddress, bitNameAddress, 2
            addi bitBase, data, 0xE08
            add bitNameAddress, bitBase, bitNameAddress
        }
        fn_801E56AC(lbl_8064FF78, data->bitFmt, ((char **)bitNameAddress)[-16]);
        break;
    case 2:
        fn_80115D8C(lbl_8064CD50 | (runeCount << 4), lbl_8064CD54, 0x4B);
    case 11:
    case 13:
    case 26:
        if (lbl_8064CD44 == 13 || lbl_8064CD44 == 26) {
            fn_80116490(0, 1, 100);
            fn_80116838(1, 0);
        } else if (lbl_8064CD44 == 11) {
            fn_80116490(0, 1, 100);
            fn_80116838(0, 0);
        }
        fn_801ED3F4(lbl_8064CD80);
        /* ASM: addi preserves both pooled addresses; C reduces the first to mr. */
        asm {
            addi textures, data, 0
            addi textureList, data, 0x310
        }
        fn_801A90BC(textures, textureList);
        fn_801168EC(0, 0, fn_801E7578(lbl_8064CD4C & 0xF));
        fn_801156D0(fn_801E8D34(lbl_80331A08[2]));
        fn_801E3AA4(0);
        alignmentText = lbl_8064C2B0;
        fn_801E3A34(&alignmentText);
        fn_801E5430(0xA8, 0x7A);
        fn_801E56AC(lbl_8064FF78, data->runeFmt);
        break;
    case 3:
        page = fn_801E8D3C(lbl_80331A08[3]);
        total = fn_801E8D44(lbl_80331A08[3]) + 1;
        fn_80115D8C(lbl_8064CD50 | (symbolMask << (lbl_8064CD54 << 2)), lbl_8064CD54, lbl_8064CD28);
        fn_801168EC(0xF, page, page + 5 < total ? page + 5 : total);
        fn_801156D0(fn_801E8D24(lbl_80331A08[3]));
        fn_801E3AA4(0);
        runeText = lbl_8064C2B0;
        fn_801E3A34(&runeText);
        if (page != 0) {
            fn_801E5430(0x9B, 0x46);
            fn_801E56AC(lbl_8064FF7C, lbl_8064B988);
        }
        if (page + 5 < total) {
            fn_801E5430(0x23F, 0x46);
            fn_801E56AC(lbl_8064FF7C, lbl_8064B98C);
        }
        fn_801E5430(0xA8, 0x7A);
        fn_801E56AC(lbl_8064FF78, data->pageFmt);
        break;
    case 4:
        idx = fn_80113E48(fn_80113CF8(lbl_8064CD50));
        max = ((lbl_8064CD50 & 0xF) << 1) + 3;
        fn_80115D8C(lbl_8064CD50, lbl_8064CD54, 0xFF);
        if (idx == -1) {
            break;
        }
        fn_801E3AA4(0);
        fn_801E5AD0(0x63);
        discoveredText = lbl_8064C2B0;
        fn_801E3A34(&discoveredText);
        switch (max) {
        case 3:
            fn_801E5430(0x19D, 0x50);
            break;
        case 5:
            fn_801E5430(0x1A2, 0x32);
            break;
        case 7:
            fn_801E5430(0x1A2, 0x32);
            break;
        }
        if ((lbl_80331748.chapterFlags[idx] & 0x08000000) || (fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000)) {
            /* ASM: addi keeps the table base separate; C folds it into the indexed load. */
            asm { addi bookBase, data, 0xEB0 }
            fn_801E56AC(lbl_8064FF78, data->bookNameFmt, ((char **)bookBase)[idx]);
        } else {
            fn_801E56AC(lbl_8064FF78, data->bookIndexFmt, idx + 1);
        }
        break;
    case 5:
        sel = 0;
        i = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        if (fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000) {
            i = lbl_8023A414[i] & 0x70000;
        } else {
            i = lbl_80331748.chapterFlags[i] & 0x70000 & lbl_8064CD48;
        }
        for (mask = 0; mask <= 3; mask++) {
            if (i & (0x10000 << mask)) {
                chapterIcon = lbl_8064C2A8;
                fn_801A852C(&chapterIcon.value, 0, mask + 0x58, 0x80000000);
                fn_801A9118(0, (sel + 0x6F) * 4, (void *)5);
                sel++;
            }
        }
        fn_80116490(1, 1, alpha);
        break;
    case 18:
    case 19:
        sel = 0;
        i = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        if (fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000) {
            i = lbl_8023A414[i] & 0x70000;
        } else {
            i = lbl_80331748.chapterFlags[i] & 0x70000 & lbl_8064CD48;
        }
        for (mask = 0; mask <= 3; mask++) {
            if (i & (0x10000 << mask)) {
                chapterPageIcon = lbl_8064C2A8;
                fn_801A852C(&chapterPageIcon.value, 0, mask + 0x58, 0x80000000);
                fn_801A9118(0, (sel + 0x6F) * 4, (void *)5);
                sel++;
            }
        }
        fn_80116490(0, 1, 100);
        fn_80116838(2, 1);
        break;
    case 23:
        fn_80116490(0, 1, 100);
        fn_80116838(1, 1);
        break;
    case 6:
        sel = 0;
        i = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        if (fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x4000) {
            i = lbl_8023A414[i] & 0x70000;
        } else {
            i = lbl_80331748.chapterFlags[i] & 0x70000 & lbl_8064CD48;
        }
        for (mask = 0; mask <= 3; mask++) {
            if (i & (0x10000 << mask)) {
                assignedIcon = lbl_8064C2A8;
                fn_801A852C(&assignedIcon.value, 0, mask + 0x58, 0x80000000);
                fn_801A9118(0, (sel + 0x6F) * 4, (void *)5);
                sel++;
            }
        }
        fn_80116490(0, 1, 100);
        fn_80116838(fn_801E8D24(lbl_80331A08[6]), 1);
        break;
    case 20:
    case 21:
    case 22:
        fn_80116490(0, 0, 100);
        fn_80116838(2, 1);
        break;
    case 7:
    case 8:
    case 9:
        fn_80116490(0, 0, 100);
        fn_80116838(fn_801E8D24(lbl_80331A08[6]), 1);
        break;
    case 27:
        fn_801E3AA4(0);
        assignmentText = lbl_8064C2B0;
        fn_801E3A34(&assignmentText);
        fn_801E5430(0xA8, 0x7A);
        fn_801E56AC(lbl_8064FF78, data->exitFmt);
        fn_801ED3F4(lbl_8064CD80);
        /* ASM: addi preserves both pooled addresses; C reduces the first to mr. */
        asm {
            addi textures, data, 0
            addi textureList, data, 0x310
        }
        fn_801A90BC(textures, textureList);
    case 14:
    case 24:
    case 28:
        fn_80116B4C();
        break;
    case 15:
    case 16:
        fn_801157B4();
        break;
    }
}
