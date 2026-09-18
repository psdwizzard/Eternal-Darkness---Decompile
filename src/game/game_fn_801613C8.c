typedef struct Entry {
    void* value;
    int minimum;
    int maximum;
} Entry;

typedef struct Object {
    char _pad00[0x34];
    int count;
    Entry* entries;
} Object;

void* fn_801613C8(Object* object, int ordinal, int key)
{
    int offset;
    int count;
    Entry* entry;
    Entry* entries;
    int i;

    count = object->count;
    i = 0;
    offset = 0;

    goto test;
loop:
    if (key < entry->maximum && --ordinal == 0)
        return (char*)entries[i].value + 0x14;
    offset += sizeof(Entry);
    i++;
test:
    if (i < count) {
        entries = object->entries;
        entry = (Entry*)((char*)entries + offset);
        if (entry->minimum <= key)
            goto loop;
    }
    return 0;
}
