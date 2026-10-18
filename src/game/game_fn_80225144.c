/* Send the vertex descriptors to the command processor and update the vertex limit. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 reserved0[4];
    u16 vNum;
    u16 vLim;
    u8 reserved8[0x14 - 8];
    u32 vcdLo;
    u32 vcdHi;
    u8 reserved1C[0x41D - 0x1C];
    u8 hasBiNrms;
} GXData;

extern GXData *gx;
extern u8 lbl_8064C460[4];
extern u8 lbl_8064C464[4];
extern u8 lbl_8064C468[4];
extern void __GXXfVtxSpecs(void);

#define FIELD(reg, width, shift) (((reg) >> (shift)) & ((1UL << (width)) - 1))
typedef union { u8 byte; u32 word; } GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;
#define FIFO8 GXWGFifo.byte
#define FIFO32 GXWGFifo.word

void __GXSetVCD(void)
{
    u32 limit, lo, hi, normalCount;
    u32 descriptorLo, descriptorHi;
    FIFO8 = 8;
    FIFO8 = 0x50;
    descriptorLo = gx->vcdLo;
    FIFO32 = descriptorLo;
    FIFO8 = 8;
    FIFO8 = 0x60;
    descriptorHi = gx->vcdHi;
    FIFO32 = descriptorHi;
    __GXXfVtxSpecs();

    if (gx->vNum != 0) {
        normalCount = gx->hasBiNrms * 2 + 1;
        lo = gx->vcdLo;
        limit = FIELD(lo, 1, 0);
        limit += FIELD(lo, 1, 1);
        limit += FIELD(lo, 1, 2);
        limit += FIELD(lo, 1, 3);
        limit += FIELD(lo, 1, 4);
        limit += FIELD(lo, 1, 5);
        limit += FIELD(lo, 1, 6);
        limit += FIELD(lo, 1, 7);
        limit += FIELD(lo, 1, 8);
        limit += lbl_8064C468[FIELD(lo, 2, 9)];
        limit += lbl_8064C468[FIELD(lo, 2, 11)] * normalCount;
        limit += lbl_8064C460[FIELD(lo, 2, 13)];
        limit += lbl_8064C460[FIELD(lo, 2, 15)];
        hi = gx->vcdHi;
        limit += lbl_8064C464[FIELD(hi, 2, 0)];
        limit += lbl_8064C464[FIELD(hi, 2, 2)];
        limit += lbl_8064C464[FIELD(hi, 2, 4)];
        limit += lbl_8064C464[FIELD(hi, 2, 6)];
        limit += lbl_8064C464[FIELD(hi, 2, 8)];
        limit += lbl_8064C464[FIELD(hi, 2, 10)];
        limit += lbl_8064C464[FIELD(hi, 2, 12)];
        limit += lbl_8064C464[FIELD(hi, 2, 14)];
        gx->vLim = limit;
    }
}
