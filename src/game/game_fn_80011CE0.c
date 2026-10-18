typedef int s32;
typedef unsigned char u8;

typedef struct Type13Entry {
    s32 first;
    s32 clear_04;
    s32 second;
    s32 third;
    s32 clear_10;
    s32 unknown_14;
} Type13Entry;

typedef struct Type13Data {
    u8 pad_00[4];
    Type13Entry entries[1];
} Type13Data;

typedef struct ObjectInfo {
    u8 pad_00[0x64];
    Type13Data* data_64;
    u8 pad_68[0x37];
    u8 type;
} ObjectInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_80011CE0(void* script)
{
    s32 handle;
    s32 index;
    s32 first;
    s32 second;
    s32 third;
    void* parser;
    void* entry;
    ObjectInfo* object;
    Type13Entry* target;

    parser = script;
    if (lua_gettop(parser) != 5) {
        luaO_verror(parser, lbl_8023BEF8, 5, lua_gettop(parser));
        return 0;
    }

    handle = (s32)lua_tonumber(parser, 1);
    index = (s32)lua_tonumber(parser, 2);
    first = (s32)lua_tonumber(parser, 3);
    second = (s32)lua_tonumber(parser, 4);
    third = (s32)lua_tonumber(parser, 5);
    entry = fn_80201814(handle);
    if (entry != 0) {
        object = fn_80201B8C(entry);
        if (object->type == 13) {
            target = &object->data_64->entries[index];
            target->first = first;
            target->second = second;
            target->third = third;
            target->clear_04 = 0;
            target->clear_10 = 0;
        }
    }
    return 0;
}
