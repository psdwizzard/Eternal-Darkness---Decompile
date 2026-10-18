typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SequenceInfo {
    u8 pad0[2];
    u16 flags;
    u8 arg2;
    u8 pitch;
    u8 key;
    u8 velocity;
    u8 arg3;
    u8 arg11;
} SequenceInfo;

extern SequenceInfo* dataGetFX(u32);

u8 synthFXGetMaxVoices(u32 sequence)
{
    SequenceInfo* info = dataGetFX(sequence);

    if (info != 0) {
        return info->arg2;
    }
    return 0;
}
