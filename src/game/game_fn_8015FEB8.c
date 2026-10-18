typedef struct Entry { int type; char pad4[0xC]; } Entry;
typedef struct List { char pad0[4]; Entry* entries; } List;

Entry* aux_stackedfunction(List* list, int ordinal, Entry* end)
{
    Entry* base = list->entries;
    int index = (end - 1) - base;
    Entry* entry = base + index;
    for (; index >= 0; --entry, --index) {
        if (entry->type == 6) {
            if (ordinal == 0)
                return base + index;
            --ordinal;
        }
    }
    return 0;
}
