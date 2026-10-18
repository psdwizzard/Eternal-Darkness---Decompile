typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BED8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D38BC(s32, void*, void*);
extern void fn_801502C0(Vec3f*, Vec3f*, s32, s16, s32, s32, s32, s32, s32,
                       s32, s32, void*, s32, s32);

s32 fn_80015320(void* script)
{
    const char* strings;
    s16* first;
    s16* second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    Vec3f first_position;
    Vec3f second_position;
    s16 transformed_short;
    s32 transformed_word;
    s32 transformed_copy;

    strings = lbl_8023BED8;
    if (lua_gettop(script) != 7) {
        luaO_verror(script, strings + 0x20, 7, lua_gettop(script));
        return 0;
    }

    first = lua_touserdata(script, 1);
    second = lua_touserdata(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);

    if (first == 0) {
        luaO_verror(script, strings + 0xBD8, 0);
    }
    if (second == 0) {
        luaO_verror(script, strings + 0xBF8, 0);
    }

    first_position.x = first[0];
    first_position.y = first[1];
    first_position.z = first[2];
    second_position.x = second[0];
    second_position.y = second[1];
    second_position.z = second[2];

    fn_801D38BC(third, &transformed_word, &transformed_short);
    transformed_copy = transformed_word;
    fn_801502C0(&first_position, &second_position, third, transformed_short,
                0x57, 0x57, fourth, fifth, sixth, seventh, 0,
                &transformed_copy, 1, 0);
    return 0;
}
