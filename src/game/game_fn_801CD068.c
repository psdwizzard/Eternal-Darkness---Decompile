typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 bytes[0xF4];
} Entry;

extern Entry* dspVoice;
extern void salReconnectVoice(Entry* entry);

void hwChangeStudio(u32 index)
{
    salReconnectVoice(&dspVoice[index]);
}
