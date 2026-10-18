typedef unsigned int u32;

extern volatile u32 __DTKState;
extern void* __DTKFlushCallback;
extern unsigned char __block_for_flushtracks[9];

extern void __DTKCallbackForFlush(int, int);
extern void DVDCancelStreamAsync(void*, void (*)(int, int));

void DTKFlushTracks(void* callback)
{
    u32 old_state;

    if (__DTKState != 3) {
        old_state = __DTKState;
        __DTKState = 3;
        __DTKFlushCallback = callback;
        if (old_state == 1) {
            DVDCancelStreamAsync(__block_for_flushtracks, __DTKCallbackForFlush);
        } else {
            __DTKCallbackForFlush(0, 0);
        }
    }
}
