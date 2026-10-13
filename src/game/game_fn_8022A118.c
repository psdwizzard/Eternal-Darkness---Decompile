/* GXSetTevOrder: select the texture coordinate, texture map and color
 * channel feeding one TEV stage, updating the shadowed RAS1_TREF register. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int s32;

typedef struct GXData {
    u8 pad0[0x2];
    u16 bpSentNot;     /* 0x002 */
    u8 pad4[0xFC];
    u32 tref[8];       /* 0x100 */
    u8 pad120[0x37C];
    u32 texmapId[16];  /* 0x49C */
    u8 pad4DC[0x4];
    u32 tevTcEnab;     /* 0x4E0 */
    u8 pad4E4[0x10];
    u32 dirtyState;    /* 0x4F4 */
} GXData;
extern GXData *gx;

typedef int GXTevStageID;
typedef int GXTexCoordID;
typedef int GXTexMapID;
typedef int GXChannelID;

#define GX_MAX_TEXCOORD 8
#define GX_MAX_TEXMAP 8
#define GX_TEXCOORD0 0
#define GX_TEXMAP0 0
#define GX_TEXMAP_NULL 0xFF
#define GX_COLOR_NULL 0xFF

extern s32 lbl_802FF2D0[];

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_8022A118(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color)
{
    u32 *ptref;
    u32 tmap;
    u32 tcoord;

    ptref = &gx->tref[stage / 2];
    gx->texmapId[stage] = map;

    tmap = map & ~0x100;
    tmap = (tmap >= GX_MAX_TEXMAP) ? GX_TEXMAP0 : tmap;

    if (coord >= GX_MAX_TEXCOORD) {
        tcoord = GX_TEXCOORD0;
        gx->tevTcEnab = gx->tevTcEnab & ~(1 << stage);
    } else {
        tcoord = coord;
        gx->tevTcEnab = gx->tevTcEnab | (1 << stage);
    }

    if (stage & 1) {
        SET_REG_FIELD(*ptref, 3, 12, tmap);
        SET_REG_FIELD(*ptref, 3, 15, tcoord);
        SET_REG_FIELD(*ptref, 3, 19, (color == GX_COLOR_NULL) ? 7 : lbl_802FF2D0[color]);
        SET_REG_FIELD(*ptref, 1, 18, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    } else {
        SET_REG_FIELD(*ptref, 3, 0, tmap);
        SET_REG_FIELD(*ptref, 3, 3, tcoord);
        SET_REG_FIELD(*ptref, 3, 7, (color == GX_COLOR_NULL) ? 7 : lbl_802FF2D0[color]);
        SET_REG_FIELD(*ptref, 1, 6, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    }

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = *ptref;
    gx->bpSentNot = 0;
    gx->dirtyState |= 1;
}
