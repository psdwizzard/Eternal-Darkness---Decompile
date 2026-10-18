typedef unsigned int u32;
typedef int s32;
typedef float f32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801FA7D0(u32, f32, s32, f32, s32, s32, s32);

s32 fn_8001A378(void* script)
{
    u32 first;
    f32 second;
    s32 third;
    f32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;

    if (lua_gettop(script) != 7) {
        luaO_verror(script, lbl_8023BEF8, 7, lua_gettop(script));
        return 0;
    }

    first = fn_800F5C54(lua_tonumber(script, 1));
    second = (f32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (f32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    fn_801FA7D0(first, second, third, fourth, fifth, sixth, seventh);
    return 0;
}
