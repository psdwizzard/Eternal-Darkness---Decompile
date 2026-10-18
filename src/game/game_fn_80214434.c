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
extern s32 DVDLowAudioBufferConfig(s32 enable, u32 size, DVDLowCallback callback);
extern void cbForStateCheckID3(u32 intType);

/* Configure the audio stream buffer from the current disk ID. */
void stateCheckID3(void)
{
    DVDLowAudioBufferConfig(currID_8064DA04->streaming, 10, cbForStateCheckID3);
}
