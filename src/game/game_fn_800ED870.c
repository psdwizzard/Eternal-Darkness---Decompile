extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int, int);
extern void GXSetArray(int, void*, unsigned char);
extern void GXSetVtxAttrFmt(int, int, int, int, unsigned char);

/* Shared storage; the attribute arrays begin at 0x40-byte offsets. */
extern unsigned char lbl_8024A620[0x178];

void fn_800ED870(void)
{
    unsigned int arrayBase = (unsigned int)lbl_8024A620;

    GXClearVtxDesc();
    GXSetVtxDesc(9, 2);
    GXSetVtxDesc(11, 2);
    GXSetVtxDesc(13, 2);
    GXSetArray(9, (void*)(arrayBase + 0x40), 6);
    GXSetArray(11, (void*)(arrayBase + 0x80), 4);
    GXSetArray(13, (void*)(arrayBase + 0xC0), 8);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 11, 1, 5, 0);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
}
