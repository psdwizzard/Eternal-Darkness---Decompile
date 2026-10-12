typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;
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
extern void fn_801E8A50(void *);
extern void fn_801E8AEC(void *, int, int, int);
extern void fn_801E8B24(void *, int, int);
extern void fn_801E8B10(void *, int, int, int, void (*)(void));
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void *fn_801E5D08(void *);
extern void *fn_801E5D20(void *);
extern int fn_801E6350(TextDescriptor *);
extern int fn_801E6380(TextDescriptor *);
extern int fn_801E63F0(TextDescriptor *);
extern int fn_801E6420(TextDescriptor *);
extern void fn_801E6328(TextDescriptor *, s16, s16);
extern void fn_801E6454(TextDescriptor *, s16);

/* Build a menu message with its row of choices and highlight the selection. */
void fn_800B8660(u16 group, u16 index, int mode)
{
    int scene;
    int special;
    u16 flags;
    int count;
    int selected;
    int i;
    int x, y, width, height;
    s16 center;
    Color *colorPtr;
    Color color;
    TextDescriptor **text;

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
    fn_801E8AEC(lbl_8064CA08, 0, count, count);
    fn_801E8B24(lbl_8064CA08, selected, 0);
    fn_801E8B10(lbl_8064CA08, 1, 0, 0, fn_80118080);
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
        s16 width0;
        int half;
        int top;
        int spacing;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C504, 0, 0x22, 10, 1);
        width0 = fn_801E63F0(lbl_80320B48[0]);
        if ((s16)fn_801E63F0(lbl_80320B48[1]) > width0) {
            half = fn_801E63F0(lbl_80320B48[1]);
        } else {
            half = fn_801E63F0(lbl_80320B48[0]);
        }
        half = (s16)half >> 1;
        top = (s16)height + 10;
        top = (s16)y + top;
        fn_801E6328(lbl_80320B48[0], center - 20 - half, top);
        half = center + half;
        fn_801E6328(lbl_80320B48[1], half + 30, top);
        spacing = fn_801E6420(lbl_80320B48[0]);
        half = fn_801E6420(lbl_8064CA0C);
        fn_801E6454(lbl_8064CA0C, half + (spacing - 5));
        break;
    }
    case 1:
    case 4: {
        int spacing;
        int top;
        int boxHeight;
        switch (mode) {
        case 4:
            lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x60, 10, 1);
            break;
        case 1:
            lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
            break;
        }
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        spacing = fn_801E6420(lbl_80320B48[0]);
        top = (s16)height + 20;
        top = (s16)y + top;
        fn_801E6328(lbl_80320B48[0], center, top);
        spacing += 4;
        spacing = (s16)spacing;
        fn_801E6328(lbl_80320B48[1], center, spacing + top);
        boxHeight = fn_801E6420(lbl_8064CA0C) - 10;
        fn_801E6454(lbl_8064CA0C, spacing * 2 + boxHeight);
        break;
    }
    case 2: {
        int spacing;
        int top;
        int first;
        int boxHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0x11, 10, 1);
        lbl_80320B48[2] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        spacing = fn_801E6420(lbl_80320B48[0]);
        top = (s16)y + (s16)height;
        fn_801E6328(lbl_80320B48[0], center, top + 10);
        spacing = (s16)spacing;
        first = top + spacing;
        fn_801E6328(lbl_80320B48[1], center, first + 5);
        fn_801E6328(lbl_80320B48[2], center, top + spacing * 2);
        boxHeight = fn_801E6420(lbl_8064CA0C) - 10;
        fn_801E6454(lbl_8064CA0C, spacing * 3 + boxHeight);
        break;
    }
    case 3: {
        int spacing;
        int top;
        int boxHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        spacing = fn_801E6420(lbl_80320B48[0]);
        top = (s16)height + 10;
        top = (s16)y + top;
        fn_801E6328(lbl_80320B48[0], center, top);
        spacing = (s16)spacing;
        fn_801E6328(lbl_80320B48[1], center, spacing + top);
        boxHeight = fn_801E6420(lbl_8064CA0C) - 10;
        fn_801E6454(lbl_8064CA0C, spacing * 2 + boxHeight);
        break;
    }
    case 5: {
        int spacing;
        int top;
        int first;
        int boxHeight;
        lbl_80320B48[0] = fn_801E6CA0(lbl_8064C504, 0, 0x21, 10, 1);
        lbl_80320B48[1] = fn_801E6CA0(lbl_8064C51C, 0, 0x10, 10, 1);
        lbl_80320B48[2] = fn_801E6CA0(lbl_8064C51C, 0, 0xf, 10, 1);
        spacing = fn_801E6420(lbl_80320B48[0]);
        top = (s16)y + (s16)height;
        first = top + 5;
        fn_801E6328(lbl_80320B48[0], center, first);
        spacing = (s16)spacing;
        fn_801E6328(lbl_80320B48[1], center, spacing + first);
        fn_801E6328(lbl_80320B48[2], center, top + spacing * 2);
        boxHeight = fn_801E6420(lbl_8064CA0C) - 10;
        fn_801E6454(lbl_8064CA0C, spacing * 3 + boxHeight);
        break;
    }
    }

    text = lbl_80320B48;
    for (i = 0; i < count; i++) {
        if (i == selected) {
            if (lbl_8064CDC8 == 3) {
                *(Color *)fn_801E5D08(*text) = lbl_8064C2B0;
            } else {
                Color highlight = lbl_8064F0B0;
                *(Color *)fn_801E5D08(*text) = highlight;
            }
            *(u32 *)fn_801E5D20(*text) |= 2;
            *(u32 *)fn_801E5D20(*text) &= ~1U;
        } else {
            *(Color *)fn_801E5D08(*text) = lbl_8064C2AC;
            *(u32 *)fn_801E5D20(*text) |= 2;
            *(u32 *)fn_801E5D20(*text) &= ~1U;
        }
        text++;
    }
}
