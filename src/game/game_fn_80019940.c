typedef unsigned char u8;
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
    u8 bytes[144];
} EffectDescriptor;

extern const char lbl_8023BED8[];
extern const double lbl_8064DCE8;
extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801839A4(EffectDescriptor*);
extern void fn_801839D8(void);
extern void* fn_80148008(Vec3f*, const Vec3s*, EffectDescriptor*, void (*)(void));
extern void *fn_80156938();
extern void fn_8017FF1C(void*, s32);
extern void fn_8018391C(const Vec3s*, const Vec3s*, EffectDescriptor*);

s32 fn_80019940(void* script)
{
    const char* errors = lbl_8023BED8;
    Vec3s direction;
    Vec3s final_position;
    Vec3f position;
    Vec3f submit_position;
    EffectDescriptor descriptor;
    Vec3s* first;
    Vec3s* second;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, errors + 0x20, 2, lua_gettop(script));
        return 0;
    }

    first = lua_touserdata(script, 1);
    second = lua_touserdata(script, 2);
    if (first == 0) {
        luaO_verror(script, errors + 0xC34, 0);
    }
    if (second == 0) {
        luaO_verror(script, errors + 0xC74, 0);
    }

    position.x = first->x;
    position.y = first->y;
    position.z = first->z;
    direction.x = second->x;
    direction.y = second->y;
    direction.z = second->z;

    fn_801839A4(&descriptor);
    descriptor.bytes[20] = 1;

    submit_position = position;
    {
        void* effect = fn_80148008(&submit_position, &direction, &descriptor,
                                   fn_801839D8);
        if (effect != 0) {
            fn_8017FF1C(fn_80156938(effect), 4);
        }
    }

    final_position.x = first->x;
    final_position.y = first->y;
    final_position.z = first->z;
    fn_8018391C(&final_position, &direction, &descriptor);
    return 0;
}
