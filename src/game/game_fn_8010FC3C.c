typedef struct SelectionEntry {
    int field_0;
    int value;
    int field_8;
    int field_C;
    int field_10;
} SelectionEntry;

extern unsigned int lbl_80331738[];
extern SelectionEntry lbl_8024C0CC[];
extern unsigned int lbl_8024E388[];
extern int lbl_8064CD20;
extern int lbl_8064CD1C;

extern void fn_80144C40(void);
extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);
extern int fn_801E8D34(unsigned int);
extern int fn_801E7B24(unsigned int*, int, int);

void fn_8010FC3C(short amount)
{
    int index;
    int scan;
    int next;
    int found;
    int value;

    switch (lbl_8064CD20) {
    case 2:
        break;
    default:
        return;
    }
    fn_80144C40();
    fn_80201B44();
    fn_80201814();
    if (fn_8020216C() & 0x80000) {
        index = fn_801E8D34(lbl_80331738[2]);
    } else {
        index = fn_801E7B24(lbl_8024E388, 3,
                            fn_801E8D34(lbl_80331738[2]));
    }
    if (index == -1) {
        return;
    }
    if (amount > 0) {
        lbl_8064CD1C = lbl_8024C0CC[index].value;
        fn_80201B44();
        fn_80201814();
        if (fn_8020216C() & 0x80000) {
            lbl_8064CD1C = lbl_8024C0CC[index].value + 1;
        } else {
            next = fn_801E8D34(lbl_80331738[2]) + 1;
            scan = fn_801E7B24(lbl_8024E388, 3, next);
            if (scan < 0) {
                goto no_next;
            }
            found = 0;
            while (scan >= 0) {
                if (lbl_8024C0CC[scan].value > lbl_8064CD1C) {
                    lbl_8064CD1C = lbl_8024C0CC[scan].value;
                    found = 1;
                    break;
                }
                next++;
                scan = fn_801E7B24(lbl_8024E388, 3, next);
            }
            if (!found) {
no_next:
                lbl_8064CD1C = lbl_8024C0CC[53].value + 1;
            }
        }
        if (lbl_8064CD1C == lbl_8024C0CC[index].value) {
            lbl_8064CD1C = -1;
        } else {
            value = lbl_8064CD1C;
            lbl_8064CD1C = lbl_8024C0CC[53].value + 1 >=
                                  (value > 0 ? value : 0)
                              ? (value > 0 ? value : 0)
                              : lbl_8024C0CC[53].value + 1;
        }
    } else {
        fn_80201B44();
        fn_80201814();
        if (fn_8020216C() & 0x80000) {
            next = fn_801E8D34(lbl_80331738[2]) - 1;
        } else {
            next = fn_801E7B24(lbl_8024E388, 3,
                               fn_801E8D34(lbl_80331738[2]) - 1);
        }
        if (next != -1) {
            lbl_8064CD1C = lbl_8024C0CC[next].value;
            value = lbl_8064CD1C;
            lbl_8064CD1C = lbl_8024C0CC[53].value >=
                                  (value > 0 ? value : 0)
                              ? (value > 0 ? value : 0)
                              : lbl_8024C0CC[53].value;
        } else {
            lbl_8064CD1C = lbl_8024C0CC[index].value;
        }
    }
}
