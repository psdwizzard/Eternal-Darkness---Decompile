typedef signed char s8;
typedef unsigned char u8;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct ColorStep {
    s8 r, g, b, a;
} ColorStep;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_8012C62C(void*, int, void*, void*, void*, int);
extern const char lbl_8024FF00[];

int fn_801755FC(void* state)
{
    Color first;
    Color second;
    ColorStep directions;
    Color call_first;
    ColorStep call_directions;
    Color call_second;
    s8 delta;
    int index;
    void* runtime;
    void* object;

    if (lua_gettop(state) != 10) {
        luaO_verror(state, lbl_8024FF00, 10, lua_gettop(state));
        return 0;
    }

    runtime = fn_80201814((int)lua_tonumber(state, 1));
    if (runtime != 0) {
        object = fn_80201BC8();
        if (object != 0) {
            index = lua_tonumber(state, 2);
            first.r = lua_tonumber(state, 3);
            first.g = lua_tonumber(state, 4);
            first.b = lua_tonumber(state, 5);
            first.a = lua_tonumber(state, 6);
            second.r = lua_tonumber(state, 7);
            second.g = lua_tonumber(state, 8);
            second.b = lua_tonumber(state, 9);
            second.a = lua_tonumber(state, 10);

            delta = -5;
            if (second.r >= first.r) delta = 5;
            directions.r = delta;
            delta = -5;
            if (second.g >= first.g) delta = 5;
            directions.g = delta;
            delta = -5;
            if (second.b >= first.b) delta = 5;
            directions.b = delta;
            delta = -5;
            if (second.a >= first.a) delta = 5;
            directions.a = delta;

            call_second = second;
            call_directions = directions;
            call_first = first;
            fn_8012C62C(object, index, &call_first, &call_directions,
                         &call_second, 4);
        }
    }
    return 0;
}
