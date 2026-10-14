typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

extern volatile u32 WorkAroundType_8064D9BC;
extern volatile u32 WorkAroundSeekLocation_8064D9C0;

void __DVDLowSetWAType(u32 type, u32 seekLocation)
{
    BOOL level;

    level = OSDisableInterrupts();
    WorkAroundType_8064D9BC = type;
    WorkAroundSeekLocation_8064D9C0 = seekLocation;
    OSRestoreInterrupts(level);
}
