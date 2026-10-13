/* DVDGetDriveStatus (Dolphin SDK dvd.c). */
typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 currTransferSize;
    u32 transferredSize;
    void *id;
    DVDCBCallback callback;
    void *userData;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern BOOL FatalErrorFlag_8064DA18;
extern BOOL PausingFlag_8064DA10;
extern DVDCommandBlock *executing_8064DA00;
extern DVDCommandBlock DummyCommandBlock_806419E0;

static inline s32 getCommandBlockStatus(const DVDCommandBlock *block) {
    BOOL level = OSDisableInterrupts();
    s32 status = block->state;

    if (status == 3) {
        status = 1;
    }
    OSRestoreInterrupts(level);
    return status;
}

s32 DVDGetDriveStatus(void) {
    BOOL level;
    s32 status;
    DVDCommandBlock *block;

    level = OSDisableInterrupts();
    if (FatalErrorFlag_8064DA18) {
        status = -1;
    } else if (PausingFlag_8064DA10) {
        status = 8;
    } else {
        block = executing_8064DA00;
        if (block == 0) {
            status = 0;
        } else if (block == &DummyCommandBlock_806419E0) {
            status = 0;
        } else {
            status = getCommandBlockStatus(block);
        }
    }
    OSRestoreInterrupts(level);
    return status;
}
