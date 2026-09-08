extern int lbl_8063B618[][4];
extern void fn_80229B08(int, int, int, int, int);

void fn_801EF000(int index, int value0, int value4, int value8, int valueC)
{
    if (lbl_8063B618[index][0] != value0 ||
        lbl_8063B618[index][1] != value4 ||
        lbl_8063B618[index][2] != value8 ||
        lbl_8063B618[index][3] != valueC) {
        lbl_8063B618[index][0] = value0;
        lbl_8063B618[index][1] = value4;
        lbl_8063B618[index][2] = value8;
        lbl_8063B618[index][3] = valueC;
        fn_80229B08(index, value0, value4, value8, valueC);
    }
}
