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

extern AramTransferQueues aramQueueLo;
extern u32 aramTop;
extern u32 aramWrite;
extern u32 aramUploadCallback;
extern u32 ARGetBaseAddress(void);
extern u32 ARGetSize(void);
extern void* salMalloc(u32);
extern void salFree(void*);
extern void DCFlushRange(void*, u32);
extern void aramUploadData(void*, u32, u32, u32, u32, u32);
extern void InitStreamBuffers(void);

void aramInit(u32 extraSize)
{
    AramTransferQueues* queues;
    volatile u8* pendingCount;
    u16* clear;
    u8* buf;
    u32 arBase;
    int i;

    queues = &aramQueueLo;
    arBase = ARGetBaseAddress();
    buf = salMalloc(0x500);
    clear = (u16*)buf;
    for (i = 0; i < 640; i++) {
        clear[i] = 0;
    }
    DCFlushRange(buf, 0x500);
    *(pendingCount = &queues->normalCount) = 0;
    queues->normalHead = 0;
    queues->highCount = 0;
    queues->highHead = 0;
    aramUploadData(buf, arBase, 0x500, 0, 0, 0);
    while (*pendingCount != 0) {
    }
    salFree(buf);
    aramTop = arBase + extraSize;
    if (aramTop > ARGetSize()) {
        aramTop = ARGetSize();
    }
    aramWrite = arBase + 0x500;
    aramUploadCallback = 0;
    InitStreamBuffers();
}
