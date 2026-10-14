/* Dolphin SDK dvd.c: DVDGetCommandBlockStatus */
typedef int s32;
typedef int BOOL;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x08];
    s32 command;
    s32 state;
} DVDCommandBlock;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

s32 fn_80215C34(const DVDCommandBlock *block) {
    BOOL level;
    s32 state;
    s32 result;

    level = OSDisableInterrupts();
    state = block->state;
    if (state == 3) {
        result = 1;
    } else {
        result = state;
    }
    OSRestoreInterrupts(level);
    return result;
}
