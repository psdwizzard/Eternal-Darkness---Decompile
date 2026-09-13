typedef struct Entry {
    unsigned char active;
    unsigned char padding[3];
    unsigned int id;
    unsigned int value8;
    unsigned int valueC;
    unsigned char remainder[116];
} Entry;

typedef struct EntryState {
    Entry entries[3];
    unsigned int next_id;
} EntryState;

extern EntryState lbl_8060B430;

#pragma peephole off
int fn_801AD9F4(Entry** result)
{
    unsigned int slot;
    Entry* entries;
    Entry* entry;

    slot = 0;
    entries = lbl_8060B430.entries;
    entry = entries;
    for (; slot < 3; entry++, slot++) {
        if (entry->active == 0) {
            unsigned int index;
            unsigned int id;

            do {
                id = lbl_8060B430.next_id++;
                if (id == 0xFFFFFFFF) {
                    id = lbl_8060B430.next_id++;
                }

                for (index = 0; index < 3; index++) {
                    if (entries[index].active != 0 &&
                        id == entries[index].id) {
                        break;
                    }
                }
            } while (index != 3);

            lbl_8060B430.entries[slot].active = 1;
            lbl_8060B430.entries[slot].id = id;
            lbl_8060B430.entries[slot].value8 = 0;
            lbl_8060B430.entries[slot].valueC = 0;
            *result = &lbl_8060B430.entries[slot];
            return id;
        }
    }

    return -1;
}
#pragma peephole reset
