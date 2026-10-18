typedef struct ShortVector {
    short x;
    short y;
    short z;
} ShortVector;

typedef struct FloatVector {
    float x;
    float y;
    float z;
} FloatVector;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushusertag(void*, void*, int);
extern void luaO_verror(void*, const char*, ...);
extern ShortVector* fn_8016BA38(int);
extern void *fn_80201814();
extern void fn_80201E78(FloatVector*, void*);
extern const char lbl_8024FF00[];

int fn_80172FF0(void* state)
{
    int index;
    int handle;
    ShortVector* vector;
    void* object;
    FloatVector position;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    index = lua_tonumber(state, 1);
    handle = lua_tonumber(state, 2);
    vector = fn_8016BA38(index);
    object = fn_80201814(handle);
    if (object != 0) {
        fn_80201E78(&position, object);
        vector->x = position.x;
        vector->y = position.y;
        vector->z = position.z;
    }
    lua_pushusertag(state, vector, 0);
    return 1;
}
