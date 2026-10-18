extern int lbl_8063B518[];
extern void GXSetTevKColorSel(int, int);

void fn_801EF220(int index, int value)
{
    if (lbl_8063B518[index] != value) {
        GXSetTevKColorSel(index, value);
        lbl_8063B518[index] = value;
    }
}
