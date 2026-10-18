typedef unsigned char u8;
typedef unsigned long u32;
typedef int BOOL;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef union {
    u8 byte;
    u32 word;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

extern u8 DrawDone; /* DrawDone */
extern OSThreadQueue FinishQueue;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL enabled);
void GXFlush(void); /* GXFlush */
void OSSleepThread(OSThreadQueue *queue); /* OSSleepThread */

static inline void GXSetDrawDone(void)
{
    BOOL enabled;
    union {
        u32 word;
        struct {
            u32 address : 8;
            u32 value : 24;
        } fields;
    } command;

    enabled = OSDisableInterrupts();
    command.word = 0x45000002;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = command.word;
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(enabled);
}

/* GXDrawDone: flush a finish command and sleep until the PE acknowledges it. */
void GXDrawDone(void)
{
    BOOL enabled;

    GXSetDrawDone();
    enabled = OSDisableInterrupts();
    while (DrawDone == 0) {
        OSSleepThread(&FinishQueue);
    }
    OSRestoreInterrupts(enabled);
}
