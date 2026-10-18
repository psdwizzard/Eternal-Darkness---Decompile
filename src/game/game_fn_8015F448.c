extern void luaK_testgo(void*, void*, int, int);

void luaK_goiffalse(void* object, void* command, int alternate)
{
    luaK_testgo(object, command, 0, alternate ? 40 : 38);
}
