typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xEC];
    u8 active;
    u8 padED[7];
} Entry;

extern Entry* dspVoice;

u32 hwVoiceInStartup(u32 index)
{
    return dspVoice[index].active == 1;
}
