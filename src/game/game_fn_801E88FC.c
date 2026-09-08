typedef unsigned int u32;
typedef struct Entry { void* value; u32 type; } Entry;
typedef struct Table { u32 count; u32 magic; Entry entries[1]; } Table;
u32 fn_801E88FC(Table* table, u32 index)
{
    Table* nested;
    if (table == 0 || table->magic != 0x6B5 || index >= table->count) return 0;
    nested = table->entries[index].value;
    if (nested == 0 || nested->magic != 0xFB90) return 0;
    return nested->count;
}
