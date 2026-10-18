extern unsigned char lbl_8064C368;

extern void GXFlush(void);
extern void* GXGetCPUFifo(void);
extern void GXGetFifoPtrs(void*, void**, void**);
extern void GXEnableBreakPt(void*);
extern void GXSetDrawSync(unsigned long);

void fn_801EF530(void)
{
    void* first;
    void* second;

    GXFlush();
    GXGetFifoPtrs(GXGetCPUFifo(), &first, &second);
    GXEnableBreakPt(second);
    if (lbl_8064C368 != 0) {
        GXSetDrawSync(0xCACE);
    }
}
