extern int luaK_code2(void*, int, int, int);

int luaK_code1(void* object, int type, int value)
{
    return luaK_code2(object, type, value, 0);
}
