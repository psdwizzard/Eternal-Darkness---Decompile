typedef unsigned int u32;
typedef unsigned char u8;

extern void* lbl_8064D2D8;
extern void* lbl_8064D2D4;
extern void* lbl_8064D2D0;
extern void* lbl_8064D2CC;
extern void* lbl_8064D2DC;
extern int lbl_8064D2C4;
extern int lbl_8064D2C0;
extern u8 lbl_80607D10[];

extern void* fn_8015D424(void*, int);
extern int fn_801AA4A0(void*);
extern void OSInitMessageQueue(void*, void*, int);
extern void OSCreateThread(void*, int (*)(void*), void*, void*, u32, void*, int);
extern void OSResumeThread(void*);

void fn_801AA550(void* arg)
{
    u8* block;
    u8* stack;
    void* info;

    block = fn_8015D424(&info, 6);
    lbl_8064D2D8 = block;
    lbl_8064D2D4 = block + 0x20;
    lbl_8064D2D0 = block + 0x1020;
    lbl_8064D2CC = block + 0x1040;
    lbl_8064D2DC = block + 0x1044;
    lbl_8064D2C4 = 0;
    lbl_8064D2C0 = 1;
    OSInitMessageQueue(block, block + 0x20, 0x400);
    OSInitMessageQueue(lbl_8064D2D0, lbl_8064D2CC, 1);
    stack = (u8*)((u32)(block + 0x5063) & ~31);
    OSCreateThread(lbl_80607D10, fn_801AA4A0, stack + 0x2000,
                stack + 0x2000,
                0x2000, arg, 1);
    OSResumeThread(lbl_80607D10);
}
