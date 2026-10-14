typedef signed int s32;
typedef unsigned int u32;
typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDCommand {
    s32 cmd;
    void *addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

extern DVDCommand CommandList_80641880[];
extern volatile s32 NextCommandNumber_8064D9DC;

extern void __DVDLowSetWAType(u32 type, u32 seekLocation);
extern void OSInitAlarm(void);

void __DVDInitWA(void)
{
    NextCommandNumber_8064D9DC = 0;
    CommandList_80641880[0].cmd = -1;
    __DVDLowSetWAType(0, 0);
    OSInitAlarm();
}
