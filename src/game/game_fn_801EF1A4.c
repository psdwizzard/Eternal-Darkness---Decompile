extern int lbl_8063B718[][4];
extern void fn_80229B88(int, int, int, int, int);

void fn_801EF1A4(int index, int value0, int value4, int value8, int valueC)
{
    if (lbl_8063B718[index][0] != value0 ||
        lbl_8063B718[index][1] != value4 ||
        lbl_8063B718[index][2] != value8 ||
        lbl_8063B718[index][3] != valueC) {
        lbl_8063B718[index][0] = value0;
        lbl_8063B718[index][1] = value4;
        lbl_8063B718[index][2] = value8;
        lbl_8063B718[index][3] = valueC;
        fn_80229B88(index, value0, value4, value8, valueC);
    }
}
