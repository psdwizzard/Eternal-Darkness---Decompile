/* Hardware and cached GX state used while bringing up the command FIFO. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef struct GXFifoObj GXFifoObj;
typedef struct GXTexRegion GXTexRegion;
typedef struct GXTlutRegion GXTlutRegion;
extern u8 *gx;
extern u8 gxData_80641EA0[];
extern volatile u16 *__cpReg, *__peReg, *__memReg;
extern volatile u32 *__piReg;
extern void __GXFifoInit(void);
extern void GXInitFifoBase(GXFifoObj *, void *, u32);
extern void GXSetCPUFifo(GXFifoObj *);
extern void GXSetGPFifo(GXFifoObj *);
extern void __GXPEInit(void);
extern u32 PPCMfhid2(void);
extern void PPCMtwpar(u32);
extern void PPCMthid2(u32);
extern void __GXFlushTextureState(void);
extern void GXInitTexCacheRegion(GXTexRegion *, u32, u32, u32, u32, u32);
extern void GXInitTlutRegion(GXTlutRegion *, u32, u32);
extern void __GXSetTmemConfig(void);
extern void __GXInitGX(void);
#define GX32(o) (*(u32 *)(gx + (o)))
#define GX16(o) (*(u16 *)(gx + (o)))
#define GX8(o) (*(u8 *)(gx + (o)))
#define FIFO8 (*(volatile u8 *)0xCC008000)
#define FIFO32 (*(volatile u32 *)0xCC008000)
#define INIT_TEX_SLOT(streamOffset, streamIndex) do { \
    u32 offsetA = streamOffset + 0x1C; \
    u32 offsetB = streamOffset + 0x3C; \
    u32 command = 0x80 | streamIndex; \
    GX32(offsetA) = (GX32(offsetA) & 0xBFFFFFFF) | 0x40000000; \
    GX32(offsetB) = (GX32(offsetB) & 0x7FFFFFFF) | 0x80000000; \
    FIFO8 = 8; \
    FIFO8 = command; \
    FIFO32 = GX32(offsetB); \
    streamOffset += 4; \
    streamIndex++; \
} while (0)

GXFifoObj *GXInit(void *base, u32 size) {
    u32 hid2, clockDiv, i, pair, offset;
    u32 bpCommand;
    register u32 streamIndex;
    u32 regA, regB, texIndex, tableOffset, streamOffset;
    u8 *fifoBase = gxData_80641EA0;
    tableOffset = 0;
    GX8(0x4F0) = tableOffset;
    GX8(0x4F1) = 1;
    GX32(0x4DC) = tableOffset;
    GX32(0x4E0) = tableOffset;
    GX16(4) = tableOffset;
    __piReg = (volatile u32 *)0xCC003000;
    __cpReg = (volatile u16 *)0xCC000000;
    __peReg = (volatile u16 *)0xCC001000;
    __memReg = (volatile u16 *)0xCC004000;
    __GXFifoInit();
    GXInitFifoBase((GXFifoObj *)(fifoBase + 0x4F8), base, size);
    GXSetCPUFifo((GXFifoObj *)(fifoBase + 0x4F8));
    GXSetGPFifo((GXFifoObj *)(fifoBase + 0x4F8));
    __GXPEInit();
    hid2 = PPCMfhid2();
    PPCMtwpar(0x0C008000);
    PPCMthid2(hid2 | 0x40000000);
    /* Seed the BP register image and the TEV register tables. */
    texIndex = 0;
    regA = 0xC0;
    regB = 0xC1;
    GX32(0x204) = tableOffset;
    GX32(0x204) &= 0x00FFFFFF;
    GX32(0x124) = 0xFF;
    GX32(0x124) = (GX32(0x124) & 0x00FFFFFF) | 0x0F000000;
    GX32(0x7C) = 0;
    GX32(0x7C) = (GX32(0x7C) & 0x00FFFFFF) | 0x22000000;
    i = 0;
    do {
        u32 value;
        u32 tagA, tagB, tagC, tagD;
        u32 offA, offB, offC, offD;
        pair = texIndex >> 1;
        offset = pair << 2;
        offA = tableOffset + 0x130;
        offB = tableOffset + 0x170;
        offC = offset + 0x1B0;
        offD = offset + 0x100;
        tagA = regA << 24;
        tagB = regB << 24;
        tagC = (0xF6 + pair) << 24;
        tagD = (0x28 + pair) << 24;
        GX32(offA) = 0;
        GX32(offB) = 0;
        GX32(offD) = 0;
        GX32(0x49C + tableOffset) = 0xFF;
        value = GX32(offA) & 0x00FFFFFF;
        GX32(offA) = value | tagA;
        value = GX32(offB) & 0x00FFFFFF;
        GX32(offB) = value | tagB;
        value = GX32(offC) & 0x00FFFFFF;
        GX32(offC) = value | tagC;
        value = GX32(offD) & 0x00FFFFFF;
        GX32(offD) = value | tagD;
        tableOffset += 4;
        regA += 2;
        regB += 2;
        texIndex++;
    } while (i++ < 15);
    GX32(0x120) = 0;
    GX32(0x120) = (GX32(0x120) & 0x00FFFFFF) | 0x27000000;
    /* Eight texture coordinate size pairs, emitted two at a time. */
    for (i = 0; i < 4; i++) {
        offset = i * 8;
        GX32(0xB8 + offset) = 0;
        GX32(0xD8 + offset) = 0;
        GX32(0xB8 + offset) = (GX32(0xB8 + offset) & 0x00FFFFFF) | ((0x30 + i * 4) << 24);
        GX32(0xD8 + offset) = (GX32(0xD8 + offset) & 0x00FFFFFF) | ((0x31 + i * 4) << 24);
        GX32(0xBC + offset) = 0;
        GX32(0xDC + offset) = 0;
        GX32(0xBC + offset) = (GX32(0xBC + offset) & 0x00FFFFFF) | ((0x32 + i * 4) << 24);
        GX32(0xDC + offset) = (GX32(0xDC + offset) & 0x00FFFFFF) | ((0x33 + i * 4) << 24);
    }
    GX32(0xF8) = (GX32(0xF8) & 0x00FFFFFF) | 0x20000000;
    GX32(0xFC) = (GX32(0xFC) & 0x00FFFFFF) | 0x21000000;
    GX32(0x1D0) = (GX32(0x1D0) & 0x00FFFFFF) | 0x41000000;
    GX32(0x1D4) = (GX32(0x1D4) & 0x00FFFFFF) | 0x42000000;
    GX32(0x1D8) = (GX32(0x1D8) & 0x00FFFFFF) | 0x40000000;
    GX32(0x1DC) = (GX32(0x1DC) & 0x00FFFFFF) | 0x43000000;
    GX32(0x1FC) &= 0xFFFFFE7F;
    GX32(0x4F4) = 0;
    GX8(0x4F2) = 0;
    /* Convert the bus clock to texture cache timing register values. */
    clockDiv = *(volatile u32 *)0x800000F8 / 500;
    __GXFlushTextureState();
    bpCommand = 0x61;
    FIFO8 = bpCommand;
    FIFO32 = 0x69000400 | (clockDiv >> 11);
    __GXFlushTextureState();
    FIFO8 = bpCommand;
    FIFO32 = 0x46000200 | (clockDiv / 4224);
    streamOffset = 0;
    streamIndex = 0;
    /* Enable the eight vertex attribute formats in the CP register image. */
    for (i = 0; i < 8; i++) {
        INIT_TEX_SLOT(streamOffset, streamIndex);
    }
    FIFO8 = 0x10;
    FIFO32 = 0x1000;
    FIFO32 = 0x3F;
    FIFO8 = 0x10;
    FIFO32 = 0x1012;
    FIFO32 = 1;
    FIFO8 = 0x61;
    FIFO32 = 0x5800000F;
    /* Install standard texture cache and TLUT regions. */
    for (i = 0; i < 8; i++) GXInitTexCacheRegion((GXTexRegion *)(gx + 0x208 + i * 16), 0, i * 0x8000, 0, 0x80000 + i * 0x8000, 0);
    i = 0;
    do {
        GXInitTexCacheRegion((GXTexRegion *)(gx + 0x288 + i * 16), 0, (8 + i * 2) << 15, 0, (9 + i * 2) << 15, 0);
    } while (i++ < 3);
    i = 0;
    do {
        GXInitTlutRegion((GXTlutRegion *)(gx + 0x2D0 + i * 16), 0xC0000 + i * 0x2000, 0x10);
    } while (i++ < 15);
    i = 0;
    do {
        GXInitTlutRegion((GXTlutRegion *)(gx + 0x3D0 + i * 16), 0xE0000 + i * 0x8000, 0x40);
    } while (i++ < 3);
    __cpReg[3] = 0;
    GX32(0x4EC) &= 0xFFFFFF0F;
    FIFO8 = 8;
    FIFO8 = 0x20;
    FIFO32 = GX32(0x4EC);
    FIFO8 = 0x10;
    FIFO32 = 0x1006;
    FIFO32 = 0;
    FIFO8 = 0x61;
    FIFO32 = 0x23000000;
    FIFO8 = 0x61;
    FIFO32 = 0x24000000;
    FIFO8 = 0x61;
    FIFO32 = 0x67000000;
    __GXSetTmemConfig();
    __GXInitGX();
    return (GXFifoObj *)(fifoBase + 0x4F8);
}
