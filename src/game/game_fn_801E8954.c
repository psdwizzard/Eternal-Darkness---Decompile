typedef unsigned int u32;
typedef struct Entry { void* value; u32 type; } Entry;
typedef struct Table { u32 count; u32 magic; Entry entries[1]; } Table;

void fn_801E8954(Table* table)
{
    u32 i;
    Entry* entry;
    if (table == 0) return;
    entry = table->entries;
    if (table->magic != 0x6B5) return;
    for (i = 0; i < table->count; i++, entry++) {
        if (entry->type != 0) {
            Table* nested = entry->value;
            if (nested->magic == 0xFB90) {
                Entry* nested_entry = nested->entries;
                u32 j;
                void* null_value = 0;
                for (j = 0; j < nested->count; j++, nested_entry++) {
                    if (nested_entry->type != 0) {
                        if (nested_entry->value < (void*)nested) {
                            nested_entry->value = (char*)nested_entry->value - (u32)nested;
                        }
                    } else {
                        nested_entry->value = null_value;
                    }
                }
            }
            entry->value = (char*)entry->value - (u32)table;
        } else {
            entry->value = 0;
        }
    }
}
