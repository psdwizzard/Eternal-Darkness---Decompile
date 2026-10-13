typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x08];
    u32 command;
} DVDCommandBlock;

extern DVDCommandBlock *executing_8064DA00;
extern u32 lbl_8064DA30;
extern s32 lbl_8064DA34;

/* Categorize a drive error, tracking the previous error and retry count. */
u32 fn_80213D88(u32 error)
{
    u32 errorCode;

    if (error == 0x00020400) {
        lbl_8064DA30 = error;
        return 1;
    }

    errorCode = error & 0x00FFFFFF;
    if (errorCode == 0x00062800 || errorCode == 0x00023A00 ||
        errorCode == 0x000B5A01) {
        return 0;
    }

    /* The retry counter is shared with the DVD interrupt callbacks. */
    (*(volatile s32 *)&lbl_8064DA34)++;
    if (*(volatile s32 *)&lbl_8064DA34 == 2) {
        if (errorCode == lbl_8064DA30) {
            lbl_8064DA30 = errorCode;
            return 1;
        }
        lbl_8064DA30 = errorCode;
        return 2;
    }

    lbl_8064DA30 = errorCode;
    if (errorCode == 0x00031100 || executing_8064DA00->command == 5) {
        return 2;
    }
    return 3;
}
