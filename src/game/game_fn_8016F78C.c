typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8015C4A4(int, int);
extern int fn_80158B20(int, int, Vec3*, Vec3*, float*);
extern float fn_8012B7D0(void*, Vec3*);
extern void* fn_8011FE34(void*);
extern void fn_8017A244(const char*, void*, float);
extern const char lbl_8024FF00[];

int fn_8016F78C(void* state)
{
    const char* string_pool = lbl_8024FF00;
    int object_id;
    unsigned int resource_id;
    void* object;
    void* runtime;
    int resource_index;
    Vec3 angles;
    Vec3 position;
    float scale;
    Vec3 position_copy;
    float facing;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, string_pool, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        resource_id = fn_800F5C54(lua_tonumber(state, 2));
        resource_index = fn_8015C4A4(resource_id, 2);
        if (resource_index != -1 &&
            fn_80158B20(resource_index, 2, &position, &angles, &scale)) {
            position_copy = position;
            facing = fn_8012B7D0(runtime, &position_copy);
            fn_8017A244(string_pool + 0x190, fn_8011FE34(runtime), facing);
        } else {
            luaO_verror(state, string_pool + 0x19C, resource_id);
        }
    } else {
        luaO_verror(state, string_pool + 0x1B8, object_id);
    }
    return 0;
}
