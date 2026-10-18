typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamState {
    u8 pad0[3];
    volatile u8 state;
    u8 pad4[0x18];
    u8* volatile read;
    u8 pad20[0x18];
    u8* volatile pending;
    u8 pad3C[0x14];
    void* volatile queue;
} StreamState;

extern StreamState lbl_805BB1E0;
extern u8 lbl_805E2600[];
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void fn_80158E84(int);
extern void fn_8015C020(int);
extern int OSReceiveMessage(void*, void*, int);

void fn_8015E0A0(u32 amount)
{
    int retry;
    int interrupts;
    u32 message;

    do {
        interrupts = OSDisableInterrupts();
        retry = 0;
        if (lbl_805BB1E0.state <= 2) {
            retry = 1;
        } else if (lbl_805BB1E0.pending + amount > lbl_805BB1E0.read) {
            retry = 1;
        }
        if (retry) {
            lbl_805BB1E0.queue = lbl_805E2600;
        }
        OSRestoreInterrupts(interrupts);
        if (retry) {
            fn_80158E84(4);
            fn_8015C020(0);
            OSReceiveMessage(lbl_805E2600, &message, 1);
            lbl_805BB1E0.queue = 0;
        }
    } while (retry);
}
