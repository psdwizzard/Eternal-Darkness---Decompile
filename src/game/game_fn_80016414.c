typedef int s32;
typedef unsigned char u8;
typedef signed short s16;

typedef struct SpawnInfo {
    u8 unk0;
    u8 unk1;
    u8 unk2[4];
    s16 unk6;
    u8 unk8[19];
    u8 unk27;
    u8 unk28[116];
} SpawnInfo;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8015319C(s32, s32, s32, s32, s32, s32, s32);
extern void fn_80152BCC(s32, s32, s32, volatile SpawnInfo*, s32, s32, s32,
                       s32);

s32 fn_80016414(void* script)
{
    s32 fifth;
    s32 fourth;
    s32 i;
    s32 first;
    s32 second;
    s32 third;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    volatile SpawnInfo info;

    if (lua_gettop(script) != 8) {
        luaO_verror(script, lbl_8023BEF8, 8, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);

    if ((u8)eighth != 0) {
        fn_8015319C(first, second, third, fourth, fifth, sixth, seventh);
    } else {
        info.unk6 = (s16)fifth;
        fourth = (u8)fourth;
        i = 0;
        info.unk1 = (u8)sixth;
        info.unk27 = (u8)seventh;
        while (i < fourth) {
            fn_80152BCC(first, second, third, &info, 17, 1, 1, 128);
            i++;
        }
    }
    return 0;
}
