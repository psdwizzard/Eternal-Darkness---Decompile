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
extern const char lbl_8023C0F0[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_8011F114();
extern s32 fn_80178E94(Vec3f*, Vec3f*);
extern void lua_pushnumber(void*, double);

s32 fn_8000BC40(void* script)
{
    s32 result = -1;
    s32 object_id;
    s32 effect_id;
    void* handle;
    void* object;
    Vec3s* offset;
    Vec3f delta;
    Vec3f base;
    Vec3f position;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    effect_id = fn_800F5C54(lua_tonumber(script, 2));
    handle = fn_80201814(object_id);
    object = handle != 0 ? fn_80201BC8(handle) : 0;
    if (handle != 0 && object != 0) {
        offset = fn_80158ABC(fn_8015C4A4(effect_id, 2), 2, 0);
        if (offset != 0) {
            fn_8011F114(&position, object);
            base = position;
            delta.x = offset->x;
            delta.y = offset->y;
            delta.z = offset->z;
            result = fn_80178E94(&base, &delta);
        } else {
            luaO_verror(script, lbl_8023C0F0, effect_id);
        }
    }
    lua_pushnumber(script, result);
    return 1;
}
