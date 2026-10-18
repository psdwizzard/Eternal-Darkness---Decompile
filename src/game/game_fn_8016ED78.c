extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_80129AF4(void*, int, unsigned short, float, float);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const char lbl_80250040[];
extern const float lbl_806506C0;

int fn_8016ED78(void* state)
{
    int value;
    unsigned short kind;
    void* result;
    int object_id;
    float first;
    float second;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    kind = (unsigned short)(int)lua_tonumber(state, 3);
    first = (float)lua_tonumber(state, 4);
    second = (float)lua_tonumber(state, 5);
    first *= lbl_806506C0;
    second *= lbl_806506C0;
    result = fn_80129AF4(fn_80201BC8(fn_80201814(object_id)), value, kind, first, second);
    lua_pushusertag(state, result, 0);
    if (result == 0) {
        luaO_verror(state, lbl_80250040, 0);
    }
    return 1;
}
