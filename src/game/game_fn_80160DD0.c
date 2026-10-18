typedef struct Object {
    char _pad00[0x5C];
    char* current;
    char* mark;
} Object;

typedef struct Args {
    void* value;
    int flag;
} Args;

extern void luaC_checkGC(void);
extern void f_parser(Object*, Args*);
extern int luaD_runprotected(Object*, void (*)(Object*, Args*), Args*);

int protectedparser(Object* object, void* value, int flag)
{
    Args args;
    char* saved;
    int result;

    args.value = value;
    args.flag = flag;
    luaC_checkGC();
    saved = object->mark;
    result = luaD_runprotected(object, f_parser, &args);
    if (result == 0) {
        object->current += object->mark - saved;
    } else if (result == 1) {
        result = 3;
    }
    return result;
}
