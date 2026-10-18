typedef struct Entry {
    long long first;
    long long second;
} Entry;

typedef struct Object {
    Entry* current;
    Entry* allocation;
    Entry* end;
    int count;
} Object;

extern void luaD_checkstack(Object*, int);

void luaD_openstack(Object* object, Entry* allocation)
{
    Entry* entry;
    int count;

    count = object->current - allocation;
    entry = allocation + count;
    goto check;
copy:
    entry[1] = entry[0];
check:
    entry--;
    if (count-- != 0)
        goto copy;
    if (object->current == object->end)
        luaD_checkstack(object, 1);
    object->current++;
}
