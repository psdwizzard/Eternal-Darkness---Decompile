typedef int s32;
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
extern s32 fn_801D3A24(s32, s32);
extern void fn_8014EAC4(Vec3f*, Vec3f*, s32, s32, s32, s32, s32, s32, s32);

s32 fn_800142DC(void* script)
{
    s16* first;
    s16* second;
    s32 third;
    s32 fourth;
    s32 fifth;
    Vec3f first_position;
    Vec3f second_position;
    s32 value_35;
    s32 value_46;
    s32 value_4A;
    s32 value_4E;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    first = lua_touserdata(script, 1);
    second = lua_touserdata(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    first_position.x = first[0];
    first_position.y = first[1];
    first_position.z = first[2];
    second_position.x = second[0];
    second_position.y = second[1];
    second_position.z = second[2];
    value_35 = fn_801D3A24(fifth, 0x35);
    value_46 = fn_801D3A24(fifth, 0x46);
    value_4A = fn_801D3A24(fifth, 0x4A);
    value_4E = fn_801D3A24(fifth, 0x4E);
    fn_8014EAC4(&first_position, &second_position, third, fourth, value_35,
                value_46, value_4A, value_4E, 4);
    return 0;
}
