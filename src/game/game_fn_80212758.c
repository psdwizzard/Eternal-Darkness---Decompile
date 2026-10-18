typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed long long s64;
typedef s64 OSTime;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDCommand {
    s32 cmd;
    void *addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

typedef struct DVDLowReadRegion {
    void *addr;
    u32 length;
    u32 offset;
} DVDLowReadRegion;

typedef struct OSAlarm {
    char data[0x28];
} OSAlarm;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

/* dvdlow.c static work area */
typedef struct DVDLowWork {
    DVDCommand cmdList[3];
    char pad_3C[0x4];
    OSAlarm alarmForWA;
    char alarms[0x50];
    DVDLowReadRegion prev;
    DVDLowReadRegion curr;
} DVDLowWork;

typedef void (*OSAlarmHandler)(OSAlarm *alarm, void *context);

extern DVDLowWork CommandList_80641880;
extern volatile s32 NextCommandNumber_8064D9DC;
extern volatile u32 WorkAroundType_8064D9BC;
extern s32 FirstRead; /* FirstTimeInBootrom */
/* LastReadFinished; the symbol table splits its low word as lbl_8064D9CC. */
extern volatile OSTime LastReadFinished;

extern OSTime __OSGetSystemTime(void);
extern void OSCreateAlarm(OSAlarm *alarm);
extern void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);
extern DVDDiskID *DVDGetCurrentDiskID(void); /* DVDGetCurrentDiskID */
extern void Read(void *addr, u32 length, u32 offset, DVDLowCallback callback);
extern void SeekTwiceBeforeRead(void *addr, u32 length, u32 offset, DVDLowCallback callback);
extern void fn_802124D4(OSAlarm *alarm, void *context);

volatile u32 __DIRegs[16] : 0xCC006000;

#define OS_BUS_CLOCK (*(u32 *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

static BOOL HitCache(DVDLowReadRegion *cur, DVDLowReadRegion *prev) {
    u32 uNumBlocks;
    u32 blockNumOfPrevEnd = (prev->offset + prev->length - 1) >> 15;
    u32 blockNumOfCurrStart = cur->offset >> 15;

    uNumBlocks = (DVDGetCurrentDiskID()->streaming ? TRUE : FALSE) ? 5 : 15;
    if (blockNumOfCurrStart > blockNumOfPrevEnd - 2 ||
        blockNumOfCurrStart < blockNumOfPrevEnd + uNumBlocks + 3) {
        return TRUE;
    }
    return FALSE;
}

/* DVDLowRead */
BOOL DVDLowRead(void *addr, u32 length, u32 offset, DVDLowCallback callback) {
    u32 blockNumOfCurrStart;
    u32 blockNumOfPrevEnd;
    u32 wait;
    OSTime diff;
    OSTime tick;
    OSTime last;
    DVDLowWork *w = &CommandList_80641880;

    __DIRegs[6] = length;
    w->curr.addr = addr;
    w->curr.length = length;
    w->curr.offset = offset;

    if (WorkAroundType_8064D9BC == 0) {
        w->cmdList[0].cmd = -1;
        NextCommandNumber_8064D9DC = 0;
        Read(addr, length, offset, callback);
    } else if (WorkAroundType_8064D9BC == 1) {
        if (FirstRead) {
            SeekTwiceBeforeRead(addr, length, offset, callback);
        } else {
            if (!HitCache(&CommandList_80641880.curr, &CommandList_80641880.prev)) {
                w->cmdList[0].cmd = -1;
                NextCommandNumber_8064D9DC = 0;
                Read(addr, length, offset, callback);
            } else {
                blockNumOfPrevEnd = (CommandList_80641880.prev.offset + CommandList_80641880.prev.length - 1) >> 15;
                if (blockNumOfPrevEnd ==
                        (blockNumOfCurrStart = CommandList_80641880.curr.offset >> 15) ||
                    blockNumOfPrevEnd + 1 == blockNumOfCurrStart) {
                    diff = __OSGetSystemTime();
                    last = LastReadFinished;
                    diff -= last;
                    wait = OSMillisecondsToTicks(5);
                    if (wait < diff) {
                        w->cmdList[0].cmd = -1;
                        NextCommandNumber_8064D9DC = 0;
                        Read(addr, length, offset, callback);
                    } else {
                        tick = wait - diff + OSMicrosecondsToTicks(500);
                        w->cmdList[0].cmd = 1;
                        w->cmdList[0].addr = addr;
                        w->cmdList[0].length = length;
                        w->cmdList[0].offset = offset;
                        w->cmdList[0].callback = callback;
                        w->cmdList[1].cmd = -1;
                        NextCommandNumber_8064D9DC = 0;
                        OSCreateAlarm(&w->alarmForWA);
                        OSSetAlarm(&w->alarmForWA, tick, fn_802124D4);
                    }
                } else {
                    SeekTwiceBeforeRead(addr, length, offset, callback);
                }
            }
        }
    }
    return TRUE;
}
