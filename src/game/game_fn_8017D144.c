typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    s8 state;
    s8 pad[3];
    void* data;
    struct Entry* next;
} Entry;

typedef struct Manager {
    void* data;
    u16 count;
    u16 pad;
    u32 size;
    Entry* entries;
    Entry* current;
    Entry* first;
    Entry* last;
} Manager;

extern Entry* fn_8017D064(Entry*, Entry*);

#pragma opt_propagation off
#pragma optimization_level 1
void fn_8017D144(Manager* manager)
{
    int state;
    int offset;
    u32 count;
    u32 i;
    int was_empty = 0;

    if (manager->first == 0) {
        was_empty = 1;
    }
    offset = 0;
    count = manager->count;
    state = offset;
    for (i = 0; i < count; i++) {
        Entry* entry = (Entry*)((char*)manager->entries + offset);
        if (entry->state == -1) {
            entry->state = state;
            manager->first = fn_8017D064(manager->first, entry);
            if (was_empty != 0) {
                was_empty = 0;
                manager->last = manager->first;
            }
        }
        offset += sizeof(Entry);
    }
}
#pragma opt_propagation reset
#pragma optimization_level reset
