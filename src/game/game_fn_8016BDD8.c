extern void* fn_80201B3C(void);
extern void lua_pushusertag(void*, void*, int);

int fn_8016BDD8(void* state)
{
    void* value = fn_80201B3C();
    lua_pushusertag(state, value, 0);
    return 1;
}
