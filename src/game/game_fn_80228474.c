/* GXInitTexObj: initialise a texture object describing an image in main
 * memory (size, format, wrap modes and optional mipmapping). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct __GXTexObjInt {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    u32 fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

#define GET_TILE_COUNT(a, b) (((a) + (1 << (b)) - 1) >> (b))

extern void *memset(void *dst, int c, u32 n);

static inline u32 GetMaxLOD(u16 width, u16 height)
{
    if (width > height) {
        return 31 - __cntlzw(width);
    } else {
        return 31 - __cntlzw(height);
    }
}

typedef struct GXTexObj {
    u32 dummy[8];
} GXTexObj;

void fn_80228474(GXTexObj *obj, void *image_ptr, u16 width, u16 height, u32 format,
                 u32 wrap_s, u32 wrap_t, u8 mipmap)
{
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    memset(t, 0, 0x20);
    SET_REG_FIELD(t->mode0, 2, 0, wrap_s);
    SET_REG_FIELD(t->mode0, 2, 2, wrap_t);
    SET_REG_FIELD(t->mode0, 1, 4, 1);
    if (mipmap != 0) {
        u8 lmax;

        t->flags |= 1;
        if (format == 8 || format == 9 || format == 10) {
            SET_REG_FIELD(t->mode0, 3, 5, 5);
        } else {
            SET_REG_FIELD(t->mode0, 3, 5, 6);
        }
        maxLOD = GetMaxLOD(width, height);
        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(t->mode1, 8, 8, lmax);
    } else {
        SET_REG_FIELD(t->mode0, 3, 5, 4);
    }
    t->fmt = format;
    SET_REG_FIELD(t->image0, 10, 0, width - 1);
    SET_REG_FIELD(t->image0, 10, 10, height - 1);
    SET_REG_FIELD(t->image0, 4, 20, format & 0xF);
    imageBase = ((u32)image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(t->image3, 21, 0, imageBase);
    switch (format & 0xF) {
    case 0:
    case 8:
        t->loadFmt = 1;
        rowT = 3;
        colT = 3;
        break;
    case 1:
    case 2:
    case 9:
        t->loadFmt = 2;
        rowT = 3;
        colT = 2;
        break;
    case 3:
    case 4:
    case 5:
    case 10:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    case 6:
        t->loadFmt = 3;
        rowT = 2;
        colT = 2;
        break;
    case 14:
        t->loadFmt = 0;
        rowT = 3;
        colT = 3;
        break;
    default:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    }
    t->loadCnt = (GET_TILE_COUNT(width, rowT) * GET_TILE_COUNT(height, colT)) & 0x7FFF;
    t->flags |= 2;
}
