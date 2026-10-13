/* DVDCancel: cancel a DVD command and wait until cancellation completes. */
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef int BOOL;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);
struct DVDCommandBlock {
    u8 pad[0x08];
    s32 command;
    s32 state;
    u8 pad10[0x18];
    DVDCBCallback callback;
};

extern BOOL fn_80215D3C(DVDCommandBlock *block, DVDCBCallback callback);
extern void fn_80216058(s32 result, DVDCommandBlock *block);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern void fn_80210004(OSThreadQueue *queue);
extern OSThreadQueue __DVDThreadQueue;

s32 fn_80215FAC(DVDCommandBlock *block)
{
    BOOL enabled;
    s32 state;

    if (!fn_80215D3C(block, fn_80216058)) {
        return -1;
    }

    enabled = OSDisableInterrupts();
    for (;;) {
        state = block->state;
        if ((u32)(state + 1) <= 1 || state == 10) {
            break;
        }
        if (state == 3) {
            if ((u32)block->command - 4 <= 1 ||
                (u32)block->command == 13 || (u32)block->command == 15) {
                break;
            }
        }
        fn_80210004(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return 0;
}
