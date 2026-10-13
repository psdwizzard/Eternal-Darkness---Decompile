/* fn_8021D558: __CARDSync. */
typedef unsigned char u8;
typedef signed long s32;
typedef int BOOL;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 reserved08[0x8C - 0x08];
    OSThreadQueue threadQueue;
    u8 reserved94[0x110 - 0x94];
} CARDControl;

extern CARDControl lbl_80641C60[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void fn_80210004(OSThreadQueue *queue);

static inline s32 CARDGetResultCode(s32 chan)
{
    CARDControl *card;

    if (chan < 0 || chan >= 2) {
        return -128;
    }
    card = &lbl_80641C60[chan];
    return card->result;
}

s32 fn_8021D558(s32 chan)
{
    s32 result;
    CARDControl *card;
    BOOL enabled;

    card = &lbl_80641C60[chan];
    enabled = OSDisableInterrupts();
    while ((result = CARDGetResultCode(chan)) == -1) {
        fn_80210004(&card->threadQueue);
    }
    OSRestoreInterrupts(enabled);
    return result;
}
