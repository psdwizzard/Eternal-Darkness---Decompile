typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158CC8(int, int, Vec3s*);
extern void fn_80179904(void*, short);
extern void fn_80153F00(u8, u8, u8, u8, Color*, int, Vec3f*, void*, u8, u8,
                       int);
extern const char lbl_8024FF00[];
extern const char lbl_8025009C[];

int fn_80173770(void* state)
{
    int resource;
    int arg2;
    int arg8;
    int arg11;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg9;
    int arg10;
    int index;
    Vec3s lookup;
    Vec3s* source;
    int arg12;
    Color color;
    Vec3f position;

    if (lua_gettop(state) != 12) {
        luaO_verror(state, lbl_8024FF00, 12, lua_gettop(state));
        return 0;
    }

    resource = fn_800F5C54(lua_tonumber(state, 1));
    arg2 = lua_tonumber(state, 2);
    arg3 = lua_tonumber(state, 3);
    arg4 = lua_tonumber(state, 4);
    arg5 = lua_tonumber(state, 5);
    arg6 = lua_tonumber(state, 6);
    arg7 = lua_tonumber(state, 7);
    arg8 = lua_tonumber(state, 8);
    arg9 = lua_tonumber(state, 9);
    arg10 = lua_tonumber(state, 10);
    arg11 = lua_tonumber(state, 11);
    arg12 = lua_tonumber(state, 12);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        luaO_verror(state, lbl_8025009C, resource);
    }

    color.r = arg2;
    color.g = arg3;
    color.b = arg4;
    color.a = arg5;
    arg10 += (u16)arg12;
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    fn_80179904(&lookup, arg11);
    fn_80153F00((u8)arg8, (u8)arg7, (u8)arg9, (u8)arg6, &color, arg10,
                &position, &lookup, 1, 1, arg12);
    return 0;
}
