typedef int s32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void PSVECScale(Vec3*, Vec3*, f32);
extern void PSVECAdd(Vec3*, Vec3*, Vec3*);
extern s32 fn_801D3A24(s32, s32);
extern void fn_80152A88(Vec3*, Vec3*, void*, s32);
extern Vec3 lbl_80237F38;
extern char lbl_8023BEF8[];

s32 fn_8001D1BC(void* script)
{
    Vec3 input;
    Vec3 basis;
    s32 value;
    void* object;

    basis = lbl_80237F38;
    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    input.x = (f32)lua_tonumber(script, 2);
    input.y = (f32)lua_tonumber(script, 3);
    input.z = (f32)lua_tonumber(script, 4);
    PSVECScale(&basis, &basis, (f32)lua_tonumber(script, 5));
    PSVECAdd(&basis, &input, &basis);
    object = (void*)fn_801D3A24(value, 0x31);
    fn_80152A88(&input, &basis, object, 4);
    return 1;
}
