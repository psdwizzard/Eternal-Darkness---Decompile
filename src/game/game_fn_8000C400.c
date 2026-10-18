typedef int s32;
typedef signed short s16;

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
extern s32 lbl_8064D18C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_800CF3D4(Vec3f*, s32, s32, s32);
extern int fn_80201B54();
extern void lua_pushnumber(void*, double);

s32 fn_8000C400(void* script)
{
    s32 id;
    s32 result = 0;
    Vec3s* source;
    s32 type;
    s32 final_type;
    Vec3f position;
    void* object;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    id = (s32)lua_tonumber(script, 1);
    source = lua_touserdata(script, 2);
    type = (s32)lua_tonumber(script, 3);
    if (source != 0) {
        final_type = type;
        if (type == -1) {
            final_type = lbl_8064D18C;
        }
        position.x = source->x;
        position.y = source->y;
        position.z = source->z;
        object = fn_800CF3D4(&position, -1, id, final_type);
        if (object != 0) {
            result = fn_80201B54(object);
        }
    }
    lua_pushnumber(script, result);
    return 1;
}
