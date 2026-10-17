typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

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

typedef struct VIData {
    VITiming timings[8];
    u16 taps[25];
} VIData;

typedef struct Sram {
    u8 reserved[0x10];
    s8 displayOffsetH;
} Sram;
typedef struct OSThreadQueue { void *head, *tail; } OSThreadQueue;
typedef void (*OSInterruptHandler)(s16, void *);
typedef void (*VIRetraceCallback)(u32);

extern VIData lbl_802FE710;
extern VIState lbl_80641AC8;
extern s32 lbl_8064DA60, lbl_8064DA64;
extern OSThreadQueue lbl_8064DA68;
extern VIRetraceCallback lbl_8064DA70, lbl_8064DA74;
extern s32 lbl_8064DA78;
extern s16 lbl_8064DA7C, lbl_8064DA7E;
extern s32 lbl_8064DA80;
extern u32 lbl_8064DA88, lbl_8064DA8C, lbl_8064DA90;
extern u32 lbl_8064DA98, lbl_8064DA9C;
extern VITiming *lbl_8064DAA0;
extern u32 CurrTvMode_8064DAA4;
extern void fn_80216CB4(s32 mode);
extern VITiming *fn_80216C24(s32 mode);
extern void fn_802169B8(s16 interrupt, void *context);
extern Sram *__OSLockSram(void);
extern s32 __OSUnlockSram(s32 write);
extern void OSInitThreadQueue(OSThreadQueue *queue);
extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);

volatile u16 VI_REGS[] : 0xCC002000;
#define POS(type, field) (*(type *)((u8 *)&state->position + (u32)&((VIPosition *)0)->field))
#define TAP(i) (*(u16 *)((u8 *)data + 0x130 + (i) * 2))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

