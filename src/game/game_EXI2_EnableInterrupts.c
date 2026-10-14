typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern EXICallback fn_8022DEFC(EXICallback callback);
extern void fn_8022E0A0(void);
extern void fn_8022E120(s32 channel, OSContext *context);

void EXI2_EnableInterrupts(void)
{
    fn_8022DEFC(fn_8022E120);
    fn_8022E0A0();
}
