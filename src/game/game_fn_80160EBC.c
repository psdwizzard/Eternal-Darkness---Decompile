extern int parse_buffer(void*, void*, void*, void*);
extern void lua_call(void*, int, int);

void lua_dobuffer(void* object, void* text, void* value, void* context)
{
    if (parse_buffer(object, text, value, context) == 0) {
        lua_call(object, 0, -1);
    }
}
