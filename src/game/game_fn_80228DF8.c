typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXTlutRegion GXTlutRegion;
typedef GXTlutRegion *(*GXTlutRegionCallback)(u32 name);

typedef struct GXData {
    u8 pad0[0x414];
    GXTlutRegionCallback tlutRegionCallback;
} GXData;

extern GXData *gx;

/* Install the TLUT region callback and return the previous callback. */
GXTlutRegionCallback fn_80228DF8(GXTlutRegionCallback callback)
{
    GXTlutRegionCallback previous = gx->tlutRegionCallback;
    gx->tlutRegionCallback = callback;
    return previous;
}
