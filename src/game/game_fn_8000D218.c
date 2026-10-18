typedef int s32;

typedef struct GlobalState {
    char pad[8];
    float value;
} GlobalState;

extern const char lbl_8023BEF8[];
extern GlobalState lbl_80302060;
extern const float lbl_8064DD00;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8011F0E8(void*);

s32 fn_8000D218(void* script)
{
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    object = fn_80201BC8(object);
    lbl_80302060.value += lbl_8064DD00;
    fn_8011F0E8(object);
    return 0;
}
