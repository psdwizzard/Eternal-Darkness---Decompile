typedef struct Object {
    char* current;
    char _pad04[4];
    char* end;
} Object;

typedef struct Value {
    double first;
    double second;
} Value;

extern char lbl_8024F5B0[];
extern Value* luaH_getglobal(void*, char*);
extern void luaD_checkstack(Object*, int);
extern void lua_pushstring(Object*, void*);
extern void luaD_call(Object*, char*, int);

void message(Object* object, void* argument)
{
    char* name = lbl_8024F5B0;
    Value* value = luaH_getglobal(object, name);

    if (*(int*)value == 5) {
        *(Value*)object->current = *value;
        if (object->current == object->end) {
            luaD_checkstack(object, 1);
        }
        object->current += sizeof(Value);
        lua_pushstring(object, argument);
        luaD_call(object, object->current - 32, 0);
    }
}
