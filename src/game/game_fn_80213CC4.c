typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock {
    u8 pad[0x28];
    void (*callback)(s32, DVDCommandBlock *);
};

extern DVDCommandBlock *executing_8064DA00;
extern DVDCommandBlock DummyCommandBlock_806419E0;
extern s32 FatalErrorFlag_8064DA18;
extern u32 Canceling;
extern void (*CancelCallback)(s32, DVDCommandBlock *);

extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void stateReady_80214A10(void);

/* Report a fatal drive error and complete any pending cancellation. */
void stateTimeout(void)
{
    DVDCommandBlock *command;

    __DVDStoreErrorCode(0x01234568);
    DVDReset();
    command = executing_8064DA00;
    FatalErrorFlag_8064DA18 = 1;
    executing_8064DA00 = &DummyCommandBlock_806419E0;
    if (command->callback != 0)
        command->callback(-1, command);

    if (Canceling != 0) {
        Canceling = 0;
        if (CancelCallback != 0)
            CancelCallback(0, command);
    }
    stateReady_80214A10();
}
