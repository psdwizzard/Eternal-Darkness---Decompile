typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef struct OSThread OSThread;

typedef struct Stream {
    s32 handle;
    u8* buffer;
    volatile u32 flags;
    s32 half;
    s32 lastHalf;
    volatile s32 delay;
    volatile u8 curVolume;
    volatile u8 volume;
    volatile u8 newVolume;
    u8 pan;
} Stream;

typedef struct StreamWork {
    u8 pad0[0x4578];
    u8 controlQueue[0x20];
    void* replyMessages[8];
    u8 replyQueue[0x20];
    u8 stack[0x2000];
    u8 thread[0x310];
    void* requestMessages[8];
    u8 requestQueue[0x20];
    Stream streams[2];
} StreamWork;

extern StreamWork lbl_80643C20;
extern volatile s32 lbl_8064DC38;
extern void* lbl_8064DC60[2];
extern s32 lbl_8064DC68;

extern void fn_8020D1F0(void* queue, void* messages, s32 count);
extern s32 fn_8020F84C(OSThread*, void* (*)(void*), void*, void*, u32, s32, u16);
extern s32 fn_8020FC0C(OSThread*);
extern void* fn_80236D60(void*);

void fn_802364B8(s32 initialized) {
    register StreamWork* work = &lbl_80643C20;

    if (lbl_8064DC38 != 0) {
        register Stream* streams;
        register u32 flags;
        /* ASM: addi and lwz preserve the shared stream-array base that MWCC
         * otherwise folds into the individual volatile field displacements. */
        asm {
            addi streams, work, 0x6928
            lwz flags, 8(streams)
        }
        streams[0].flags = flags | 8;
        streams[1].flags |= 8;
    }
    lbl_8064DC68 = 1;
    if (initialized == 0) {
        register void* stackTop;
        register void* (*entry)(void*);
        register u32 entryHigh;
        fn_8020D1F0(work->requestQueue, work->requestMessages, 8);
        fn_8020D1F0(work->replyQueue, work->replyMessages, 8);
        fn_8020D1F0(work->controlQueue, lbl_8064DC60, 2);
        /* ASM: lis and addi preserve the callback-address split and the
         * separate stack-base and stack-size additions that MWCC folds in C. */
        asm {
            lis entryHigh, fn_80236D60@ha
            addi stackTop, work, 0x45D8
            addi entry, entryHigh, fn_80236D60@l
        }
        /* ASM: addi completes the stack-end calculation separately from the
         * base; C folds it into the adjacent thread object's address. */
        asm { addi stackTop, stackTop, 0x2000 }
        fn_8020F84C((OSThread*)work->thread, entry, 0,
                    stackTop, 0x2000, 0x12, 1);
        fn_8020FC0C((OSThread*)work->thread);
    }
}
