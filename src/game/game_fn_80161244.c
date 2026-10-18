typedef struct Object {
    char _pad00[0x60];
    int allocation_size;
} Object;

typedef struct Entry {
    char _pad00[0x1C];
    int count;
} Entry;

extern int protosize(Entry*);

void luaF_protook(Object* object, Entry* entry, int count)
{
    entry->count = count;
    object->allocation_size += protosize(entry);
}
