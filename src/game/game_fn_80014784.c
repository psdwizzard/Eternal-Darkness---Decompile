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
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D551C(Vec3f*, Vec3f*, s32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32, s32);
extern void *fn_80156938();
extern void fn_8017FF14(s32, s32);
extern u32 fn_80193860(s32);
extern void fn_801938D8(s32, u32);

s32 fn_80014784(void* script)
{
    s16* first;
    s16* second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    s32 ninth;
    Vec3f first_position;
    Vec3f second_position;
    s32 object;

    if (lua_gettop(script) != 9) {
        luaO_verror(script, lbl_8023BEF8, 9, lua_gettop(script));
        return 0;
    }

    first = lua_touserdata(script, 1);
    second = lua_touserdata(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);
    ninth = (s32)lua_tonumber(script, 9);
    first_position.x = first[0];
    first_position.y = first[1];
    first_position.z = first[2];
    second_position.x = second[0];
    second_position.y = second[1];
    second_position.z = second[2];
    fn_801D551C(&first_position, &second_position, third, fourth, fifth, sixth,
                seventh, eighth, 1, 0, 0x11, 10, 4);
    object = (s32)fn_80156938();
    fn_8017FF14(object, ninth);
    fn_801938D8(object, (fn_80193860(object) & ~8) | 0x400);
    return 0;
}
