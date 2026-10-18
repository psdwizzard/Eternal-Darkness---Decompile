typedef signed short s16;
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
extern s32 lbl_8064D18C;

extern unsigned int fn_800F5C54(double);
extern Player* fn_8015C28C(s32);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void *fn_80201B9C();
extern int fn_80035628(void*);
extern int fn_80201B54();
extern void *fn_80201BC8();
extern void fn_800385D0(void*, s32, s16*);
extern s32 fn_80036E50(void*);
extern s32 fn_8011FB4C(void*);
extern s32 fn_8013B8C0(void*, void*);
extern unsigned long long fn_8020123C();
extern void* fn_80201BC0(void*);

s32 fn_800096E0(void* script)
{
    Player* player;
    u32 object_id;
    s32 entry_offset;
    s32 i;
    s32 count;

    player = fn_8015C28C(2);
    count = 0;
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object_id = fn_800F5C54(lua_tonumber(script, 1));
    i = 0;
    entry_offset = 0;
    for (; i < player->count; entry_offset += 0x74, i++) {
        s32 kind;
        register s32 eligible;
        void* iterator;

        if (*(u32*)(player->entries + entry_offset + 0x2C) != object_id) {
            continue;
        }

        iterator = fn_80201B9C();
        while (iterator != 0) {
            void* context;
            void* object;
            s16 state;
            register s32 state_value;
            register s32 kind_allowed;

            kind = fn_80035628(iterator);
            state = -1;
            object = (void*)fn_80201B54(iterator);
            context = fn_80201BC8(iterator);
            fn_800385D0(object, 0, &state);

            asm {
                lha state_value, 8(r1)
                li eligible, 0
                mr kind_allowed, r24
            }
            if (state_value == 0 && (kind == 2 || kind == 4)) {
                kind_allowed = 1;
            }
            if (kind_allowed != 0 && fn_80036E50(iterator) == 3) {
                eligible = 1;
            }

            if (context != 0 && eligible != 0
                && lbl_8064D18C == fn_8011FB4C(context)
                && fn_8013B8C0(context, player->entries + entry_offset) != 0) {
                fn_8020123C(8, 0, object, 0);
                count++;
            }
            iterator = fn_80201BC0(iterator);
        }
    }

    lua_pushnumber(script, (double)count);
    return 1;
}
