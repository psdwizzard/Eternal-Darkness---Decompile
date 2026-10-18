typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags[50];
    u8 padEC[8];
} Entry;

extern Entry* dspVoice;
extern u8 salTimeOffset;

void hwBreak(u32 index)
{
    Entry* entry = &dspVoice[index];

    if (((u8*)entry)[0xEC] == 1 && salTimeOffset == 0) {
        ((u8*)entry)[0xEE] = 1;
    }
    dspVoice[index].flags[salTimeOffset] |= 0x20;
}
