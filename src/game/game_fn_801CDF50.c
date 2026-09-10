typedef unsigned char u8;
typedef unsigned int u32;

extern void (*lbl_8064D510)(void);
extern void* lbl_8064D514;
extern u32 lbl_8064D518;
extern volatile u32 lbl_8064D51C;
extern volatile u32 lbl_8064D520;
extern u8 lbl_8064D534;
extern u8 lbl_80619C20[];

extern void* fn_801CE330(u32);
extern void fn_801CDE34(void);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void* fn_8021A044(void*);
extern void fn_8021A088(void*, u32);

u32 fn_801CDF50(void (*callback)(void), u32 unused, u32* config)
{
    void* allocation;
    char* base;

    allocation = fn_801CE330(0xA00);
    lbl_8064D514 = allocation;
    if (allocation != 0) {
        memset(lbl_8064D514, 0, 0xA00);
        DCFlushRange(lbl_8064D514, 0xA00);
        lbl_8064D510 = callback;
        lbl_8064D518 = 1;
        lbl_8064D534 = 1;
        lbl_8064D520 = lbl_8064D51C = 0;
        fn_8021A044((void*)fn_801CDE34);
        base = (char*)((u32)lbl_8064D514 + 0x80000000U);
        fn_8021A088(base + lbl_8064D534 * 0x280, 0x280);
        *(u32*)(lbl_80619C20 + 4) = 0x20;
        *config = 32000;
        return 1;
    }
    return 0;
}
