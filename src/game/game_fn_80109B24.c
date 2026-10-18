typedef unsigned int u32;

extern u32 lbl_8064CC88;
extern u32 lbl_8064CC8C;
extern unsigned char lbl_8032EA70[];
extern unsigned char lbl_80330A70[];
extern void HVQM4InitDecoder(void);
extern void fn_801090D4(void);
extern void OSCreateThread(void*, void*, void*, void*, u32, u32, u32);
extern void OSResumeThread(void*);

void fn_80109B24(void* state, u32 arg1, u32 arg2)
{
    lbl_8064CC88 = arg1;
    lbl_8064CC8C = arg2;
    HVQM4InitDecoder();
    OSCreateThread(lbl_80330A70, fn_801090D4, state,
                lbl_8032EA70 + 0x2000, 0x2000, 0x1F, 1);
    OSResumeThread(lbl_80330A70);
}
