typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x08];
    u32 command;
} DVDCommandBlock;

extern DVDCommandBlock *executing_8064DA00;
extern u32 LastError;
extern s32 NumInternalRetry;

/* Categorize a drive error, tracking the previous error and retry count. */
u32 CategorizeError(u32 error)
{
    u32 errorCode;

    if (error == 0x00020400) {
        LastError = error;
        return 1;
    }

    errorCode = error & 0x00FFFFFF;
    if (errorCode == 0x00062800 || errorCode == 0x00023A00 ||
        errorCode == 0x000B5A01) {
        return 0;
    }

    /* The retry counter is shared with the DVD interrupt callbacks. */
    (*(volatile s32 *)&NumInternalRetry)++;
    if (*(volatile s32 *)&NumInternalRetry == 2) {
        if (errorCode == LastError) {
            LastError = errorCode;
            return 1;
        }
        LastError = errorCode;
        return 2;
    }

    LastError = errorCode;
    if (errorCode == 0x00031100 || executing_8064DA00->command == 5) {
        return 2;
    }
    return 3;
}
