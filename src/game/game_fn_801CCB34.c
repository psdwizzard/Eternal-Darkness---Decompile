typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xD4];
    u8 fieldD4;
    u8 padD5[0x1F];
} Entry;

extern Entry* dspVoice;
extern u8 salTimeOffset;
extern void salActivateVoice(Entry*, u8);

void hwStart(u32 index, u8 value)
{
    dspVoice[index].fieldD4 = salTimeOffset;
    salActivateVoice(&dspVoice[index], value);
}
