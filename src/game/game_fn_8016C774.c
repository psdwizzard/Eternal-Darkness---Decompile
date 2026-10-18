extern unsigned int fn_8015C910(void);
extern void lua_pushnumber(void*, double);

int fn_8016C774(void* state)
{
    lua_pushnumber(state, fn_8015C910());
    return 1;
}
