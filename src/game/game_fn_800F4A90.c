/* TRKTargetAccessFP: MetroTRK TRKTargetAccessFP. Reads/writes FPRs
 * firstRegister..lastRegister (plus FPSCR) through the message buffer. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int DSError;

typedef struct TRKExceptionStatus {
    u32 field0;
    u32 field4;
    u8 field8;
    u8 field9;
    u8 fieldA;
    u8 fieldB;
    u8 fieldC;
    u8 exceptionDetected;
    u8 fieldE;
    u8 fieldF;
} TRKExceptionStatus;

extern TRKExceptionStatus gTRKExceptionStatus_8024A864;

extern unsigned int __TRK_get_MSR(void);
extern void __TRK_set_MSR(unsigned int value);
extern DSError TRKPPCAccessFPRegister(void *value, u32 fpr, BOOL read);
extern DSError TRKReadBuffer1_ui64(void *buffer, u64 *data);
extern DSError TRKAppendBuffer1_ui64(void *buffer, u64 data);

DSError TRKTargetAccessFP(u32 firstRegister, u32 lastRegister, void *b,
                    u32 *registersLengthPtr, BOOL read)
{
    u64 temp;
    TRKExceptionStatus savedException;
    DSError error;
    u32 current;

    if (lastRegister > 0x21) {
        return 0x701;
    }

    savedException = gTRKExceptionStatus_8024A864;
    gTRKExceptionStatus_8024A864.exceptionDetected = 0;

    __TRK_set_MSR(__TRK_get_MSR() | 0x2000);

    *registersLengthPtr = 0;
    error = 0;

    for (current = firstRegister; current <= lastRegister && error == 0;
         current++, *registersLengthPtr += sizeof(u64)) {
        if (read) {
            TRKPPCAccessFPRegister(&temp, current, read);
            error = TRKAppendBuffer1_ui64(b, temp);
        } else {
            TRKReadBuffer1_ui64(b, &temp);
            error = TRKPPCAccessFPRegister(&temp, current, read);
        }
    }

    if (gTRKExceptionStatus_8024A864.exceptionDetected) {
        error = 0x702;
        *registersLengthPtr = 0;
    }

    gTRKExceptionStatus_8024A864 = savedException;
    return error;
}
