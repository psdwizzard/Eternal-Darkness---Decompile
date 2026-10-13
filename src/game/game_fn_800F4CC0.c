typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef int DSError;

/* MetroTRK: TRKTargetAccessMemory */

typedef struct TRKExceptionStatus {
    u32 field0;
    u32 field4;
    u32 field8;
    u8 fieldC;
    u8 exceptionDetected;
    u8 padE[2];
} TRKExceptionStatus;

extern TRKExceptionStatus gTRKExceptionStatus_8024A864;
extern u8 gTRKCPUState[];

extern unsigned int fn_800F5030(unsigned int address);
extern DSError fn_800F4E0C(u32 address, u32 length, BOOL readOnly);
extern unsigned int fn_800F36A0(void);
extern void fn_800F36B0(void *destination, const void *source, unsigned int length,
                        unsigned int read_msr, unsigned int write_msr);
extern void fn_800F35AC(void *address, unsigned int length);

DSError fn_800F4CC0(void *data, u32 start, u32 *length, int accessOptions, BOOL read)
{
    DSError error;
    u32 target_msr;
    u32 trans_msr;
    void *addr;
    TRKExceptionStatus tempExceptionStatus = gTRKExceptionStatus_8024A864;

    gTRKExceptionStatus_8024A864.exceptionDetected = 0;

    addr = (void *)fn_800F5030(start);
    error = fn_800F4E0C((u32)addr, *length, read == 0);

    if (error != 0) {
        *length = 0;
    } else {
        target_msr = fn_800F36A0();
        trans_msr = target_msr | (*(u32 *)(gTRKCPUState + 0x1F8) & 0x10);
        if (read) {
            fn_800F36B0(data, addr, *length, target_msr, trans_msr);
        } else {
            fn_800F36B0(addr, data, *length, trans_msr, target_msr);
            fn_800F35AC(addr, *length);
            if ((void *)start != addr) {
                fn_800F35AC((void *)start, *length);
            }
        }
    }

    if (gTRKExceptionStatus_8024A864.exceptionDetected) {
        error = 0x702;
        *length = 0;
    }

    gTRKExceptionStatus_8024A864 = tempExceptionStatus;
    return error;
}
