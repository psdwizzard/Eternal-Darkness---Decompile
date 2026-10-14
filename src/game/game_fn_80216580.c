/* Remove a DVD command block from its waiting queue. */
typedef int BOOL;
typedef struct DVDCommandBlock DVDCommandBlock;

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

BOOL fn_80216580(DVDCommandBlock *block) {
    BOOL level;
    DVDCommandBlock *prev;
    DVDCommandBlock *next;

    level = OSDisableInterrupts();
    prev = block->prev;
    next = block->next;
    if (prev == 0 || next == 0) {
        OSRestoreInterrupts(level);
        return 0;
    }

    prev->next = next;
    next->prev = prev;
    OSRestoreInterrupts(level);
    return 1;
}
