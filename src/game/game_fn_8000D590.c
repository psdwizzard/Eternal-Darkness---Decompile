typedef int s32;
typedef signed short s16;

typedef struct ObjectData {
    char pad_000[0xEA];
    s16 values_0EA[15];
    s16 values_108[15];
    s16 values_126[15];
} ObjectData;

typedef struct ObjectInstance {
    char pad_00[0x8C];
    ObjectData* data;
    void* component;
} ObjectInstance;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern int fn_80201B44();
extern void* fn_80072354(void*);
extern int fn_80038308(void *, int, short *);
extern int fn_80038464(void*, int, s16*);

s32 fn_8000D590(void* script)
{
    s32 category;
    void* object;
    s32 mode;
    s32 object_id;
    s32 slot;
    ObjectInstance* instance;
    void* component;
    s16 result = 0;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    mode = (s32)lua_tonumber(script, 2);
    slot = (s32)lua_tonumber(script, 3);
    category = (s32)lua_tonumber(script, 4);
    object = fn_80201814(object_id);
    instance = object != 0 ? fn_80201B8C(object) : 0;
    component = instance != 0 ? fn_80072354(instance->component) : 0;

    if (object != 0 && instance != 0 && component != 0) {
        switch (mode) {
        case 0:
            if (category == 15) {
                if (slot == 0) {
                    fn_80038308(object, mode, &result);
                } else {
                    fn_80038464(object, mode, &result);
                }
            } else if (object_id != fn_80201B44()) {
                if (slot == 0) {
                    result = instance->data->values_0EA[category];
                } else if (slot == 1) {
                    result = instance->data->values_108[category];
                } else {
                    result = instance->data->values_126[category];
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            if (object_id == fn_80201B44() && category == 15) {
                if (slot == 0) {
                    fn_80038308(object, mode, &result);
                } else {
                    fn_80038464(object, mode, &result);
                }
            }
            break;
        }
    }

    lua_pushnumber(script, (double)result);
    return 1;
}
