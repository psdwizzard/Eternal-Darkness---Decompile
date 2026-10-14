typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

extern DVDDiskID *currID_8064DA04;
extern s32 fn_80212E2C(s32 enable, u32 size, DVDLowCallback callback);
extern void fn_80214658(u32 intType);

/* Configure the audio stream buffer from the current disk ID. */
void fn_80214434(void)
{
    fn_80212E2C(currID_8064DA04->streaming, 10, fn_80214658);
}
