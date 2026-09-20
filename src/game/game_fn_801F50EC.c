typedef unsigned char u8;
typedef unsigned short u16;

#pragma use_lmw_stmw on

extern void fn_801F4FC8(u8*, int*, int*, int*);

void fn_801F50EC(u8* source, u8* destination)
{
    int red;
    int green;
    int blue;
    u8 sample[3];
    register unsigned int destination_base;
    register u8* pixel;
    register int row_offset;
    register int column;
    register int row;
    register u8* source_base;
    register unsigned int block;
    register unsigned int output;

    destination_base = (unsigned int)destination;
    source_base = source;

    for (row = 0; row < 480; row++) {
        row_offset = (row & 3) * 8;
        block = destination_base + (row >> 2) * 5120;
        pixel = source_base;
        for (column = 0; column < 640; column += 2, pixel += 4) {
            /* Keep the tiled byte offset in the eventual store-address accumulator. */
            output = row_offset + (column & 3) * 2;
            output += (column >> 2) * 32;
            output = block + output;

            sample[0] = pixel[0];
            sample[1] = pixel[1];
            sample[2] = pixel[3];
            fn_801F4FC8(sample, &red, &green, &blue);
            ((u16*)output)[0] = ((red & 0xF8) << 8) | ((green & 0xFC) << 3) |
                        ((blue & 0xF8) >> 3);

            sample[0] = pixel[2];
            if (column != 638) {
                sample[1] = (pixel[1] + pixel[5]) / 2;
                sample[2] = (pixel[3] + pixel[7]) / 2;
            } else {
                sample[1] = pixel[1];
                sample[2] = pixel[3];
            }
            fn_801F4FC8(sample, &red, &green, &blue);
            ((u16*)output)[1] = ((red & 0xF8) << 8) | ((green & 0xFC) << 3) |
                        ((blue & 0xF8) >> 3);
        }
        source_base += 1280;
    }
}
