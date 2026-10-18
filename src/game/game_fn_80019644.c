typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_801CE980(s32, s32, s32, s32, Vec3s*, s32, s32);

s32 fn_80019644(void* script)
{
    Vec3s positions[4];
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 i;
    s32 last;

    if (lua_gettop(script) != 9) {
        luaO_verror(script, lbl_8023BEF8, 9, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);

    for (i = 0; i < 4; i++) {
        positions[i] = *fn_80158ABC(
            fn_8015C4A4(fn_800F5C54(lua_tonumber(script, i + 5)), 2), 2, 0);
    }

    last = (s32)lua_tonumber(script, 9);
    fn_801CE980(first, second, third, fourth, positions, 0, last);
    return 0;
}
