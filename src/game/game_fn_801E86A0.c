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

void* fn_801E86A0(Table* table, u32 index)
{
    if (table == 0 || table->magic != 0x6B5 || index >= table->count) {
        return 0;
    }
    return table->entries[index].value;
}
