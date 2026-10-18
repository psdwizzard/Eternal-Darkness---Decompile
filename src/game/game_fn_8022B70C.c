/* GXSetCurrentMtx: select the current position/normal matrix index. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x80 - 4];
    u32 matIdxA;
    u32 matIdxB;
} GXData;

extern GXData *gx;

extern void __GXSetMatrixIndex(int attr);

void GXSetCurrentMtx(u32 id)
{
    u32 *reg = &gx->matIdxA;

    *reg = (*reg & ~0x3F) | id;
    __GXSetMatrixIndex(0);
}
