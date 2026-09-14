typedef struct Entry {
    unsigned char active;
    unsigned char padding[79];
    void* handle;
    unsigned char remainder[48];
} Entry;

typedef struct EntryState {
    Entry entries[3];
    unsigned int next_id;
} EntryState;

extern EntryState lbl_8060B430;
extern void fn_801BB3A0(void*);
extern void fn_801BB1A0(void*);

void fn_801AD95C(int state)
{
    int i;
    Entry* entry;

    if (state != 0) {
        i = 0;
        entry = lbl_8060B430.entries;
        do {
            if (entry->active != 0) {
                fn_801BB3A0(entry->handle);
            }
            entry++;
            i++;
        } while (i < 3);
    } else {
        i = 0;
        entry = lbl_8060B430.entries;
        do {
            if (entry->active != 0) {
                fn_801BB1A0(entry->handle);
            }
            entry++;
            i++;
        } while (i < 3);
    }
}
