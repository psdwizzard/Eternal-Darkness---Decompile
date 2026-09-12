typedef unsigned int u32;

typedef struct Entry {
    void* value;
    u32 type;
} Entry;

typedef struct Table {
    u32 count;
    u32 magic;
    Entry entries[1];
} Table;

extern char lbl_80265AB0[];
extern void fn_801E7DCC(const char*, ...);

void fn_801E86D8(Table* destination, Table* source)
{
    u32 i;
    u32 count;
    u32 source_count;
    u32 destination_count;
    Entry* destination_entry;
    Entry* source_entry;

    if (destination == 0) {
        return;
    }
    if (source == 0) {
        return;
    }
    if (destination->magic != 0x6B5) {
        return;
    }
    if (source->magic != 0x6B5) {
        return;
    }

    source_count = source->count;
    destination_count = destination->count;
    count = source_count;
    if (destination_count < source_count) {
        count = destination_count;
    }
    if (destination_count < source_count) {
        fn_801E7DCC(lbl_80265AB0, source_count, destination_count);
    }

    destination_entry = (Entry*)destination;
    source_entry = (Entry*)source;
    for (i = 0; i < count; i++, destination_entry++, source_entry++) {
        if (destination_entry[1].value == 0) {
            destination_entry[1] = source_entry[1];
        }
    }
}
