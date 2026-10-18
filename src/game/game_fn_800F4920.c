/* MetroTRK access to the saved extended register block. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int DSError;
typedef int BOOL;

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

typedef struct TRKCPUState {
    u8 standardAndFloatingPoint[0x1A8];
    u32 extended[97];
    u8 remainingState[0x104];
} TRKCPUState;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

typedef struct TRKRestoreFlags {
    u8 timeBase;
    u8 decrementer;
    u8 reserved[7];
} TRKRestoreFlags;

extern TRKCPUState gTRKCPUState;
extern TRKExceptionStatus gTRKExceptionStatus_8024A864;
extern TRKRestoreFlags gTRKRestoreFlags;
extern DSError TRKReadBuffer_ui32(TRKBuffer *buffer, u32 *values, int count);
/* The retail append routine returns its buffer error in r3. */
extern DSError TRKAppendBuffer_ui32(TRKBuffer *buffer, u32 *values, int count);

DSError TRKTargetAccessExtended1(u32 firstRegister, u32 lastRegister, TRKBuffer *buffer,
                    u32 *registerStorageSize, BOOL read)
{
    TRKExceptionStatus savedException;
    DSError error = firstRegister;
    u32 count;
    u32 *registers;
    u32 (*extendedRegisters)[97];

    if (lastRegister > 96) {
        return 0x701;
    }
    savedException = gTRKExceptionStatus_8024A864;
    gTRKExceptionStatus_8024A864.exceptionDetected = 0;
    *registerStorageSize = 0;

    if (firstRegister <= lastRegister) {
        count = lastRegister - firstRegister + 1;
        extendedRegisters = &gTRKCPUState.extended;
        registers = &(*extendedRegisters)[firstRegister];
        *registerStorageSize += count * sizeof(u32);
        if (read) {
            error = TRKAppendBuffer_ui32(buffer, registers, count);
        } else {
            if (registers <= &gTRKCPUState.extended[17] &&
                registers + count - 1 >= &gTRKCPUState.extended[16]) {
                gTRKRestoreFlags.timeBase = 1;
            }
            if (registers <= &gTRKCPUState.extended[52] &&
                registers + count - 1 >= &gTRKCPUState.extended[52]) {
                gTRKRestoreFlags.decrementer = 1;
            }
            error = TRKReadBuffer_ui32(buffer, registers, count);
        }
    }

    if (gTRKExceptionStatus_8024A864.exceptionDetected) {
        *registerStorageSize = 0;
        error = 0x702;
    }
    gTRKExceptionStatus_8024A864 = savedException;
    return error;
}
