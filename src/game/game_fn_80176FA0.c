extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80176FA0(void* state)
{
    unsigned int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = *(unsigned int*)((char*)lua_touserdata(state, 1) + 0x2C);
    lua_pushnumber(state, (double)value);
    return 1;
}
