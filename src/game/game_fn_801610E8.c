typedef struct Entry {
    int _field00;
    struct Entry* next;
    struct Entry* self;
    short _field0C;
    short count;
} Entry;

typedef struct Object {
    char _pad00[0x24];
    Entry* entries;
    char _pad28[0x38];
    int allocation_size;
} Object;

extern char lbl_8064BA80;
extern void* luaM_realloc(Object*, int, unsigned int, char*, int);

void luaF_newclosure(Object* object, int count)
{
    int size = ((count - 1) << 4) + 0x20;
    Entry* entry = luaM_realloc(object, 0, size, &lbl_8064BA80, 22);

    entry->next = object->entries;
    object->entries = entry;
    entry->self = entry;
    entry->count = count;
    object->allocation_size += size;
}
