typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

extern u8 lbl_80607120[];

void fn_80184E3C(u8* dst, const u8* color, int height, int alpha_step, u8 width)
{
    u8* second;
    int alpha;
    int pass;
    int row;
    int row_count;

    row_count = (u8)height;
    second = dst + *(u16*)(lbl_80607120 + 2) * 4;
    pass = 0;
    alpha = color[3];
    do {
        row = 0;
        while (row < row_count) {
            int column;
            for (column = 0; column < width; column++) {
                dst[0] = color[0];
                dst[1] = color[1];
                dst[2] = color[2];
                dst[3] = alpha;
                dst += 4;
            }
            alpha -= (u8)alpha_step;
            if ((s16)alpha < 0) {
                alpha = 0;
            }
            row++;
        }
        pass++;
        alpha = color[3];
        dst = second;
    } while (pass < 2);
}
