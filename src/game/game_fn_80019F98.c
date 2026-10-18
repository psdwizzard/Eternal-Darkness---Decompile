typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    s32 v2;
    s32 v1;
    s32 v0;
    s32 pad;
} Values;

extern const char lbl_8023BED8[];
extern double lbl_8064DCE8;
extern const f32 lbl_8064DCF0;
extern const f32 lbl_8064DCF4;
extern s32 lbl_8064D18C;
extern const f32 lbl_8064DE8C;
extern const f32 lbl_8064DE90;
extern const f32 lbl_8064DE94;
extern s32 lbl_806518D8;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern s32 fn_80128258(void);
extern s32 fn_80128130(void);
extern s32 fn_800453AC(s32, s32, s32, s32, s32, s32, s32, s32,
                      Vec3f*, s32, s32, f32);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_801D3974(s32);
extern void* fn_8012C62C(void*, s32, void*, void*, void*, s32);
extern unsigned int fn_8011FA8C(void*, int, int);
extern void fn_8012CBE8(s32, s32, Vec3f*, Vec3f*, Vec3f*, s32);
extern void fn_8012F58C(s32, s32, s32, s32, s32, s32);
extern void luaO_verror(void*, const char*, ...);

s32 fn_80019F98(void* script)
{
    const char* strings = lbl_8023BED8;
    f32 value;
    f32 scale = lbl_8064DCF4;
    f32 duration = lbl_8064DE8C;
    Vec3f default_position;
    Vec3f position;
    Vec3f preset1;
    Vec3f preset0;
    Vec3f position_copy;
    Values values;
    s32 handle;
    s32 kind;
    s32 effect;
    s32 object;
    void* state;

    state = script;

    switch (lua_gettop(state)) {
    case 5:
        duration = (f32)lua_tonumber(state, 5);
    case 4:
        scale = lbl_8064DE90 * (f32)lua_tonumber(state, 4);
    case 3:
        value = (f32)lua_tonumber(state, 3);
        kind = (s32)lua_tonumber(state, 2);
        handle = fn_800F5C54(lua_tonumber(state, 1));
        break;
    }

    object = fn_8015C4A4(handle, 2);
    default_position.z = duration;
    default_position.y = duration;
    default_position.x = duration;
    if (object != -1) {
        Vec3s* source = fn_80158ABC(object, 2, 0);
        position.x = source->x;
        position.y = source->y;
        position.z = source->z;

        if (fn_80128258() != 0 || fn_80128130() != 0) {
            effect = fn_800453AC(91, 104, lbl_8064D18C, -1, -1, -1, -1,
                                 62, &position, 1, 0, scale);
            fn_8020104C(57, effect, effect, 0, value);
            fn_8020104C(156, effect, effect, 6, lbl_8064DCF0);
            fn_80201814(effect);
            state = fn_80201BC8();
            kind = fn_801D3974(kind);

            values.pad = kind;
            values.v2 = kind;
            values.v0 = kind;
            values.v1 = lbl_806518D8;
            fn_8012C62C(state, 15, &values.v0, &values.v1,
                         &values.v2, 2);
            fn_8011FA8C(state, 0, 0x1000000);

            position_copy = default_position;
            preset0 = *(Vec3f*)(strings + 0xD24);
            preset1 = *(Vec3f*)(strings + 0xD30);
            fn_8012CBE8((s32)state, 15, &preset1, &preset0, &position_copy, 1);
            fn_8012F58C((s32)state, 15, 1, 0,
                         (s32)(value - lbl_8064DE94), 0x100);
        }
    } else {
        luaO_verror(state, strings + 0xD3C, handle);
    }
    return 0;
}
