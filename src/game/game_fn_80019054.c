typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern const f32 lbl_8064DCF0;
extern const f32 lbl_8064DE7C;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_800CEA1C(s32, s32, Vec3f*, s32, s32, s32, Color*,
                       f32, f32, f32);

s32 fn_80019054(void* script)
{
    s32 object_id;
    s32 value;
    s32 red;
    s32 green;
    s32 blue;
    s32 alpha;
    f32 scale;
    f32 third;
    Vec3s* packed;
    Vec3f position;
    Color color;

    if (lua_gettop(script) != 8) {
        luaO_verror(script, lbl_8023BEF8, 8, lua_gettop(script));
        return 0;
    }

    object_id = fn_800F5C54(lua_tonumber(script, 1));
    value = (s32)lua_tonumber(script, 2);
    red = (s32)lua_tonumber(script, 3);
    green = (s32)lua_tonumber(script, 4);
    blue = (s32)lua_tonumber(script, 5);
    alpha = (s32)lua_tonumber(script, 6);
    scale = (f32)lua_tonumber(script, 7);
    third = (f32)lua_tonumber(script, 8);

    packed = fn_80158ABC(fn_8015C4A4(object_id, 2), 2, 0);
    if (packed != 0) {
        position.x = packed->x;
        position.y = packed->y;
        position.z = packed->z;
        color.r = red;
        color.g = green;
        color.b = blue;
        color.a = alpha;
        fn_800CEA1C(0x17, 3, &position, 0, 3, value, &color,
                    lbl_8064DE7C, lbl_8064DCF0 / scale, third);
    }
    return 0;
}
