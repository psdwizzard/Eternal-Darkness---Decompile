/* GXGetTexBufferSize: storage required for a tiled texture and its mip levels. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define TILE_COUNT(size, shift) (((size) + (1 << (shift)) - 1) >> (shift))

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod)
{
    u32 size;
    u32 level;
    int width_shift;
    int height_shift;
    u32 tile_size;
    u32 width_tiles;
    u32 height_tiles;

    switch (format) {
    case 0x0:
    case 0x8:
    case 0xE:
    case 0x20:
    case 0x30:
        width_shift = 3;
        height_shift = 3;
        break;
    case 0x1:
    case 0x2:
    case 0x9:
    case 0x11:
    case 0x22:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x39:
    case 0x3A:
        width_shift = 3;
        height_shift = 2;
        break;
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0xA:
    case 0x13:
    case 0x16:
    case 0x23:
    case 0x2B:
    case 0x2C:
    case 0x3C:
        width_shift = 2;
        height_shift = 2;
        break;
    default:
        width_shift = height_shift = 0;
        break;
    }
    if (format == 6 || format == 0x16) {
        tile_size = 64;
    } else {
        tile_size = 32;
    }
    if (mipmap == 1) {
        size = 0;
        for (level = 0; level < max_lod; ++level) {
            width_tiles = TILE_COUNT(width, width_shift);
            height_tiles = TILE_COUNT(height, height_shift);
            size += tile_size * (width_tiles * height_tiles);
            if (width == 1 && height == 1) {
                break;
            }
            width = width > 1 ? width >> 1 : 1;
            height = height > 1 ? height >> 1 : 1;
        }
    } else {
        width_tiles = TILE_COUNT(width, width_shift);
        height_tiles = TILE_COUNT(height, height_shift);
        size = tile_size * (width_tiles * height_tiles);
    }
    return size;
}
