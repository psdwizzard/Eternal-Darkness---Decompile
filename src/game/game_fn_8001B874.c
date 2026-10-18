typedef short s16;
typedef int s32;

typedef struct InitState {
    float first;
    float second;
    float third;
    s32 value_c;
    s32 value_10;
    s32 value_14;
    s32 value_18;
    s32 value_1c;
    s32 value_20;
    s32 value_24;
    s32 value_28;
    s32 value_2c;
} InitState;

typedef struct GlobalState {
    char pad[8];
    void* object;
} GlobalState;

extern InitState lbl_803022C4;
extern GlobalState lbl_80606328;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8015AA58(InitState*);
extern void fn_8015AA28(s32);
extern char lbl_8023BEF8[];

s32 fn_8001B874(void* arg)
{
    lbl_803022C4.first = 250.0f;
    lbl_803022C4.second = 0.5f;
    lbl_803022C4.third = 0.5f;
    lbl_803022C4.value_c = 200;
    lbl_803022C4.value_10 = 250;
    lbl_803022C4.value_14 = 1;
    lbl_803022C4.value_18 = 2;
    lbl_803022C4.value_1c = 2;
    lbl_803022C4.value_20 = 0;
    lbl_803022C4.value_24 = *(s16*)((char*)lbl_80606328.object + 0xAC0);
    lbl_803022C4.value_28 = 2;
    lbl_803022C4.value_2c = 1;

    if (lua_gettop(arg) != 1) {
        luaO_verror(arg, lbl_8023BEF8, 1, lua_gettop(arg));
        return 0;
    }

    switch ((s32)lua_tonumber(arg, 1)) {
    case 1:
        fn_8015AA58(&lbl_803022C4);
        break;
    default:
        fn_8015AA28(0);
        break;
    }
    return 0;
}
