typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u16 vNum;
    u8 pad6[0x4F1 - 6];
    u8 dlSaveContext;
    u8 pad4F2[2];
    u32 dirtyState;
} GXData;

extern GXData *gx;

void GXSetMisc(int token, u32 value)
{
    switch (token) {
    case 0:
        break;
    case 1:
        gx->vNum = value;
        gx->vNumNot = !gx->vNum;
        gx->bpSentNot = 1;
        if (gx->vNum != 0) {
            gx->dirtyState |= 8;
        }
        break;
    case 2:
        gx->dlSaveContext = value != 0;
        break;
    }
}
