typedef unsigned char u8;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern u8 *pucEXI2InputPending;
extern EXICallback TRK_Callback;

/* Latch pending input and dispatch the debug port callback. */
void EXI2_CallBack(s32 channel, OSContext *context)
{
    *pucEXI2InputPending = 1;
    if (TRK_Callback != 0) {
        TRK_Callback(0, context);
    }
}
