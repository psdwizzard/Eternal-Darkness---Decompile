typedef int s32;

#pragma use_lmw_stmw on

char lbl_8023CB90[] =
    "\nInvalid Num of Args Expecting 1 or 2 or 3, and got %i";
extern void* lbl_8064C4E0;
extern void* lbl_8064C504;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8016B400(int, int, int);
extern void *fn_80201814();
extern void* fn_80201C24();
extern s32 fn_80157BC4(void*);
extern s32 fn_80157BF4(void*);
extern s32 fn_8015821C(void*);
extern int fn_801E79FC(void*, int);
extern void fn_801B05E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern int fn_80201AE4(void);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027948(void*, s32, void*, s32, s32, s32, s32);

s32 fn_80016D68(void* script_arg)
{
    register void* result;
    s32 value2 = 0;
    s32 object_id;
    s32 value3 = 0;
    s32 position1;
    void* script = script_arg;
    void* object;

    if (lua_gettop(script) > 0) {
        object_id = (s32)lua_tonumber(script, 1);

        if (lua_gettop(script) >= 2) {
            value2 = (s32)lua_tonumber(script, 2);
        }

        if (lua_gettop(script) == 3) {
            value3 = (s32)lua_tonumber(script, 3);
        }
    } else {
        luaO_verror(script, lbl_8023CB90, lua_gettop(script));
        return 0;
    }

    if (object_id == -1 && value2 > 0) {
        fn_8016B400(value2, 0, 0);
    }

    object = fn_80201C24(fn_80201814(object_id));
    position1 = fn_80157BC4(object);
    script = (void*)fn_80157BF4(object);

    if (fn_8015821C(object) == 0x1F &&
        fn_801E79FC(lbl_8064C4E0, 0x10A) == 0) {
        fn_801B05E8(0xC, 0x64, 6, 1, 0, 5, 0, 0);
    }

    fn_80201AE4();
    asm {
        mr result, r3
    }
    object = fn_801E6CA0(lbl_8064C504, (s32)script, position1, 0, 1);
    fn_80027948(object, value2, result, object_id, value3, 0, 0);
    return 0;
}
