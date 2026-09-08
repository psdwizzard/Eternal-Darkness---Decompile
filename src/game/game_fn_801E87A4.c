typedef unsigned int u32;
typedef struct Entry { void* value; u32 type; } Entry;
typedef struct Table { u32 count; u32 magic; Entry entries[1]; } Table;

void fn_801E87A4(Table* table, Table* other)
{
    Entry* entry;
    u32 i;
    if (table == 0) return;
    if (other == 0) return;
    if (table->magic != 0x6B5) return;
    if (other->magic != 0x6B5) return;
    entry = (Entry*)table;
    for (i = 0; i < table->count; ) {
        if (entry[1].value == other->entries[0].value) entry[1].value = 0;
        other = (Table*)((char*)other + 8);
        entry++;
        i++;
    }
}
