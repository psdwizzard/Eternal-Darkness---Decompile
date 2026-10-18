typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct VIPosition {
    u16 dispPosX, dispPosY;
    u16 dispSizeX, dispSizeY;
    u16 adjustedDispPosX, adjustedDispPosY;
    u16 adjustedDispSizeY, adjustedPanPosY, adjustedPanSizeY;
    u16 fbSizeX, fbSizeY;
    u16 panPosX, panPosY, panSizeX, panSizeY;
    u16 padding;
    s32 xfbMode;
    u32 nonInter, tv;
    u8 wordPerLine, std, wpl;
    u8 padding1F;
    u32 bufAddr, tfbb, bfbb;
    u8 xof;
    u8 reserved2D[3];
    s32 black;
    s32 threeD;
    u32 rbufAddr, rtfbb, rbfbb;
    void *timing;
} VIPosition;

typedef struct VIState {
    u16 regs[59];
    u16 regsPadding;
    u16 shadowRegs[59];
    u16 shadowPadding;
    VIPosition position;
} VIState;

extern VIState lbl_80641AC8;
extern BOOL FBSet;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void setFbbRegs(VIPosition *hv, u32 *tfbb, u32 *bfbb,
                        u32 *rtfbb, u32 *rbfbb);

/* VISetNextFrameBuffer */
void VISetNextFrameBuffer(void *frameBuffer) {
    VIState *state = &lbl_80641AC8;
    BOOL enabled = OSDisableInterrupts();

    state->position.bufAddr = (u32)frameBuffer;
    FBSet = 1;
    setFbbRegs(&state->position, &state->position.tfbb,
                &state->position.bfbb, &state->position.rtfbb,
                &state->position.rbfbb);
    OSRestoreInterrupts(enabled);
}
