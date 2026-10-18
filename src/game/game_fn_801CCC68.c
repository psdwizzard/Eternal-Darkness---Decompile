typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0xD0];
    u16 fieldD0;
    u16 fieldD2;
    u8 padD4[0x1C];
    u32 flagsF0;
} Entry;

extern Entry* dspVoice;

void hwSetITDMode(u32 index, u8 enabled)
{
    if (enabled == 0) {
        dspVoice[index].flagsF0 |= 0x80000000;
        dspVoice[index].fieldD0 = 0x10;
        dspVoice[index].fieldD2 = 0x10;
    } else {
        dspVoice[index].flagsF0 &= 0x7FFFFFFF;
    }
}
