extern void* memset(void*, int, unsigned long);

extern unsigned char lbl_8063BEA0[0x20];
extern unsigned char lbl_8063BEC0[];
extern unsigned char lbl_8064D758;
extern unsigned int lbl_8064D738;
extern unsigned int lbl_8064D6B8;
extern unsigned int lbl_8064D780;
extern char lbl_802FC644[];

extern void* fn_801FEA8C(unsigned long, int, char*, int);
extern void GXSetDrawDone(void);
extern void* GXGetCPUFifo(void);
extern void GXInitFifoBase(void*, void*, unsigned long);
extern void GXInitFifoLimits(void*, unsigned long, int);
extern void GXSetCPUFifo(void*);
extern void GXSetGPFifo(void*);
extern void OSInitMessageQueue(void*, void*, int);
extern void GXSetDrawSync(unsigned long);
extern void fn_801EB09C(void);
extern void GXSetDrawDoneCallback(void (*)(void));
extern void fn_801EFDF4(void);
extern void VISetPostRetraceCallback(void (*)(void));
extern void fn_801F5598(int);
extern void GXSetMisc(int, int);
extern void* GXGetFifoBase(void*);
extern void fn_801FEB2C(void*, char*, int);

void fn_801EF400(void)
{
    void* fifo;
    void* old_fifo;

    memset(lbl_8063BEA0, 0, 0x20);
    fifo = fn_801FEA8C(0x80, 1, lbl_802FC644, 0x1D0);
    GXSetDrawDone();
    old_fifo = GXGetCPUFifo();
    GXInitFifoBase(fifo, fn_801FEA8C(0x30000, 1, lbl_802FC644, 0x1D7), 0x30000);
    GXInitFifoLimits(fifo, 0x2C000, 0);
    GXSetCPUFifo(fifo);
    GXSetGPFifo(fifo);
    OSInitMessageQueue(lbl_8063BEC0, &lbl_8064D758, 1);
    GXSetDrawSync(0xBEEF);
    GXSetDrawDoneCallback(fn_801EB09C);
    lbl_8064D738 = 0;
    VISetPostRetraceCallback(fn_801EFDF4);
    lbl_8064D6B8 = 0;
    lbl_8064D780 = 0;
    fn_801F5598(0);
    GXSetMisc(2, 0);
    fn_801FEB2C(GXGetFifoBase(old_fifo), lbl_802FC644, 0x1F6);
}
