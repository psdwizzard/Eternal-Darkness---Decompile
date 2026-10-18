extern void luaK_testgo(void*, void*, int, int);

void luaK_goiftrue(void* object, void* command, int alternate)
{
    luaK_testgo(object, command, 1, alternate ? 41 : 39);
}
