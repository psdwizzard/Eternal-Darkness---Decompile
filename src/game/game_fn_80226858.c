typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    u32 data[0xB2];
} OSContext;

typedef void (*GXBreakPtCallback)(u16 token);

extern volatile u16 *__peReg;
extern GXBreakPtCallback TokenCB;

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);

/* GXTokenInterruptHandler: run the token callback in a fresh context with
 * the current PE token, then acknowledge the PE token interrupt. */
void GXTokenInterruptHandler(s16 interrupt, OSContext *context)
{
    u16 token;
    OSContext exceptionContext;

    token = __peReg[7];
    if (TokenCB != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        TokenCB(token);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    __peReg[5] = (u16)((__peReg[5] & ~0x4) | 0x4);
}
