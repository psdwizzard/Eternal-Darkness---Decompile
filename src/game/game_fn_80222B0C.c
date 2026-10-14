/* Return the default texture lookup table region for a TLUT name. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXTlutRegion {
    u32 loadTlut1;
    u32 tlutBase;
    u32 tlutAddress;
    u32 tlutEntries;
} GXTlutRegion;

typedef struct GXData {
    u8 padding[0x2D0];
    GXTlutRegion tlutRegions[20];
} GXData;

extern GXData *gx;

GXTlutRegion *fn_80222B0C(u32 name)
{
    if (name >= 20) {
        return 0;
    }
    return &gx->tlutRegions[name];
}
