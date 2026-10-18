extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void* fn_80204A8C(void);
extern void fn_80204CE4(void*, void*);
extern int fn_80201C2C(void*);
extern int fn_80204C2C(void*);
extern void* fn_80155DB4(void*);
extern void fn_801568B8(void*, int);
extern const char lbl_8024FF00[];

int fn_8016CEF0(void* state)
{
    void* result;
    void* source;
    void* target;
    void* handle;
    int third;
    int second;
    int first;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);

    if (first == -2) {
        target = fn_80201814(second);
        if (target != 0) {
            result = fn_80204A8C();
            fn_80204CE4(target, result);
        }
    } else {
        source = fn_80201814(first);
        if (source != 0) {
            target = fn_80201814(second);
            if (target != 0) {
                int value = fn_80201C2C(source);
                if (value == 0) {
                    value = fn_80204C2C(source);
                }
                fn_80204CE4(target, (void*)value);
                if (third == 0) {
                    handle = fn_80155DB4(target);
                    if (handle != 0) {
                        fn_801568B8(handle, 0);
                    }
                }
            }
        }
    }
    return 0;
}
