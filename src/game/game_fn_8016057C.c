typedef struct Object {
    char* current;
    char* allocation;
    char* end;
    int count;
} Object;

extern void luaD_breakrun(Object*, int);
extern void lua_error(Object*, const char*);
extern char lbl_8024F5A0[];

void luaD_checkstack(Object* object, int requested)
{
    if ((object->end - object->current) / 16 <= requested) {
        if ((object->end - object->allocation) / 16 > object->count - 1) {
            luaD_breakrun(object, 5);
        } else {
            object->end += 640;
            lua_error(object, lbl_8024F5A0);
        }
    }
}
