typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ShortVec3 {
    short x;
    short y;
    short z;
} ShortVec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern ShortVec3* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_8012976C(void*, int, unsigned short, Vec3*, float);
extern void* fn_80129878(void*, int, unsigned short, Vec3*, float);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;
extern const float lbl_806506C0;

int fn_8016E8F8(void* state, int alternate)
{
    int value;
    unsigned short kind;
    int id;
    ShortVec3* source;
    Vec3 position;
    float scale;
    void* object;
    void* result;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    kind = (unsigned short)(int)lua_tonumber(state, 3);
    source = lua_touserdata(state, 4);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    scale = (float)lua_tonumber(state, 5);
    scale *= lbl_806506C0;

    if (id == 162) {
        asm { nop }
    }
    object = fn_80201814(id);
    object = object != 0 ? fn_80201BC8(object) : 0;

    if (alternate != 0) {
        result = object != 0 ? fn_80129878(object, value, kind, &position, scale) : 0;
    } else {
        result = object != 0 ? fn_8012976C(object, value, kind, &position, scale) : 0;
    }
    lua_pushusertag(state, result, 0);
    return 1;
}
