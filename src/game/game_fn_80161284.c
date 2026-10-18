typedef struct Object {
    char _pad00[0x60];
    int allocation_size;
} Object;

typedef struct Entry {
    int field00;
    int field04;
    int field08;
    int field0C;
    int field10;
    int field14;
    int field18;
    int count;
    int field20;
    int field24;
    int field28;
    int field2C;
    int field30;
    int field34;
    int field38;
} Entry;

extern char lbl_8064BA80;
extern int protosize(Entry*);
extern void* luaM_realloc(Object*, int, unsigned int, char*, int);

void luaF_freeproto(Object* object, Entry* entry)
{
    if (entry->count > 0)
        object->allocation_size -= protosize(entry);

    luaM_realloc(object, entry->field18, 0, &lbl_8064BA80, 78);
    luaM_realloc(object, entry->field38, 0, &lbl_8064BA80, 79);
    luaM_realloc(object, entry->field08, 0, &lbl_8064BA80, 80);
    luaM_realloc(object, entry->field00, 0, &lbl_8064BA80, 81);
    luaM_realloc(object, entry->field10, 0, &lbl_8064BA80, 82);
    luaM_realloc(object, entry->field2C, 0, &lbl_8064BA80, 83);
    luaM_realloc(object, (int)entry, 0, &lbl_8064BA80, 84);
}
