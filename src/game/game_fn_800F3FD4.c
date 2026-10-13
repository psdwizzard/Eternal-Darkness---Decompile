typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int DSError;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

typedef struct TRKExceptionStatus {
    u32 PC;
    u32 instruction;
    u16 exceptionID;
    u8 reserved[3];
    u8 exceptionDetected;
    u8 padding[2];
} TRKExceptionStatus;

extern TRKExceptionStatus gTRKExceptionStatus_8024A864;
extern int fn_800EFA84(TRKBuffer *buffer, u32 value);
extern int fn_800EFAE8(TRKBuffer *buffer, u16 value);
extern DSError fn_800F4CC0(void *data, u32 start, u32 *length,
                         int accessOptions, int read);

/* MetroTRK: append the exception address, instruction, and exception ID. */
void fn_800F3FD4(TRKBuffer *buffer)
{
    DSError error;
    u32 instruction;
    u32 length;

    error = fn_800EFA84(buffer, gTRKExceptionStatus_8024A864.PC);
    if (error == 0) {
        length = sizeof(instruction);
        error = fn_800F4CC0(&instruction, gTRKExceptionStatus_8024A864.PC,
                          &length, 0, 1);
        if (error == 0 && length != sizeof(instruction)) {
            error = 0x700;
        }
    }
    if (error == 0) {
        error = fn_800EFA84(buffer, instruction);
    }
    if (error == 0) {
        fn_800EFAE8(buffer, gTRKExceptionStatus_8024A864.exceptionID);
    }
}
