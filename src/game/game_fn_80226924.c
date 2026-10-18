typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    u32 data[0xB2];
} OSContext;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef void (*GXDrawDoneCallback)(void);

extern volatile u16 *__peReg;
extern GXDrawDoneCallback DrawDoneCB;
extern u8 DrawDone;
extern OSThreadQueue FinishQueue;

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern void OSWakeupThread(OSThreadQueue *queue);

/* GXFinishInterruptHandler: acknowledge PE finish, run the draw-done
 * callback in a fresh context, and wake threads waiting on GXDrawDone. */
void GXFinishInterruptHandler(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;

    __peReg[5] = (u16)((__peReg[5] & ~0x8) | 0x8);
    DrawDone = 1;
    if (DrawDoneCB != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        DrawDoneCB();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    OSWakeupThread(&FinishQueue);
}
