typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void *fn_80201814();
extern void* fn_80201C24();
extern void fn_80157B80(void*, u32);

s32 fn_80013564(void* script)
{
    s32 object_id;
    u32 value;
    void* parser = script;

    if (lua_gettop(parser) != 2) {
        luaO_verror(parser, lbl_8023BEF8, 2, lua_gettop(parser));
        return 0;
    }

    object_id = (s32)lua_tonumber(parser, 1);
    value = fn_800F5C54(lua_tonumber(parser, 2));
    if (fn_80201814(object_id) != 0) {
        fn_80157B80(fn_80201C24(), value);
    }
    return 0;
}
