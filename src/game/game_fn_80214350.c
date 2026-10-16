typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
    s32 currTransferSize;
    u8 pad14[0x10];
    DVDDiskID *id;
    void (*callback)(s32, DVDCommandBlock *);
};

extern DVDCommandBlock *executing_8064DA00;
extern DVDDiskID *currID_8064DA04;
extern s32 CurrCommand_8064DA1C;
extern void (*lbl_8064DA48)(DVDCommandBlock *);
extern DVDDiskID tmpBuffer_80641960;

extern int fn_800F98EC(const void *, const void *, unsigned long); /* memcmp */
extern void *memcpy(void *, const void *, unsigned long);
extern void DCInvalidateRange(void *, u32);
extern s32 DVDLowStopMotor(void (*)(u32));
extern void fn_802144A0(u32);
/* These state handlers ignore the command block passed by the dispatcher. */
extern void fn_80214468();
extern void fn_80214434();

/* stateCheckID */
void fn_80214350(void)
{
    struct {
        DVDDiskID *id;
    } buffer;

    buffer.id = &tmpBuffer_80641960;

    switch (CurrCommand_8064DA1C) {
    case 3:
        if (fn_800F98EC(buffer.id, executing_8064DA00->id, 0x1C) != 0) {
            DVDLowStopMotor(fn_802144A0);
            break;
        }
        memcpy(currID_8064DA04, buffer.id, sizeof(DVDDiskID));
        executing_8064DA00->state = 1;
        DCInvalidateRange(buffer.id, sizeof(DVDDiskID));
        lbl_8064DA48 = fn_80214468;
        fn_80214468(executing_8064DA00);
        break;
    default:
        if (fn_800F98EC(buffer.id, currID_8064DA04, sizeof(DVDDiskID)) != 0) {
            DVDLowStopMotor(fn_802144A0);
            break;
        }
        lbl_8064DA48 = fn_80214434;
        fn_80214434(executing_8064DA00);
        break;
    }
}
