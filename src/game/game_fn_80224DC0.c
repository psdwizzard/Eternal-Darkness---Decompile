/* GXSetVtxDescv: update vertex descriptors from an attribute/type list. */
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
typedef struct GXVtxDescList {
    GXAttr attr;
    GXAttrType type;
} GXVtxDescList;

typedef struct GXData {
    u8 pad0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1C[0x418 - 0x1C];
    GXAttrType nrmType;
    u8 hasNrms;
    u8 hasBiNrms;
    u8 pad41E[0x4F4 - 0x41E];
    u32 dirtyState;
} GXData;
extern GXData *gx;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_80224DC0(const GXVtxDescList *list)
{
    GXAttr attr;
    GXAttrType type;

    while (list->attr != GX_VA_NULL) {
        attr = list->attr;
        type = list->type;
        switch (attr) {
        case GX_VA_PNMTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 0, type);
            break;
        case GX_VA_TEX0MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 1, type);
            break;
        case GX_VA_TEX1MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 2, type);
            break;
        case GX_VA_TEX2MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 3, type);
            break;
        case GX_VA_TEX3MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 4, type);
            break;
        case GX_VA_TEX4MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 5, type);
            break;
        case GX_VA_TEX5MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 6, type);
            break;
        case GX_VA_TEX6MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 7, type);
            break;
        case GX_VA_TEX7MTXIDX:
            SET_REG_FIELD(gx->vcdLo, 1, 8, type);
            break;
        case GX_VA_POS:
            SET_REG_FIELD(gx->vcdLo, 2, 9, type);
            break;
        case GX_VA_NRM:
            if (type != GX_NONE) {
                gx->hasNrms = 1;
                gx->hasBiNrms = 0;
                gx->nrmType = type;
            } else {
                gx->hasNrms = 0;
            }
            break;
        case GX_VA_NBT:
            if (type != GX_NONE) {
                gx->hasBiNrms = 1;
                gx->hasNrms = 0;
                gx->nrmType = type;
            } else {
                gx->hasBiNrms = 0;
            }
            break;
        case GX_VA_CLR0:
            SET_REG_FIELD(gx->vcdLo, 2, 13, type);
            break;
        case GX_VA_CLR1:
            SET_REG_FIELD(gx->vcdLo, 2, 15, type);
            break;
        case GX_VA_TEX0:
            SET_REG_FIELD(gx->vcdHi, 2, 0, type);
            break;
        case GX_VA_TEX1:
            SET_REG_FIELD(gx->vcdHi, 2, 2, type);
            break;
        case GX_VA_TEX2:
            SET_REG_FIELD(gx->vcdHi, 2, 4, type);
            break;
        case GX_VA_TEX3:
            SET_REG_FIELD(gx->vcdHi, 2, 6, type);
            break;
        case GX_VA_TEX4:
            SET_REG_FIELD(gx->vcdHi, 2, 8, type);
            break;
        case GX_VA_TEX5:
            SET_REG_FIELD(gx->vcdHi, 2, 10, type);
            break;
        case GX_VA_TEX6:
            SET_REG_FIELD(gx->vcdHi, 2, 12, type);
            break;
        case GX_VA_TEX7:
            SET_REG_FIELD(gx->vcdHi, 2, 14, type);
            break;
        }
        list++;
    }
    if (gx->hasNrms || gx->hasBiNrms) {
        SET_REG_FIELD(gx->vcdLo, 2, 11, gx->nrmType);
    } else {
        SET_REG_FIELD(gx->vcdLo, 2, 11, GX_NONE);
    }
    gx->dirtyState |= 8;
}
