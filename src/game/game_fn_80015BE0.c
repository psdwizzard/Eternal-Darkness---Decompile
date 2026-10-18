typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Value {
    s32 word;
} Value;

extern const char lbl_8023BEF8[];
char lbl_8023CB0C[] = " (Error: pStartVert is NULL)";
extern Value lbl_8064DE58;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80152404(Vec3f*, s32, s32, s32, Value*);

s32 fn_80015BE0(void* script)
{
    s16* position;
    s32 second;
    s32 third;
    Vec3f vector;
    Value value = lbl_8064DE58;
    Value copy;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);

    if (position == 0) {
        luaO_verror(script, lbl_8023CB0C, 0);
    }

    vector.x = position[0];
    vector.y = position[1];
    vector.z = position[2];
    copy = value;
    fn_80152404(&vector, second, third, 4, &copy);
    return 0;
}
