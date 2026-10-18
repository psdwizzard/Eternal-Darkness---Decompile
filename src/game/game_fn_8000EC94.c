typedef int s32;
typedef short s16;

typedef struct SubObject {
    char pad0[0x6];
    s16 value;
} SubObject;

typedef struct ObjectInfo {
    char pad0[0x48];
    SubObject* sub;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000EC94(void* script)
{
    s32 index;
    s32 value;
    void* object;
    ObjectInfo* info;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    index = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);
    object = fn_80201814(index);
    if (object != 0) {
        info = fn_80201B8C(object);
        info->sub->value = value;
    }
    return 0;
}
