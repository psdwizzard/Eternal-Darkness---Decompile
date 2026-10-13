typedef unsigned int u32;
typedef unsigned char u8;

typedef struct TaskDesc {
    char pad0[0x2C];
    void *unk2C;
} TaskDesc;

extern u32 lbl_8023A414[];
extern TaskDesc lbl_8024DE38;
typedef struct JournalState {
    u32 header[2];
    u32 chapterFlags[24];
    u32 bookFlags[12];
} JournalState;

extern JournalState lbl_80331748;
extern int lbl_80331A08[];
extern void *lbl_8064C4E0;
extern u8 lbl_8064CD28;
extern int lbl_8064CD34;
extern int lbl_8064CD44;
extern u32 lbl_8064CD48;
extern u32 lbl_8064CD50;
extern int lbl_8064CD54;
extern u32 lbl_8064CD60;
extern void *lbl_8064CDC0;
extern int lbl_8064CDC8;

extern void fn_8010AD7C(void);
extern void fn_80111F2C(int, unsigned int);
extern void fn_80112278(int);
extern void fn_8011336C(void);
extern void fn_801139D4(void);
extern void fn_801147D0(int, int);
extern void fn_80117EF0(void);
extern void *fn_80144628(int, void *, int);
extern void fn_80144680(void *);
extern void fn_801446D4(void *, void (*)(void));
extern void fn_80144C40(void);
extern int fn_801A98F4(int, int);
extern u32 *fn_801E5D20(void *);
extern void fn_801E5FB0(void *);
extern u32 fn_801E7578(u32);
extern int fn_801E79FC(void *, int);
extern int fn_801E8D34(int);
extern int fn_801E8D3C(int);
extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);

static inline u32 fn_80114330_mask(void)
{
    u32 mask;

    fn_80201B44();
    fn_80201814();
    if (fn_8020216C() & 0x4000) {
        mask = lbl_8023A414[lbl_8064CD34] & 0x70000;
    } else {
        mask = lbl_80331748.chapterFlags[lbl_8064CD34] & 0x70000 & lbl_8064CD48;
    }
    return mask;
}

void fn_80114330(int arg0, int arg1)
{
    u32 *task;
    int count;
    int sel;

    fn_80144C40();
    switch (lbl_8064CD44) {
    case 28:
        fn_801E5FB0(lbl_8024DE38.unk2C);
        lbl_8024DE38.unk2C = 0;
        fn_801139D4();
        fn_8010AD7C();
        break;
    case 17:
        fn_801147D0(arg0, arg1);
        break;
    case 0:
        lbl_8064CDC8 = 2;
        break;
    case 4:
        fn_801A98F4(0x263, 0x32);
        fn_80111F2C(0, 0);
        lbl_8064CD44 = 0;
        break;
    case 1:
    case 24:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 0;
        break;
    case 2:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 1;
        break;
    case 3:
        if (lbl_8064CD28 == 0x4B) {
            fn_801A98F4(0x263, 0x32);
            lbl_8064CD54--;
            lbl_8064CD50 &= ~(0xFF << (lbl_8064CD54 * 4));
            if (lbl_8064CD54 <= 1) {
                lbl_8064CD44 = 2;
            }
        }
        break;
    case 5:
        fn_801A98F4(0x263, 0x32);
        fn_80117EF0();
        lbl_8064CD44 = 0;
        break;
    case 6:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 5;
        break;
    case 8:
    case 21:
        task = fn_801E5D20(lbl_8024DE38.unk2C);
        if (task == 0 || (*task & 0x4000)) {
            fn_801A98F4(0x263, 0x32);
            fn_801E5FB0(lbl_8024DE38.unk2C);
            lbl_8024DE38.unk2C = 0;
            if (lbl_8064CD44 == 21) {
                lbl_8064CD44 = 22;
            } else {
                lbl_8064CD44 = 9;
            }
        }
        break;
    case 12:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 6;
        break;
    case 13:
        count = fn_801E7578(fn_80114330_mask());
        fn_801A98F4(0x263, 0x32);
        if (count > 1) {
            lbl_8064CD44 = 12;
            lbl_8064CD60 = fn_80114330_mask();
        } else {
            fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
            lbl_8064CD44 = 6;
        }
        break;
    case 14:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 13;
        fn_80144680(lbl_8064CDC0);
        lbl_8064CDC0 = fn_80144628(6, &lbl_8024DE38, 0);
        fn_801446D4(lbl_8064CDC0, fn_8011336C);
        fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
        break;
    case 10:
        fn_801A98F4(0x263, 0x32);
        fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
        lbl_8064CD44 = 6;
        break;
    case 11:
        sel = fn_801E8D34(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        fn_801A98F4(0x263, 0x32);
        switch (sel) {
        case 5:
        case 7:
        case 9:
            fn_80112278(fn_801E8D3C(lbl_80331A08[5]) * 3);
            lbl_8064CD44 = 6;
            break;
        default:
            lbl_8064CD44 = 10;
            lbl_8064CD60 = fn_80114330_mask();
            break;
        }
        break;
    case 16:
        if (fn_801E79FC(lbl_8064C4E0, 0x3D) == 0 || fn_801E79FC(lbl_8064C4E0, 0x3C) != 0) {
            fn_801A98F4(0x263, 0x32);
            lbl_8064CD44 = 0;
        }
        break;
    case 15:
        fn_801A98F4(0x263, 0x32);
        lbl_8064CD44 = 0;
        break;
    }
}
