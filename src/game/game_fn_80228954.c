/* GXLoadTexObjPreLoaded: load a texture object into a preloaded TMEM region. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTexObjInt {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    u32 fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObjInt;

typedef struct GXTexRegionInt {
    u32 image1;
    u32 image2;
} GXTexRegionInt;

typedef struct GXTlutRegionInt {
    u32 loadTlut1;
    u32 tlut;
} GXTlutRegionInt;

typedef GXTlutRegionInt *(*GXTlutRegionCallback)(u32 idx);

typedef struct GXData {
    u16 pad0;
    u16 bpSentNot;
    u8 pad4[0x414 - 0x4];
    GXTlutRegionCallback tlutRegionCallback;
    u8 pad418[0x45C - 0x418];
    u32 tImage0[8];
    u32 tMode0[8];
    u8 pad49C[0x4F4 - 0x49C];
    u32 dirtyState;
} GXData;
extern GXData *gx;

extern u8 GXTexMode0Ids[8];
extern u8 GXTexMode1Ids[8];
extern u8 GXTexImage0Ids[8];
extern u8 GXTexImage1Ids[8];
extern u8 GXTexImage2Ids[8];
extern u8 GXTexImage3Ids[8];
extern u8 GXTexTlutIds[8];

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

#define GX_WRITE_U8(v) (*(volatile u8 *)0xCC008000 = (u8)(v))
#define GX_WRITE_U32(v) (*(volatile u32 *)0xCC008000 = (u32)(v))

#define GX_WRITE_RAS_REG(val) \
    do { \
        GX_WRITE_U8(0x61); \
        GX_WRITE_U32(val); \
    } while (0)

void GXLoadTexObjPreLoaded(GXTexObjInt *t, GXTexRegionInt *r, u32 id)
{
    GXTlutRegionInt *tlr;

    SET_REG_FIELD(t->mode0, 8, 24, GXTexMode0Ids[id]);
    SET_REG_FIELD(t->mode1, 8, 24, GXTexMode1Ids[id]);
    SET_REG_FIELD(t->image0, 8, 24, GXTexImage0Ids[id]);
    SET_REG_FIELD(r->image1, 8, 24, GXTexImage1Ids[id]);
    SET_REG_FIELD(r->image2, 8, 24, GXTexImage2Ids[id]);
    SET_REG_FIELD(t->image3, 8, 24, GXTexImage3Ids[id]);

    GX_WRITE_RAS_REG(t->mode0);
    GX_WRITE_RAS_REG(t->mode1);
    GX_WRITE_RAS_REG(t->image0);
    GX_WRITE_RAS_REG(r->image1);
    GX_WRITE_RAS_REG(r->image2);
    GX_WRITE_RAS_REG(t->image3);

    if (!(t->flags & 2)) {
        tlr = gx->tlutRegionCallback(t->tlutName);
        SET_REG_FIELD(tlr->tlut, 8, 24, GXTexTlutIds[id]);
        GX_WRITE_RAS_REG(tlr->tlut);
    }

    gx->tImage0[id] = t->image0;
    gx->tMode0[id] = t->mode0;
    gx->dirtyState |= 1;
    gx->bpSentNot = 0;
}
