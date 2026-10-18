/* GXSetIndTexOrder: GXSetIndTexOrder (Dolphin SDK GXBump.c).
 * Selects the texture coordinate and texture map used by an indirect
 * texture stage, then sends the IREF BP register and marks the
 * indirect/TEV state dirty. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef enum {
    GX_INDTEXSTAGE0,
    GX_INDTEXSTAGE1,
    GX_INDTEXSTAGE2,
    GX_INDTEXSTAGE3
} GXIndTexStageID;

typedef int GXTexCoordID;
typedef int GXTexMapID;

typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad4[0x120 - 0x4];
    u32 iref;
    u8 pad124[0x4F4 - 0x124];
    u32 dirtyState;
} GXData;

extern GXData *gx;

typedef union { u8 u8; u32 u32; } PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map)
{
    switch (ind_stage) {
    case GX_INDTEXSTAGE0:
        SET_REG_FIELD(gx->iref, 3, 0, tex_map);
        SET_REG_FIELD(gx->iref, 3, 3, tex_coord);
        break;
    case GX_INDTEXSTAGE1:
        SET_REG_FIELD(gx->iref, 3, 6, tex_map);
        SET_REG_FIELD(gx->iref, 3, 9, tex_coord);
        break;
    case GX_INDTEXSTAGE2:
        SET_REG_FIELD(gx->iref, 3, 12, tex_map);
        SET_REG_FIELD(gx->iref, 3, 15, tex_coord);
        break;
    case GX_INDTEXSTAGE3:
        SET_REG_FIELD(gx->iref, 3, 18, tex_map);
        SET_REG_FIELD(gx->iref, 3, 21, tex_coord);
        break;
    }
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->iref;
    gx->dirtyState |= 3;
    gx->bpSentNot = 0;
}
