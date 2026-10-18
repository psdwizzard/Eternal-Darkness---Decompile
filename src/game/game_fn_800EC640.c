extern unsigned char lbl_80327E88[];
extern unsigned char lbl_80327CD8[];
extern void GXGetVtxDescv(void *);
extern void GXGetVtxAttrFmtv(int, void *);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int, int);
extern void GXSetVtxAttrFmt(int, int, int, int, int);

void fn_800EC640(void)
{
    GXGetVtxDescv(lbl_80327E88);
    GXGetVtxAttrFmtv(3, lbl_80327CD8);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(10, 1);
    GXSetVtxAttrFmt(3, 9, 1, 4, 0);
    GXSetVtxAttrFmt(3, 10, 0, 4, 0);
}