void fn_80216EAC(void)
{
    VIData *data = &lbl_802FE710;
    VIState *state = &lbl_80641AC8;
    u32 *nonInter;
    u32 *tvMode;
    VITiming *volatile *timing;
    u16 *dispY;
    s32 *xfbMode;
    u16 *panY;
    VITiming *currentTiming;
    VITiming *selectedTiming;
    s32 lowerClip, upperClip, shiftedTop, shiftedBottom;
    s16 offsetV;
    u16 displayConfig;
    u32 tv;
    Sram *sram;
    s32 factor, top, bottom;
    u16 acv;
    u16 *activeLines;

    /* Initialize the VI encoder and its pending register state. */
    lbl_8064DA78 = 1;
    if (!(VI_REGS[1] & 1)) {
        fn_80216CB4(0);
    }
    lbl_8064DA60 = 0;
    lbl_8064DA8C = 0;
    lbl_8064DA88 = 0;
    lbl_8064DA9C = 0;
    lbl_8064DA98 = 0;
    lbl_8064DA80 = 0;
    lbl_8064DA90 = 0;
    lbl_8064DA64 = 0;

    /* Pack the horizontal filter taps into the hardware registers. */
    VI_REGS[39] = TAP(0) | ((TAP(1) << 10) & 0xFC00);
    VI_REGS[38] = (TAP(1) >> 6) | (TAP(2) << 4);
    VI_REGS[41] = TAP(3) | ((TAP(4) << 10) & 0xFC00);
    VI_REGS[40] = (TAP(4) >> 6) | (TAP(5) << 4);
    VI_REGS[43] = TAP(6) | ((TAP(7) << 10) & 0xFC00);
    VI_REGS[42] = (TAP(7) >> 6) | (TAP(8) << 4);
    VI_REGS[45] = TAP(9) | (TAP(10) << 8);
    VI_REGS[44] = TAP(11) | (TAP(12) << 8);
    VI_REGS[47] = TAP(13) | (TAP(14) << 8);
    VI_REGS[46] = TAP(15) | (TAP(16) << 8);
    VI_REGS[49] = TAP(17) | (TAP(18) << 8);
    VI_REGS[48] = TAP(19) | (TAP(20) << 8);
    VI_REGS[51] = TAP(21) | (TAP(22) << 8);
    VI_REGS[50] = TAP(23) | (TAP(24) << 8);
    VI_REGS[56] = 640;

    /* Import the console's horizontal display calibration. */
    sram = __OSLockSram();
    lbl_8064DA7C = sram->displayOffsetH;
    lbl_8064DA7E = 0;
    __OSUnlockSram(0);

    displayConfig = VI_REGS[1];
    POS(u32, nonInter) = (displayConfig >> 2) & 1;
    nonInter = &POS(u32, nonInter);
    POS(u32, tv) = (displayConfig >> 8) & 3;
    tvMode = &POS(u32, tv);
    tv = POS(u32, tv);
    tv = tv == 3 ? 0 : tv;
    selectedTiming = fn_80216C24((tv << 2) + *nonInter);
    timing = &POS(VITiming *, timing);
    *timing = selectedTiming;
    state->regs[1] = displayConfig;
    lbl_8064DAA0 = (*timing);
    CurrTvMode_8064DAA4 = (*tvMode);
    POS(u16, dispSizeX) = 640;
    currentTiming = lbl_8064DAA0;
    activeLines = &currentTiming->acv;
    POS(u16, dispSizeY) = (u16)(currentTiming->acv * 2);
    POS(u16, dispPosX) = (720 - POS(u16, dispSizeX)) / 2;
    POS(u16, dispPosY) = 0;
    dispY = &POS(u16, dispPosY);

    /* Clip the display window and its corresponding framebuffer pan. */
    acv = *activeLines;
    POS(u16, adjustedDispPosX) = ((s16)POS(u16, dispPosX) + lbl_8064DA7C > 720 - POS(u16, dispSizeX)
        ? 720 - POS(u16, dispSizeX) : MAX(0, (s16)POS(u16, dispPosX) + lbl_8064DA7C));
    xfbMode = &POS(s32, xfbMode);
    factor = POS(s32, xfbMode) == 0 ? 2 : 1;
    top = (*dispY) & 1;
    offsetV = lbl_8064DA7E;
    POS(u16, adjustedDispPosY) = MAX((s16)(*dispY) + offsetV, top);
    shiftedBottom = (s16)acv;
    shiftedBottom *= 2;
    bottom = shiftedBottom - top;
    shiftedBottom = (s16)*dispY + (s16)POS(u16, dispSizeY) + offsetV;
    upperClip = MAX(shiftedBottom - bottom, 0);
    shiftedTop = (s16)*dispY + offsetV;
    if (shiftedTop - top < 0) {
        lowerClip = shiftedTop - top;
    } else {
        lowerClip = 0;
    }
    POS(u16, adjustedDispSizeY) = POS(u16, dispSizeY) + lowerClip - upperClip;
    shiftedTop = (s16)*dispY + offsetV;
    if (shiftedTop - top < 0) {
        lowerClip = shiftedTop - top;
    } else {
        lowerClip = 0;
    }
    panY = &POS(u16, panPosY);
    POS(u16, adjustedPanPosY) = POS(u16, panPosY) - lowerClip / factor;
    shiftedBottom = (s16)*dispY + (s16)POS(u16, dispSizeY) + offsetV;
    upperClip = MAX(shiftedBottom - bottom, 0);
    shiftedTop = (s16)*dispY + offsetV;
    if (shiftedTop - top < 0) {
        lowerClip = shiftedTop - top;
    } else {
        lowerClip = 0;
    }
    POS(u16, adjustedPanSizeY) = POS(u16, panSizeY) + lowerClip / factor - upperClip / factor;

    /* Establish the default framebuffer and retrace interrupt state. */
    POS(u16, fbSizeX) = 640;
    POS(u16, fbSizeY) = (u16)(*activeLines * 2);
    POS(u16, panPosX) = 0;
    (*panY) = 0;
    POS(u16, panSizeX) = 640;
    POS(u16, panSizeY) = (u16)(*activeLines * 2);
    (*xfbMode) = 0;
    POS(u8, wordPerLine) = 40;
    POS(u8, std) = 40;
    POS(u8, wpl) = 40;
    POS(u8, xof) = 0;
    POS(s32, black) = 1;
    POS(s32, threeD) = 0;
    OSInitThreadQueue(&lbl_8064DA68);
    VI_REGS[24] = VI_REGS[24] & 0x7FFF;
    VI_REGS[26] = VI_REGS[26] & 0x7FFF;
    lbl_8064DA70 = 0;
    lbl_8064DA74 = 0;
    __OSSetInterruptHandler(24, fn_802169B8);
    __OSUnmaskInterrupts(0x80);
}
