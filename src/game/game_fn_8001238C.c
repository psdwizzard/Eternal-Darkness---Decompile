typedef int s32;

typedef struct GameState {
    void* value;
    unsigned char pad_04[4];
    s32 mode;
} GameState;

extern const char lbl_8023BEF8[];
extern s32 lbl_8023D5B8[];
extern GameState lbl_803003C8;
extern s32 lbl_8064D18C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80045A24(s32, s32);
extern void fn_80025A78(int);

s32 fn_8001238C(void* script)
{
    s32 value;
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    value = (s32)lua_tonumber(parser, 1);
    lbl_8064D18C = lbl_8023D5B8[value];
    lbl_803003C8.mode = value;
    fn_80045A24(0, 0);
    fn_80025A78(9);
    return 0;
}
