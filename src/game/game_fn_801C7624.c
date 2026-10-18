typedef unsigned char u8;

typedef struct Entry Entry;
struct Entry {
    unsigned char pad00[0xC];
    Entry* next;
    Entry* previous;
    unsigned char pad14[0xD8];
    u8 active;
    unsigned char padED[2];
    u8 group;
};

typedef struct Group {
    unsigned char pad00[0x48];
    Entry* head;
    unsigned char pad4C[0x70];
} Group;

extern Group dspStudio[];

void salDeactivateVoice(Entry* entry)
{
    if (entry->active == 0) {
        return;
    }

    if (entry->previous != 0) {
        entry->previous->next = entry->next;
    } else {
        dspStudio[entry->group].head = entry->next;
    }

    if (entry->next != 0) {
        entry->next->previous = entry->previous;
    }
    entry->active = 0;
}
