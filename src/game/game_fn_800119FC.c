typedef int s32;
typedef unsigned char u8;

typedef struct Type12Data Type12Data;

typedef struct ObjectInfo {
    u8 pad_00[0x54];
    Type12Data* data_54;
    u8 pad_58[0x47];
    u8 type;
} ObjectInfo;

typedef struct Type12Entry {
    s32 first;
    s32 second;
    s32 third;
} Type12Entry;

struct Type12Data {
    Type12Entry primary[8];
    Type12Entry alternate[1];
};

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_800119FC(void* script)
{
    s32 handle;
    s32 index;
    s32 selection;
    void* parser;
    s32 alternate;
    void* entry;
    ObjectInfo* object;
    s32 flags[3] = {0x10000, 0x20000, 0x40000};

    parser = script;
    if (lua_gettop(parser) != 4) {
        luaO_verror(parser, lbl_8023BEF8, 4, lua_gettop(parser));
        return 0;
    }

    handle = (s32)lua_tonumber(parser, 1);
    index = (s32)lua_tonumber(parser, 2);
    selection = (s32)lua_tonumber(parser, 3);
    alternate = (s32)lua_tonumber(parser, 4);
    entry = fn_80201814(handle);
    if (entry != 0) {
        object = fn_80201B8C(entry);
        if (object->type == 12) {
            if (alternate != 0) {
                object->data_54->alternate[index].third = flags[selection];
            } else {
                object->data_54->primary[index].third = flags[selection];
            }
        }
    }
    return 0;
}
