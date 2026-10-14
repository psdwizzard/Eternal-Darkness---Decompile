/* GXSetFieldMask: select field updates in the pixel engine. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_8022A9B8(u8 evenMask, u8 oddMask)
{
    u32 fieldMask = oddMask;
    fieldMask = (fieldMask & ~(1UL << 1)) | ((u32)evenMask << 1);
    fieldMask = (fieldMask & 0x00FFFFFFUL) | 0x44000000UL;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = fieldMask;
    gx->bpSentNot = 0;
}
