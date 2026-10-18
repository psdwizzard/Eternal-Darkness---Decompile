typedef int s32;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern const float lbl_8064DD00;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8011F114();
extern s32 fn_801FBC18(Vec3f*, float);

s32 fn_8000AEB4(void* script)
{
    s32 result = 0;
    void* entry;
    void* info;
    Vec3f source;
    Vec3f position;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    entry = fn_80201814((s32)lua_tonumber(script, 1));
    if (entry != 0) {
        info = fn_80201BC8(entry);
    } else {
        info = 0;
    }
    if (info != 0) {
        fn_8011F114(&source, info);
        position = source;
        result = fn_801FBC18(&position, lbl_8064DD00);
    }
    lua_pushnumber(script, result);
    return 1;
}
