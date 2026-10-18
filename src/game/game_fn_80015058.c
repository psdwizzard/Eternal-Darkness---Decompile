typedef int s32;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern unsigned int fn_800F5C54(double);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D5BC8(Vec3f*, u32, s32, s32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32, s32, s32);

s32 fn_80015058(void* script)
{
    s16* position;
    u32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    s32 ninth;
    s32 tenth;
    s32 eleventh;
    s32 twelfth;
    s32 thirteenth;
    s32 fourteenth;
    s32 fifteenth;
    Vec3f vector;

    if (lua_gettop(script) != 15) {
        luaO_verror(script, lbl_8023BEF8, 15, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    second = fn_800F5C54(lua_tonumber(script, 2));
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);
    ninth = (s32)lua_tonumber(script, 9);
    tenth = (s32)lua_tonumber(script, 10);
    eleventh = (s32)lua_tonumber(script, 11);
    twelfth = (s32)lua_tonumber(script, 12);
    thirteenth = (s32)lua_tonumber(script, 13);
    fourteenth = (s32)lua_tonumber(script, 14);
    fifteenth = (s32)lua_tonumber(script, 15);

    vector.x = position[0];
    vector.y = position[1];
    vector.z = position[2];
    fn_801D5BC8(&vector, second, third, fourth, fifth, sixth, seventh, eighth,
                ninth, tenth, eleventh, twelfth, thirteenth, fourteenth,
                fifteenth);
    return 0;
}
