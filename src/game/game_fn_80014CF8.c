typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern unsigned int fn_800F5C54(double);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D62D0(u32, s32, s32, u32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32, s32, s32, s32, s32, s32, s32, u32, s32,
                       s32, u32, u32, s32, s32);

s32 fn_80014CF8(void* script)
{
    u32 v1;
    s32 v2;
    s32 v3;
    u32 v4;
    s32 v5;
    s32 v6;
    s32 v7;
    s32 v8;
    s32 v9;
    s32 v10;
    s32 v11;
    s32 v12;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 v16;
    s32 v17;
    s32 v18;
    s32 v19;
    s32 v20;
    s32 v21;
    s32 v22;
    s32 v23;
    s32 v24;
    u32 flags;
    u32 transformed;

    if (lua_gettop(script) != 24) {
        luaO_verror(script, lbl_8023BEF8, 24, lua_gettop(script));
        return 0;
    }

    v1 = fn_800F5C54(lua_tonumber(script, 1));
    v2 = (s32)lua_tonumber(script, 2);
    v3 = (s32)lua_tonumber(script, 3);
    v4 = fn_800F5C54(lua_tonumber(script, 4));
    v5 = (s32)lua_tonumber(script, 5);
    v6 = (s32)lua_tonumber(script, 6);
    v7 = (s32)lua_tonumber(script, 7);
    v8 = (s32)lua_tonumber(script, 8);
    v9 = (s32)lua_tonumber(script, 9);
    v10 = (s32)lua_tonumber(script, 10);
    v11 = (s32)lua_tonumber(script, 11);
    v12 = (s32)lua_tonumber(script, 12);
    v13 = (s32)lua_tonumber(script, 13);
    v14 = (s32)lua_tonumber(script, 14);
    v15 = (s32)lua_tonumber(script, 15);
    v16 = (s32)lua_tonumber(script, 16);
    v17 = (s32)lua_tonumber(script, 17);
    v18 = (s32)lua_tonumber(script, 18);
    v19 = (s32)lua_tonumber(script, 19);
    v20 = (s32)lua_tonumber(script, 20);
    v21 = (s32)lua_tonumber(script, 21);
    v22 = (s32)lua_tonumber(script, 22);
    v23 = (s32)lua_tonumber(script, 23);
    v24 = (s32)lua_tonumber(script, 24);

    flags = 0x40000;
    if (v22 & 1) {
        flags |= 0x10000;
    }
    if (v22 & 2) {
        flags |= 0x20000;
    }
    if (v22 & 4) {
        flags |= 0x2000;
    }
    if (v23 != 0) {
        flags |= 0x40;
    }
    flags |= 0x800;
    transformed = (v18 & 0x3F) << 2;
    fn_801D62D0(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13,
                v14, v15, v16, v17, v18, v19, transformed, v20, v21, v24,
                flags, 0x110, 4);
    return 0;
}
