typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern EXICallback AmcEXISetExiCallback(EXICallback callback);
extern void AmcEXIEnableInterrupts(void);
extern void EXI2_CallBack(s32 channel, OSContext *context);

void EXI2_EnableInterrupts(void)
{
    AmcEXISetExiCallback(EXI2_CallBack);
    AmcEXIEnableInterrupts();
}
