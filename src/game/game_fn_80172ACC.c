typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RuntimeEntry {
    unsigned char pad_00[0x2C];
    u32 id;
    unsigned char pad_30[0x38];
    u32 flags;
    unsigned char pad_6C[8];
} RuntimeEntry;

typedef struct RuntimeInfo {
    unsigned char pad_00[0xB0];
    u16 count;
    u16 pad_B2;
    RuntimeEntry* entries;
} RuntimeInfo;

extern RuntimeInfo* fn_8015C28C(int);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern const double lbl_806506D8;

int fn_80172ACC(void* state)
{
    RuntimeInfo* info = fn_8015C28C(2);
    int i;
    u32 id;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    id = fn_800F5C54(lua_tonumber(state, 1));
    for (i = 0; i < info->count; i++) {
        RuntimeEntry* entry = &info->entries[i];
        if (id == entry->id && (entry->flags & 1) != 0) {
            lua_pushnumber(state, lbl_806506D8);
            return 1;
        }
    }

    lua_pushnil(state);
    return 1;
}
