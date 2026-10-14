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
extern volatile u32 WorkAroundSeekLocation_8064D9C0;
extern volatile s32 NextCommandNumber_8064D9DC;
extern s32 fn_802129F0(u32 offset, DVDLowCallback callback);

/* Queue a workaround seek before the requested read. */
void fn_802126D8(void *addr, u32 length, u32 offset, DVDLowCallback callback) {
    DVDCommand *commands = CommandList_80641880;
    u32 blockOffset = offset & ~0x7FFF;
    u32 seekOffset;

    if (blockOffset == 0) {
        seekOffset = 0;
    } else {
        seekOffset = blockOffset + WorkAroundSeekLocation_8064D9C0;
    }

    commands[0].cmd = 2;
    commands[0].offset = seekOffset;
    commands[0].callback = callback;
    commands[1].cmd = 1;
    commands[1].addr = addr;
    commands[1].length = length;
    commands[1].offset = offset;
    commands[1].callback = callback;
    commands[2].cmd = -1;
    NextCommandNumber_8064D9DC = 0;
    fn_802129F0(seekOffset, callback);
}
