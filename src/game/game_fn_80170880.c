extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const char lbl_8025014C[];
extern void* lbl_8064C4E4;

int fn_80170880(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    switch ((int)lua_tonumber(state, 1)) {
    case 0:
        lua_pushusertag(state, lbl_8064C4E4, 0);
        return 1;
    case 1:
        lua_pushusertag(state, 0, 0);
        return 1;
    default:
        luaO_verror(state, lbl_8025014C, (int)lua_tonumber(state, 1));
        lua_pushusertag(state, 0, 0);
        return 1;
    }
}
