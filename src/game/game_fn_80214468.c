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
extern BOOL fn_80212758(void *, u32, u32, void (*)(u32));
extern void fn_802145B4(u32);

void fn_80214468(void)
{
    fn_80212758(&tmpBuffer_80641960, 0x20, 0x420, fn_802145B4);
}
