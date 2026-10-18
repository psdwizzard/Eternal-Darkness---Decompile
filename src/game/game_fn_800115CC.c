typedef int s32;
typedef unsigned char u8;

typedef struct ObjectData {
    u8 pad_00[0x42];
    u8 value_42;
    u8 value_43;
    u8 value_44;
} ObjectData;

typedef struct ObjectInfo {
    u8 pad_00[0x0C];
    ObjectData* data;
    u8 pad_10[0x8F];
    u8 type;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_800115CC(void* script)
{
    register s32 value;
    s32 object_id;
    s32 option;
    void* entry;
    ObjectInfo* object;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    option = (s32)lua_tonumber(script, 2);
    value = (s32)lua_tonumber(script, 3);
    entry = fn_80201814(object_id);
    if (entry != 0) {
        object = fn_80201B8C(entry);
        if (object->type == 7) {
            switch (option) {
            case 3:
                object->data->value_42 = value;
                break;
            case 4:
                object->data->value_43 = value;
                break;
            case 6:
                object->data->value_44 = value;
                break;
            }
        }
    }
    return 0;
}
