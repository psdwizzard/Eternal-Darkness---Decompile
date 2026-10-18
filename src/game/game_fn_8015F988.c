extern int luaK_code2(void*, int, int, int);

void luaK_code0(void* object, int type)
{
    luaK_code2(object, type, 0, 0);
}
