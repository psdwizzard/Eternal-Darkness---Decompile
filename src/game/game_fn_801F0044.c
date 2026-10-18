extern int lbl_8064D760;

extern void GXSetVtxAttrFmt(int, int, int, int, int);

void fn_801F0044(void)
{
    lbl_8064D760 = 4;
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 10, 0, 4, 0);
    GXSetVtxAttrFmt(0, 13, 1, 3, 9);
    GXSetVtxAttrFmt(0, 14, 1, 3, 9);
    GXSetVtxAttrFmt(1, 9, 1, 3, lbl_8064D760 & 0xFF);
    GXSetVtxAttrFmt(1, 25, 2, 3, 15);
    GXSetVtxAttrFmt(1, 13, 1, 3, 9);
    GXSetVtxAttrFmt(3, 9, 1, 4, 0);
    GXSetVtxAttrFmt(5, 9, 1, 3, 0);
    GXSetVtxAttrFmt(5, 13, 1, 3, 9);
    GXSetVtxAttrFmt(5, 11, 1, 5, 0);
    GXSetVtxAttrFmt(6, 9, 1, 3, 0);
    GXSetVtxAttrFmt(6, 13, 1, 4, 0);
    GXSetVtxAttrFmt(6, 11, 1, 5, 0);
    GXSetVtxAttrFmt(7, 9, 1, 3, 4);
    GXSetVtxAttrFmt(7, 10, 0, 3, 15);
    GXSetVtxAttrFmt(7, 13, 1, 3, 9);
    GXSetVtxAttrFmt(2, 9, 1, 3, 5);
    GXSetVtxAttrFmt(2, 13, 1, 4, 0);
    GXSetVtxAttrFmt(4, 9, 1, 3, 0);
    GXSetVtxAttrFmt(4, 10, 1, 4, 0);
    GXSetVtxAttrFmt(4, 13, 1, 3, 9);
    GXSetVtxAttrFmt(4, 14, 1, 3, 9);
}
