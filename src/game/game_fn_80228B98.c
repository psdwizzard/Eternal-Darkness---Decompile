/* GXLoadTlut: load a texture lookup table into its assigned region. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXTlutObj {
    u32 format;
    u32 load;
    u32 entries;
} GXTlutObj;

typedef struct GXTlutRegion {
    u32 load;
    GXTlutObj object;
} GXTlutRegion;

typedef GXTlutRegion *(*GXTlutRegionCallback)(u32 name);
typedef struct GXData {
    u8 padding[0x414];
    GXTlutRegionCallback tlutRegionCallback;
} GXData;
extern GXData *gx;
extern void __GXFlushTextureState(void);

typedef union GXWGPipe {
    u8 u8_data;
    u32 u32_data;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void GXLoadTlut(GXTlutObj *object, u32 name)
{
    u32 pad[2]; /* Unused space retained in the original stack frame. */
    GXTlutRegion *region = gx->tlutRegionCallback(name);

    __GXFlushTextureState();
    GXWGFifo.u8_data = 0x61;
    GXWGFifo.u32_data = object->load;
    GXWGFifo.u8_data = 0x61;
    GXWGFifo.u32_data = region->load;
    __GXFlushTextureState();
    object->format = (object->format & ~0x3FF) | (region->load & 0x3FF);
    region->object = *object;
}
