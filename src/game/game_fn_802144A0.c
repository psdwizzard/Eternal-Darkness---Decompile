typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
    s32 currTransferSize;
    u8 pad14[0x14];
    void (*callback)(s32, DVDCommandBlock *);
};

extern DVDCommandBlock *executing_8064DA00;
extern u32 lbl_8064DA20;
extern void (*lbl_8064DA24)(s32, DVDCommandBlock *);
extern s32 ResumeFromHere_8064DA28;
extern s32 lbl_8064DA34;
extern DVDCommandBlock DummyCommandBlock_806419E0;

extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern void DVDLowStopMotor(void (*)(s32));
extern void stateReady_80214A10(void);
extern void fn_80214904(DVDCommandBlock *);

/* The SDK declares Canceling, ResumeFromHere and NumInternalRetry as vu32/vs32;
 * the shared extern declarations are plain, so the volatile access is
 * expressed at the use sites here. */
static inline s32 CheckCancel(s32 resume)
{
    DVDCommandBlock *finished;

    if (*(volatile u32 *)&lbl_8064DA20 != 0) {
        *(volatile s32 *)&ResumeFromHere_8064DA28 = resume;
        *(volatile u32 *)&lbl_8064DA20 = 0;
        finished = executing_8064DA00;
        executing_8064DA00 = &DummyCommandBlock_806419E0;
        finished->state = 10;
        if (finished->callback != 0)
            finished->callback(-3, finished);
        if (lbl_8064DA24 != 0)
            lbl_8064DA24(0, finished);
        stateReady_80214A10();
        return 1;
    }
    return 0;
}

void fn_802144A0(u32 intType)
{
    if (intType == 0x10) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError_80213C1C(0);
        return;
    }
    if (intType & 2) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor(cbForStateError_80213C1C);
        return;
    }

    *(volatile s32 *)&lbl_8064DA34 = 0;
    if (!CheckCancel(1)) {
        DVDCommandBlock *command = executing_8064DA00;

        command->state = 6;
        fn_80214904(command);
    }
}
