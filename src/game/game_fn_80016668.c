typedef int s32;
typedef signed short s16;
typedef unsigned char u8;

typedef struct GameData {
    u8 pad_000[0x1D4];
    s16 value_1D4;
} GameData;

extern GameData lbl_8030F540;
extern s32 lbl_8064D1BC;
extern const char lbl_8023BEF8[];
extern const char lbl_8023CB70[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80052424(s32, s32, s32, s32);

s32 fn_80016668(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    if (value < 0) {
        luaO_verror(script, lbl_8023CB70, value);
    }
    fn_80052424(value, -1, 0, 0);
    lbl_8030F540.value_1D4 = lbl_8064D1BC;
    return 0;
}
