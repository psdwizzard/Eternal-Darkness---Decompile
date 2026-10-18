typedef struct Object {
    char* current;
    char padding04[12];
    char* saved;
    char padding14[88];
    int active;
} Object;

typedef void (*Callback)(Object*, void*);

extern void luaD_checkstack(Object*, int);

void dohook(Object* object, void* argument, Callback callback)
{
    char* current;
    char* saved;

    saved = object->saved;
    current = object->current;

    object->saved = current;
    luaD_checkstack(object, 20);
    object->active = 0;
    callback(object, argument);
    object->active = 1;
    object->current = current;
    object->saved = saved;
}
