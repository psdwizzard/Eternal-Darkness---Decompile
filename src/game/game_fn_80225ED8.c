/* GXGetVtxAttrFmtv: collect the vertex attribute formats and terminate the list. */
typedef unsigned char u8;

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

typedef struct GXVtxAttrFmtList {
    GXAttr attr;
    GXCompCnt cnt;
    GXCompType type;
    u8 frac;
} GXVtxAttrFmtList;

extern void GXGetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt *cnt,
                       GXCompType *type, u8 *frac);

void GXGetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList *list)
{
    int attr;

    for (attr = GX_VA_POS; attr < GX_VA_NBT + 1; ++attr, ++list) {
        list->attr = (GXAttr)attr;
        GXGetVtxAttrFmt(fmt, (GXAttr)attr, &list->cnt, &list->type, &list->frac);
    }
    list->attr = (GXAttr)0xFF;
}
