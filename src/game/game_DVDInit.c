/* DVDInit (0x80213A4C, 252 bytes): SDK dvd.c */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    unsigned char diskNumber;
    unsigned char gameVersion;
    unsigned char streaming;
    unsigned char streamingBufSize;
    unsigned char padding[22];
} DVDDiskID;

typedef struct OSBootInfo {
    DVDDiskID DVDDiskID;
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType;
    void *arenaLo;
    void *arenaHi;
    void *FSTLocation;
    u32 FSTMaxLength;
} OSBootInfo;

typedef void (*__OSInterruptHandler)(short interrupt, void *context);

extern void OSInitAlarm(void);
extern void __DVDFSInit(void);
extern void __DVDClearWaitingQueue(void);
extern void __DVDInitWA(void);
extern __OSInterruptHandler __OSSetInterruptHandler(short interrupt, __OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSInitThreadQueue(OSThreadQueue *queue);
extern void OSReport(const char *msg, ...);
extern void __fstLoad(void);
extern void __DVDInterruptHandler(short interrupt, void *context);

extern BOOL DVDInitialized_8064DA44;
extern BOOL FirstTimeInBootrom_8064DA40;
extern OSBootInfo *bootInfo_8064DA08;
extern DVDDiskID *currID_8064DA04;
extern OSThreadQueue __DVDThreadQueue;

volatile u32 __DIRegs[16] : 0xCC006000;

void DVDInit(void) {
    u32 magic;

    if (DVDInitialized_8064DA44) {
        return;
    }

    OSInitAlarm();
    DVDInitialized_8064DA44 = 1;
    __DVDFSInit();
    __DVDClearWaitingQueue();
    __DVDInitWA();

    bootInfo_8064DA08 = (OSBootInfo *)0x80000000;
    currID_8064DA04 = &bootInfo_8064DA08->DVDDiskID;

    __OSSetInterruptHandler(21, __DVDInterruptHandler);
    __OSUnmaskInterrupts(0x400);
    OSInitThreadQueue(&__DVDThreadQueue);

    __DIRegs[0] = 0x2A;
    __DIRegs[1] = 0;

    magic = bootInfo_8064DA08->magic;
    if (magic == 0xE5207C22) {
        OSReport("app booted via JTAG\n");
        OSReport("load fst\n");
        __fstLoad();
    } else if (magic == 0x0D15EA5E) {
        OSReport("app booted from bootrom\n");
    } else {
        FirstTimeInBootrom_8064DA40 = 1;
        OSReport("bootrom\n");
    }
}
