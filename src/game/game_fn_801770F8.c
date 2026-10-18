extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_801F99B8(void*);
extern const char lbl_8024FF00[];
extern char lbl_8063CD18[];

int fn_801770F8(void* state)
{
    unsigned int value;

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    value = fn_801F99B8(*(void**)(lbl_8063CD18 + 0x18C));
    lua_pushnumber(state, (double)value);
    return 1;
}
