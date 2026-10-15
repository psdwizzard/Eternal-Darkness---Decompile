typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;
typedef struct Object Object;
typedef struct Range Range;
typedef struct Color { u32 value; } Color;

extern int lbl_8064CDC8;
extern void *lbl_8064C504;
extern void *lbl_8064C51C;
extern void *lbl_8064CA08;
extern u8 lbl_80320B54[];
extern TextDescriptor *lbl_8064CA0C;
extern TextDescriptor *lbl_80320B48[3];
extern Color lbl_8064C2AC;
extern Color lbl_8064C2B0;
extern const Color lbl_8064F0AC;
extern const Color lbl_8064F0B0;
extern int fn_800B194C(void);
extern void fn_80118080(void);
extern void fn_801E8A50(Object *);
extern void fn_801E8AEC(Range *, int, int, void *);
extern void fn_801E8B24(Object *, int, int);
extern void fn_801E8B10(Object *, u32, u32, u32, u32);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void *fn_801E5D08(void *);
extern void *fn_801E5D20(void *);
extern s16 fn_801E6350(TextDescriptor *);
extern s16 fn_801E6380(TextDescriptor *);
extern s16 fn_801E63F0(TextDescriptor *);
extern s16 fn_801E6420(TextDescriptor *);
extern void fn_801E6328(TextDescriptor *, s16, s16);
extern void fn_801E6454(TextDescriptor *, s16);

