/* GXBegin: flush any dirty GX state, send a flush primitive if no vertex or
 * BP command has gone out since the last one, then write the draw command
 * (primitive | vertex format) and vertex count into the write-gather FIFO. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    /* vNumNot and bpSentNot are both cleared when commands are sent; the
     * pair is tested together as one word to see if anything went out. */
    union {
        struct {
            u16 vNumNot;   /* 0x000 */
            u16 bpSentNot; /* 0x002 */
        } s;
        u32 notSent;
    } sent;
    u8 pad4[0x4F4 - 4];
    u32 dirtyState; /* 0x4F4 */
} GXData;

extern GXData *gx;

typedef enum {
    GX_POINTS = 0xB8,
    GX_LINES = 0xA8,
    GX_LINESTRIP = 0xB0,
    GX_TRIANGLES = 0x90,
    GX_TRIANGLESTRIP = 0x98,
    GX_TRIANGLEFAN = 0xA0,
    GX_QUADS = 0x80
} GXPrimitive;

typedef enum {
    GX_VTXFMT0,
    GX_VTXFMT1,
    GX_VTXFMT2,
    GX_VTXFMT3,
    GX_VTXFMT4,
    GX_VTXFMT5,
    GX_VTXFMT6,
    GX_VTXFMT7,
    GX_MAX_VTXFMT
} GXVtxFmt;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

static inline void GXWriteU8(u8 v)
{
    GXWGFifo.u8 = v;
}

static inline void GXWriteU16(u16 v)
{
    GXWGFifo.u16 = v;
}

void __GXSetSUTexRegs(void); /* __GXSetSUTexRegs */
void __GXUpdateBPMask(void); /* __GXUpdateBPMask */
void __GXSetGenMode(void); /* __GXSetGenMode */
void __GXSetVCD(void); /* __GXSetVCD */
void __GXSetVAT(void); /* __GXSetVAT */
void __GXSendFlushPrim(void); /* __GXSendFlushPrim */

static inline void __GXSetDirtyState(void)
{
    if (gx->dirtyState & 1) {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2) {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4) {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8) {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10) {
        __GXSetVAT();
    }
    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }

    if (gx->sent.notSent == 0) {
        __GXSendFlushPrim();
    }

    GXWriteU8(vtxfmt | type);
    GXWriteU16(nverts);
}
