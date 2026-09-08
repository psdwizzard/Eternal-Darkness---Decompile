extern void* memset(void*, int, unsigned long);

extern unsigned char lbl_8063BEA0[0x20];
extern unsigned char lbl_8063BEC0[];
extern unsigned char lbl_8064D758;
extern unsigned int lbl_8064D738;
extern unsigned int lbl_8064D6B8;
extern unsigned int lbl_8064D780;
extern char lbl_802FC644[];

extern void* fn_801FEA8C(unsigned long, int, char*, int);
extern void fn_80226598(void);
extern void* fn_80224640(void);
extern void GXInitFifoBase(void*, void*, unsigned long);
extern void fn_80223D94(void*, unsigned long, int);
extern void GXSetCPUFifo(void*);
extern void GXSetGPFifo(void*);
extern void fn_8020D1F0(void*, void*, int);
extern void fn_802264D4(unsigned long);
extern void fn_801EB09C(void);
extern void fn_802268E0(void (*)(void));
extern void fn_801EFDF4(void);
extern void fn_80216BE0(void (*)(void));
extern void fn_801F5598(int);
extern void fn_80226300(int, int);
extern void* fn_80224330(void*);
extern void fn_801FEB2C(void*, char*, int);

void fn_801EF400(void)
{
    void* fifo;
    void* old_fifo;

    memset(lbl_8063BEA0, 0, 0x20);
    fifo = fn_801FEA8C(0x80, 1, lbl_802FC644, 0x1D0);
    fn_80226598();
    old_fifo = fn_80224640();
    GXInitFifoBase(fifo, fn_801FEA8C(0x30000, 1, lbl_802FC644, 0x1D7), 0x30000);
    fn_80223D94(fifo, 0x2C000, 0);
    GXSetCPUFifo(fifo);
    GXSetGPFifo(fifo);
    fn_8020D1F0(lbl_8063BEC0, &lbl_8064D758, 1);
    fn_802264D4(0xBEEF);
    fn_802268E0(fn_801EB09C);
    lbl_8064D738 = 0;
    fn_80216BE0(fn_801EFDF4);
    lbl_8064D6B8 = 0;
    lbl_8064D780 = 0;
    fn_801F5598(0);
    fn_80226300(2, 0);
    fn_801FEB2C(fn_80224330(old_fifo), lbl_802FC644, 0x1F6);
}
