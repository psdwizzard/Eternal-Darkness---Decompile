/* GXInitTexCacheRegion: describe an even/odd TMEM texture cache region. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTexRegion {
    u32 image1;
    u32 image2;
    u32 image3;
    u8 is32bMipmap;
    u8 isCached;
} GXTexRegion;

typedef enum {
    GX_TEXCACHE_32K,
    GX_TEXCACHE_128K,
    GX_TEXCACHE_512K,
    GX_TEXCACHE_NONE
} GXTexCacheSize;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXInitTexCacheRegion(GXTexRegion *region, u8 is_32b_mipmap, u32 tmem_even,
                          GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd) {
    u32 WidthExp2;
    GXTexRegion *t = region;

    switch (size_even) {
    case GX_TEXCACHE_32K:
        WidthExp2 = 3;
        break;
    case GX_TEXCACHE_128K:
        WidthExp2 = 4;
        break;
    case GX_TEXCACHE_512K:
        WidthExp2 = 5;
        break;
    }

    t->image1 = 0;
    SET_REG_FIELD(t->image1, 15, 0, tmem_even >> 5);
    SET_REG_FIELD(t->image1, 3, 15, WidthExp2);
    SET_REG_FIELD(t->image1, 3, 18, WidthExp2);
    SET_REG_FIELD(t->image1, 1, 21, 0);

    switch (size_odd) {
    case GX_TEXCACHE_32K:
        WidthExp2 = 3;
        break;
    case GX_TEXCACHE_128K:
        WidthExp2 = 4;
        break;
    case GX_TEXCACHE_512K:
        WidthExp2 = 5;
        break;
    case GX_TEXCACHE_NONE:
        WidthExp2 = 0;
        break;
    }

    t->image2 = 0;
    SET_REG_FIELD(t->image2, 15, 0, tmem_odd >> 5);
    SET_REG_FIELD(t->image2, 3, 15, WidthExp2);
    SET_REG_FIELD(t->image2, 3, 18, WidthExp2);
    t->is32bMipmap = is_32b_mipmap;
    t->isCached = 1;
}
