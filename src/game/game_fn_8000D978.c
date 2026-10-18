typedef int s32;

typedef struct Inner {
    void* unk0;
    s32 value;
} Inner;

typedef struct Outer {
    void* unk0;
    Inner* inner;
} Outer;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000D978(void* script)
{
    s32 object_id;
    s32 value;
    void* object;
    Outer* outer;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    value = (s32)lua_tonumber(script, 2);
    object = fn_80201814(object_id);
    if (object != 0) {
        outer = fn_80201B8C(object);
    } else {
        outer = 0;
    }
    if (object != 0 && outer != 0 && outer->inner != 0) {
        outer->inner->value = value;
    }
    return 0;
}
