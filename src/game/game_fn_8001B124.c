typedef short s16;
typedef unsigned short u16;
typedef int s32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C504;
extern double lbl_8064DE60;

extern s32 fn_8011804C(s32);
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201B3C();
extern void* fn_80201C24();
extern int fn_80038464(void*, int, s16*);
extern int fn_80038308(void *, int, short *);
extern int fn_800389E0(void*, int, s32, int);
extern s32 fn_80157994(void*);
extern void fn_80157A28(void*, s32);
extern int fn_801A98F4(int, int);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027730(void*, s32, s32);

s32 fn_8001B124(void* script)
{
    s32 id;
    void* manager;
    void* context;
    s16 first;
    s16 second;

    id = fn_8011804C(0);
    manager = fn_80201B3C();

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    if (fn_80038464(manager, 2, &first) != 0 &&
        fn_80038308(manager, 2, &second) != 0) {
        context = fn_80201C24(fn_80201814(id));
        if (first != second) {
            fn_800389E0(manager, 2, first, 1);
            fn_80157A28(context, (unsigned char)(fn_80157994(context) - 1));
            fn_801A98F4(0x229, 100);
        } else {
            fn_80027730(fn_801E6CA0(lbl_8064C504, 0, 0x38, 0, 1), 0, 0);
        }
    }

    lua_pushnumber(script, (u16)fn_80157994(context));
    return 1;
}
