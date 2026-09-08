extern int lbl_8063B518[];
extern void fn_80229E74(int, int);

void fn_801EF220(int index, int value)
{
    if (lbl_8063B518[index] != value) {
        fn_80229E74(index, value);
        lbl_8063B518[index] = value;
    }
}
