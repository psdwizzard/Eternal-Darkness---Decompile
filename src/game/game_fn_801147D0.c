typedef struct {
    short x;
    short y;
} Point16;

typedef struct {
    Point16 points[7];
} PointPath;

typedef struct {
    char pad0[0x12];
    short enabled;
    char pad14[0xC];
} MenuEntry;

extern unsigned int lbl_80331748[];
extern int lbl_80331A08[];
extern int lbl_8024DE38[];
extern MenuEntry lbl_8024DEF8[];
extern const PointPath lbl_8023A3C0[];
extern const unsigned int lbl_8023A414[];

extern void *lbl_8064C4E0;
extern void *lbl_8064C504;
extern unsigned char lbl_8064CD28;
extern unsigned int lbl_8064CD34;
extern int lbl_8064CD38;
extern int lbl_8064CD3C;
extern int lbl_8064CD44;
extern unsigned int lbl_8064CD48;
extern unsigned int lbl_8064CD4C;
extern unsigned int lbl_8064CD50;
extern unsigned int lbl_8064CD54;
extern int lbl_8064CD58;
extern unsigned int lbl_8064CD5C;
extern unsigned int lbl_8064CD60;
extern unsigned char lbl_8064CD64;
extern unsigned int lbl_8064CD68;
extern int lbl_8064CD6C;
extern int lbl_8064CDB0;
extern int lbl_8064CDB4;
extern int lbl_8064CDC0;
extern int lbl_8064CDC8;
extern int lbl_8064D18C;

extern void fn_80144C40(void);
extern int fn_801A98F4(int, int);
extern int fn_801E79FC(void *, int);
extern void fn_801E7974(void *, int);
extern void fn_80111F2C(int, int);
extern void fn_8016B400(int, int, int);
extern int fn_801E8D3C(int);
extern int fn_801E8D34(int);
extern void fn_80112278(int);
extern void fn_80144680(int);
extern int fn_80144628(int, void *, int);
extern void fn_801446D4(int, void (*)(int, int));
extern void fn_8011336C(int, int);
extern void fn_801139D4(void);
extern void fn_80112950(void);
extern unsigned int fn_801E7578(unsigned int);
extern int fn_801E75A4(unsigned int, int);
extern void fn_801E8AEC(int, int, unsigned int, int);
extern void fn_801E8B24(int, int, int);
extern void fn_801E8B6C(int, int);
extern void *fn_801E6CA0(void *, int, int, int, int);
extern void fn_80027730(void *, int, int);
extern void fn_801E5FB0(int);
extern void fn_80117AE0(short, short, int, int);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern unsigned int fn_8020216C(void *);
extern void fn_80117EF0(void);
extern void *fn_80201B3C(void);
extern void *fn_80049194(void);
extern int fn_801A6D94(void *);
extern void *fn_80201B94(void *);
extern int fn_80201C48(void *);
extern int fn_80201EB8(void *);
extern void *fn_80204318(void *, int);
extern int fn_8006D3E4(int, int);
extern void fn_80118060(int, unsigned int);
extern void fn_8010AD7C(void);

