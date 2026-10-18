extern unsigned char lbl_80327E88[];
extern unsigned char lbl_80327CD8[];
extern void GXSetVtxDescv(void *);
extern void GXSetVtxAttrFmtv(int, void *);

void fn_800EC6C4(void)
{
    GXSetVtxDescv(lbl_80327E88);
    GXSetVtxAttrFmtv(3, lbl_80327CD8);
}
