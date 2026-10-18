typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x94];
    u32 field94;
    u32 field98;
    u8 pad9C[0x58];
} Entry;

extern Entry* dspVoice;

void hwSetVirtualSampleLoopBuffer(u32 index, u32 value94, u32 value98)
{
    dspVoice[index].field94 = value94;
    dspVoice[index].field98 = value98;
}