void fn_801147D0(void)
{
    unsigned int mask;
    unsigned int bit;
    unsigned int limit;
    unsigned int flags;
    void *actor;
    void *target;
    int count;
    int i;
    int targetId;

    fn_80144C40();
    switch (lbl_8064CD44) {
    case 17:
        if (lbl_8064CD68 > ((lbl_80331748[lbl_8064CD6C + 26] & 0xF) << 1) + 3) {
            fn_801A98F4(0x222, 100);
            if (fn_801E79FC(lbl_8064C4E0, 0x3B) == 0) {
                fn_801E7974(lbl_8064C4E0, 0x3B);
                fn_80111F2C(0, 0);
                fn_8016B400(0x8AB, 0, 0);
                lbl_80331748[lbl_8064CD6C + 2] &= 0xFDFFFFFF;
                lbl_8064CD44 = 18;
                fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
            } else {
                fn_80144680(lbl_8064CDC0);
                lbl_8064CDC0 = fn_80144628(6, lbl_8024DE38, 0);
                fn_801446D4(lbl_8064CDC0, fn_8011336C);
                lbl_80331748[lbl_8064CD6C + 2] &= 0xFDFFFFFF;
                fn_801139D4();
                fn_80112950();
            }
            fn_80111F2C(0, 0);
        }
        break;
    case 0:
        switch (fn_801E8D34(lbl_80331A08[0])) {
        case 0:
            fn_801A98F4(0x222, 100);
            fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
            lbl_8064CD44 = 5;
            break;
        case 1:
            if (lbl_8064CD48 != 0 && (lbl_8064CD4C & 0xF) != 0 && (lbl_8064CD4C & 0x1FF0) != 0) {
                mask = fn_801E7578(lbl_8064CD48);
                fn_801A98F4(0x222, 100);
                fn_801E8AEC(lbl_80331A08[1], 0, mask, 5);
                fn_801E8B24(lbl_80331A08[1], 0, 0);
                lbl_8064CD44 = 1;
                lbl_8064CD28 = 0x4B;
            } else {
                fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x3C, 0, 1), 0, 0);
            }
            break;
        case 2:
            fn_801A98F4(0x222, 100);
            lbl_8064CD44 = 15;
            break;
        case 3:
            fn_801A98F4(0x222, 100);
            lbl_8064CD44 = 24;
            break;
        }
        if (lbl_8064CD44 != 0) {
            fn_801E5FB0(lbl_8064CDB4);
            lbl_8064CDB4 = 0;
            fn_801E5FB0(lbl_8064CDB0);
            lbl_8064CDB0 = 0;
        }
        break;
    case 1:
        lbl_8064CD44 = 2;
        lbl_8064CD50 = fn_801E75A4(lbl_8064CD48, fn_801E8D34(lbl_80331A08[1])) - 16;
        fn_801A98F4(0x222, 100);
        lbl_8064CD54 = 1;
        break;
    case 2:
        lbl_8064CD44 = 3;
        lbl_8064CD50 |= fn_801E75A4(lbl_8064CD4C & 0xF, fn_801E8D34(lbl_80331A08[2])) << 4;
        fn_801A98F4(0x108, 100);
        lbl_8064CD54 = 2;
        lbl_8064CD28 = 0;
        fn_80117AE0(lbl_8023A3C0[lbl_8064CD50 & 0xF].points[0].x,
                    lbl_8023A3C0[lbl_8064CD50 & 0xF].points[0].y, 1, 1);
        break;
    case 3:
        if (lbl_8064CD28 == 0x4B) {
            limit = ((lbl_8064CD50 & 0xF) << 1) + 3;
            lbl_8064CD50 |= fn_801E75A4(lbl_8064CD4C & 0x3FF0, fn_801E8D34(lbl_80331A08[3]))
                            << (lbl_8064CD54 << 2);
            if (lbl_8064CD54 <= limit) {
                fn_801A98F4(0x108, 100);
                fn_80117AE0(lbl_8023A3C0[lbl_8064CD50 & 0xF].points[lbl_8064CD54 - 1].x,
                            lbl_8023A3C0[lbl_8064CD50 & 0xF].points[lbl_8064CD54 - 1].y,
                            lbl_8064CD54, 1);
                lbl_8064CD28 = 0;
                lbl_8064CD54++;
            }
        }
        break;
    case 4:
        fn_801A98F4(0x222, 100);
        fn_80111F2C(0, 0);
        lbl_8064CD44 = 0;
        break;
    case 5:
        i = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        if ((lbl_80331748[i + 2] & 0x0C000000) == 0) {
            if ((fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000) == 0) {
                break;
            }
        }
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = 6;
        if ((lbl_80331748[i + 2] & 0x04000000) == 0) {
            if ((fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000) == 0 && fn_801E8D34(lbl_80331A08[6]) != 0) {
                fn_801E8B6C(lbl_80331A08[6], 2);
            }
        }
        fn_801E8B6C(lbl_80331A08[6], 0);
        break;
    case 19:
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = 23;
        lbl_8064CD54 = 1;
        lbl_8064CD64 = 0;
        lbl_8064CD68 = 0;
        lbl_80331748[lbl_8064CD6C + 2] |= 0x04000000U;
        fn_80117EF0();
        fn_801E5FB0(lbl_8024DE38[11]);
        lbl_8024DE38[11] = 0;
        break;
    case 18:
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = 20;
        fn_801E5FB0(lbl_8064CD58);
        lbl_8064CD58 = 0;
        break;
    case 23:
        mask = lbl_80331748[lbl_8064CD34 + 2] & 0x70000;
        lbl_8064CD60 = mask & lbl_8064CD48;
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = 25;
        fn_801E5FB0(lbl_8024DE38[11]);
        lbl_8024DE38[11] = 0;
        break;
    case 16:
        if (fn_801E79FC(lbl_8064C4E0, 0x3D) != 0 && fn_801E79FC(lbl_8064C4E0, 0x3C) == 0) {
            fn_801A98F4(0x222, 100);
            fn_80144680(lbl_8064CDC0);
            lbl_8064CDC0 = fn_80144628(4, lbl_8024DE38, 0);
            fn_801446D4(lbl_8064CDC0, fn_8011336C);
            lbl_8064CD44 = 18;
            fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
            fn_801E7974(lbl_8064C4E0, 0x3C);
            lbl_8064CD58 = (int)fn_801E6CA0(lbl_8064C504, 0xF, 4, 0, 1);
        }
        break;
    case 6:
        count = 0;
        fn_801A98F4(0x222, 100);
        lbl_8064CD34 = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        if ((fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000) != 0) {
            mask = lbl_8023A414[lbl_8064CD34] & 0x70000;
        } else {
            flags = lbl_80331748[lbl_8064CD34 + 2] & 0x70000;
            mask = flags & lbl_8064CD48;
        }
        fn_801E8AEC(lbl_80331A08[1], 0, fn_801E7578(mask), 5);
        if (lbl_8064CD3C >= 0 && (mask & (1 << (lbl_8064CD3C + 16))) != 0) {
            for (i = 0; i < 3; i++) {
                if (((1 << (i + 16)) & mask) != 0) {
                    if (i == lbl_8064CD3C) {
                        break;
                    }
                    count++;
                }
            }
        } else {
            count = 0;
        }
        fn_801E8B24(lbl_80331A08[1], count, 0);
        switch (fn_801E8D34(lbl_80331A08[6])) {
        case 0:
            if ((lbl_8023A414[lbl_8064CD34] & 0x1FF0) == 0x810) {
                target = 0;
                actor = fn_80201B3C();
                if (fn_801A6D94(fn_80049194()) != 0) {
                    targetId = fn_80201C48(fn_80201B94(actor));
                    if (targetId != 0) {
                        target = fn_80201814(targetId);
                        if (lbl_8064D18C != fn_80201EB8(target)) {
                            target = 0;
                        }
                    }
                }
                if (target == 0) {
                    target = fn_80204318(actor, 1);
                }
                if (target == 0) {
                    fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 3, 0, 1), 0, 0);
                    break;
                }
            }
            lbl_8064CD60 = mask;
            lbl_8064CD44 = 10;
            break;
        case 1:
            lbl_8064CD60 = mask;
            lbl_8064CD44 = 12;
            break;
        case 2:
            lbl_8064CD44 = 7;
            break;
        }
        break;
    case 12:
    case 25: {
        register int count;
        count = 0;
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = (lbl_8064CD44 == 12) ? 13 : 26;
        lbl_8064CD60 = 1 << fn_801E75A4(lbl_8064CD60, fn_801E8D34(lbl_80331A08[1]));
        lbl_8064CD3C = fn_801E75A4(lbl_8064CD60 >> 16, 0);
        if ((lbl_8064CD4C & (1U << lbl_8064CD38)) != 0) {
            for (i = 0; i < 4; i++) {
                if (((1U << i) & lbl_8064CD4C) != 0) {
                    if (i == lbl_8064CD38) {
                        break;
                    }
                    count++;
                }
            }
        }
        fn_801E8B24(lbl_80331A08[2], count, 0);
        break;
    }
    case 13:
    case 26:
        lbl_8064CD38 = fn_801E75A4(lbl_8064CD4C & 0xF, fn_801E8D34(lbl_80331A08[2]));
        lbl_8064CD5C = 1 << lbl_8064CD38;
        if (lbl_8064CD5C == 8 && (lbl_8023A414[lbl_8064CD34] & 0x1FF0) == 0x820) {
            fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x39, 0, 1), 0, 0);
            break;
        }
        fn_801A98F4(0x222, 100);
        fn_80117EF0();
        fn_80144680(lbl_8064CDC0);
        for (i = 0; i < 5; i++) {
            lbl_8024DEF8[i].enabled = 1;
        }
        if (lbl_8064CD44 == 26) {
            lbl_8064CDC0 = fn_80144628(6, lbl_8024DEF8, 0);
            fn_80027730(fn_801E6CA0(lbl_8064C504, 0xF, 0xC, 0, 1), 0, 0);
            lbl_8064CD44 = 27;
        } else {
            lbl_8064CDC0 = fn_80144628(8, lbl_8024DEF8, 0);
            lbl_8064CD44 = 14;
        }
        fn_801446D4(lbl_8064CDC0, fn_8011336C);
        fn_80117EF0();
        break;
    case 10: {
        register int count;
        count = 0;
        fn_801A98F4(0x222, 100);
        lbl_8064CD44 = 11;
        lbl_8064CD60 = 1 << fn_801E75A4(lbl_8064CD60, fn_801E8D34(lbl_80331A08[1]));
        lbl_8064CD3C = fn_801E75A4(lbl_8064CD60 >> 16, 0);
        if ((lbl_8064CD4C & (1U << lbl_8064CD38)) != 0) {
            for (i = 0; i < 4; i++) {
                if (((1U << i) & lbl_8064CD4C) != 0) {
                    if (i == lbl_8064CD38) {
                        break;
                    }
                    count++;
                }
            }
        }
        fn_801E8B24(lbl_80331A08[2], count, 0);
        break;
    }
    case 11:
        fn_801A98F4(0x222, 100);
        lbl_8064CD38 = fn_801E75A4(lbl_8064CD4C & 0xF, fn_801E8D34(lbl_80331A08[2]));
        bit = 1 << lbl_8064CD38;
        lbl_8064CD5C = bit;
        if (bit == 8 && (lbl_8023A414[lbl_8064CD34] & 0x1FF0) == 0x820) {
            fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x39, 0, 1), 0, 0);
            break;
        }
        flags = lbl_8064CD60 | (bit | (lbl_8023A414[lbl_8064CD34] & 0x1FF0));
        fn_80117EF0();
        if (lbl_8064CD34 == 0) {
            if (fn_8006D3E4(0x800, 0) != 0) {
                fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0xC, 0, 1), 0, 0);
                break;
            }
            fn_80118060(2, flags);
            fn_801139D4();
            fn_8010AD7C();
        } else {
            lbl_8064CDC8 = 2;
            lbl_80331748[43] = flags;
        }
        break;
    case 14:
        fn_801A98F4(0x222, 100);
        fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
        fn_80144680(lbl_8064CDC0);
        lbl_8064CDC0 = fn_80144628(6, lbl_8024DE38, 0);
        fn_801446D4(lbl_8064CDC0, fn_8011336C);
        lbl_8064CD44 = 6;
        break;
    }
}
