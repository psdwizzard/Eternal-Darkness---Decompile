typedef unsigned char u8;
typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    unsigned id;
    int buffer;
} TRKEvent;

extern int TRKGetNextEvent(TRKEvent *);
extern void TRKDestructEvent(TRKEvent *);
extern void *TRKGetBuffer(int);
extern void TRKDispatchMessage(void *);
extern void TRKTargetInterrupt(TRKEvent *);
extern void TRKTargetSupportRequest(void);
extern void TRKGetInput(void);
extern int TRKTargetStopped(void);
extern void TRKTargetContinue(void);
extern u8 *gTRKInputPendingPtr;

void TRKNubMainLoop(void)
{
    int done = 0;
    int input = 0;
    TRKEvent event;

    while (!done) {
        if (TRKGetNextEvent(&event)) {
            input = 0;
            switch (event.type) {
            case 0:
                break;
            case 2:
                TRKDispatchMessage(TRKGetBuffer(event.buffer));
                break;
            case 1:
                done = 1;
                break;
            case 3:
            case 4:
                TRKTargetInterrupt(&event);
                break;
            case 5:
                TRKTargetSupportRequest();
                break;
            }
            TRKDestructEvent(&event);
        } else if (!input || *gTRKInputPendingPtr) {
            input = 1;
            TRKGetInput();
        } else {
            if (!TRKTargetStopped())
                TRKTargetContinue();
            input = 0;
        }
    }
}
