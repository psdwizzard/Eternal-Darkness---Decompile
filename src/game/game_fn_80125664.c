typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Record {
    u32 first;
    u8 pad4[0x114];
    u32 source;
    u8 pad11C[8];
    u32 second;
} Record;

typedef struct Header {
    u8 pad0[0x10];
    u32 self_offset;
    u16 count;
    u8 pad16[2];
    s32 records;
    u8 pad1C[4];
    s32 field20;
    u8 pad24[4];
    s32 field28;
} Header;

typedef struct Buffer {
    u8 pad0[0x10];
    u32 count;
} Buffer;

extern s32 fn_80125D1C(Header*);

Header* fn_80125664(Header* header, Buffer* buffer)
{
    u8* base;
    s32 i;
    u32 buffer_offset;

    if (fn_80125D1C(header)) {
        buffer_offset = 0;
        if (buffer != 0) {
            buffer_offset = ((buffer->count * 16 + 31) & ~31) + 32;
        }

        header->self_offset = (u32)header + header->self_offset;
        header->records = header->records == 0 ? 0 : (s32)header + header->records;
        header->field20 = header->field20 == 0 ? 0 : (s32)header + header->field20;
        header->field28 = header->field28 == 0 ? 0 : (s32)header + header->field28;

        base = (u8*)buffer + buffer_offset;
        for (i = 0; i < header->count; i++) {
            Record* record = &((Record*)header->records)[i];
            u32 source = record->source;
            record->first = 0;
            record->second = 0;
            if (source & 0x40000000)
                record->source = (source & ~0x40000000) + (u32)base;
            else
                record->source = (u32)((u8*)header + source);
        }
    }
    return header;
}
