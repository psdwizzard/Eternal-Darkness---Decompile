/* __GXSetDirtyState: flush each dirty piece of GX state flagged in
 * gx->dirtyState (SU tex size, BP mask, gen mode, VCD, VAT), then clear it. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x4F4];
    u32 dirtyState; /* 0x4F4 */
} GXData;

extern GXData *gx;

void fn_80228ED8(void); /* __GXSetSUTexSize */
void fn_80229874(void); /* __GXUpdateBPMask */
void fn_80226DBC(void); /* __GXSetGenMode */
void fn_80225144(void); /* __GXSetVCD */
void fn_80225BF4(void); /* __GXSetVAT */

void fn_80226A28(void) {
    if (gx->dirtyState & 1) {
        fn_80228ED8();
    }
    if (gx->dirtyState & 2) {
        fn_80229874();
    }
    if (gx->dirtyState & 4) {
        fn_80226DBC();
    }
    if (gx->dirtyState & 8) {
        fn_80225144();
    }
    if (gx->dirtyState & 0x10) {
        fn_80225BF4();
    }
    gx->dirtyState = 0;
}
