typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags[4];
    u8 pad34[4];
    u32 values[4];
    u8 pad48[0x9C];
    u8 fieldE4;
    u8 padE5[0xF];
} Entry;

extern Entry* dspVoice;
extern u8 salTimeOffset;

void hwSetPitch(u32 index, u32 value)
{
    Entry* entry = &dspVoice[index];
    u8 slot;

    if ((u16)value >= 0x4000) {
        value = 0x3FFF;
    }
    if (entry->fieldE4 != 0xFF &&
        entry->values[entry->fieldE4] == ((value << 4) & 0xFFFF0)) {
        return;
    }
    slot = salTimeOffset;
    entry->values[slot] = (value << 4) & 0xFFFF0;
    entry->flags[salTimeOffset] |= 8;
    entry->fieldE4 = salTimeOffset;
}
