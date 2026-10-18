typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef void (*DVDLowCallback)(u32);

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
    u32 offset;
    u8 pad14[0x14];
    void (*callback)(s32, DVDCommandBlock *);
};

extern DVDCommandBlock *executing_8064DA00;
extern u32 Canceling;
extern void (*CancelCallback)(s32, DVDCommandBlock *);
extern void (*lbl_8064DA48)(DVDCommandBlock *);
extern s32 ResumeFromHere_8064DA28;
extern DVDCommandBlock DummyCommandBlock_806419E0;

extern u32 CategorizeError(u32);
extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern s32 DVDLowStopMotor(DVDLowCallback);
extern void stateReady_80214A10(void);
extern void stateGoToRetry(void);
extern void stateMotorStopped(void);
extern void stateCoverClosed(void);
extern s32 DVDLowSeek(u32, DVDLowCallback);
extern void cbForUnrecoveredError(u32);

void cbForStateGettingError(u32 error)
{
    DVDCommandBlock *command;
    u32 status;
    u32 errorWord;
    u32 errorClass;
    s32 resumeState;
    s32 handled;

    if (error == 0x10) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError_80213C1C(0);
        return;
    }
    if (error & 2) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor((DVDLowCallback)cbForStateError_80213C1C);
        return;
    }

    errorWord = *(volatile u32 *)0xCC006020;
    errorClass = errorWord & 0xFF000000;
    status = CategorizeError(errorWord);
    if (status == 1) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(errorWord);
        DVDLowStopMotor((DVDLowCallback)cbForStateError_80213C1C);
        return;
    }

    if (status == 2 || status == 3)
        resumeState = 0;
    else if (errorClass == 0x01000000)
        resumeState = 4;
    else if (errorClass == 0x02000000)
        resumeState = 6;
    else if (errorClass == 0x03000000)
        resumeState = 3;
    else
        resumeState = 5;

    /* Cancellation flags are volatile in the SDK; preserve their access order. */
    if (*(volatile u32 *)&Canceling != 0) {
        *(volatile s32 *)&ResumeFromHere_8064DA28 = resumeState;
        *(volatile u32 *)&Canceling = 0;
        command = executing_8064DA00;
        executing_8064DA00 = &DummyCommandBlock_806419E0;
        command->state = 10;
        if (command->callback != 0)
            command->callback(-3, command);
        if (CancelCallback != 0)
            CancelCallback(0, command);
        stateReady_80214A10();
        handled = 1;
    } else {
        handled = 0;
    }

    if (handled == 0) {
        if (status == 2) {
            __DVDStoreErrorCode(errorWord);
            stateGoToRetry();
            return;
        }
        if (status == 3) {
            if ((errorWord & 0x00FFFFFF) == 0x00031100) {
                DVDLowSeek(executing_8064DA00->offset,
                            cbForUnrecoveredError);
                return;
            }
            lbl_8064DA48(executing_8064DA00);
            return;
        }
        if (errorClass == 0x01000000) {
            executing_8064DA00->state = 5;
            stateMotorStopped();
            return;
        }
        if (errorClass == 0x02000000) {
            executing_8064DA00->state = 3;
            stateCoverClosed();
            return;
        }
        if (errorClass == 0x03000000) {
            executing_8064DA00->state = 4;
            stateMotorStopped();
            return;
        }
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor((DVDLowCallback)cbForStateError_80213C1C);
    }
}
