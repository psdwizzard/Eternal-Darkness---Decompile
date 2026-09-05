typedef struct Entry {
    int id;
} Entry;

typedef struct Owner {
    unsigned char pad_00[4];
    Entry *entries[3];
} Owner;

Entry *fn_8006ED3C(Owner *owner, int id, int *index)
{
    Entry *result;
    int i;

    *index = -1;
    result = 0;
    for (i = 0; i < 3; i++) {
        if (owner->entries[i] != 0 && owner->entries[i]->id == id) {
            *index = i;
            result = owner->entries[i];
            break;
        }
    }
    return result;
}
