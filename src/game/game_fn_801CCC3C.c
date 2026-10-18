typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags;
    u8 pad28[0xA6];
    u16 fieldCE;
    u8 padD0[0x24];
} Entry;

extern Entry* dspVoice;
extern u16 lbl_8064C2F0[4];

void hwSetPolyPhaseFilter(u32 index, u8 value)
{
    Entry* entry = &dspVoice[index];
    entry->fieldCE = lbl_8064C2F0[value];
    entry->flags |= 0x80;
}
