typedef short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_801F49EC(Vec3f*, float, float);

s32 fn_8000AFB4(void* script)
{
    u32 object_id;
    float first;
    float second;
    Vec3f converted;
    Vec3f position;
    Vec3s* source;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }
    object_id = fn_800F5C54(lua_tonumber(script, 1));
    first = (s32)lua_tonumber(script, 2);
    second = lua_tonumber(script, 3);
    source = fn_80158ABC(fn_8015C4A4(object_id, 2), 2, 0);
    converted.x = source->x;
    converted.y = source->y;
    converted.z = source->z;
    position = converted;
    fn_801F49EC(&position, first, second);
    return 1;
}
