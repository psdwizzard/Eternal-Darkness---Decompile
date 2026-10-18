typedef int s32;
typedef unsigned char u8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern const char lbl_8023BEF8[];
extern const char lbl_8023C154[];
extern void* lbl_8064D5A8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_80032B18(void*, s32, s32, Color);
extern void fn_80032B84(void*, s32, s32, float);

s32 fn_8000C220(void* script)
{
    void* handle;
    s32 object_id;
    s32 mode;
    s32 value;
    Color color;

    object_id = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);
    mode = (s32)lua_tonumber(script, 3);
    handle = fn_80201814(object_id);
    if (handle != 0) {
        switch (mode) {
        case 0:
            if (lua_gettop(script) != 7) {
                luaO_verror(script, lbl_8023BEF8, 7, lua_gettop(script));
                return 0;
            }
            color.r = (s32)lua_tonumber(script, 4);
            color.g = (s32)lua_tonumber(script, 5);
            color.b = (s32)lua_tonumber(script, 6);
            color.a = (s32)lua_tonumber(script, 7);
            fn_80032B18(handle, value, mode, color);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if (lua_gettop(script) != 4) {
                luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
                return 0;
            }
            fn_80032B84(handle, value, mode, (float)lua_tonumber(script, 4));
            break;
        }
    } else {
        luaO_verror(script, lbl_8023C154, object_id, lbl_8064D5A8);
    }
    return 0;
}
