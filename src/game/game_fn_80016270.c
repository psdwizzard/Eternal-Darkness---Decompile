typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BED8[];
extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80152838(Vec3f*, Vec3f*, s32);

s32 fn_80016270(void* script)
{
    const char* errors = lbl_8023BED8;
    s16* start_position;
    s16* offset;
    Vec3f start;
    Vec3f end;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, errors + 0x20, 2, lua_gettop(script));
        return 0;
    }

    start_position = lua_touserdata(script, 1);
    offset = lua_touserdata(script, 2);
    if (start_position == 0) {
        luaO_verror(script, errors + 0xC34, 0);
    }
    if (offset == 0) {
        luaO_verror(script, errors + 0xC74, 0);
    }

    start.x = start_position[0];
    start.y = start_position[1];
    start.z = start_position[2];
    end.x = start.x + offset[0];
    end.y = start.y + offset[1];
    end.z = start.z + offset[2];
    fn_80152838(&start, &end, 4);
    return 0;
}
