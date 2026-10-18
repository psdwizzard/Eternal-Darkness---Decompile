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

typedef void (*DVDLowCallback)(u32);

extern DVDDiskID tmpBuffer_80641960;
extern s32 DVDLowReadDiskID(void *addr, DVDLowCallback callback);
extern void cbForStateCoverClosed(u32 intType);

void stateCoverClosed_CMD(void)
{
    DVDLowReadDiskID(&tmpBuffer_80641960, cbForStateCoverClosed);
}
