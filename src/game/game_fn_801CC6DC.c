typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad[0xEC];
    u8 active;
    u8 rest[7];
} Entry;

extern Entry* dspVoice;

u32 hwIsActive(u32 index)
{
    return dspVoice[index].active != 0;
}
