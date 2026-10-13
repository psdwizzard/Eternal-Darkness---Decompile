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
extern void (*lbl_8064DA48)(DVDCommandBlock *);
extern s32 ResumeFromHere_8064DA28;
extern DVDCommandBlock DummyCommandBlock_806419E0;

extern u32 fn_80213D88(u32);
extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern void DVDLowStopMotor(void (*)(s32));
extern void stateReady_80214A10(void);
extern void fn_802141D0(void);
extern void fn_80214904(DVDCommandBlock *);
extern void fn_80214798(DVDCommandBlock *);
extern void fn_802129F0(s32, void (*)(void), DVDCommandBlock *);
extern void fn_802140D0(void);

void fn_80213E3C(u32 error)
{
    DVDCommandBlock *command;
    u32 status;
    u32 errorClass;
    u32 errorWord;
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
        DVDLowStopMotor(cbForStateError_80213C1C);
        return;
    }

    errorWord = *(volatile u32 *)0xCC006020;
    errorClass = errorWord & 0xFF000000;
    status = fn_80213D88(errorWord);
    if (status == 1) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(errorWord);
        DVDLowStopMotor(cbForStateError_80213C1C);
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

    if (lbl_8064DA20 != 0) {
        ResumeFromHere_8064DA28 = resumeState;
        command = executing_8064DA00;
        lbl_8064DA20 = 0;
        executing_8064DA00 = &DummyCommandBlock_806419E0;
        command->state = 10;
        if (command->callback != 0)
            command->callback(-3, command);
        if (lbl_8064DA24 != 0)
            lbl_8064DA24(0, command);
        stateReady_80214A10();
        handled = 1;
    } else {
        handled = 0;
    }

    if (handled == 0) {
        if (status == 2) {
            __DVDStoreErrorCode(errorWord);
            fn_802141D0();
            return;
        }
        if (status == 3) {
            if ((errorWord & 0x00FFFFFF) == 0x00031100) {
                fn_802129F0(executing_8064DA00->currTransferSize,
                            fn_802140D0, executing_8064DA00);
                return;
            }
            lbl_8064DA48(executing_8064DA00);
            return;
        }
        if (errorClass == 0x01000000) {
            executing_8064DA00->state = 5;
            fn_80214904(executing_8064DA00);
            return;
        }
        if (errorClass == 0x02000000) {
            executing_8064DA00->state = 3;
            fn_80214798(executing_8064DA00);
            return;
        }
        if (errorClass == 0x03000000) {
            executing_8064DA00->state = 4;
            fn_80214904(executing_8064DA00);
            return;
        }
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor(cbForStateError_80213C1C);
    }
}
