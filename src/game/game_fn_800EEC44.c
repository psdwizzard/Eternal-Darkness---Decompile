typedef unsigned char u8;

extern u8 lbl_803281E0[];
extern void fn_800EEC0C(u8 *, int, int, int);

void fn_800EEC44(u8 *input, u8 *output, int width, int height)
{
    u8 * volatile output_ptr = output;
    int columns = width >> 1;
    int rows = height >> 1;
    u8 *middle = input + width * height;
    u8 *lower = middle;
    int y = 0;

    lower += columns * rows;

    while (rows > 0) {
        u8 *top0 = input;
        u8 *top1;
        int remaining = columns;
        int x = 0;
        u8 *dst = output_ptr + ((y >> 1) * width * 16) + ((y & 1) ? 16 : 0);

        input += width;
        top1 = input;
        while (remaining > 0) {
            int cb = *lower++ - 128;
            int cr = *middle++ - 128;
            int blue = -52 * cb - 25 * cr + 0x2020;
            int green = 102 * cb + 0x2020;
            int red = 129 * cr + 0x2020;
            int lum = ((int)lbl_803281E0[*top0++] - 16) * 74;
            u8 *block = dst + ((x >> 1) * 64) + ((x & 1) ? 4 : 0);
            u8 *block2 = block + 8;

            fn_800EEC0C(block, lum + green, lum + blue, lum + red);
            lum = ((int)lbl_803281E0[*top0++] - 16) * 74;
            fn_800EEC0C(block + 2, lum + green, lum + blue, lum + red);
            lum = ((int)lbl_803281E0[*top1++] - 16) * 74;
            fn_800EEC0C(block2, lum + green, lum + blue, lum + red);
            lum = ((int)lbl_803281E0[*top1++] - 16) * 74;
            fn_800EEC0C(block2 + 2, lum + green, lum + blue, lum + red);
            x++;
            remaining--;
        }
        input += width;
        y++;
        rows--;
    }
}
