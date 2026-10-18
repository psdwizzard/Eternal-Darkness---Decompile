typedef signed short s16;
typedef unsigned int u32;

extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern u32 fn_80178F14(int, int, int, int, int, int);
extern const char lbl_8024FF00[];

int fn_80175F0C(void* state)
{
    s16* first;
    s16* second;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (s16*)lua_touserdata(state, 1);
    second = (s16*)lua_touserdata(state, 2);
    lua_pushnumber(state, (double)fn_80178F14(first[0], first[1], first[2],
                                           second[0], second[1], second[2]));
    return 1;
}
