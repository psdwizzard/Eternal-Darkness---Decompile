typedef unsigned char u8;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80130214(void*, u8);
extern void fn_80130258(void*, unsigned int, unsigned int);
extern u8 fn_801303BC(void*);
extern void fn_80130434(void*, int);
extern const char lbl_8024FF00[];

int fn_8016F2AC(void* state)
{
    int mode;
    void* object;
    int index;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    object = fn_80201BC8(fn_80201814((int)lua_tonumber(state, 1)));
    mode = (int)lua_tonumber(state, 2);
    index = (int)lua_tonumber(state, 3);
    if (mode != 0) {
        if (index < 0) {
            fn_80130214(object, 0);
        } else {
            fn_80130258(object, 1 << index, 0);
        }
    } else {
        if (index < 0) {
            fn_80130434(object, 1);
            fn_80130214(object, 0xFF);
        } else {
            fn_80130258(object, 0, 1 << index);
            if (index == fn_801303BC(object)) {
                fn_80130434(object, 1);
            }
        }
    }
    return 0;
}
