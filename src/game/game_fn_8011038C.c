typedef struct SelectionEntry {
    int field_0;
    int value;
    int field_8;
    int field_C;
    int field_10;
} SelectionEntry;

extern unsigned int lbl_80331738[];
extern unsigned int lbl_8024E388[];
extern SelectionEntry lbl_8024C0CC[];
extern int lbl_8064CD20;
extern int lbl_8064CD1C;
extern int lbl_8064CD04;

extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);
extern int fn_801E8D34(unsigned int);
extern int fn_801E8D44(unsigned int);
extern int fn_801E7B24(unsigned int*, int, int);
extern void fn_8010F9D8(short, int);

void fn_8011038C(void* event, int kind)
{
    int current;
    int previous;
    int currentOffset;
    int* values;
    int currentValue;
    int allow;

    if (kind == 1) {
        switch (lbl_8064CD20) {
        case 2:
            break;
        default:
            goto set_invalid;
        }
        fn_80201B44();
        fn_80201814();
        if (fn_8020216C() & 0x80000) {
            current = fn_801E8D34(lbl_80331738[2]);
        } else {
            current = fn_801E7B24(lbl_8024E388, 3,
                                  fn_801E8D34(lbl_80331738[2]));
        }
        if (current != -1) {
            values = &lbl_8024C0CC[0].value;
            allow = 1;
            currentOffset = current * sizeof(SelectionEntry);
            currentValue = *(int*)((char*)values + currentOffset);
            fn_80201B44();
            fn_80201814();
            if (fn_8020216C() & 0x80000) {
                previous = fn_801E8D34(lbl_80331738[2]) - 1;
            } else {
                previous = fn_801E7B24(lbl_8024E388, 3,
                                       fn_801E8D34(lbl_80331738[2]) - 1);
            }
            if (current < fn_801E7B24(lbl_8024E388, 3,
                                      fn_801E8D44(lbl_80331738[2]))) {
                allow = 0;
            }
            if (lbl_8064CD1C != -1 &&
                (!allow || lbl_8064CD1C <= currentValue) &&
                (*(int*)((char*)values + currentOffset) ==
                     *(int*)((char*)values + previous * sizeof(SelectionEntry)) ||
                 lbl_8064CD1C != *(int*)((char*)values + currentOffset))) {
                fn_8010F9D8((short)((lbl_8064CD1C - currentValue) * 2), 0);
            } else if (lbl_8064CD04 == 0) {
                lbl_8064CD1C = -1;
            }
        }
    }
    return;

set_invalid:
    lbl_8064CD1C = -1;
}
