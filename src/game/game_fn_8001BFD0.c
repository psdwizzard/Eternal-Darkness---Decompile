typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;

typedef struct Inner {
    u8 pad[0x146];
    u16 value;
} Inner;

typedef struct Object {
    u8 pad[0x8C];
    Inner* inner;
} Object;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern char lbl_8023BEF8[];

s32 fn_8001BFD0(void* arg)
{
    s32 id;
    s32 value;
    Object* object;

    if (lua_gettop(arg) != 2) {
        luaO_verror(arg, lbl_8023BEF8, 2, lua_gettop(arg));
        return 0;
    }

    id = (s32)lua_tonumber(arg, 1);
    value = (s32)lua_tonumber(arg, 2);
    object = fn_80201B8C(fn_80201814(id));
    object->inner->value = value;
    return 1;
}
