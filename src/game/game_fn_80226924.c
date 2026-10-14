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
extern GXDrawDoneCallback lbl_8064DBB4;
extern u8 lbl_8064DBB8;
extern OSThreadQueue lbl_8064DBBC;

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern void fn_802100F0(OSThreadQueue *queue);

/* GXFinishInterruptHandler: acknowledge PE finish, run the draw-done
 * callback in a fresh context, and wake threads waiting on GXDrawDone. */
void fn_80226924(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;

    __peReg[5] = (u16)((__peReg[5] & ~0x8) | 0x8);
    lbl_8064DBB8 = 1;
    if (lbl_8064DBB4 != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        lbl_8064DBB4();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    fn_802100F0(&lbl_8064DBBC);
}
