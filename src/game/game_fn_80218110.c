typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct VITiming {
    u8 equ;
    u8 padding;
    u16 acv;
    u16 prbOdd, prbEven, psbOdd, psbEven;
    u8 bs[4];
    u16 be[4];
    u16 nhlines, hlw;
    u8 hsy, hcs, hce, hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

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
    VITiming *timing;
} VIPosition;

typedef struct VIState {
    u16 regs[59];
    u16 regsPadding;
    u16 shadowRegs[59];
    u16 shadowPadding;
    VIPosition position;
} VIState;

extern VIState lbl_80641AC8;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv,
                        u16 prbOdd, u16 prbEven, u16 psbOdd, u16 psbEven,
                        BOOL black);

/* VISetBlack */
void VISetBlack(BOOL black) {
    VIState *state = &lbl_80641AC8;
    BOOL enabled = OSDisableInterrupts();
    VITiming *timing;

    state->position.black = black;
    timing = state->position.timing;
    setVerticalRegs(state->position.adjustedDispPosY, state->position.dispSizeY,
                timing->equ, timing->acv, timing->prbOdd, timing->prbEven,
                timing->psbOdd, timing->psbEven, state->position.black);
    OSRestoreInterrupts(enabled);
}