/* Build a menu message with its row of choices and highlight the selection. */
void fn_800B8660(u16 group, u16 index, int mode)
{
    register int first;
    int scene;
    int special;
    u16 flags;
    int count;
    int selected;
    int i;
    s16 x, y, width, height;
    s16 center;
    Color *colorPtr;
    Color color;

    scene = fn_800B194C();
    flags = 8;
    special = lbl_8064CDC8 == 3;
    switch (mode) {
    case 0:
        count = 2;
        selected = 1;
        if (scene == 0x23) {
            selected = 0;
        }
        break;
    case 1:
    case 4:
        count = 2;
        if (scene == 0xb || scene == 0xc) {
            selected = 0;
        } else {
            selected = 1;
        }
        break;
    case 2:
        count = 3;
        selected = 0;
        break;
    case 5:
        count = 3;
        selected = 1;
        break;
    case 3:
        count = 2;
        selected = 0;
        break;
    }

    lbl_8064CA08 = lbl_80320B54;
    fn_801E8A50(lbl_8064CA08);
    fn_801E8AEC(lbl_8064CA08, 0, count, (void *)count);
    fn_801E8B24(lbl_8064CA08, selected, 0);
    fn_801E8B10(lbl_8064CA08, 1, 0, 0, (u32)fn_80118080);
    if (group == 0 && index == 0x5f) {
        return;
    }

    if (!special) {
        flags |= 0x2000;
    }
    lbl_8064CA0C = fn_801E6CA0(lbl_8064C51C, group, index, flags, 1);
    if (special) {
        colorPtr = &lbl_8064C2B0;
    } else {
        color = lbl_8064F0AC;
        colorPtr = &color;
    }
    *(Color *)fn_801E5D08(lbl_8064CA0C) = *colorPtr;
    x = fn_801E6350(lbl_8064CA0C);
    y = fn_801E6380(lbl_8064CA0C);
    width = fn_801E63F0(lbl_8064CA0C);
    height = fn_801E6420(lbl_8064CA0C);
    center = x + ((s16)width >> 1);

    switch (mode) {
    case 0: {
        int width0;
        int half;
        s16 maxWidth;
        register s16 rawHeight;
        register int padded;
        register s16 spacing;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C504, 0, 0x22, 10, 1);
        width0 = fn_801E63F0(lbl_80320B48[0]);
        if ((s16)fn_801E63F0(lbl_80320B48[1]) > width0) {
            maxWidth = fn_801E63F0(lbl_80320B48[1]);
        } else {
            maxWidth = fn_801E63F0(lbl_80320B48[0]);
        }
        half = maxWidth >> 1;

        fn_801E6328(lbl_80320B48[0], (s16)(center - 20) - half, (s16)y + (s16)((s16)height + 10));
        half = center + half;
        fn_801E6328(lbl_80320B48[1], half + 30, (s16)y + (s16)((s16)height + 10));
        spacing = fn_801E6420(lbl_80320B48[0]);
        rawHeight = fn_801E6420(lbl_8064CA0C);
        /* ASM: addi retains the choice padding before the message sum;
         * MWCC reassociates the equivalent C expression. */
        asm {
            addi padded, spacing, -5;
        }
        fn_801E6454(lbl_8064CA0C, rawHeight + padded);
        break;
    }
    case 1:
    case 4: {
        register int spacing;
        register s16 rawSpacing;
        register int top;
        register int fullHeight;
        register int baseY;
        register u32 high;
        register TextDescriptor *firstText;
        register int boxHeight;
        register s16 rawHeight;
        switch (mode) {
        case 4:
            lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x60, 10, 1);
            break;
        case 1:
            lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
            break;
        }
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        rawSpacing = fn_801E6420(lbl_80320B48[0]);
        fullHeight = (s16)height;
        baseY = (s16)y;
        /* ASM: addi, lis, mr, lwz, and add retain padding and the saved
         * return value around the text load; MWCC reorders the equivalent C. */
        asm {
            addi top, fullHeight, 20;
            lis high, lbl_80320B48@ha;
            mr spacing, rawSpacing;
            lwz firstText, lbl_80320B48@l(high);
            add top, baseY, top;
        }
        fn_801E6328(firstText, center, top);
        spacing = (s16)(spacing + 4);
        fn_801E6328(lbl_80320B48[1], center, spacing + top);
        rawHeight = fn_801E6420(lbl_8064CA0C);
        /* ASM: addi and slwi preserve the subtraction and scale order;
         * MWCC reuses the subtraction result register for the wrong operand. */
        asm {
            addi boxHeight, rawHeight, -10;
            slwi rawHeight, spacing, 1;
        }
        fn_801E6454(lbl_8064CA0C, rawHeight + boxHeight);
        break;
    }
    case 2: {
        register int spacing;
        register s16 rawSpacing;
        register int top;
        register TextDescriptor *secondText;
        register TextDescriptor **choiceRows;
        register int sum;
        int doubled;
        register int boxHeight;
        register s16 rawHeight;
        register int lineHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        secondText = fn_801E6CA0(lbl_8064C51C, 0, 0x11, 10, 1);
        choiceRows = lbl_80320B48;
        choiceRows[1] = secondText;
        lbl_80320B48[2] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        rawSpacing = fn_801E6420(lbl_80320B48[0]);
        fn_801E6328(lbl_80320B48[0], center, (top = (s16)y + (s16)height) + 10);
        spacing = (s16)rawSpacing;
        /* ASM: lwz and add retain the choice load before the row sum;
         * MWCC reassociates the padding and moves the C load after the sum. */
        asm {
            lwz secondText, 4(choiceRows);
            add sum, top, spacing;
        }
        fn_801E6328(secondText, center, sum + 5);
        doubled = spacing * 2;
        fn_801E6328(lbl_80320B48[2], center, doubled + top);
        rawHeight = fn_801E6420(lbl_8064CA0C);
        /* ASM: mulli and addi retain the line height and message padding order;
         * MWCC reassociates the equivalent C expression. */
        asm {
            mulli lineHeight, spacing, 3;
            addi boxHeight, rawHeight, -10;
        }
        fn_801E6454(lbl_8064CA0C, lineHeight + boxHeight);
        break;
    }
    case 3: {
        register int spacing;
        register s16 rawSpacing;
        int top;
        register int boxHeight;
        register s16 rawHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        rawSpacing = fn_801E6420(lbl_80320B48[0]);
        fn_801E6328(lbl_80320B48[0], center, (s16)y + (top = (s16)height + 10));
        spacing = (s16)rawSpacing;
        fn_801E6328(lbl_80320B48[1], center, ((s16)y + top) + spacing);
        rawHeight = fn_801E6420(lbl_8064CA0C);
        /* ASM: addi and slwi preserve the subtraction and scale order;
         * MWCC reuses the subtraction result register for the wrong operand. */
        asm {
            addi boxHeight, rawHeight, -10;
            slwi rawHeight, spacing, 1;
        }
        fn_801E6454(lbl_8064CA0C, rawHeight + boxHeight);
        break;
    }
    case 5: {
        register int spacing;
        register s16 rawSpacing;
        int top;
        int doubled;
        register int boxHeight;
        register s16 rawHeight;
        register int lineHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        lbl_80320B48[2] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        rawSpacing = fn_801E6420(lbl_80320B48[0]);
        fn_801E6328(lbl_80320B48[0], center, first = (top = (s16)y + (s16)height) + 5);
        spacing = (s16)rawSpacing;
        fn_801E6328(lbl_80320B48[1], center, spacing + first);
        doubled = spacing * 2;
        fn_801E6328(lbl_80320B48[2], center, doubled + top);
        rawHeight = fn_801E6420(lbl_8064CA0C);
        /* ASM: mulli and addi retain the line height and message padding order;
         * MWCC reassociates the equivalent C expression. */
        asm {
            mulli lineHeight, spacing, 3;
            addi boxHeight, rawHeight, -10;
        }
        fn_801E6454(lbl_8064CA0C, lineHeight + boxHeight);
        break;
    }
    }

    for (i = 0; i < count; i++) {
        if (i == selected) {
            if (lbl_8064CDC8 == 3) {
                *(Color *)fn_801E5D08(lbl_80320B48[i]) = lbl_8064C2B0;
            } else {
                Color highlight = lbl_8064F0B0;
                *(Color *)fn_801E5D08(lbl_80320B48[i]) = highlight;
            }
            *(u32 *)fn_801E5D20(lbl_80320B48[i]) |= 2;
            *(u32 *)fn_801E5D20(lbl_80320B48[i]) &= ~1U;
        } else {
            *(Color *)fn_801E5D08(lbl_80320B48[i]) = lbl_8064C2AC;
            *(u32 *)fn_801E5D20(lbl_80320B48[i]) |= 2;
            *(u32 *)fn_801E5D20(lbl_80320B48[i]) &= ~1U;
        }
    }
}
