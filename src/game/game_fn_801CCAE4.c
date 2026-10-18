typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x9C];
    u8 field9C;
    u8 pad9D[0x57];
} Entry;

extern Entry* dspVoice;

u8 hwGetVirtualSampleState(u32 index)
{
    return dspVoice[index].field9C;
}
