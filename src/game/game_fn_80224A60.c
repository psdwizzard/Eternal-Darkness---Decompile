/* fn_80224A60: GXSetVtxDesc (Dolphin SDK GXAttr.c).
 * Updates the vertex component descriptor (vcdLo/vcdHi) for one attribute,
 * folds the normal/NBT state into the NRM field and marks the VCD dirty. */

typedef unsigned char u8;
typedef unsigned long u32;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

typedef enum {
    GX_VA_PNMTXIDX,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NRM,
    GX_VA_CLR0,
    GX_VA_CLR1,
    GX_VA_TEX0,
    GX_VA_TEX1,
    GX_VA_TEX2,
    GX_VA_TEX3,
    GX_VA_TEX4,
    GX_VA_TEX5,
    GX_VA_TEX6,
    GX_VA_TEX7,
    GX_POS_MTX_ARRAY,
    GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY,
    GX_LIGHT_ARRAY,
    GX_VA_NBT
} GXAttr;

typedef enum {
    GX_NONE,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16
} GXAttrType;

typedef struct GXData {
    u8 pad0[0x14];
    u32 vcdLo;           /* 0x014 */
    u32 vcdHi;           /* 0x018 */
    u8 pad1C[0x418 - 0x1C];
    GXAttrType nrmType;  /* 0x418 */
    u8 hasNrms;          /* 0x41C */
    u8 hasBiNrms;        /* 0x41D */
    u8 pad41E[0x4F4 - 0x41E];
    u32 dirtyState;      /* 0x4F4 */
} GXData;

extern GXData *gx;

void fn_80224A60(GXAttr attr, GXAttrType type) {
    switch (attr) {
    case GX_VA_PNMTXIDX:   SET_REG_FIELD(gx->vcdLo, 1, 0, type); break;
    case GX_VA_TEX0MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 1, type); break;
    case GX_VA_TEX1MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 2, type); break;
    case GX_VA_TEX2MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 3, type); break;
    case GX_VA_TEX3MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 4, type); break;
    case GX_VA_TEX4MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 5, type); break;
    case GX_VA_TEX5MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 6, type); break;
    case GX_VA_TEX6MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 7, type); break;
    case GX_VA_TEX7MTXIDX: SET_REG_FIELD(gx->vcdLo, 1, 8, type); break;
    case GX_VA_POS:        SET_REG_FIELD(gx->vcdLo, 2, 9, type); break;
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
    case GX_VA_CLR0: SET_REG_FIELD(gx->vcdLo, 2, 13, type); break;
    case GX_VA_CLR1: SET_REG_FIELD(gx->vcdLo, 2, 15, type); break;
    case GX_VA_TEX0: SET_REG_FIELD(gx->vcdHi, 2, 0, type); break;
    case GX_VA_TEX1: SET_REG_FIELD(gx->vcdHi, 2, 2, type); break;
    case GX_VA_TEX2: SET_REG_FIELD(gx->vcdHi, 2, 4, type); break;
    case GX_VA_TEX3: SET_REG_FIELD(gx->vcdHi, 2, 6, type); break;
    case GX_VA_TEX4: SET_REG_FIELD(gx->vcdHi, 2, 8, type); break;
    case GX_VA_TEX5: SET_REG_FIELD(gx->vcdHi, 2, 10, type); break;
    case GX_VA_TEX6: SET_REG_FIELD(gx->vcdHi, 2, 12, type); break;
    case GX_VA_TEX7: SET_REG_FIELD(gx->vcdHi, 2, 14, type); break;
    default: break;
    }

    if (gx->hasNrms || gx->hasBiNrms) {
        SET_REG_FIELD(gx->vcdLo, 2, 11, gx->nrmType);
    } else {
        SET_REG_FIELD(gx->vcdLo, 2, 11, 0);
    }
    gx->dirtyState |= 8;
}
