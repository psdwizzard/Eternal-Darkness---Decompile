typedef struct Object {
    char _pad00[0x60];
    int allocation_size;
} Object;

typedef struct Entry {
    char _pad00[0xE];
    short count;
} Entry;

extern char lbl_8064BA80;
extern void* luaM_realloc(Object*, Entry*, unsigned int, char*, int);

void luaF_freeclosure(Object* object, Entry* entry)
{
    object->allocation_size -= ((entry->count - 1) << 4) + 0x20;
    luaM_realloc(object, entry, 0, &lbl_8064BA80, 90);
}
