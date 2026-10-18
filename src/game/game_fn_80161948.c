typedef struct Entry {
    char pad00[0x10];
    int state;
    char pad14[4];
} Entry;

typedef struct Collection {
    char pad00[0x50];
    Entry* entries;
    int count;
} Collection;

#pragma use_lmw_stmw on

extern int hasmark(Entry*);

void invalidaterefs(Collection* collection)
{
    int unused = -3;
    int offset;
    int count = collection->count;
    int index;

    for (index = 0, offset = 0; index < count; offset += sizeof(Entry), index++) {
        Entry* entry = (Entry*)((char*)collection->entries + offset);
        if (entry->state == -2 && !hasmark(entry))
            entry->state = unused;
    }
}
