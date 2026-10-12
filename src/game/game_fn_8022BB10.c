/* fn_8022BB10: GXSetGPMetric (Dolphin SDK GXPerf.c).
 * Disables the currently selected GP performance counters, then selects
 * and enables the new pair (perf0 = XF/SU/RAS counters, perf1 = TX/TC/CP). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))

#define GX_WRITE_XF_REG(addr, v) \
    do { \
        GX_WRITE_U8(0x10); \
        GX_WRITE_U32(0x1000 + (addr)); \
        GX_WRITE_U32(v); \
    } while (0)

#define GX_WRITE_RAS_REG(v) \
    do { \
        GX_WRITE_U8(0x61); \
        GX_WRITE_U32(v); \
    } while (0)

#define GX_WRITE_CP_STRM_REG(addr, v) \
    do { \
        GX_WRITE_U8(0x08); \
        GX_WRITE_U8(addr); \
        GX_WRITE_U32(v); \
    } while (0)

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

typedef enum {
    GX_PERF0_VERTICES,
    GX_PERF0_CLIPPED,
    GX_PERF0_CLIP_VTX,
    GX_PERF0_CLIP_CLKS,
    GX_PERF0_XF_WAIT_IN,
    GX_PERF0_XF_WAIT_OUT,
    GX_PERF0_XF_XFRM_CLKS,
    GX_PERF0_XF_LIT_CLKS,
    GX_PERF0_XF_BOT_CLKS,
    GX_PERF0_XF_REGLD_CLKS,
    GX_PERF0_XF_REGRD_CLKS,
    GX_PERF0_CLIP_RATIO,
    GX_PERF0_TRIANGLES,
    GX_PERF0_TRIANGLES_CULLED,
    GX_PERF0_TRIANGLES_PASSED,
    GX_PERF0_TRIANGLES_SCISSORED,
    GX_PERF0_TRIANGLES_0TEX,
    GX_PERF0_TRIANGLES_1TEX,
    GX_PERF0_TRIANGLES_2TEX,
    GX_PERF0_TRIANGLES_3TEX,
    GX_PERF0_TRIANGLES_4TEX,
    GX_PERF0_TRIANGLES_5TEX,
    GX_PERF0_TRIANGLES_6TEX,
    GX_PERF0_TRIANGLES_7TEX,
    GX_PERF0_TRIANGLES_8TEX,
    GX_PERF0_TRIANGLES_0CLR,
    GX_PERF0_TRIANGLES_1CLR,
    GX_PERF0_TRIANGLES_2CLR,
    GX_PERF0_QUAD_0CVG,
    GX_PERF0_QUAD_NON0CVG,
    GX_PERF0_QUAD_1CVG,
    GX_PERF0_QUAD_2CVG,
    GX_PERF0_QUAD_3CVG,
    GX_PERF0_QUAD_4CVG,
    GX_PERF0_CLOCKS,
    GX_PERF0_NONE
} GXPerf0;

typedef enum {
    GX_PERF1_TEXELS,
    GX_PERF1_TX_IDLE,
    GX_PERF1_TX_REGS,
    GX_PERF1_TX_MEMSTALL,
    GX_PERF1_TC_CHECK1_2,
    GX_PERF1_TC_CHECK3_4,
    GX_PERF1_TC_CHECK5_6,
    GX_PERF1_TC_CHECK7_8,
    GX_PERF1_TC_MISS,
    GX_PERF1_VC_ELEMQ_FULL,
    GX_PERF1_VC_MISSQ_FULL,
    GX_PERF1_VC_MEMREQ_FULL,
    GX_PERF1_VC_STATUS7,
    GX_PERF1_VC_MISSREP_FULL,
    GX_PERF1_VC_STREAMBUF_LOW,
    GX_PERF1_VC_ALL_STALLS,
    GX_PERF1_VERTICES,
    GX_PERF1_FIFO_REQ,
    GX_PERF1_CALL_REQ,
    GX_PERF1_VC_MISS_REQ,
    GX_PERF1_CP_ALL_REQ,
    GX_PERF1_CLOCKS,
    GX_PERF1_NONE
} GXPerf1;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x4E0];
    u32 perf0;
    u32 perf1;
    u32 perfSel;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

void fn_8022BB10(GXPerf0 perf0, GXPerf1 perf1) {
    switch (gx->perf0) {
    case GX_PERF0_VERTICES:
    case GX_PERF0_CLIPPED:
    case GX_PERF0_CLIP_VTX:
    case GX_PERF0_CLIP_CLKS:
    case GX_PERF0_XF_WAIT_IN:
    case GX_PERF0_XF_WAIT_OUT:
    case GX_PERF0_XF_XFRM_CLKS:
    case GX_PERF0_XF_LIT_CLKS:
    case GX_PERF0_XF_BOT_CLKS:
    case GX_PERF0_XF_REGLD_CLKS:
    case GX_PERF0_XF_REGRD_CLKS:
    case GX_PERF0_CLOCKS:
        GX_WRITE_XF_REG(6, 0);
        break;
    case GX_PERF0_CLIP_RATIO:
    case GX_PERF0_TRIANGLES:
    case GX_PERF0_TRIANGLES_CULLED:
    case GX_PERF0_TRIANGLES_PASSED:
    case GX_PERF0_TRIANGLES_SCISSORED:
    case GX_PERF0_TRIANGLES_0TEX:
    case GX_PERF0_TRIANGLES_1TEX:
    case GX_PERF0_TRIANGLES_2TEX:
    case GX_PERF0_TRIANGLES_3TEX:
    case GX_PERF0_TRIANGLES_4TEX:
    case GX_PERF0_TRIANGLES_5TEX:
    case GX_PERF0_TRIANGLES_6TEX:
    case GX_PERF0_TRIANGLES_7TEX:
    case GX_PERF0_TRIANGLES_8TEX:
    case GX_PERF0_TRIANGLES_0CLR:
    case GX_PERF0_TRIANGLES_1CLR:
        GX_WRITE_RAS_REG(0x23000000);
        break;
    case GX_PERF0_TRIANGLES_2CLR:
    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
        GX_WRITE_RAS_REG(0x24000000);
        break;
    case GX_PERF0_NONE:
    default:
        break;
    }

    switch (gx->perf1) {
    case GX_PERF1_TEXELS:
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_CHECK1_2:
    case GX_PERF1_TC_CHECK3_4:
    case GX_PERF1_TC_CHECK5_6:
    case GX_PERF1_TC_CHECK7_8:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_CLOCKS:
        GX_WRITE_RAS_REG(0x67000000);
        break;
    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(gx->perfSel, 4, 4, 0);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        __cpReg[3] = 0;
        break;
    case GX_PERF1_NONE:
    default:
        break;
    }

    gx->perf0 = perf0;

    switch (gx->perf0) {
    case GX_PERF0_VERTICES:
        GX_WRITE_XF_REG(6, 0x273);
        break;
    case GX_PERF0_CLIPPED:
        GX_WRITE_XF_REG(6, 0x14A);
        break;
    case GX_PERF0_CLIP_VTX:
        GX_WRITE_XF_REG(6, 0x16B);
        break;
    case GX_PERF0_CLIP_CLKS:
        GX_WRITE_XF_REG(6, 0x84);
        break;
    case GX_PERF0_XF_WAIT_IN:
        GX_WRITE_XF_REG(6, 0xC6);
        break;
    case GX_PERF0_XF_WAIT_OUT:
        GX_WRITE_XF_REG(6, 0x210);
        break;
    case GX_PERF0_XF_XFRM_CLKS:
        GX_WRITE_XF_REG(6, 0x252);
        break;
    case GX_PERF0_XF_LIT_CLKS:
        GX_WRITE_XF_REG(6, 0x231);
        break;
    case GX_PERF0_XF_BOT_CLKS:
        GX_WRITE_XF_REG(6, 0x1AD);
        break;
    case GX_PERF0_XF_REGLD_CLKS:
        GX_WRITE_XF_REG(6, 0x1CE);
        break;
    case GX_PERF0_CLOCKS:
        GX_WRITE_XF_REG(6, 0x21);
        break;
    case GX_PERF0_XF_REGRD_CLKS:
        GX_WRITE_XF_REG(6, 0x153);
        break;
    case GX_PERF0_CLIP_RATIO:
        GX_WRITE_RAS_REG(0x2300AE7F);
        break;
    case GX_PERF0_TRIANGLES:
        GX_WRITE_RAS_REG(0x23008E7F);
        break;
    case GX_PERF0_TRIANGLES_CULLED:
        GX_WRITE_RAS_REG(0x23009E7F);
        break;
    case GX_PERF0_TRIANGLES_PASSED:
        GX_WRITE_RAS_REG(0x23001E7F);
        break;
    case GX_PERF0_TRIANGLES_SCISSORED:
        GX_WRITE_RAS_REG(0x2300AC3F);
        break;
    case GX_PERF0_TRIANGLES_0TEX:
        GX_WRITE_RAS_REG(0x2300AC7F);
        break;
    case GX_PERF0_TRIANGLES_1TEX:
        GX_WRITE_RAS_REG(0x2300ACBF);
        break;
    case GX_PERF0_TRIANGLES_2TEX:
        GX_WRITE_RAS_REG(0x2300ACFF);
        break;
    case GX_PERF0_TRIANGLES_3TEX:
        GX_WRITE_RAS_REG(0x2300AD3F);
        break;
    case GX_PERF0_TRIANGLES_4TEX:
        GX_WRITE_RAS_REG(0x2300AD7F);
        break;
    case GX_PERF0_TRIANGLES_5TEX:
        GX_WRITE_RAS_REG(0x2300ADBF);
        break;
    case GX_PERF0_TRIANGLES_6TEX:
        GX_WRITE_RAS_REG(0x2300ADFF);
        break;
    case GX_PERF0_TRIANGLES_7TEX:
        GX_WRITE_RAS_REG(0x2300AE3F);
        break;
    case GX_PERF0_TRIANGLES_8TEX:
        GX_WRITE_RAS_REG(0x2300A27F);
        break;
    case GX_PERF0_TRIANGLES_0CLR:
        GX_WRITE_RAS_REG(0x2300A67F);
        break;
    case GX_PERF0_TRIANGLES_1CLR:
        GX_WRITE_RAS_REG(0x2300AA7F);
        break;
    case GX_PERF0_TRIANGLES_2CLR:
        GX_WRITE_RAS_REG(0x2402C0C6);
        break;
    case GX_PERF0_QUAD_0CVG:
        GX_WRITE_RAS_REG(0x2402C16B);
        break;
    case GX_PERF0_QUAD_NON0CVG:
        GX_WRITE_RAS_REG(0x2402C0E7);
        break;
    case GX_PERF0_QUAD_1CVG:
        GX_WRITE_RAS_REG(0x2402C108);
        break;
    case GX_PERF0_QUAD_2CVG:
        GX_WRITE_RAS_REG(0x2402C129);
        break;
    case GX_PERF0_QUAD_3CVG:
        GX_WRITE_RAS_REG(0x2402C14A);
        break;
    case GX_PERF0_QUAD_4CVG:
        GX_WRITE_RAS_REG(0x2402C1AD);
        break;
    case GX_PERF0_NONE:
    default:
        break;
    }

    gx->perf1 = perf1;

    switch (gx->perf1) {
    case GX_PERF1_TEXELS:
        GX_WRITE_RAS_REG(0x67000042);
        break;
    case GX_PERF1_TX_IDLE:
        GX_WRITE_RAS_REG(0x67000084);
        break;
    case GX_PERF1_TX_REGS:
        GX_WRITE_RAS_REG(0x67000063);
        break;
    case GX_PERF1_TX_MEMSTALL:
        GX_WRITE_RAS_REG(0x67000129);
        break;
    case GX_PERF1_TC_MISS:
        GX_WRITE_RAS_REG(0x67000252);
        break;
    case GX_PERF1_CLOCKS:
        GX_WRITE_RAS_REG(0x67000021);
        break;
    case GX_PERF1_TC_CHECK1_2:
        GX_WRITE_RAS_REG(0x6700014B);
        break;
    case GX_PERF1_TC_CHECK3_4:
        GX_WRITE_RAS_REG(0x6700018D);
        break;
    case GX_PERF1_TC_CHECK5_6:
        GX_WRITE_RAS_REG(0x670001CF);
        break;
    case GX_PERF1_TC_CHECK7_8:
        GX_WRITE_RAS_REG(0x67000211);
        break;
    case GX_PERF1_VC_ELEMQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 2);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_MISSQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 3);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_MEMREQ_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 4);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_STATUS7:
        SET_REG_FIELD(gx->perfSel, 4, 4, 5);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_MISSREP_FULL:
        SET_REG_FIELD(gx->perfSel, 4, 4, 6);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_STREAMBUF_LOW:
        SET_REG_FIELD(gx->perfSel, 4, 4, 7);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VC_ALL_STALLS:
        SET_REG_FIELD(gx->perfSel, 4, 4, 9);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(gx->perfSel, 4, 4, 8);
        GX_WRITE_CP_STRM_REG(0x20, gx->perfSel);
        break;
    case GX_PERF1_FIFO_REQ:
        __cpReg[3] = 2;
        break;
    case GX_PERF1_CALL_REQ:
        __cpReg[3] = 3;
        break;
    case GX_PERF1_VC_MISS_REQ:
        __cpReg[3] = 4;
        break;
    case GX_PERF1_CP_ALL_REQ:
        __cpReg[3] = 5;
        break;
    case GX_PERF1_NONE:
    default:
        break;
    }

    gx->bpSentNot = 0;
}
