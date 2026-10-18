extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801F7208(void*, float);
extern const char lbl_8024FF00[];
extern unsigned char lbl_8063CD18[];
extern unsigned char lbl_8063D400[];

typedef struct TargetOwner {
    unsigned char padding[0x110];
    unsigned char target;
} TargetOwner;

int fn_80170090(void* state)
{
    float value;
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (float)lua_tonumber(state, 1);
    fn_801F7208(target, value);
    fn_801F7208(lbl_8063D400, value);
    return 0;
}
