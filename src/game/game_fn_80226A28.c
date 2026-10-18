/* __GXSetDirtyState: flush each dirty piece of GX state flagged in
 * gx->dirtyState (SU tex size, BP mask, gen mode, VCD, VAT), then clear it. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x4F4];
    u32 dirtyState; /* 0x4F4 */
} GXData;

extern GXData *gx;

void __GXSetSUTexRegs(void); /* __GXSetSUTexSize */
void __GXUpdateBPMask(void); /* __GXUpdateBPMask */
void __GXSetGenMode(void); /* __GXSetGenMode */
void __GXSetVCD(void); /* __GXSetVCD */
void __GXSetVAT(void); /* __GXSetVAT */

void __GXSetDirtyState(void) {
    if (gx->dirtyState & 1) {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2) {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4) {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8) {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10) {
        __GXSetVAT();
    }
    gx->dirtyState = 0;
}
