typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x70];
    u16 field70;
    u8 pad72[0x82];
} Entry;

extern Entry* dspVoice;

u16 hwGetSampleID(u32 index)
{
    return dspVoice[index].field70;
}
