typedef unsigned short u16;

typedef struct Entry {
    unsigned char pad[8];
    u16 id;
    unsigned char tail[6];
} Entry;

typedef struct Header {
    unsigned char pad[0x10];
    unsigned int count;
    Entry* entries;
} Header;

Entry* fn_80138950(Header* header, u16 id)
{
    unsigned int i;
    Entry* result = 0;
    Entry* entry = header->entries;

    for (i = 0; i < header->count; i++, entry++) {
        if (entry->id == id) {
            result = entry;
            break;
        }
    }
    return result;
}
