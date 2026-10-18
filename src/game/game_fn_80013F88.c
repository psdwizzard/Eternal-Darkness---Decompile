typedef int s32;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec4 {
    u32 x;
    u32 y;
    u32 z;
    u32 w;
} Vec4;

typedef struct GameState {
    unsigned char position[0xC];
    Vec4 unk_0C;
    u32 count;
    s16 values[4];
    unsigned char data[0xC];
} GameState;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E4;
extern GameState lbl_80301D08;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void *fn_80201814();
extern void fn_8011F114();
extern Vec4* fn_8011FE34(void*);
extern int fn_80038308(void *, int, short *);
extern unsigned int fn_800F5C54(double);
extern void fn_80144E78(void*, u32);

s32 fn_80013F88(void* script)
{
    void* object;
    u32 count;

    object = fn_80201814(fn_80201B44());
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    fn_8011F114(&lbl_80301D08, lbl_8064C4E4);
    lbl_80301D08.unk_0C = *fn_8011FE34(lbl_8064C4E4);
    fn_80038308(object, 0, &lbl_80301D08.values[0]);
    fn_80038308(object, 2, &lbl_80301D08.values[2]);
    fn_80038308(object, 1, &lbl_80301D08.values[1]);
    fn_80038308(object, 3, &lbl_80301D08.values[3]);
    count = fn_800F5C54(lua_tonumber(script, 1));
    lbl_80301D08.count = count;
    lbl_80301D08.count = count > 1 ? count : 1;
    fn_80144E78(lbl_80301D08.data, lbl_80301D08.count);
    return 0;
}
