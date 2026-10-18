typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern void lua_pushnumber(void*, double);

s32 fn_8000D0BC(void* script)
{
    s32 result = -1;
    void* object;
    void* transform;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0 && (transform = fn_80201BC8(object)) != 0) {
        result = fn_8011EB04(transform);
    }
    lua_pushnumber(script, result);
    return 1;
}
