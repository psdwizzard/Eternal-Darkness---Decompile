typedef unsigned long u32;
typedef unsigned short u16;

/* Like GXGetTexBufferSize helpers: compute tile counts for a texture format. */
void fn_802283AC(int fmt, u16 width, u16 height, u32* rowTiles, u32* colTiles, u32* cmpTiles) {
    u32 shiftX;
    u32 shiftY;

    switch (fmt) {
    case 0x00:
    case 0x08:
    case 0x0E:
    case 0x20:
    case 0x30:
        shiftX = 3;
        shiftY = 3;
        break;
    case 0x01:
    case 0x02:
    case 0x09:
    case 0x11:
    case 0x22:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x39:
    case 0x3A:
        shiftX = 3;
        shiftY = 2;
        break;
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x0A:
    case 0x13:
    case 0x16:
    case 0x23:
    case 0x2B:
    case 0x2C:
    case 0x3C:
        shiftX = 2;
        shiftY = 2;
        break;
    default:
        shiftY = 0;
        shiftX = 0;
        break;
    }

    if (width == 0) {
        width = 1;
    }
    if (height == 0) {
        height = 1;
    }

    *rowTiles = (width + (1 << shiftX) - 1) >> shiftX;
    *colTiles = (height + (1 << shiftY) - 1) >> shiftY;
    *cmpTiles = (fmt == 0x06 || fmt == 0x16) ? 2 : 1;
}
