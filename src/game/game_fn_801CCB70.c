typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags[4];
    u8 pad34[0xC0];
} Entry;

extern Entry* dspVoice;
extern u8 salTimeOffset;

void hwKeyOff(u32 index)
{
    dspVoice[index].flags[salTimeOffset] |= 0x40;
}
