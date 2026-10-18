typedef struct Object {
    char* current;
} Object;

typedef struct Args {
    char* entry;
    void* value;
} Args;

extern void f_call(void*, Args*);
extern int luaD_runprotected(Object*, void (*)(void*, Args*), Args*, int);

void lua_call(Object* object, int count, void* value)
{
    Args args;
    int size;
    char* saved;

    size = (count + 1) * 16;
    saved = object->current - size;
    args.entry = saved;
    args.value = value;
    if (luaD_runprotected(object, f_call, &args, size) != 0) {
        object->current = saved;
    }
}
