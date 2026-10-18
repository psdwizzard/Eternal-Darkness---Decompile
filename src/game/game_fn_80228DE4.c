typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXTexObj GXTexObj;
typedef struct GXTexRegion GXTexRegion;
typedef GXTexRegion *(*GXTexRegionCallback)(GXTexObj *obj, u32 id);

typedef struct GXData {
    u8 pad0[0x410];
    GXTexRegionCallback texRegionCallback;
} GXData;

extern GXData *gx;

/* Install the texture region callback and return the previous callback. */
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback)
{
    GXTexRegionCallback previous = gx->texRegionCallback;
    gx->texRegionCallback = callback;
    return previous;
}
