extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_801295E8(void*, int, unsigned short, int);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const char lbl_80250028[];

int fn_8016EB1C(void* state)
{
    int value;
    unsigned short kind;
    int object_id;
    int mode;
    void* result;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    kind = (unsigned short)(int)lua_tonumber(state, 3);
    mode = (int)lua_tonumber(state, 4);
    result = fn_801295E8(fn_80201BC8(fn_80201814(object_id)), value, kind, mode);
    lua_pushusertag(state, result, 0);
    if (result == 0) {
        luaO_verror(state, lbl_80250028, 0);
    }
    return 1;
}
