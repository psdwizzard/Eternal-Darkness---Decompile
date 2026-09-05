extern unsigned int lbl_80331738[];
extern unsigned int lbl_8024E388[];
extern int lbl_8064CD20;
extern int lbl_8064CD04;
extern int lbl_8064CCE8;
extern unsigned int lbl_8064CCF0;
extern int lbl_8064CD0C;
extern int lbl_8064CD08;

extern int fn_801E8D34(unsigned int);
extern int fn_801E8D24(unsigned int);
extern void fn_801E8B6C(unsigned int, int);
extern void fn_801E8B24(unsigned int, int, int);
extern void fn_80144C40(void);
extern int fn_8010F8B0(int);
extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);
extern int fn_801E7B24(unsigned int*, int, int);

void fn_8010F9D8(int direction)
{
    int previous;
    unsigned int* handles;
    int i;

    switch (lbl_8064CD20) {
    case 1:
        handles = lbl_80331738;
        fn_801E8D34(handles[1]);
        fn_801E8B6C(handles[1], direction);
        break;
    case 2:
        if (lbl_8064CD04 != 0) {
            break;
        }
        handles = lbl_80331738;
        previous = fn_801E8D34(handles[2]);
        fn_801E8B6C(handles[2], (short)((short)direction > 0 ? 1 : -1));
        if (previous != fn_801E8D24(handles[2])) {
            if (fn_801E8D24(handles[2]) < previous) {
                lbl_8064CD04 = -120;
            } else {
                lbl_8064CD04 = 120;
            }
        }
        fn_80144C40();
        if (fn_8010F8B0(lbl_8064CCE8) == 0) {
            for (i = 0; i < 3; i++) {
                if (fn_8010F8B0(i) != 0) {
                    fn_801E8B24(lbl_8064CCF0, i, 0);
                    break;
                }
            }
        } else {
            fn_801E8B24(lbl_8064CCF0, lbl_8064CCE8, 0);
        }
        fn_80201B44();
        fn_80201814();
        if (fn_8020216C() & 0x80000) {
            lbl_8064CD0C = fn_801E8D34(handles[2]);
        } else {
            lbl_8064CD0C = fn_801E7B24(lbl_8024E388, 3,
                                      fn_801E8D34(handles[2]));
        }
        lbl_8064CD08 = fn_801E8D34(lbl_8064CCF0);
        break;
    }
}
