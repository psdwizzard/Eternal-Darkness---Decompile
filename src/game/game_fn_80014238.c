typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void *fn_80201814();
extern void* fn_80204318(void*, s32);
extern int fn_80201B54();
extern void fn_800CC3BC(s32, s32, s32, s32, s32, s32);

s32 fn_80014238(void* script)
{
    s32 object_id;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    object_id = fn_80201B44();
    if (fn_80204318(fn_80201814(fn_80201B44()), 1) != 0) {
        fn_800CC3BC(0, object_id, fn_80201B54(), 0, 0, 0);
    }
    return 0;
}
