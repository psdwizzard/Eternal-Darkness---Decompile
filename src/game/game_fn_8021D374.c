/* fn_8021D374: __CARDPutControlBlock. */
typedef signed int s32;
typedef int BOOL;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
} CARDControl;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

s32 fn_8021D374(CARDControl *card, s32 result)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (card->attached) {
        card->result = result;
    } else if (card->result == -1) {
        card->result = result;
    }
    OSRestoreInterrupts(enabled);
    return result;
}
