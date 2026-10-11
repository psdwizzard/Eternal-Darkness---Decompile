typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;
typedef struct Color { u32 value; } Color;

extern int lbl_8064CDC8;
extern u8 lbl_8064C9EC;
extern void *lbl_8064C51C;
extern TextDescriptor *lbl_8064C9F0;
extern TextDescriptor *lbl_8064C9F4;
extern Color lbl_8064C2B0;
extern const Color lbl_8064F0B8;
extern const Color lbl_8064F0BC;
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void *fn_801E5D08(void *);
extern void *fn_801E5D20(void *);
extern s16 fn_801E6350(TextDescriptor *);
extern s16 fn_801E6380(TextDescriptor *);
extern s16 fn_801E63F0(TextDescriptor *);
extern s16 fn_801E6420(TextDescriptor *);
extern void fn_801E6328(TextDescriptor *, s16, s16);
extern void fn_801E6454(TextDescriptor *, s16);

/* Create the message and, in mode 1, position its prompt underneath it. */
void fn_800B90B8(u16 group, u16 index, u8 mode)
{
    int flags = 0;
    int special;
    s16 x, y, width, height, center;
    lbl_8064C9EC = mode;
    special = lbl_8064CDC8 == 3;
    if (mode == 1 || mode == 2) {
        flags |= 8;
    }
    if (special) {
        lbl_8064C9F0 = fn_801E6CA0(lbl_8064C51C, group, index, flags, 1);
        *(Color *)fn_801E5D08(lbl_8064C9F0) = lbl_8064C2B0;
    } else {
        lbl_8064C9F0 = fn_801E6CA0(lbl_8064C51C, group, index, flags | 0x2000, 1);
        {
            Color color = lbl_8064F0B8;
            *(Color *)fn_801E5D08(lbl_8064C9F0) = color;
        }
    }
    x = fn_801E6350(lbl_8064C9F0);
    y = fn_801E6380(lbl_8064C9F0);
    width = fn_801E63F0(lbl_8064C9F0);
    height = fn_801E6420(lbl_8064C9F0);
    center = x + (width >> 1);
    if (mode == 1) {
        register s16 extraHeight;
        register int padded;
        register int fullHeight;
        lbl_8064C9F4 = fn_801E6CA0(lbl_8064C51C, 0, 15, 10, 1);
        extraHeight = fn_801E6420(lbl_8064C9F4);
        fullHeight = height;
        /* ASM: addi keeps the padding addition before the position addition;
         * MWCC reassociates the equivalent C expression. */
        asm { addi padded, fullHeight, 20 }
        fn_801E6328(lbl_8064C9F4, center, y + padded);
        /* ASM: addi keeps the prompt padding addition before the height sum;
         * MWCC reassociates the equivalent C expression. */
        asm { addi padded, extraHeight, 10 }
        fn_801E6454(lbl_8064C9F0, fullHeight + padded);
        if (special) {
            *(Color *)fn_801E5D08(lbl_8064C9F4) = lbl_8064C2B0;
        } else {
            Color color = lbl_8064F0BC;
            *(Color *)fn_801E5D08(lbl_8064C9F4) = color;
        }
        *(u32 *)fn_801E5D20(lbl_8064C9F4) &= ~1U;
    }
}
