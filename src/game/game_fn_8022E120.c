typedef unsigned char u8;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern u8 *lbl_8064C4C0;
extern EXICallback lbl_8064DC00;

/* Latch pending input and dispatch the debug port callback. */
void fn_8022E120(s32 channel, OSContext *context)
{
    *lbl_8064C4C0 = 1;
    if (lbl_8064DC00 != 0) {
        lbl_8064DC00(0, context);
    }
}
