/* GXSetNumIndStages: set the indirect stage count and mark the BP mask
 * and general-mode register for update. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad208[0x4F4 - 0x208];
    u32 dirtyState;
} GXData;
extern GXData *gx;

void GXSetNumIndStages(u8 count)
{
    gx->genMode = (gx->genMode & ~(7UL << 16)) | ((u32)count << 16);
    gx->dirtyState |= 6;
}
