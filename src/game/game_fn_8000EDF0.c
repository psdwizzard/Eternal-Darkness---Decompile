typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_80158598(int, int);
extern void fn_80158668(void*);
extern int fn_801E8328();
extern void *fn_80201814();
extern int fn_80201B44();

s32 fn_8000EDF0(void* script)
{
    void* object = fn_80201814(fn_80201B44());

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    if (object != 0) {
        void* value = fn_80158598(fn_80201B44(), 0);
        if (value != 0) {
            fn_80158668(value);
            fn_801E8328(2, object);
        }
    }
    return 0;
}
