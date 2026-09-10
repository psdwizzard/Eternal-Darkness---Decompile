typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AramTransferQueues {
    u8 entries[0x280];
    u8 normalHead;
    volatile u8 normalCount;
    u8 pad[0x282];
    u8 highHead;
    volatile u8 highCount;
} AramTransferQueues;

extern AramTransferQueues lbl_80630A30;
extern u32 lbl_8064D4E8;
extern u32 lbl_8064D4EC;
extern u32 lbl_8064D4F4;
extern u32 fn_8021AB5C(void);
extern u32 fn_8021AB64(void);
extern void* fn_801CE330(u32);
extern void fn_801CE358(void*);
extern void DCFlushRange(void*, u32);
extern void fn_801CD5D0(void*, u32, u32, u32, u32, u32);
extern void fn_801CDB2C(void);

void fn_801CD7E0(u32 extraSize)
{
    AramTransferQueues* queues;
    volatile u8* pendingCount;
    u16* clear;
    u8* buf;
    u32 arBase;
    int i;

    queues = &lbl_80630A30;
    arBase = fn_8021AB5C();
    buf = fn_801CE330(0x500);
    clear = (u16*)buf;
    for (i = 0; i < 640; i++) {
        clear[i] = 0;
    }
    DCFlushRange(buf, 0x500);
    *(pendingCount = &queues->normalCount) = 0;
    queues->normalHead = 0;
    queues->highCount = 0;
    queues->highHead = 0;
    fn_801CD5D0(buf, arBase, 0x500, 0, 0, 0);
    while (*pendingCount != 0) {
    }
    fn_801CE358(buf);
    lbl_8064D4E8 = arBase + extraSize;
    if (lbl_8064D4E8 > fn_8021AB64()) {
        lbl_8064D4E8 = fn_8021AB64();
    }
    lbl_8064D4EC = arBase + 0x500;
    lbl_8064D4F4 = 0;
    fn_801CDB2C();
}
