/* DVD audio stream command, with issueCommand inlined. */
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
    u8 pad[0x08];
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 currTransferSize;
    u32 transferredSize;
    u8 pad24[0x04];
    DVDCBCallback callback;
};

extern void DCInvalidateRange(void *addr, u32 nBytes);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern BOOL __DVDPushWaitingQueue(s32 prio, DVDCommandBlock *block);
extern void stateReady_80214A10(void);

extern BOOL autoInvalidation_8064C408;
extern DVDCommandBlock *executing_8064DA00;
extern BOOL PauseFlag_8064DA0C;

static inline BOOL issueCommand(s32 prio, DVDCommandBlock *block) {
    BOOL level;
    BOOL result;

    if (autoInvalidation_8064C408 &&
        (block->command == 1 || block->command == 4 || block->command == 5 ||
         block->command == 14)) {
        DCInvalidateRange(block->addr, block->length);
    }

    level = OSDisableInterrupts();
    block->state = 2;
    result = __DVDPushWaitingQueue(prio, block);
    if (executing_8064DA00 == 0 && PauseFlag_8064DA0C == 0) {
        stateReady_80214A10();
    }
    OSRestoreInterrupts(level);
    return result;
}

BOOL DVDPrepareStreamAbsAsync(DVDCommandBlock *block, u32 length, u32 offset,
                 DVDCBCallback callback) {
    BOOL idle;

    block->command = 6;
    block->length = length;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}
