extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);

void GXSetTevOp(int index, int mode) {
    int color = 10;
    int alpha = 5;

    if (index != 0) {
        color = 0;
        alpha = 0;
    }

    switch (mode) {
    case 0:
        GXSetTevColorIn(index, 15, 8, color, 15);
        GXSetTevAlphaIn(index, 7, 4, alpha, 7);
        break;
    case 1:
        GXSetTevColorIn(index, color, 8, 9, 15);
        GXSetTevAlphaIn(index, 7, 7, 7, alpha);
        break;
    case 2:
        GXSetTevColorIn(index, color, 12, 8, 15);
        GXSetTevAlphaIn(index, 7, 4, alpha, 7);
        break;
    case 3:
        GXSetTevColorIn(index, 15, 15, 15, 8);
        GXSetTevAlphaIn(index, 7, 7, 7, 4);
        break;
    case 4:
        GXSetTevColorIn(index, 15, 15, 15, color);
        GXSetTevAlphaIn(index, 7, 7, 7, alpha);
        break;
    }

    GXSetTevColorOp(index, 0, 0, 0, 1, 0);
    GXSetTevAlphaOp(index, 0, 0, 0, 1, 0);
}
