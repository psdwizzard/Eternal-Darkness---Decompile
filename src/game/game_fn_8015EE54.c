extern int luaK_code1(void*, int, int);

int luaK_adjuststack(void* object, int value)
{
    if (value > 0)
        return luaK_code1(object, 5, value);
    return luaK_code1(object, 4, -value);
}
