/* GXLoadNrmMtxImm: load the normal matrix into XF matrix memory. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef float f32;
typedef f32 Mtx[3][4];

typedef union {
    u8 u8;
    u32 u32;
    f32 f32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

extern void WriteMTXPS3x3from3x4(const Mtx mtx, volatile f32 *fifo);

void GXLoadNrmMtxImm(const Mtx mtx, register u32 id)
{
    register u32 address;

    /* ASM: mulli and addi form the XF address after the stack prologue;
     * MWCC hoists the equivalent C multiply into the prologue. */
    asm {
        mulli r4, id, 3
        addi address, r4, 0x400
    }
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = address | 0x80000;
    WriteMTXPS3x3from3x4(mtx, &GXWGFifo.f32);
}
