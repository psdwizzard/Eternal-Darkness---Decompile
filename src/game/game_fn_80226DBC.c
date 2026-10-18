typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 pad0;
    u16 bpSentNot;
    u8 pad4[0x204 - 4];
    u32 genMode;
} GXData;

extern GXData *gx;

typedef union {
    u8 byte;
    u32 word;
} GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;

/* Upload the cached general-mode register to the graphics processor. */
void __GXSetGenMode(void)
{
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->genMode;
    gx->bpSentNot = 0;
}
