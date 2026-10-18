typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags;
    u8 pad28[0xA4];
    u16 fieldCC;
    u8 padCE[0x26];
} Entry;

extern Entry* dspVoice;
extern u16 lbl_8064C2E8[4];

void hwSetSRCType(u32 index, u8 value)
{
    Entry* entry = &dspVoice[index];
    entry->fieldCC = lbl_8064C2E8[value];
    entry->flags |= 0x100;
}
