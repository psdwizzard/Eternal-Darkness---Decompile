typedef unsigned int u32;
typedef struct Entry { void* value; u32 type; } Entry;
typedef struct Table { u32 count; u32 magic; Entry entries[1]; } Table;
void* fn_801E880C(Table* table, u32 outer, u32 inner)
{
    Table* nested;
    if (table == 0 || table->magic != 0x6B5 || outer >= table->count) return 0;
    nested = table->entries[outer].value;
    if (nested == 0 || nested->magic != 0xFB90 || inner >= nested->count) return 0;
    return nested->entries[inner].value;
}
