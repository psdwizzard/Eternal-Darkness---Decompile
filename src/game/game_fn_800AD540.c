typedef unsigned char u8;
typedef unsigned short u16;

extern u8 lbl_8031D858[];
extern u16* lbl_8064D71C[2];
extern void fn_8015CBB0(void*, int, u8*);
extern void DCStoreRange(void*, int);

static inline int clamp_index(int value, int limit)
{
    return limit < (value > 0 ? value : 0) ? limit : (value > 0 ? value : 0);
}

static inline int mask_pixel(const u8* mask, int width, int xmax, int ymax,
                             int x, int y)
{
    int cx = clamp_index(x, xmax);
    int cy = clamp_index(y, ymax);
    return mask[cy * (width >> 3) + (cx >> 3)] & (1 << (cx & 7));
}

void fn_800AD540(void* source, int width, int height, int source_stride)
{
    int buffer_index;
    u16 x;
    u16 y;
    int row_offset;
    int column_offset;
    const u8* center_row;
    u8* mask = lbl_8031D858;

    fn_8015CBB0(source, source_stride, mask);

    for (buffer_index = 0; buffer_index < 2; buffer_index++) {
        u16* pixels = lbl_8064D71C[buffer_index] + 0x21E80;
        for (y = 0; y < 46; y++) {
            for (x = 0; x < 640; x++) {
                if (x == 0 || y == 0 || x == 639 || y == 45) {
                    pixels[x] = 0x2880;
                } else {
                    pixels[x] = 0x1080;
                }
            }
            pixels += 640;
        }
    }

    row_offset = (480 - height) >> 1;
    column_offset = ((640 - width) >> 1) / 2;

    for (buffer_index = 0; buffer_index < 2; buffer_index++) {
        u16* buffer = lbl_8064D71C[buffer_index];
        int column_bytes = column_offset * 4;
        int row_bytes = row_offset * 1280;
        u16* output = (u16*)((u8*)buffer + row_bytes + column_bytes);
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                int intensity = 0;
                center_row = mask + (height - y - 1) * (width >> 3);
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x, height - y)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x, height - y - 2)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x + 1, height - y)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x + 1, height - y - 1)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x + 1, height - y - 2)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x - 1, height - y)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x - 1, height - y - 1)) {
                    intensity += 20;
                }
                if (mask_pixel(mask, width, width - 1,
                               height - 1, x - 1, height - y - 2)) {
                    intensity += 20;
                }
                if (center_row[x >> 3] &
                    (1 << (x & 7))) {
                    intensity = 150;
                }
                if (intensity > 150) {
                    intensity = 150;
                }
                output[x] = (u16)((intensity << 8) | 0x80);
            }
            output += 640;
        }
        DCStoreRange(buffer, 0x96000);
    }
}
