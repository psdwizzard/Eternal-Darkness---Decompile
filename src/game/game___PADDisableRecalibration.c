/* Set the recalibration boot flag and return its previous state. */
typedef unsigned char u8;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u8 __PADBootFlags : 0x800030E3;

BOOL __PADDisableRecalibration(BOOL disable)
{
    BOOL previous;
    BOOL level = OSDisableInterrupts();

    if (__PADBootFlags & 0x40) {
        previous = 1;
    } else {
        previous = 0;
    }
    __PADBootFlags &= 0xBF;
    if (disable) {
        __PADBootFlags |= 0x40;
    }

    OSRestoreInterrupts(level);
    return previous;
}
