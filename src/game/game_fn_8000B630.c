typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern s32 fn_80128EAC(void*);
extern void lua_pushnumber(void*, double);

s32 fn_8000B630(void* script)
{
    s32 result = 0;
    void* object;
    void* info;
    s32 type;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    info = object != 0 ? fn_80201BC8(object) : 0;
    if (object != 0 && info != 0) {
        type = fn_80128EAC(info);
        switch (type) {
        case 46:
        case 47:
        case 157:
            result = 1;
            break;
        }
    }
    lua_pushnumber(script, result);
    return 1;
}
