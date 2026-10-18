typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

#pragma use_lmw_stmw on

typedef struct Player {
    unsigned char pad0[0xB0];
    u16 count;
    unsigned char padB2[2];
    unsigned char* entries;
} Player;

extern const char lbl_8023BEF8[];

extern unsigned int fn_800F5C54(double);
extern Player* fn_8015C28C(s32);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern u16 fn_80034054(void*, s32);

s32 fn_800098C0(void* script)
{
    Player* player;
    u32 object_id;
    s32 entry_offset;
    s32 i;
    s32 value;

    player = fn_8015C28C(2);
    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    object_id = fn_800F5C54(lua_tonumber(script, 1));
    value = (s32)lua_tonumber(script, 2);
    i = 0;
    entry_offset = 0;
    for (; i < player->count; entry_offset += 0x74, i++) {
        void* entry;
        s32 result;

        entry = player->entries + entry_offset;
        if (object_id != *(u32*)((unsigned char*)entry + 0x2C)) {
            continue;
        }

        result = fn_80034054(entry, value);
        if (result > 0) {
            lua_pushnumber(script, (double)result);
            return 1;
        }
    }

    lua_pushnil(script);
    return 1;
}
