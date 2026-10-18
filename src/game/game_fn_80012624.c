typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E0;
extern s32 lbl_8064C5D8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80113B50(s32);
extern void fn_80113BA8(s32);
extern void fn_801E7974(void*, int);
extern int fn_801E79FC(void*, int);
extern void fn_80111C48(void);
extern s32 fn_80111780(void);
extern s32 fn_801118E8(void);

s32 fn_80012624(void* script)
{
    s32 value;

    value = (s32)script;
    if (lua_gettop((void*)value) != 1) {
        luaO_verror((void*)value, lbl_8023BEF8, 1, lua_gettop((void*)value));
        return 0;
    }

    value = (s32)lua_tonumber((void*)value, 1);
    if (value != 0) {
        if (value > 0) {
            fn_80113B50((u32)value << 18 >> 18);
            fn_80113BA8(((u32)value >> 16 & 7) << 16);
            if ((value & 0x70000) != 0) {
                fn_801E7974(lbl_8064C4E0, 0x1F3);
            }
            if ((value & 0x3FFF) != 0) {
                fn_801E7974(lbl_8064C4E0, 0x3DD);
            }
        }

        fn_80111C48();
        if (fn_80111780() != 0) {
            lbl_8064C5D8 = 1;
        }
        if (fn_801118E8() != 0
            && fn_801E79FC(lbl_8064C4E0, 0x3DE) == 0
            && fn_801E79FC(lbl_8064C4E0, 0x3DD) != 0) {
            fn_801E7974(lbl_8064C4E0, 0x3DD);
            lbl_8064C5D8 = 1;
        }
    }
    return 0;
}
