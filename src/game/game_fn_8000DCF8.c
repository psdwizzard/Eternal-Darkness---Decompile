typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern unsigned int fn_80036D5C(void*);
extern void fn_80036DA4(void*, u32);

s32 fn_8000DCF8(void* script)
{
    void* object;
    s32 object_id;
    s32 flags;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    lua_tonumber(script, 2);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_80201B8C();
        flags = fn_80036D5C(object);
        fn_80036DA4(object, flags | 0x200);
    }
    return 0;
}
