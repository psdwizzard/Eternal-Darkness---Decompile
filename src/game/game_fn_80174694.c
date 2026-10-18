typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EffectDescriptor {
    u8 pad00;
    u8 byte01;
    u8 byte02;
    u8 byte03;
    u16 value04;
    u16 value06;
    u8 pad08[0xE];
    u8 byte16;
    u8 byte17;
    u8 pad18[4];
    u32 value1C;
    u32 value20;
    u32 value24;
    u32 value28;
    u8 pad2C[8];
    float value34;
    u32 value38;
    u8 pad3C[0x6C];
    u32 owner;
    u8 padAC[0x14];
} EffectDescriptor;

typedef struct SpawnedEffect {
    u8 pad00[8];
    int kind;
    u8 pad0C[0x3C];
    int channel;
} SpawnedEffect;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern SpawnedEffect* fn_80149E04(void);
extern void fn_80147E88(EffectDescriptor*);
extern void fn_8014F4CC(EffectDescriptor*, SpawnedEffect*);
extern void fn_8019B13C(EffectDescriptor*);
extern void *fn_80201814();
extern void* fn_80155DB4(void);
extern void* fn_80148300(void*, EffectDescriptor*, SpawnedEffect*);
extern void fn_80149EB8(SpawnedEffect*);
extern const char lbl_8024FF00[];

int fn_80174694(void* state)
{
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;
    float arg12;
    int arg13;
    SpawnedEffect* spawned;
    void* manager;
    EffectDescriptor effect;

    if (lua_gettop(state) != 13) {
        luaO_verror(state, lbl_8024FF00, 13, lua_gettop(state));
        return 0;
    }

    arg1 = fn_800F5C54(lua_tonumber(state, 1));
    arg2 = lua_tonumber(state, 2);
    arg3 = lua_tonumber(state, 3);
    arg4 = lua_tonumber(state, 4);
    arg5 = lua_tonumber(state, 5);
    arg6 = lua_tonumber(state, 6);
    arg7 = lua_tonumber(state, 7);
    arg8 = lua_tonumber(state, 8);
    arg9 = lua_tonumber(state, 9);
    arg10 = lua_tonumber(state, 10);
    arg11 = lua_tonumber(state, 11);
    arg12 = lua_tonumber(state, 12);
    arg13 = lua_tonumber(state, 13);

    spawned = fn_80149E04();
    if (spawned != 0) {
        fn_80147E88(&effect);
        fn_8014F4CC(&effect, spawned);
        effect.owner = arg1;
        spawned->kind = arg2;
        spawned->channel = arg3;
        fn_8019B13C(&effect);
        effect.value04 = arg4;
        effect.byte01 = arg6;
        effect.value06 = arg7;
        effect.byte02 = arg8;
        effect.byte03 = arg9;
        effect.value1C = 0;
        effect.value20 = 0;
        effect.value24 = arg5;
        if (arg5 != 0) {
            effect.value28 = 1;
        }
        effect.byte16 = arg10;
        effect.byte17 = arg11;
        effect.value34 = arg12;
        effect.value38 = arg13;
        fn_80201814(arg1);
        manager = fn_80155DB4();
        if (manager != 0) {
            if (fn_80148300(manager, &effect, spawned) == 0) {
                fn_80149EB8(spawned);
            }
        } else {
            fn_80149EB8(spawned);
        }
    }
    return 0;
}
