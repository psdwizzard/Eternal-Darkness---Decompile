typedef signed short s16;
typedef unsigned char u8;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201C24();
extern void fn_80157B48(void*, s16);
extern void fn_80157B54(void*, s16);
extern void fn_80157B94(void*, u8);
extern void fn_80157BAC(void*, u8);
extern void fn_80157BB8(void*, u8);
extern void fn_80157BA0(void*, s16);
extern void fn_80157B60(void*, u8);
extern void fn_80157B3C(void*, u8);
extern const char lbl_8024FF00[];

int fn_80175A08(void* state)
{
    struct { const char* strings; } diagnostic;
    int kind;
    int object_id;
    void* object;
    int value;
    diagnostic.strings = lbl_8024FF00;
    if (lua_gettop(state) != 3) {
        luaO_verror(state, diagnostic.strings, 3, lua_gettop(state));
        return 0;
    }

    object_id = lua_tonumber(state, 1);
    kind = lua_tonumber(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        value = lua_tonumber(state, 3);
        switch (kind) {
        case 0:
            fn_80157B48(object, value);
            break;
        case 1:
            fn_80157B54(object, value);
            break;
        case 2:
            fn_80157B94(object, value);
            break;
        case 3:
            fn_80157BAC(object, value);
            break;
        case 4:
            fn_80157BB8(object, value);
            break;
        case 5:
            fn_80157BA0(object, value);
            break;
        case 6:
            fn_80157B60(object, value);
            break;
        case 7:
            fn_80157B3C(object, value);
            break;
        default:
            luaO_verror(state, diagnostic.strings + 0x5A8, kind);
            break;
        }
    } else {
        luaO_verror(state, diagnostic.strings + 0x5CC, object_id);
    }
    return 0;
}
