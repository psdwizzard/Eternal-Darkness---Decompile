typedef unsigned int u32;
typedef unsigned char u8;
typedef int BOOL;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

extern DVDDiskID tmpBuffer_80641960;
extern BOOL DVDLowRead(void *, u32, u32, void (*)(u32));
extern void cbForStateCheckID2(u32);

void stateCheckID2(void)
{
    DVDLowRead(&tmpBuffer_80641960, 0x20, 0x420, cbForStateCheckID2);
}
