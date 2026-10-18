extern int lbl_8064D760;

extern void GXSetVtxAttrFmt(int, int, int, int, int);

void fn_801EFFE4(int value)
{
    if (lbl_8064D760 != value) {
        lbl_8064D760 = value;
        GXSetVtxAttrFmt(1, 9, 1, 3, value & 0xFF);
        GXSetVtxAttrFmt(7, 9, 1, 3, lbl_8064D760 & 0xFF);
    }
}
