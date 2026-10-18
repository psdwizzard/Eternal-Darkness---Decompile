typedef int s32;
typedef unsigned char u8;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern u8* fn_80036D38(void*);

s32 fn_80009248(void* script)
{
    s32 value;
    s32 object_id;
    void* object;
    u8* state;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);
    object = fn_80201814(object_id);
    state = object != 0 ? fn_80036D38(object) : 0;
    if (object != 0 && state != 0) {
        state[0x166] = value;
    }
    return 0;
}
