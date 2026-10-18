typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DisplayConfig {
    u32 flags;
    u16 width;
    u16 field_6;
    u16 height;
    u8 pad_A[0xF];
    u8 field_19;
    u8 field_1A[0x18];
    u8 field_32[1];
} DisplayConfig;

typedef struct DisplayState {
    void* field_0;
    void* field_4;
} DisplayState;

typedef union U16ToDouble {
    struct {
        u32 high;
        u32 low;
    } words;
    double value;
} U16ToDouble;

extern char lbl_802FC2C0[];
extern char lbl_802FC644[];
extern char lbl_802662C0[];
extern u32 lbl_80651358;
extern float lbl_80651348;
extern float lbl_8065134C;
extern double lbl_80651350;
extern DisplayConfig* lbl_8064C38C;
extern DisplayState lbl_8064D71C;
extern u32 lbl_8064D718;
extern void* lbl_8064D714;
extern void* lbl_8064D710;
extern u32 lbl_8064D6D8;
extern void* lbl_8064D74C;

extern void* memset(void*, int, unsigned long);
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaLo(void*);
extern void OSInit(void);
extern void DVDInit(void);
extern void OSSetErrorHandler(int, void*);
extern void fn_8015DAB0(void*);
extern void DVDSetAutoInvalidation(int);
extern void fn_801EF788(void);
extern void VIInit(void);
extern void fn_801EFE84(int);
extern void fn_801EF39C(int);
extern void VIFlush(void);
extern void VIWaitForRetrace(void);
extern void fn_801EF814(void);
extern void fn_801EF840(void);
extern void fn_801EF89C(void);
extern void fn_801EF8F8(void);
extern void* OSInitAlloc(void*, void*, int);
extern void OSCreateHeap(void*, void*);
extern void OSSetCurrentHeap(void);
extern void fn_801EF910(void);
extern void VIConfigure(DisplayConfig*);
extern void VISetNextFrameBuffer(void*);
extern void* fn_801FEA8C(u32, int, char*, int);
extern void* GXInit(void*, u32);
extern void GXSetViewport(float, float, float, float, float, float);
extern void GXSetScissor(int, int, u16, u16);
extern void GXSetDispCopySrc(int, int, u16, u16);
extern void GXSetDispCopyDst(u16, u16);
extern void GXSetDispCopyYScale(float);
extern void GXSetCopyFilter(u8, void*, int, void*);
extern void GXSetPixelFmt(int, int);
extern void GXSetDither(int);
extern void GXSetCopyClear(u32*, u32);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void GXCopyDisp(void*, int);
extern void GXDrawDone(void);
extern void PADSetSpec(int);
extern void OSGetCurrentThread(void);
extern void fn_800AE254(void);
extern void fn_801A58FC(void);
extern void fn_8014447C(int);
extern void fn_80145004(void);
extern void fn_801EF400(void);

void fn_801EFA68(DisplayConfig* config)
{
    void* arenaLo;
    void* arenaHi;
    void* newLo;
    u16 height;
    u16 width;
    u32 framebufferSize;
    DisplayState* state = &lbl_8064D71C;
    char* label = lbl_802FC2C0;
    u32 initialValue = lbl_80651358;
    volatile u32 value = initialValue;
    u32 gxValue;
    U16ToDouble heightValue;
    U16ToDouble widthValue;

    fn_8015DAB0(label);
    OSInit();
    DVDInit();
    DVDSetAutoInvalidation(1);
    fn_801EF788();
    VIInit();
    fn_801EFE84(1);
    fn_801EF39C(1);
    VIFlush();
    VIWaitForRetrace();
    OSSetErrorHandler(2, fn_801EF814);
    OSSetErrorHandler(3, fn_801EF840);
    OSSetErrorHandler(7, fn_801EF89C);
    OSSetErrorHandler(15, fn_801EF8F8);

    lbl_8064C38C = config;
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    memset(arenaLo, 0, (u8*)arenaHi - (u8*)arenaLo);
    height = lbl_8064C38C->height;
    width = lbl_8064C38C->width;
    framebufferSize = ((u16)((width + 15) & ~15) * height) << 1;
    state->field_0 = lbl_802662C0;
    state->field_4 = (void*)(((u32)arenaLo + 31) & ~31);
    OSSetArenaLo((void*)(((u32)state->field_4 +
        framebufferSize + 31) & ~31));

    newLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    newLo = OSInitAlloc(newLo, arenaHi, 1);
    OSSetArenaLo(newLo);
    arenaLo = (void*)(((u32)newLo + 31) & ~31);
    arenaHi = (void*)((u32)arenaHi & ~31);
    memset(arenaLo, 0, (u8*)arenaHi - (u8*)arenaLo);
    OSCreateHeap(arenaLo, arenaHi);
    OSSetCurrentHeap();
    fn_801EF910();
    OSSetArenaLo(arenaHi);

    VIConfigure(lbl_8064C38C);
    VISetNextFrameBuffer(state->field_0);
    lbl_8064D718 = (u32)state->field_4;
    VIFlush();
    VIWaitForRetrace();
    lbl_8064D714 = fn_801FEA8C(0x30000, 1, lbl_802FC644, 991);
    lbl_8064D710 = GXInit(lbl_8064D714, 0x30000);
    lbl_8064D6D8 = 0;

    widthValue.words.high = 0x43300000;
    widthValue.words.low = lbl_8064C38C->width;
    heightValue.words.low = lbl_8064C38C->height;
    heightValue.words.high = 0x43300000;
    GXSetViewport(lbl_80651348, lbl_80651348,
                (float)(widthValue.value - lbl_80651350),
                (float)(heightValue.value - lbl_80651350), lbl_80651348,
                lbl_8065134C);
    GXSetScissor(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    GXSetDispCopySrc(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    GXSetDispCopyDst(lbl_8064C38C->width, lbl_8064C38C->height);
    GXSetDispCopyYScale((float)lbl_8064C38C->height / (float)lbl_8064C38C->field_6);
    GXSetCopyFilter(lbl_8064C38C->field_19, lbl_8064C38C->field_1A, 1,
                lbl_8064C38C->field_32);
    GXSetPixelFmt(1, 0);
    GXSetDither(1);
    gxValue = value;
    GXSetCopyClear(&gxValue, 0xFFFFFF);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXCopyDisp(state->field_0, 1);
    GXCopyDisp(state->field_0, 1);
    GXCopyDisp(state->field_4, 1);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    VIFlush();
    VISetNextFrameBuffer(state->field_4);
    lbl_8064D718 = (u32)state->field_0;
    VIWaitForRetrace();
    GXDrawDone();
    if (lbl_8064C38C->flags & 1) {
        VIWaitForRetrace();
    }
    lbl_8064D74C = config;
    PADSetSpec(5);
    OSGetCurrentThread();
    fn_800AE254();
    fn_801A58FC();
    fn_8014447C(1);
    fn_80145004();
    fn_801EF400();
}
