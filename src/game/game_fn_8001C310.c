typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Command {
    u32 unknown0;
    void* context;
    s32 unknown8;
    u32 id;
    s32 value;
} Command;

extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern Command lbl_803023E0;
extern void* lbl_8064D1BC;

void fn_8001C310(void* arg)
{
    lbl_803023E0.unknown8 = 0;
    lbl_803023E0.context = lbl_8064D1BC;
    lbl_803023E0.id = fn_800F5C54(lua_tonumber(arg, 1));
    lbl_803023E0.value = (s32)lua_tonumber(arg, 2);
}
