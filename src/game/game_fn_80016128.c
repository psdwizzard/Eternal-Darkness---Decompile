typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern const char lbl_8023CB0C[];
extern float lbl_8064DE5C;
extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80152838(Vec3f*, Vec3f*, s32);

s32 fn_80016128(void* script)
{
    s16* position;
    Vec3f start;
    Vec3f end;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    if (position == 0) {
        luaO_verror(script, lbl_8023CB0C, 0);
    }

    start.x = position[0];
    start.y = position[1];
    start.z = position[2];
    end.x = position[0];
    end.y = position[1];
    end.z = lbl_8064DE5C + position[2];
    fn_80152838(&start, &end, 4);
    return 0;
}
