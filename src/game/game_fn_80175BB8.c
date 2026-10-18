typedef signed short s16;
typedef unsigned char u8;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnil(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201C24();
extern s16 fn_801578E8(void*);
extern s16 fn_801578F4(void*);
extern unsigned int fn_80157BC4(void*);
extern unsigned int fn_80157BDC(void*);
extern unsigned int fn_80157BD0(void*);
extern unsigned int fn_80157900(void*);
extern u8 fn_80157AB8(void*);
extern u8 fn_80157918(void*);
extern const char lbl_8024FF00[];

int fn_80175BB8(void* state)
{
    struct { const char* strings; } diagnostic;
    int kind;
    int object_id;
    void* object;

    diagnostic.strings = lbl_8024FF00;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, diagnostic.strings, 2, lua_gettop(state));
        return 0;
    }
    object_id = lua_tonumber(state, 1);
    kind = lua_tonumber(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        lua_tonumber(state, 3);
        switch (kind) {
        case 0: lua_pushnumber(state, fn_801578E8(object)); break;
        case 1: lua_pushnumber(state, fn_801578F4(object)); break;
        case 2: lua_pushnumber(state, fn_80157BC4(object)); break;
        case 3: lua_pushnumber(state, fn_80157BDC(object)); break;
        case 4: lua_pushnumber(state, fn_80157BD0(object)); break;
        case 5: lua_pushnumber(state, fn_80157900(object)); break;
        case 6: lua_pushnumber(state, fn_80157AB8(object)); break;
        case 7: lua_pushnumber(state, fn_80157918(object)); break;
        default:
            lua_pushnil(state);
            luaO_verror(state, diagnostic.strings + 0x5A8, kind);
            break;
        }
    } else {
        lua_pushnil(state);
        luaO_verror(state, diagnostic.strings + 0x5CC, object_id);
    }
    return 1;
}
