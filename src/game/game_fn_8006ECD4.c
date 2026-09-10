typedef struct Entry {
    int id;
} Entry;

typedef struct Owner {
    unsigned char pad_00[4];
    Entry *entries[3];
} Owner;

int fn_8006ECD4(Owner *owner, int id)
{
    Entry *entry;
    int i;
    int result;

    result = -1;
    for (i = 0; i < 3; i++) {
        entry = owner->entries[i];
        if (entry != 0 && entry->id == id) {
            result = i;
            break;
        }
    }
    return result;
}
