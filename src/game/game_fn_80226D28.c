typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad208[0x4F4 - 0x208];
    u32 dirtyState;
} GXData;

extern GXData *gx;

/* GXSetCullMode: translate the cull mode to the hardware encoding. */
void GXSetCullMode(int mode)
{
    switch (mode) {
    case 1:
        mode = 2;
        break;
    case 2:
        mode = 1;
        break;
    }

    gx->genMode = (gx->genMode & ~0xC000UL) | ((u32)mode << 14);
    gx->dirtyState |= 4;
}
