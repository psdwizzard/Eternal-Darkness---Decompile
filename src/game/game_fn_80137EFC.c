typedef struct Entry {
    unsigned int flags;
    int id;
    void* owner;
    float position[3];
    float radius;
} Entry;

extern Entry lbl_805ADE20[15];

Entry* fn_80137EFC(int id)
{
    int i;
    Entry* entry;
    Entry* result;

    result = 0;
    entry = lbl_805ADE20;
    for (i = 0; i < 15; i++, entry++) {
        if ((entry->flags & 1) && entry->id == id) {
            result = entry;
        }
    }
    return result;
}
