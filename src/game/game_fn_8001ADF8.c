typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];
extern double lbl_8064DE60;

extern s32 fn_8011804C(s32);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201C24();
extern s32 fn_80157994(void*);
extern void fn_80157A28(void*, s32);
extern void* fn_801D0050(s32, u32*);
extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern void *fn_8006D444(void);
extern s32 fn_8006BCB4(void);
extern s32 fn_800462C8(s32);
extern void fn_801D1790(void*, void*);

s32 fn_8001ADF8(void* script)
{
    s32 id;
    void* context;
    s32 value;
    u32 mask;

    id = fn_8011804C(0);
    mask = 0x40011041;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    context = fn_80201C24(fn_80201814(id));
    value = fn_80157994(context);

    switch ((s32)lua_tonumber(script, 1)) {
    case 0:
        lua_pushnumber(script, (u16)value);
        return 1;
    case 1:
    case 2:
        if ((u16)value != 0) {
            void* result = fn_801D0050(0, &mask);
            if (result != 0) {
                fn_80204844(fn_80201B9C(), 0x20);
                fn_8006D444();
                if (fn_8006BCB4() != 0x24 && fn_800462C8(1) == 0) {
                    fn_80157A28(context, value - 1);
                    fn_801D1790(result, context);
                }
            }
        }
        return 0;
    }

    return 0;
}
