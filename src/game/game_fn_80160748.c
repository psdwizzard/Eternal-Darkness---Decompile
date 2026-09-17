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

extern void fn_8016057C(Object*, int);

void fn_80160748(Object* object, Entry* allocation)
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
        fn_8016057C(object, 1);
    object->current++;
}
