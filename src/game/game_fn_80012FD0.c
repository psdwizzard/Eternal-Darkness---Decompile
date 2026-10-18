typedef int s32;

typedef struct ObjectInfo {
    char pad0[0x94];
    s32 value;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void lua_pushnumber(void*, double);

s32 fn_80012FD0(void* script)
{
    register s32 value = 0;
    register void* parser = script;
    void* object;
    ObjectInfo* info;

    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(parser, 1));
    if (object != 0) {
        info = fn_80201B8C(object);
        if (info != 0) {
            value = info->value;
        }
    }

    lua_pushnumber(parser, (double)value);
    return 1;
}
