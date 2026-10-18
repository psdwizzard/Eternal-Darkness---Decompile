typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern int fn_800389E0(void*, int, s32, int);

s32 fn_8000D7C8(void* script)
{
    s32 index;
    s32 value;
    s32 object_id;
    void* object;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    index = (s32)lua_tonumber(script, 2);
    value = (s32)lua_tonumber(script, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_800389E0(object, index, value, 0);
        return 1;
    }
    return 0;
}
