extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801F70C4(void*, float);
extern const char lbl_8024FF00[];
extern unsigned char lbl_8063CD18[];

typedef struct TargetOwner {
    unsigned char padding[0x110];
    unsigned char target;
} TargetOwner;

int fn_8017026C(void* state)
{
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_801F70C4(target, (float)lua_tonumber(state, 1));
    return 0;
}
