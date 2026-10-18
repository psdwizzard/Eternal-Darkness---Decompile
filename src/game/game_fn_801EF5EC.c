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

extern char lbl_802FC500[];
extern DisplayConfig* lbl_8064C38C;
extern DisplayState lbl_8064D71C;
extern u32 lbl_8064D718;
extern void* lbl_8064D74C;

extern void* VIGetDTVStatus(void);
extern void fn_801EFE84(int);
extern void VIConfigure(DisplayConfig*);
extern void VISetNextFrameBuffer(void*);
extern void GXSetViewport(float, float, float, float, float, float);
extern void GXSetScissor(int, int, u16, u16);
extern void GXSetDispCopySrc(int, int, u16, u16);
extern void GXSetDispCopyDst(u16, u16);
extern void GXSetDispCopyYScale(float);
extern void GXSetCopyFilter(u8, void*, int, void*);
extern void GXSetPixelFmt(int, int);
extern void GXSetDither(int);
extern void GXCopyDisp(void*, int);
extern void VIFlush(void);
extern void VIWaitForRetrace(void);

void fn_801EF5EC(void)
{
    if (!VIGetDTVStatus()) {
        return;
    }

    fn_801EFE84(1);
    lbl_8064C38C = (DisplayConfig*)lbl_802FC500;
    VIConfigure(lbl_8064C38C);
    VISetNextFrameBuffer(lbl_8064D71C.field_0);
    lbl_8064D718 = (u32)lbl_8064D71C.field_4;

    GXSetViewport(0.0f, 0.0f, (float)lbl_8064C38C->width,
                (float)lbl_8064C38C->height, 0.0f, 1.0f);
    GXSetScissor(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    GXSetDispCopySrc(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    GXSetDispCopyDst(lbl_8064C38C->width, lbl_8064C38C->height);
    GXSetDispCopyYScale((float)lbl_8064C38C->height / (float)lbl_8064C38C->field_6);
    GXSetCopyFilter(lbl_8064C38C->field_19, lbl_8064C38C->field_1A, 1,
                lbl_8064C38C->field_32);
    GXSetPixelFmt(1, 0);
    GXSetDither(1);
    GXCopyDisp(lbl_8064D71C.field_0, 1);
    GXCopyDisp(lbl_8064D71C.field_0, 1);
    GXCopyDisp(lbl_8064D71C.field_4, 1);
    VIFlush();
    VIWaitForRetrace();
    if (lbl_8064C38C->flags & 1) {
        VIWaitForRetrace();
    }
    fn_801EFE84(0);
    lbl_8064D74C = lbl_8064C38C;
}
