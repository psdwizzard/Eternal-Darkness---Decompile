typedef unsigned int u32;

extern u32 lbl_8064D678;
extern void GXInvalidateVtxCache(void);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int, int);

void fn_801ECF50(u32 mode)
{
    if (mode == lbl_8064D678) {
        return;
    }

    lbl_8064D678 = mode;
    GXInvalidateVtxCache();
    GXClearVtxDesc();

    switch (mode) {
    case 1:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(25, 3);
        GXSetVtxDesc(13, 3);
        break;
    case 0:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(25, 3);
        GXSetVtxDesc(13, 3);
        GXSetVtxDesc(14, 3);
        break;
    case 7:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(10, 3);
        GXSetVtxDesc(13, 3);
        break;
    case 2:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(10, 3);
        GXSetVtxDesc(13, 3);
        GXSetVtxDesc(14, 3);
        break;
    case 3:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(13, 3);
        GXSetVtxDesc(11, 3);
        break;
    case 4:
        GXSetVtxDesc(9, 1);
        break;
    case 6:
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(13, 3);
        break;
    case 5:
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(13, 3);
        break;
    case 8:
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(13, 1);
        break;
    case 9:
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(13, 1);
        GXSetVtxDesc(11, 1);
        break;
    }
}
