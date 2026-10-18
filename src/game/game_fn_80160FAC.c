extern void message(void*, void*);
extern void luaD_breakrun(void*, int);

void lua_error(void* object, void* argument)
{
    if (argument != 0) {
        message(object, argument);
    }
    luaD_breakrun(object, 1);
}
