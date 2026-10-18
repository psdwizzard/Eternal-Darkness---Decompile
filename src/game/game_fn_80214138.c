typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
} DVDCommandBlock;

extern DVDCommandBlock *executing_8064DA00;
extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern void DVDLowStopMotor(void (*)(s32));

volatile u32 __DIRegs[16] : 0xCC006000;

void cbForUnrecoveredErrorRetry(u32 error)
{
    if (error == 0x10) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError_80213C1C(0);
        return;
    }

    executing_8064DA00->state = -1;
    if (error & 2) {
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor(cbForStateError_80213C1C);
    } else {
        __DVDStoreErrorCode(__DIRegs[8]);
        DVDLowStopMotor(cbForStateError_80213C1C);
    }
}
