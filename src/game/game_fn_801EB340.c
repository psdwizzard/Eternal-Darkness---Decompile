typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern void fn_802288C4(void*, void**, u16*, u16*, u32*, u32*, u32*, u8*);
extern void DCInvalidateRange(void*, u32);
extern void DCFlushRange(void*, u32);

void fn_801EB340(u8* dl, void* tex_obj)
{
    void* image;
    u32 format;
    u32 wrap_s;
    u32 wrap_t;
    u16 width;
    u16 height;
    u8 mipmap;
    u32 image_hi;
    u32 image_mid;
    u32 image_lo;
    u32 size;
    u32 image_value;
    int flags = 0;
    int amount;
    int done = 0;
    u32 w;
    u32 h;
    u32 m;
    u32 f;

    fn_802288C4(tex_obj, &image, &width, &height, &format, &wrap_s, &wrap_t, &mipmap);
    f = format;
    w = width - 1;
    h = height - 1;
    m = mipmap & 1;
    format = f % 16u;
    width = w;
    height = h;
    width = w & 0x3FF;
    height = h & 0x3FF;
    mipmap = m;
    format = (f % 16u) << 4;
    DCInvalidateRange(dl, 0x20);

    amount = 0;
    size = width | ((u32)height << 10);
    image_value = (u32)image & ~0x30000000;
    image_hi = image_value >> 21;
    image_mid = image_value >> 13;
    image_lo = image_value >> 5;

    while (!done) {
        switch (*dl) {
        case 0:
            dl += 1;
            amount += 1;
            break;
        case 8:
            dl += 6;
            amount += 6;
            break;
        case 0x10:
            dl += 9;
            amount += 9;
            break;
        case 0x61:
            switch (dl[1]) {
            case 0x80:
                if (flags != 0) {
                    done = 1;
                }
                break;
            case 0x88:
                flags |= 1;
                dl[2] = format | (size >> 16);
                dl[3] = size >> 8;
                dl[4] = size;
                DCFlushRange(dl, 3);
                break;
            case 0x84:
                dl[2] = 0;
                flags |= 0x10;
                dl[3] = 0;
                dl[4] = 0;
                DCFlushRange(dl, 3);
                break;
            case 0x94:
                dl[2] = image_hi;
                flags |= 2;
                dl[3] = image_mid;
                dl[4] = image_lo;
                DCFlushRange(dl, 3);
                break;
            case 0x30:
                flags |= 4;
                dl[2] = wrap_s;
                dl[3] = width >> 8;
                dl[4] = width;
                DCFlushRange(dl, 3);
                break;
            case 0x31:
                flags |= 8;
                dl[2] = wrap_t;
                dl[3] = height >> 8;
                dl[4] = height;
                DCFlushRange(dl, 3);
                break;
            }
            dl += 5;
            amount += 5;
            break;
        default:
            done = 1;
            break;
        }
        if (amount > 0x16) {
            DCInvalidateRange(dl, 0x20);
            amount = 0;
        }
    }
}
