typedef int s32;
typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E4;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80205470(void*, s32, Vec3s*, s32, float);

s32 fn_80013098(void* script)
{
    s32 value;
    Vec3s* position;
    void* parser = script;
    float scale;

    if (lua_gettop(parser) != 3) {
        luaO_verror(parser, lbl_8023BEF8, 3, lua_gettop(parser));
        return 0;
    }

    position = lua_touserdata(parser, 1);
    value = (s32)lua_tonumber(parser, 2);
    scale = (float)lua_tonumber(parser, 3);
    fn_80205470(lbl_8064C4E4, value, position, 0x48, scale);
    return 0;
}
