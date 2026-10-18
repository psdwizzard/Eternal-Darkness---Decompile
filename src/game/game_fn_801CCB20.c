typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xA0];
    u8 fieldA0;
    u8 padA1[0x53];
} Entry;

extern Entry* dspVoice;

void hwSetStreamLoopPS(u32 index, u8 value)
{
    dspVoice[index].fieldA0 = value;
}
