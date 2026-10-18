typedef unsigned int u32;

typedef struct MenuData {
    unsigned char data[0x11EC];
    char startFmt[0x1C];
    char flagsFmt[0x18];
    char runeFmt[0x0C];
    char chapterFmt[0x18];
} MenuData;

extern u32 lbl_80331748[];
extern const volatile u32 lbl_8023A414[12];
extern MenuData lbl_8024CE40;
extern int fn_801118E8(void);
extern void fn_801E7FDC(const char *, ...);
extern int fn_801E75A4(u32, int);
extern int fn_801E76E0(u32);
extern u32 fn_80113D50(u32);

static inline u32 MaskFlags(u32 flags, u32 mask)
{
    return flags & mask;
}

int fn_80111C48(void)
{
    MenuData *menu = &lbl_8024CE40;
    int i;
    int changed = 0;

    fn_801E7FDC(menu->startFmt);
    if (fn_801118E8() != 0) {
        for (i = 0; i < 12; i++) {
            u32 value;
            u32 flagMask;
            u32 runeMask;
            u32 rune;
            u32 selected;
            u32 knownRunes;

            if ((lbl_80331748[i + 2] & 0x08000000) == 0 || (lbl_80331748[i + 2] & 0x02000000) != 0)
                continue;

            value = lbl_8023A414[i];
            flagMask = value & 0x3FF0;
            runeMask = (value << 16) & 0x3FF00000;
            rune = value & 0xF;

            fn_801E7FDC(menu->flagsFmt,
                        flagMask & lbl_80331748[0], flagMask,
                        (runeMask == (runeMask & lbl_80331748[0])));
            if (flagMask != (flagMask & lbl_80331748[0]) ||
                runeMask != (runeMask & lbl_80331748[0]))
                continue;

            rune &= lbl_80331748[0];
            fn_801E7FDC(menu->runeFmt, 0);
            if (rune == 0)
                continue;

            knownRunes = rune & (lbl_80331748[0] >> 16);
            selected = lbl_80331748[1] & (lbl_80331748[i + 14] & (lbl_8023A414[i] & 0x70000));
            fn_801E7FDC(menu->chapterFmt,
                        MaskFlags(lbl_80331748[i + 2], selected), selected, knownRunes, selected);
            if (selected == (selected & lbl_80331748[i + 2]) || knownRunes == 0 || selected == 0)
                continue;

            {
                u32 runeBit = 1U << fn_801E75A4(knownRunes, 0);
                u32 selectedBit = 1U << fn_801E76E0(selected);
                u32 newFlags = selectedBit | (flagMask | 0x06000000 | runeBit);

                lbl_80331748[i + 2] |= newFlags;
                lbl_80331748[i + 26] = fn_80113D50(selectedBit | (flagMask | runeBit));
                changed = 1;
            }
        }
    }
    return changed;
}
