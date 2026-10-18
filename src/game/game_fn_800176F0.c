typedef signed short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void *fn_80201814();
extern int fn_80201B54();
extern void fn_800CCF60(void*, s32, s32, s32, s32, s32, Vec3*, s32, s32, s32,
                       s32);

s32 fn_800176F0(void* script)
{
    u32 handle;
    s32 second;
    s32 third;
    s16* packed_position;
    Vec3 position;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    handle = fn_800F5C54(lua_tonumber(script, 1));
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    packed_position = lua_touserdata(script, 4);

    position.x = packed_position[0];
    position.y = packed_position[1];
    position.z = packed_position[2];

    fn_800CCF60(fn_80201814(handle), second, third, 0, -1, -1, &position, 0, 10,
                20, 0);
    lua_pushnumber(script, (double)fn_80201B54());
    return 1;
}
