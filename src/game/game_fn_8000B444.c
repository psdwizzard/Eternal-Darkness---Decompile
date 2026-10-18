typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ObjectState {
    u8 pad_00[0x2C];
    u32 flags;
} ObjectState;

typedef struct ObjectInfo {
    u8 pad_00[0x68];
    ObjectState* state;
    u8 pad_6C[0x33];
    u8 type;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000B444(void* script)
{
    void* object;
    ObjectInfo* info;
    s32 enabled;
    s32 object_id;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    enabled = (s32)lua_tonumber(script, 2);
    object = fn_80201814(object_id);
    info = object != 0 ? fn_80201B8C(object) : 0;

    if (object != 0 && info != 0 && info->type == 10 && info->state != 0) {
        if (enabled != 0) {
            info->state->flags |= 0x100;
        } else {
            info->state->flags &= 0xFFFFFEFF;
        }
    }
    return 0;
}
