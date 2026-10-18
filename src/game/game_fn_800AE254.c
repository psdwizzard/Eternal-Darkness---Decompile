extern int lbl_8064C9AC;
extern int lbl_8064C9B8;
extern void* lbl_8064C9C4;
extern void* lbl_8064C9C8;
extern char lbl_8031E408[];
extern char lbl_8031E718[];

extern void fn_800ADCB0(void);
extern void* OSGetCurrentThread(void);
extern void OSCreateThread(void*, void (*)(void), int, void*, int, int, int);
extern void OSResumeThread(void*);

void fn_800AE254(void* value)
{
    lbl_8064C9C4 = value;
    lbl_8064C9B8 = 0;
    lbl_8064C9C8 = OSGetCurrentThread();
    if (lbl_8064C9AC == 0) {
        OSCreateThread(lbl_8031E408, fn_800ADCB0, 0,
                    lbl_8031E718 + 0x1000, 0x1000, 0, 1);
        OSResumeThread(lbl_8031E408);
        lbl_8064C9AC = 1;
    }
}
