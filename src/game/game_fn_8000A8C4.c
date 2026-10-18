typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201B94();
extern s32 fn_80201CD4(void);
extern void fn_80201E60(void*, s32);

s32 fn_8000A8C4(void* script)
{
    s32 first;
    s32 second;
    void* object;
    s32 flags;
    s32 mode;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    object = fn_80201814(first);
    if (object != 0) {
        object = fn_80201B94(object);
    } else {
        object = 0;
    }
    if (object != 0) {
        flags = fn_80201CD4();
        mode = flags & ~4;
        if (second != 0) {
            mode = flags | 4;
        }
        fn_80201E60(object, mode);
    }
    return 0;
}
