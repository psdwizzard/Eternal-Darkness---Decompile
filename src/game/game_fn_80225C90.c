/* GXGetVtxAttrFmt: read back the component count, type and fraction bits
 * of one attribute from the shadowed vertex attribute format registers. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
} GXData;
extern GXData *gx;

typedef enum {
    GX_VA_PNMTXIDX, GX_VA_TEX0MTXIDX, GX_VA_TEX1MTXIDX, GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX, GX_VA_TEX4MTXIDX, GX_VA_TEX5MTXIDX, GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX, GX_VA_POS, GX_VA_NRM, GX_VA_CLR0, GX_VA_CLR1,
    GX_VA_TEX0, GX_VA_TEX1, GX_VA_TEX2, GX_VA_TEX3, GX_VA_TEX4,
    GX_VA_TEX5, GX_VA_TEX6, GX_VA_TEX7, GX_POS_MTX_ARRAY, GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY, GX_LIGHT_ARRAY, GX_VA_NBT
} GXAttr;

typedef int GXVtxFmt;
typedef int GXCompCnt;
typedef int GXCompType;

#define GX_TEX_ST 1
#define GX_NRM_NBT3 2
#define GX_RGB565 0

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))

void fn_80225C90(GXVtxFmt fmt, GXAttr attr, GXCompCnt *cnt, GXCompType *type, u8 *frac)
{
    u32 *va = &gx->vatA[fmt];
    u32 *vb = &gx->vatB[fmt];
    u32 *vc = &gx->vatC[fmt];

    switch (attr) {
    case GX_VA_POS:
        *cnt = GET_REG_FIELD(*va, 1, 0);
        *type = GET_REG_FIELD(*va, 3, 1);
        *frac = GET_REG_FIELD(*va, 5, 4);
        return;
    case GX_VA_NRM:
    case GX_VA_NBT:
        *cnt = GET_REG_FIELD(*va, 1, 9);
        if (*cnt == GX_TEX_ST && (*va >> 31) != 0) {
            *cnt = GX_NRM_NBT3;
        }
        *type = GET_REG_FIELD(*va, 3, 10);
        *frac = 0;
        return;
    case GX_VA_CLR0:
        *cnt = GET_REG_FIELD(*va, 1, 13);
        *type = GET_REG_FIELD(*va, 3, 14);
        *frac = 0;
        return;
    case GX_VA_CLR1:
        *cnt = GET_REG_FIELD(*va, 1, 17);
        *type = GET_REG_FIELD(*va, 3, 18);
        *frac = 0;
        return;
    case GX_VA_TEX0:
        *cnt = GET_REG_FIELD(*va, 1, 21);
        *type = GET_REG_FIELD(*va, 3, 22);
        *frac = GET_REG_FIELD(*va, 5, 25);
        return;
    case GX_VA_TEX1:
        *cnt = GET_REG_FIELD(*vb, 1, 0);
        *type = GET_REG_FIELD(*vb, 3, 1);
        *frac = GET_REG_FIELD(*vb, 5, 4);
        return;
    case GX_VA_TEX2:
        *cnt = GET_REG_FIELD(*vb, 1, 9);
        *type = GET_REG_FIELD(*vb, 3, 10);
        *frac = GET_REG_FIELD(*vb, 5, 13);
        return;
    case GX_VA_TEX3:
        *cnt = GET_REG_FIELD(*vb, 1, 18);
        *type = GET_REG_FIELD(*vb, 3, 19);
        *frac = GET_REG_FIELD(*vb, 5, 22);
        return;
    case GX_VA_TEX4:
        *cnt = GET_REG_FIELD(*vb, 1, 27);
        *type = GET_REG_FIELD(*vb, 3, 28);
        *frac = GET_REG_FIELD(*vc, 5, 0);
        return;
    case GX_VA_TEX5:
        *cnt = GET_REG_FIELD(*vc, 1, 5);
        *type = GET_REG_FIELD(*vc, 3, 6);
        *frac = GET_REG_FIELD(*vc, 5, 9);
        return;
    case GX_VA_TEX6:
        *cnt = GET_REG_FIELD(*vc, 1, 14);
        *type = GET_REG_FIELD(*vc, 3, 15);
        *frac = GET_REG_FIELD(*vc, 5, 18);
        return;
    case GX_VA_TEX7:
        *cnt = GET_REG_FIELD(*vc, 1, 23);
        *type = GET_REG_FIELD(*vc, 3, 24);
        *frac = GET_REG_FIELD(*vc, 5, 27);
        return;
    default:
        *cnt = GX_TEX_ST;
        *type = GX_RGB565;
        *frac = 0;
        return;
    }
}
