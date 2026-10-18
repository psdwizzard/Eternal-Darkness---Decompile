typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern const char lbl_8023BEF8[];
extern double lbl_8064DE60;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern int fn_80201B44();
extern void *fn_80201814();
extern void* fn_80201B3C();
extern void fn_80205288(s32);
extern void* fn_80201C24();
extern s32 fn_8004918C(void);
extern void* fn_801A7778(s32);
extern s32 fn_80158234(void*);
extern s32 fn_80157994(void*);
extern void fn_80157C98(void*, s32, s32);
extern void* fn_80201C2C(void*);
extern void* fn_802051A4(void*);
extern s32 fn_80205134(void*);
extern u32 fn_80157BF4(void*);
extern void fn_80157A28(void*, u8);

s32 fn_800173CC(void* script)
{
    void* target;
    u8 result;
    void* target_data;
    void* entry;
    void* related;
    void* temp;
    s32 kind;
    u16 target_kind;
    u16 temp_kind;
    void* object;

    related = fn_80201814(fn_80201B44());
    fn_80205288((s32)fn_80201B3C());
    result = 0;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    target = fn_80201814((s32)lua_tonumber(script, 1));
    if (target != 0) {
        target_data = fn_80201C24(target);
        temp = fn_801A7778(fn_8004918C());
        if (temp != 0) {
            target_kind = fn_80158234(target_data);
            temp_kind = fn_80158234(temp);
            if (temp_kind == target_kind &&
                (u16)fn_80157994(target_data) != 0 &&
                (u16)fn_80157994(temp) == 0) {
                fn_80157C98(temp, 0x80, 0x20);
            }
        }

        kind = (u16)fn_80158234(target_data);
        related = fn_802051A4(fn_80201C2C(related));
        while (related != 0) {
            entry = fn_80201814(fn_80205134(related));
            if (entry != 0) {
                object = fn_80201C24(entry);
                if (fn_80157BF4(object) == 4) {
                    if (kind == (u16)fn_80158234(object) &&
                        target != entry) {
                        result = 1;
                        fn_80157A28(object,
                                   (u8)(fn_80157994(target_data) + fn_80157994(object)));
                    }
                } else if (fn_80157BF4(object) == 3) {
                    if ((u16)fn_80158234(object) == (u16)fn_80158234(target_data) &&
                        (u16)fn_80157994(target_data) != 0 &&
                        (u16)fn_80157994(object) == 0) {
                        fn_80157C98(object, 0x80, 0x20);
                    }
                }
            }
            related = fn_802051A4(related);
        }
    }

    lua_pushnumber(script, result);
    return 1;
}
