typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamHeader {
    u8 padding00[4];
    u16 format;
    u8 padding06[10];
} StreamHeader;

typedef struct Entry {
    u8 state;
    u8 type;
    u8 channels;
    u8 rate;
    u8 padding04[12];
    StreamHeader* header;
    u8 padding14[60];
    void* stream;
    u8 padding54[16];
    u32 buffer_size;
    u8 padding68[20];
    u32 buffered;
    u32 consumed;
} Entry;

extern u32 fn_801A9B94(u32, u32);
extern void sndStreamMixParameterEx(void*, u32, u32, u32, u32, u32);
extern void sndStreamFrq(void*, u32);
extern void sndStreamADPCMParameter(void*, void*);
extern void sndStreamARAMUpdate(void*, u32, u32, u32, u32);
extern u32 sndStreamActivate(void*);
extern int fn_801AE3C8(Entry*);
extern void DVDClose(void*);

int fn_801AE5DC(Entry* entry)
{
    u32 format = fn_801A9B94(entry->type, 2);

    sndStreamMixParameterEx(entry->stream, format, entry->channels, entry->rate, 0, 0);
    sndStreamFrq(entry->stream, entry->header->format);
    sndStreamADPCMParameter(entry->stream, (u8*)entry->header + 0x10);

    entry->consumed = 0;
    entry->buffered = 0;
    sndStreamARAMUpdate(entry->stream, 0, entry->buffer_size >> 1, 0, 0);

    if (sndStreamActivate(entry->stream) != 0) {
        entry->state = 4;
        fn_801AE3C8(entry);
        return 1;
    }

    entry->state = 0;
    DVDClose((u8*)entry + 0x14);
    return 0;
}
