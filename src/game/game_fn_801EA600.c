typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 pad00[12];
    u32 data0C;
    u32 data10;
} Entry;

typedef struct Header {
    u8 pad00[4];
    s32 count;
    u8 pad08[24];
    Entry* entries;
} Header;

extern void fn_801E9124(u32*);

u32 fn_801EA600(const u8* source, Header** output)
{
    Header** out = output;
    const u8* data = source;
    u32 offset = 0;
    u32 size;
    s32 count;
    s32 i;

    *out = (Header*)data;
    offset += sizeof(Header);
    fn_801E9124(&offset);
    size = (u32)(*out)->entries;
    count = (*out)->count;
    if (size != 0) {
        (*out)->entries = (Entry*)(data + offset);
        offset += size;
    }
    for (i = 0; i < count; i++) {
        size = (*out)->entries[i].data10;
        if (size != 0) {
            (*out)->entries[i].data10 = (u32)(data + offset);
            offset += size;
        }
        size = (*out)->entries[i].data0C;
        if (size != 0) {
            (*out)->entries[i].data0C = (u32)(data + offset);
            offset += size;
        }
    }
    return offset;
}
