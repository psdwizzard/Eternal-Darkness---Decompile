typedef signed int s32;
typedef unsigned int u32;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enabled);
extern void fn_80210004(OSThreadQueue *queue);
extern u32 lbl_8064DA60;
extern OSThreadQueue lbl_8064DA68;

/* Wait for the next video retrace. */
void fn_80217324(void)
{
    s32 enabled;
    u32 retraceCount;

    enabled = OSDisableInterrupts();
    retraceCount = lbl_8064DA60;
    do {
        fn_80210004(&lbl_8064DA68);
    } while (retraceCount == lbl_8064DA60);
    OSRestoreInterrupts(enabled);
}
