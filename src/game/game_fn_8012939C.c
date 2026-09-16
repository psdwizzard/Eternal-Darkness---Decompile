typedef struct Entry {
    int packed;
    int value;
    int key;
} Entry;

extern void fn_801292E0(void*, int*, int*);

int fn_8012939C(void* owner, int value, int keyed, int key, int* result,
                int start)
{
    int index = start + 1;
    int count;
    Entry* entry;
    int entries;
    int found = -1;

    fn_801292E0(owner, &count, &entries);
    if (count > 0 && index < count) {
        Entry* base = (Entry*)entries;
        int current = index;
        entry = base;
        entry += index;

        while (current < count) {
            int key_matches = !keyed || (keyed && key == entry->key);
            if (value == entry->value && key_matches) {
                found = current;
                *result = base[current].packed >> 17;
                break;
            }
            entry++;
            current++;
        }
    }
    return found;
}
