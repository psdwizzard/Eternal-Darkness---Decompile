typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct OSBootInfo {
    u8 _00[0x28];
    u32 memorySize;
    u32 consoleType;
    void* arenaLo;
    void* arenaHi;
} OSBootInfo;

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 reserved[0x18];
} DVDDriveInfo;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCallback)(s32, DVDCommandBlock*);
struct DVDCommandBlock {
    DVDCommandBlock* next;
    DVDCommandBlock* prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void* addr;
    u32 currentTransferSize;
    u32 transferredSize;
    void* id;
    DVDCallback callback;
    void* userData;
};

typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16, OSContext*);

typedef enum OSConsoleType {
    OS_CONSOLE_MAC = 0x10000000,
    OS_CONSOLE_PC = 0x10000001,
    OS_CONSOLE_ARTHUR = 0x10000002,
    OS_CONSOLE_MINNOW = 0x10000003,
    OS_CONSOLE_DEVELOPMENT = 0x10000004
} OSConsoleType;

typedef struct OSReportStrings {
    char version[0x20];
    char kernelBuilt[0x18];
    char buildDate[0xC];
    char buildTime[0xC];
    char consoleType[0x10];
    char retail[0xC];
    char macEmulator[0x10];
    char pcEmulator[0x10];
    char arthur[0x10];
    char minnow[0x10];
    char development[0x14];
    char memory[0x10];
    char arena[0x14];
} OSReportStrings;

extern int AreWeInitialized_8064D8FC;
extern OSBootInfo* BootInfo_8064D8F0;
extern u32* BI2DebugFlag_8064D8F4;
extern u32 BI2DebugFlagHolder_8064D8F8;
extern int __OSInIPL;
extern u64 __OSStartTime;
extern u32 __DVDLongFileNameFlag;
extern u32 __PADSpec;
extern DVDDriveInfo DriveInfo_80640D80;

extern u64 __OSGetSystemTime(void);
extern s32 OSDisableInterrupts(void);
extern void PPCDisableSpeculation(void);
extern void PPCSetFpNonIEEEMode(void);
extern void OSSetArenaLo(void*);
extern void OSSetArenaHi(void*);
extern void OSExceptionInit_8020A19C(void);
extern void __OSInitSystemCall(void);
extern void OSInitAlarm(void);
extern void __OSModuleInit(void);
extern void __OSInterruptInit(void);
extern OSInterruptHandler __OSSetInterruptHandler(s16, OSInterruptHandler);
extern void __OSResetSWInterruptHandler(s16, OSContext*);
extern void __OSContextInit(void);
extern void __OSCacheInit(void);
extern void EXIInit(void);
extern void SIInit(void);
extern void __OSInitSram(void);
extern void __OSThreadInit(void);
extern void __OSInitAudioSystem(void);
extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32);
extern void __OSInitMemoryProtection(void);
extern void OSReport(const char*, ...);
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void EnableMetroTRKInterrupts(void);
extern void ClearArena_80209CA0(void);
extern s32 OSEnableInterrupts(void);
extern void DVDInit(void);
extern void DCInvalidateRange(void*, u32);
extern s32 DVDInquiryAsync(DVDCommandBlock*, DVDDriveInfo*, DVDCallback);
extern void InquiryCallback_80209DC8(s32, DVDCommandBlock*);

/* The first report string starts 0x1E bytes before the named remainder of the pool. */
extern u8 lbl_802FCBBE[];
extern char __ArenaLo[];
extern char __ArenaHi[];
extern char _stack_addr[];

