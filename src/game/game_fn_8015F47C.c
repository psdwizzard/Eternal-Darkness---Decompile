extern int luaK_getlabel(void*);
extern int luaK_code1(void*, int, int);

int code_label(void* object, int type, int value)
{
    luaK_getlabel(object);
    return luaK_code1(object, type, value);
}
