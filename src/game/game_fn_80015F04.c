typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern const char lbl_8023CB2C[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801D3974(s32);
extern void fn_80153DF0(Vec3f*, s32, s32, s32, s32*, s32, s32, s32, s32,
                       s32, s32, s32);

s32 fn_80015F04(void* script)
{
    s16* position;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    s32 ninth;
    s32 tenth;
    s32 eleventh;
    Vec3f vector;
    s32 transformed;

    if (lua_gettop(script) != 11) {
        luaO_verror(script, lbl_8023BEF8, 11, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);
    ninth = (s32)lua_tonumber(script, 9);
    tenth = (s32)lua_tonumber(script, 10);
    eleventh = (s32)lua_tonumber(script, 11);

    if (position == 0) {
        luaO_verror(script, lbl_8023CB2C, 0);
    }

    vector.x = position[0];
    vector.y = position[1];
    vector.z = position[2];
    transformed = fn_801D3974(fifth);
    fn_80153DF0(&vector, second, third, fourth, &transformed, sixth, seventh,
                eighth, ninth, tenth, eleventh, 4);
    return 0;
}
