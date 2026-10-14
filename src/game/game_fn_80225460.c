/* GXGetVtxDescv: retrieve all vertex descriptors and append a terminator. */
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

extern void fn_802252AC(GXAttr attr, GXAttrType *type);

void fn_80225460(GXVtxDescList *list)
{
    GXAttr attr;

    for (attr = GX_VA_PNMTXIDX; attr < GX_VA_NBT + 1; attr++) {
        list[attr].attr = attr;
        fn_802252AC(attr, &list[attr].type);
    }
    list[attr].attr = GX_VA_NULL;
}
