typedef struct Entry {
    int type;
    char padding04[4];
    void* value;
    char padding0C[4];
} Entry;

typedef struct Object {
    Entry* current;
} Object;

typedef void (*Callback)(Object*, Entry*, void*);

extern void luaD_openstack(Object*, Entry*);
extern void luaD_call(Object*, Entry*, void*);

void luaD_callTM(Object* object, void* value, int index, void* callback)
{
    Entry* entry;

    entry = object->current - index;
    luaD_openstack(object, entry);
    entry->value = value;
    entry->type = 5;
    luaD_call(object, entry, callback);
}
