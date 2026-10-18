typedef struct Entry {
    int value;
    char padding[12];
} Entry;

typedef struct Object {
    Entry* current;
    Entry* allocation;
    Entry* end;
    int count;
} Object;

extern void luaD_checkstack(Object*, int);

void luaD_adjusttop(Object* object, Entry* allocation, int count)
{
    int missing = count - (object->current - allocation);

    if (missing <= 0) {
        object->current = allocation + count;
    } else {
        luaD_checkstack(object, missing);
        while (missing != 0) {
            (object->current++)->value = 1;
            missing--;
        }
    }
}
