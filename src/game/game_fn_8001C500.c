typedef unsigned int u32;

typedef struct Command {
    u32 words[8];
} Command;

extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern Command lbl_803023E0;

void fn_8001C500(void* arg)
{
    lbl_803023E0.words[5] = fn_800F5C54(lua_tonumber(arg, 3));
    lbl_803023E0.words[6] = fn_800F5C54(lua_tonumber(arg, 4));
}
