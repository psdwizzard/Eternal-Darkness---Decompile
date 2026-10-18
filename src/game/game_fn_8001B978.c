typedef unsigned char u8;
typedef int s32;

typedef struct Color {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Color;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801ECBBC(Color*);
extern char lbl_8023BEF8[];

s32 fn_8001B978(void* arg)
{
    Color values;
    Color color;

    if (lua_gettop(arg) != 4) {
        luaO_verror(arg, lbl_8023BEF8, 4, lua_gettop(arg));
        return 0;
    }

    values.red = (u8)lua_tonumber(arg, 1);
    values.green = (u8)lua_tonumber(arg, 2);
    values.blue = (u8)lua_tonumber(arg, 3);
    values.alpha = (u8)lua_tonumber(arg, 4);
    color = values;
    fn_801ECBBC(&color);
    return 0;
}
