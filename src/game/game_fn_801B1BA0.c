typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry801B1BA0 {
    u8 type;
    u8 arg;
    u16 value;
} Entry801B1BA0;

extern Entry801B1BA0 lbl_80251858[];
extern s32 lbl_8064D378;
extern s32 lbl_8064D374;
extern s32 lbl_8064D360;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D35C;
extern s32 lbl_8064D364;
extern s32 lbl_8064D350;
extern s32 lbl_8064D368;
extern s32 lbl_8064D354;
extern s32 lbl_8064D370;
extern s32 lbl_8064D36C;
extern s32 lbl_8064C4E0;
extern s32 lbl_8064C578;
extern u8 lbl_803003C8[];

extern s32 fn_801AD898(void);
extern s32 fn_8015E4B4(void);
extern s32 fn_801AD72C(void);
extern void fn_801B1A1C(s32, s32);
extern u32 fn_801B192C(void);
extern void fn_801A98F4(s32, s32);
extern s32 fn_800FBFB0(void);
extern void fn_801B2348(s32);
extern void fn_801B1B0C(s32, s32);
extern s32 fn_801E79FC(s32, s32);
extern s32 fn_800473A4(void);
extern s32 fn_8007D834(void);

void fn_801B1BA0(void)
{
    s32 current;
    Entry801B1BA0* entry;

    if (lbl_8064D378 != 1) {
        return;
    }
    if (lbl_8064D374 != 1) {
        return;
    }
    if (!fn_801AD898()) {
        return;
    }
    if (fn_8015E4B4()) {
        return;
    }

    current = fn_801AD72C();
    if (lbl_8064D360 != -1 && lbl_8064D360 != lbl_8064D18C) {
        current = lbl_8064D35C;
        if (current == 255) {
            current = *(s32*)(lbl_803003C8 + 8);
        }
        fn_801B1A1C(current, 5);
        return;
    }

    if (current == lbl_8064D364) {
        if (current == 94) {
            u32 elapsed = fn_801B192C();
            if (elapsed > 0x348000 && elapsed <= 0x360000) {
                if (lbl_8064D350 == 0) {
                    fn_801A98F4(0x266, 100);
                    lbl_8064D350 = 1;
                }
            } else {
                lbl_8064D350 = 0;
            }
        }
        return;
    }

    if (current != -1) {
        return;
    }
    if (lbl_8064D368 != 0) {
        lbl_8064D368--;
        return;
    }
    if (lbl_8064D354 == 0) {
        return;
    }

    entry = &lbl_80251858[lbl_8064D370];
    switch (entry->type) {
    case 0:
        lbl_8064D370++;
        break;
    case 1:
        fn_801B1B0C(entry->value, entry->arg);
        break;
    case 2:
        lbl_8064D368 = entry->value;
        lbl_8064D370++;
        break;
    case 3: {
        s32 count = (fn_800FBFB0() % entry->value) + 1;
        do {
            lbl_8064D370++;
        } while (--count != 0);
        break;
    }
    case 4:
        if (entry->value == lbl_8064D36C) {
            fn_801B1A1C(lbl_8064D36C, 0);
        } else {
            lbl_8064D370++;
        }
        break;
    case 5:
        fn_801B2348(0);
        break;
    case 6: {
        int value = entry->value;
        if (value == 0xFFFF) {
            value = lbl_8064D18C;
        }
        lbl_8064D360 = value;
        lbl_8064D35C = entry->arg;
        lbl_8064D370++;
        break;
    }
    case 7:
        fn_801A98F4(entry->value, entry->arg);
        lbl_8064D370++;
        break;
    case 8:
        switch (entry->value) {
        case 1:
            if (lbl_8064D18C == 0x27) {
                fn_801B1A1C(0xF, 5);
            } else if (fn_801E79FC(lbl_8064C4E0, 0x46D)) {
                if (lbl_8064D36C != 0x27) {
                    fn_801B1A1C(0x27, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0xA) {
                fn_801B1A1C(0xA, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 9:
            if (!fn_801E79FC(lbl_8064C4E0, 0x5F)) {
                if (lbl_8064D36C != 0x14) {
                    fn_801B1A1C(0x14, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0xF) {
                fn_801B1A1C(0xF, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 2:
            if (lbl_8064D18C == 0x9D) {
                if (lbl_8064D36C != 0x1C) {
                    fn_801B1A1C(0x1C, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 3) {
                fn_801B1A1C(3, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 3:
            if ((lbl_8064D18C == 0xB9 &&
                 fn_801E79FC(lbl_8064C4E0, 0x296)) ||
                (lbl_8064D18C == 0xBF &&
                 fn_801E79FC(lbl_8064C4E0, 0xBD))) {
                if (lbl_8064D36C != 0x1D) {
                    fn_801B1A1C(0x1D, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 4) {
                fn_801B1A1C(4, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 4:
            if (lbl_8064D18C == 0x33 &&
                fn_801E79FC(lbl_8064C4E0, 0x46C)) {
                if (lbl_8064D36C != 0x1E) {
                    fn_801B1A1C(0x1E, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064C578 != 4 &&
                       fn_801E79FC(lbl_8064C4E0, 0x206)) {
                if (lbl_8064D36C != 0x22) {
                    fn_801B1A1C(0x22, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 9) {
                fn_801B1A1C(9, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 5:
            if (fn_801E79FC(lbl_8064C4E0, 0x284) ||
                fn_801E79FC(lbl_8064C4E0, 0x386)) {
                if (lbl_8064D36C != 7) {
                    fn_801B1A1C(7, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0x1F) {
                fn_801B1A1C(0x1F, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 6:
            if (lbl_8064D18C == 0x124) {
                if (lbl_8064D36C != 0x20) {
                    fn_801B1A1C(0x20, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (!fn_801E79FC(lbl_8064C4E0, 0x3B0) ||
                       (fn_801E79FC(lbl_8064C4E0, 0x80) &&
                        !fn_800473A4())) {
                if (lbl_8064D36C != 5) {
                    fn_801B1A1C(5, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0x20) {
                fn_801B1A1C(0x20, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 7:
            if (fn_8007D834() == 5) {
                if (lbl_8064D36C != 0x23) {
                    fn_801B1A1C(0x23, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0xB) {
                fn_801B1A1C(0xB, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 8:
            if (lbl_8064D18C == 0x33 ||
                fn_801E79FC(lbl_8064C4E0, 0x313)) {
                if (lbl_8064D36C != 0) {
                    fn_801B1A1C(0, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (fn_801E79FC(lbl_8064C4E0, 0x2EF)) {
                if (lbl_8064D36C != 0x25) {
                    fn_801B1A1C(0x25, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (fn_801E79FC(lbl_8064C4E0, 0x131)) {
                if (lbl_8064D36C != 0) {
                    fn_801B1A1C(0, 5);
                } else {
                    lbl_8064D370++;
                }
            } else if (lbl_8064D36C != 0x24) {
                fn_801B1A1C(0x24, 5);
            } else {
                lbl_8064D370++;
            }
            break;
        case 0:
            break;
        }
        break;
    }
}
