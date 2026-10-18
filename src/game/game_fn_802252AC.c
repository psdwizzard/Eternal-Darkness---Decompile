/* GXGetVtxDesc: read back the current descriptor type of a vertex attribute. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef enum {
    GX_VA_PNMTXIDX, GX_VA_TEX0MTXIDX, GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX, GX_VA_TEX3MTXIDX, GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX, GX_VA_TEX6MTXIDX, GX_VA_TEX7MTXIDX,
    GX_VA_POS, GX_VA_NRM, GX_VA_CLR0, GX_VA_CLR1,
    GX_VA_TEX0, GX_VA_TEX1, GX_VA_TEX2, GX_VA_TEX3,
    GX_VA_TEX4, GX_VA_TEX5, GX_VA_TEX6, GX_VA_TEX7,
    GX_VA_POS_MTX_ARRAY, GX_VA_NRM_MTX_ARRAY,
    GX_VA_TEX_MTX_ARRAY, GX_VA_LIGHT_ARRAY, GX_VA_NBT,
    GX_VA_NULL = 0xFF
} GXAttr;

typedef enum { GX_NONE, GX_DIRECT, GX_INDEX8, GX_INDEX16 } GXAttrType;

typedef struct GXData {
    u8 pad0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1C[0x418 - 0x1C];
    GXAttrType nrmType;
    u8 hasNrms;
    u8 hasBiNrms;
} GXData;
extern GXData *gx;

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))

void GXGetVtxDesc(GXAttr attr, GXAttrType *type)
{
    u32 cpType;

    switch (attr) {
    case GX_VA_PNMTXIDX:   cpType = GET_REG_FIELD(gx->vcdLo, 1, 0); break;
    case GX_VA_TEX0MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 1); break;
    case GX_VA_TEX1MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 2); break;
    case GX_VA_TEX2MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 3); break;
    case GX_VA_TEX3MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 4); break;
    case GX_VA_TEX4MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 5); break;
    case GX_VA_TEX5MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 6); break;
    case GX_VA_TEX6MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 7); break;
    case GX_VA_TEX7MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 8); break;
    case GX_VA_POS:        cpType = GET_REG_FIELD(gx->vcdLo, 2, 9); break;
    case GX_VA_NRM:
        cpType = gx->hasNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0;
        break;
    case GX_VA_NBT:
        cpType = gx->hasBiNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0;
        break;
    case GX_VA_CLR0: cpType = GET_REG_FIELD(gx->vcdLo, 2, 13); break;
    case GX_VA_CLR1: cpType = GET_REG_FIELD(gx->vcdLo, 2, 15); break;
    case GX_VA_TEX0: cpType = GET_REG_FIELD(gx->vcdHi, 2, 0); break;
    case GX_VA_TEX1: cpType = GET_REG_FIELD(gx->vcdHi, 2, 2); break;
    case GX_VA_TEX2: cpType = GET_REG_FIELD(gx->vcdHi, 2, 4); break;
    case GX_VA_TEX3: cpType = GET_REG_FIELD(gx->vcdHi, 2, 6); break;
    case GX_VA_TEX4: cpType = GET_REG_FIELD(gx->vcdHi, 2, 8); break;
    case GX_VA_TEX5: cpType = GET_REG_FIELD(gx->vcdHi, 2, 10); break;
    case GX_VA_TEX6: cpType = GET_REG_FIELD(gx->vcdHi, 2, 12); break;
    case GX_VA_TEX7: cpType = GET_REG_FIELD(gx->vcdHi, 2, 14); break;
    default: cpType = 0; break;
    }
    *type = (GXAttrType)cpType;
}
