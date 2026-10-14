/* GXSetNumTevStages: update the TEV stage count in the general-mode
 * register and mark it for submission. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;       /* 0x204 */
    u8 pad208[0x2EC];
    u32 dirtyState;    /* 0x4F4 */
} GXData;
extern GXData *gx;

void fn_8022A2F4(u8 count)
{
    gx->genMode = (gx->genMode & ~(0xFUL << 10)) |
                  ((u32)(count - 1) << 10);
    gx->dirtyState |= 4;
}