void OSInit(void)
{
    OSBootInfo* bootInfo;
    u32 consoleType;
    register void* arenaHi;
    register void* arenaLo;
    register u32 lowAddress;
    register u32 highAddress;
    register u32* console;
    register u32 value;
    register OSReportStrings* reports;
    register DVDDriveInfo* driveInfo;
    register u32 reportHigh;
    register u32 driveHigh;
    register int initialized = AreWeInitialized_8064D8FC;

    /* ASM: lis/addi/cmpwi/bne initialize persistent addresses and test the guard in retail order; C inserts copies and places the comparison after both addresses. */
    asm {
        lis driveHigh, DriveInfo_80640D80@ha
        lis reportHigh, (lbl_802FCBBE - 0x1E)@ha
        cmpwi initialized, 0
        addi driveInfo, driveHigh, DriveInfo_80640D80@l
        addi reports, reportHigh, (lbl_802FCBBE - 0x1E)@l
        bne initializedReturn
    }

    AreWeInitialized_8064D8FC = 1;
    __OSStartTime = __OSGetSystemTime();
    OSDisableInterrupts();
    PPCDisableSpeculation();
    PPCSetFpNonIEEEMode();

    BI2DebugFlag_8064D8F4 = 0;
    BootInfo_8064D8F0 = (OSBootInfo*)0x80000000;
    __DVDLongFileNameFlag = 0;
    bootInfo = *(OSBootInfo**)0x800000F4;
    if (bootInfo != 0) {
        BI2DebugFlag_8064D8F4 = (u32*)((u8*)bootInfo + 0xC);
        __PADSpec = *(u32*)((u8*)bootInfo + 0x24);
        value = *BI2DebugFlag_8064D8F4;
        /* ASM: clrlwi preserves the explicit byte conversion that MWCC removes before stb. */
        asm { clrlwi value, value, 24 }
        *(volatile u8*)0x800030E8 = (u8)value;
        value = __PADSpec;
        /* ASM: clrlwi preserves the explicit byte conversion that MWCC removes before stb. */
        asm { clrlwi value, value, 24 }
        *(volatile u8*)0x800030E9 = (u8)value;
    } else if (*(u32*)0x80000034 != 0) {
        BI2DebugFlagHolder_8064D8F8 = *(u8*)0x800030E8;
        BI2DebugFlag_8064D8F4 = &BI2DebugFlagHolder_8064D8F8;
        __PADSpec = *(u8*)0x800030E9;
    }

    __DVDLongFileNameFlag = 1;
    {
        register void* arena = BootInfo_8064D8F0->arenaLo;
        if (arena == 0) {
            arena = __ArenaLo;
        }
        OSSetArenaLo(arena);
    }
    if (BootInfo_8064D8F0->arenaLo == 0 && BI2DebugFlag_8064D8F4 != 0 &&
        *BI2DebugFlag_8064D8F4 < 2) {
        OSSetArenaLo((void*)(((u32)_stack_addr + 31) & ~31));
    }
    {
        register void* arena = BootInfo_8064D8F0->arenaHi;
        if (arena == 0) {
            arena = __ArenaHi;
        }
        OSSetArenaHi(arena);
    }

    OSExceptionInit_8020A19C();
    __OSInitSystemCall();
    OSInitAlarm();
    __OSModuleInit();
    __OSInterruptInit();
    __OSSetInterruptHandler(0x16, __OSResetSWInterruptHandler);
    __OSContextInit();
    __OSCacheInit();
    EXIInit();
    SIInit();
    __OSInitSram();
    __OSThreadInit();
    __OSInitAudioSystem();
    PPCMthid2(PPCMfhid2() & 0xBFFFFFFF);

    console = &BootInfo_8064D8F0->consoleType;
    /* ASM: lwz/rlwinm preserve the console-field pointer and separate mask, which C folds into the boot-info base and a record-form test. */
    asm {
        lwz value, 0(console)
        rlwinm value, value, 0, 3, 3
    }
    if (value != 0) {
        *console = OS_CONSOLE_DEVELOPMENT;
    } else {
        *console = 1;
    }
    {
        register volatile u32* registers = (volatile u32*)0xCC003000;
        u32 currentConsole;
        OSBootInfo* hardwareBoot = BootInfo_8064D8F0;
        /* ASM: lwz retains the hardware-register base; C folds 0x3000 into the load displacement. */
        asm { lwz value, 0x2C(registers) }
        currentConsole = hardwareBoot->consoleType;
        /* ASM: clrrwi/srwi preserve the separate hardware revision mask and shift, which MWCC combines when the shift is written in C. */
        asm {
            clrrwi value, value, 28
            srwi value, value, 28
        }
        hardwareBoot->consoleType = currentConsole + value;
    }
    if (!__OSInIPL) {
        __OSInitMemoryProtection();
    }

    OSReport(reports->version);
    OSReport(reports->kernelBuilt, reports->buildDate, reports->buildTime);
    OSReport(reports->consoleType);
    bootInfo = BootInfo_8064D8F0;
    if (bootInfo == 0 || (consoleType = bootInfo->consoleType) == 0) {
        register OSConsoleType defaultConsole = OS_CONSOLE_ARTHUR;
        consoleType = (u32)defaultConsole;
    }
    value = consoleType;
    /* ASM: rlwinm keeps the mask separate from the comparison; C combines them into rlwinm. */
    asm { rlwinm value, value, 0, 3, 3 }
    if (value == 0) {
        OSReport(reports->retail, consoleType);
    } else {
        switch ((int)consoleType) {
        case OS_CONSOLE_MAC: OSReport(reports->macEmulator); break;
        case OS_CONSOLE_PC: OSReport(reports->pcEmulator); break;
        case OS_CONSOLE_ARTHUR: OSReport(reports->arthur); break;
        case OS_CONSOLE_MINNOW: OSReport(reports->minnow); break;
        default: OSReport(reports->development, consoleType - 0x10000003); break;
        }
    }
    OSReport(reports->memory, BootInfo_8064D8F0->memorySize >> 20);
    arenaHi = OSGetArenaHi();
    arenaLo = OSGetArenaLo();
    /* ASM: mr keeps the two arena-address copies paired; C merges pointer-to-integer conversions into zero-offset addi expressions. */
    asm {
        mr lowAddress, arenaLo
        mr highAddress, arenaHi
    }
    OSReport(reports->arena, lowAddress, highAddress);
    if (BI2DebugFlag_8064D8F4 != 0 && *BI2DebugFlag_8064D8F4 >= 2) {
        EnableMetroTRKInterrupts();
    }
    ClearArena_80209CA0();
    OSEnableInterrupts();
    if (!__OSInIPL) {
        DVDInit();
        DCInvalidateRange(driveInfo, 0x20);
        DVDInquiryAsync((DVDCommandBlock*)((u8*)driveInfo + sizeof(*driveInfo)), driveInfo,
                        InquiryCallback_80209DC8);
    }
initializedReturn:
    return;
}
