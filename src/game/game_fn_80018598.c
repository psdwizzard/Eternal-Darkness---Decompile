typedef int s32;
typedef unsigned short u16;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_8014B888(s32, void**, s32*);
extern void fn_801978F8(void*, u16);

s32 fn_80018598(void* script)
{
    s32 object_id;
    s32 value;
    void* object;
    s32 unused;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);
    fn_8014B888(object_id, &object, &unused);
    if (object != 0) {
        fn_801978F8(object, (u16)value);
    }
    return 0;
}
