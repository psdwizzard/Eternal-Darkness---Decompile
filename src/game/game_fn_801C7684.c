typedef unsigned char u8;

typedef struct Entry Entry;
struct Entry {
    unsigned char pad00[0xC];
    Entry* next;
    Entry* previous;
    Entry* next_secondary;
    unsigned char pad18[0xD4];
    u8 active;
    unsigned char padED[2];
    u8 group;
};

typedef struct Group {
    unsigned char pad00[0x48];
    Entry* head;
    Entry* secondary_head;
    unsigned char pad50[0x6C];
} Group;

extern Group lbl_80628CB0[];

void fn_801C7684(Entry* entry, u8 group)
{
    Group* groups = lbl_80628CB0;
    Entry* next;

    if (entry->active != 0) {
        if (entry->previous != 0) {
            entry->previous->next = entry->next;
        } else {
            groups[entry->group].head = entry->next;
        }

        if (entry->next != 0) {
            entry->next->previous = entry->previous;
        }

        next = groups[group].head;
        entry->next = next;
        if (next != 0) {
            entry->next->previous = entry;
        }
        entry->previous = 0;
        groups[group].head = entry;

        if (entry->active == 2) {
            u8* secondary = (u8*)&groups->secondary_head;
            entry->next_secondary = *(Entry**)(secondary + entry->group * sizeof(Group));
            *(Entry**)(secondary + entry->group * sizeof(Group)) = entry;
        }
    }
    entry->group = group;
}
