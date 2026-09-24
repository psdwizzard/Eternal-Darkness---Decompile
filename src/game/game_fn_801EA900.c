typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Record {
    u32 tag;
    u32 data;
} Record;

typedef struct Entry {
    u8 pad00[0x2C];
    u32 data2C;
    s8 count30;
    u8 pad31[3];
    u32 data34;
} Entry;

u32 fn_801EA900(const u8* source, Entry** output, u16 count)
{
    Entry* entries;
    Entry* entry;
    u32 size = (u32)*output;
    u32 offset = 0;
    int outer;

    if (size != 0) {
        *output = (Entry*)source;
        offset = size;
    } else {
        *output = 0;
    }
    entries = *output;
    for (outer = 0; outer < count; outer++) {
        entry = &entries[outer];
        size = entry->data2C;
        if (size != 0) {
            entry->data2C = (u32)(source + offset);
            offset += size;
        } else {
            entry->data2C = 0;
        }
    }
    for (outer = 0; outer < count; outer++) {
        entry = &entries[outer];
        size = entry->data34;
        if (size != 0) {
            int i = 0;

            entry->data34 = (u32)(source + offset);
            offset += size;
            while (i < entry->count30) {
                size = ((Record*)entry->data34)[i].data;
                if (size != 0) {
                    ((Record*)entry->data34)[i].data = (u32)(source + offset);
                    offset += size;
                } else {
                    ((Record*)entry->data34)[i].data = 0;
                }
                i++;
            }
        } else {
            entry->data34 = 0;
        }
    }
    return offset;
}
