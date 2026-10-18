/* __OSReboot (0x8020DBEC, 448 bytes): Dolphin SDK os/OSReboot.c */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct OSContext {
    u8 data[0x2C8];
} OSContext;

typedef struct DVDCommandBlock {
    void *next;
    void *prev;
    u32 command;
    s32 state;
    u8 pad10[0x20];
} DVDCommandBlock;

typedef struct ApploaderHeader {
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} ApploaderHeader;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSEnableInterrupts(void);
extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void ICInvalidateRange(void *addr, u32 nBytes);
extern void DVDInit(void);
extern BOOL DVDSetAutoInvalidation(BOOL autoInval);                     /* DVDSetAutoInvalidation */
extern BOOL __DVDPrepareResetAsync(DVDCBCallback callback);              /* __DVDPrepareResetAsync */
extern BOOL DVDCheckDisk(void);                                /* DVDCheckDisk */
extern void __OSDoHotReset(u32 resetCode);                       /* __OSDoHotReset */
extern BOOL DVDReadAbsAsyncForBS(DVDCommandBlock *block, void *addr, s32 length,
                        s32 offset, DVDCBCallback callback);  /* DVDReadAbsAsyncForBS */
extern void Run(void *addr);                          /* Run */
extern void fn_8020DBE0(s32 result, DVDCommandBlock *block);  /* Callback */

extern ApploaderHeader Header;  /* Header */
extern void *SaveStart;            /* SaveStart */
extern void *SaveEnd;            /* SaveEnd */
extern volatile BOOL Prepared;    /* Prepared */

#define OS_RESET_CODE (*(u32 *)0x817FFFFC)
#define OS_APPLOADER_ADDR ((void *)0x81300000)

static inline void ReadApploader(DVDCommandBlock *dvdCmd, void *addr, u32 offset, u32 numBytes) {
    while (!Prepared) {
    }
    DVDReadAbsAsyncForBS(dvdCmd, addr, numBytes, offset + 0x2440, 0);
    while (1) {
        switch (dvdCmd->state) {
        case 1:
            break;
        case 0:
            return;
        case -1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            __OSDoHotReset(OS_RESET_CODE);
            break;
        default:
            break;
        }
    }
}

void __OSReboot(void) {
    OSContext exceptionContext;
    DVDCommandBlock dvdCmd;
    DVDCommandBlock dvdCmd2;
    u32 numBytes;
    u32 offset;

    OSDisableInterrupts();

    *(u32 *)0x817FFFFC = 0;
    *(u32 *)0x817FFFF8 = 0;
    *(u8 *)0x800030E2 = 1;
    *(void **)0x812FDFF0 = SaveStart;
    *(void **)0x812FDFEC = SaveEnd;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    DVDInit();
    DVDSetAutoInvalidation(1);
    __DVDPrepareResetAsync(fn_8020DBE0);

    if (!DVDCheckDisk()) {
        __OSDoHotReset(OS_RESET_CODE);
    }

    __OSMaskInterrupts(0xFFFFFFE0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();

    ReadApploader(&dvdCmd, &Header, 0, 0x20);

    offset = Header.size + 0x20;
    numBytes = (Header.rebootSize + 0x1F) & ~0x1F;
    ReadApploader(&dvdCmd2, OS_APPLOADER_ADDR, offset, numBytes);

    ICInvalidateRange(OS_APPLOADER_ADDR, numBytes);
    Run(OS_APPLOADER_ADDR);
}
