typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern void* fn_80201B3C();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_80049220(void*, s32);
extern void* fn_80049304(void*, void*);
extern int fn_80201B54();
extern void lua_pushnumber(void*, double);

s32 fn_800131E8(void* script)
{
    register s32 value = -1;
    register void* context;
    register void* parser = script;
    void* temporary;
    void* object;

    context = fn_80201B3C();
    if (lua_gettop(parser) != 0) {
        luaO_verror(parser, lbl_8023BEF8, 0, lua_gettop(parser));
        return 0;
    }

    temporary = fn_80049220(context, 1);
    object = fn_80049304(context, temporary);
    if (object != 0) {
        value = fn_80201B54(object);
    }
    lua_pushnumber(parser, (double)value);
    return 1;
}
