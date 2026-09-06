extern unsigned int lbl_80331738[];
extern unsigned int lbl_8024E388[];
extern int lbl_8064CD20;
extern unsigned int lbl_8064CCF0;
extern int lbl_8064CCE8;
extern int lbl_8064CD08;

extern void fn_801E8B6C(unsigned int, int);
extern int fn_801E8D34(unsigned int);
extern int fn_801E7B24(unsigned int*, int, int);
extern int fn_801E7AD0(unsigned int*, int, int);
extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);

void fn_8010FB5C(int value)
{
    int selection;

    switch (lbl_8064CD20) {
    case 0:
        fn_801E8B6C(lbl_80331738[0], value);
        break;
    case 2:
        selection = fn_801E8D34(lbl_80331738[2]);
        selection = fn_801E7B24(lbl_8024E388, 3, selection);
        if (fn_801E7AD0(lbl_8024E388, 3, selection) > 1 ||
            (fn_80201B44(), fn_80201814(), fn_8020216C() & 0x80000)) {
            fn_801E8B6C(lbl_8064CCF0, value);
            lbl_8064CCE8 = fn_801E8D34(lbl_8064CCF0);
        }
        lbl_8064CD08 = fn_801E8D34(lbl_8064CCF0);
        break;
    }
}
