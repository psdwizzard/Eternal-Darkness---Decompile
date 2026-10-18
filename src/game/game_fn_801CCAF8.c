typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x90];
    u8 field90;
    u8 pad91[0x63];
} Entry;

extern Entry* dspVoice;

u8 hwGetSampleType(u32 index)
{
    return dspVoice[index].field90;
}
