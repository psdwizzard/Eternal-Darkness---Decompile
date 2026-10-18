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

extern unsigned int TRKTargetTranslate(unsigned int address);
extern DSError TRKValidMemory32(u32 address, u32 length, BOOL readOnly);
extern unsigned int __TRK_get_MSR(void);
extern void TRK_ppc_memcpy(void *destination, const void *source, unsigned int length,
                        unsigned int read_msr, unsigned int write_msr);
extern void TRK_flush_cache(void *address, unsigned int length);

DSError TRKTargetAccessMemory(register void *dataArg, register u32 startArg,
                    register u32 *lengthArg, int accessOptions,
                    register BOOL readArg)
{
    DSError error;
    register BOOL read;
    register u32 *length;
    register u32 start;
    register void *data;
    u32 target_msr;
    u32 trans_msr;
    void *addr;
    TRKExceptionStatus tempExceptionStatus;

    start = startArg;
    length = lengthArg;
    data = dataArg;
    read = readArg;
    tempExceptionStatus = gTRKExceptionStatus_8024A864;

    gTRKExceptionStatus_8024A864.exceptionDetected = 0;

    addr = (void *)TRKTargetTranslate(start);
    error = TRKValidMemory32((u32)addr, *length, read == 0);

    if (error != 0) {
        *length = 0;
    } else {
        target_msr = __TRK_get_MSR();
        trans_msr = target_msr | (*(u32 *)(gTRKCPUState + 0x1F8) & 0x10);
        if (read) {
            TRK_ppc_memcpy(data, addr, *length, target_msr, trans_msr);
        } else {
            TRK_ppc_memcpy(addr, data, *length, trans_msr, target_msr);
            TRK_flush_cache(addr, *length);
            if ((void *)start != addr) {
                TRK_flush_cache((void *)start, *length);
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
