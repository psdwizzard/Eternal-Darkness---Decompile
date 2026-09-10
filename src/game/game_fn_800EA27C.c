typedef struct Entry {
    unsigned char pad[0xA4];
    int priority;
    unsigned char padA8[6];
    unsigned char flags;
} Entry;

extern Entry *lbl_80325F1C[6];

int fn_800EA27C(int *result)
{
    Entry *entry;
    int i;
    int found = 0;
    int first = 1;
    int best;

    *result = -1;
    for (i = 0; i < 6; i++) {
        if (lbl_80325F1C[i] == 0) {
            *result = i;
            found = 1;
            break;
        }
        entry = lbl_80325F1C[i];
        if ((entry->flags & 0x40) == 0 && (entry->flags & 0x10) != 0) {
            if (first || entry->priority < best) {
                best = entry->priority;
                first = 0;
                *result = i;
            }
        }
    }
    return found;
}
