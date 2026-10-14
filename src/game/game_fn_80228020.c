/* GXSetNumChans: set the number of active lighting channels. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad208[0x4F4 - 0x208];
    u32 dirtyState;
} GXData;
extern GXData *gx;

typedef union GXWGPipe {
    u8 u8_data;
    u32 u32_data;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_80228020(u8 numChans)
{
    gx->genMode = (gx->genMode & ~0x70UL) | ((u32)numChans << 4);
    GXWGFifo.u8_data = 0x10;
    GXWGFifo.u32_data = 0x1009;
    GXWGFifo.u32_data = numChans;
    gx->dirtyState |= 4;
}
