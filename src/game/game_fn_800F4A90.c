/* fn_800F4A90: MetroTRK TRKTargetAccessFP. Reads/writes FPRs
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

extern unsigned int fn_800F36A0(void);
extern void fn_800F36A8(unsigned int value);
extern DSError fn_800F3A44(void *value, u32 fpr, BOOL read);
extern DSError fn_800EF604(void *buffer, u64 *data);
extern DSError fn_800EF9FC(void *buffer, u64 data);

DSError fn_800F4A90(u32 firstRegister, u32 lastRegister, void *b,
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

    fn_800F36A8(fn_800F36A0() | 0x2000);

    *registersLengthPtr = 0;
    error = 0;

    for (current = firstRegister; current <= lastRegister && error == 0;
         current++, *registersLengthPtr += sizeof(u64)) {
        if (read) {
            fn_800F3A44(&temp, current, read);
            error = fn_800EF9FC(b, temp);
        } else {
            fn_800EF604(b, &temp);
            error = fn_800F3A44(&temp, current, read);
        }
    }

    if (gTRKExceptionStatus_8024A864.exceptionDetected) {
        error = 0x702;
        *registersLengthPtr = 0;
    }

    gTRKExceptionStatus_8024A864 = savedException;
    return error;
}
