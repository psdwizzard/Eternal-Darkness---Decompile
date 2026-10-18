/* MakeNest: expand a 16-bit source image region into a 4-bit-per-pixel
 * byte buffer, mirroring the edges and zero-padding the remainder. */

typedef struct ImageSrc {
    unsigned char pad0[4];
    unsigned char *data;      /* 0x4 */
    unsigned short width;     /* 0x8 */
    unsigned short height;    /* 0xA */
    unsigned short stride;    /* 0xC */
    unsigned char pad1[0x325C - 0xE];
    unsigned short dstWidth;  /* 0x325C */
    unsigned short dstHeight; /* 0x325E */
    unsigned char pad2;
    unsigned char dst[1];     /* 0x3261 */
} ImageSrc;

void MakeNest(ImageSrc *img, int x, int y)
{
    unsigned char *row;
    unsigned char *src;
    unsigned char *out;
    unsigned char *mirror;
    int stride;
    int cols, mirrorCols, padCols;
    int rows, mirrorRows, padRows;
    int i, j;

    stride = img->stride;
    cols = img->width;
    rows = img->height;
    row = img->data + (x + y * stride) * 2;

    if (cols < img->dstWidth) {
        mirrorCols = img->dstWidth - cols;
        if (mirrorCols > cols) {
            mirrorCols = cols;
        }
        padCols = img->dstWidth - (cols + mirrorCols);
    } else {
        cols = img->dstWidth;
        padCols = 0;
        mirrorCols = 0;
    }

    if (rows < img->dstHeight) {
        mirrorRows = img->dstHeight - rows;
        if (mirrorRows > rows) {
            mirrorRows = rows;
        }
        padRows = img->dstHeight - (rows + mirrorRows);
    } else {
        rows = img->dstHeight;
        padRows = 0;
        mirrorRows = 0;
    }

    out = img->dst;
    for (j = rows; j > 0; j--) {
        src = row;
        for (i = cols; i > 0; i--) {
            *out++ = (*src >> 4) & 0xF;
            src += 2;
        }
        for (i = mirrorCols; i > 0; i--) {
            src -= 2;
            *out++ = (*src >> 4) & 0xF;
        }
        for (i = padCols; i > 0; i--) {
            *out++ = 0;
        }
        row += stride * 2;
    }

    mirror = out - img->dstWidth;
    for (j = mirrorRows; j > 0; j--) {
        src = mirror;
        for (i = img->dstWidth; i > 0; i--) {
            *out++ = *src++;
        }
        mirror -= img->dstWidth;
    }

    for (j = padRows; j > 0; j--) {
        for (i = img->dstWidth; i > 0; i--) {
            *out++ = 0;
        }
    }
}
