typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef struct Ref Ref;
typedef struct Object Object;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void *fn_80201814();
extern void* fn_80201C24();
extern int fn_80201B44();
extern u32 fn_80157BF4(Object*);
extern u16 fn_80158234(Object*);
extern s32 fn_801586FC(s32, void*);
extern s32 fn_801579F4(Object*);
extern s32 fn_801579EC(Object*);
extern u16 fn_80157948(Object*);
extern u16 fn_80157994(void*);
extern char lbl_8023BEF8[];
extern double lbl_8064DD38;
extern double lbl_8064DDB8;
extern double lbl_8064DE08;
extern double lbl_8064DD40;
extern double lbl_8064DE00;
extern double lbl_8064DCF8;
extern double lbl_8064DE68;

s32 fn_8001BAE4(void* arg)
{
    s32 id1;
    s32 id2;
    Ref* ref1;
    Ref* ref2;
    Object* object;
    Object* first;
    Object* second;
    u16 value1;
    s32 value2;

    if (lua_gettop(arg) != 2) {
        luaO_verror(arg, lbl_8023BEF8, 2, lua_gettop(arg));
        return 0;
    }

    id1 = (s32)lua_tonumber(arg, 1);
    id2 = (s32)lua_tonumber(arg, 2);
    ref1 = fn_80201814(id1);
    ref2 = fn_80201814(id2);
    if (ref1 == 0 || ref2 == 0)
        goto invalid_refs;

    object = fn_80201C24(ref1);
    if (fn_80157BF4(object) == 3) {
        first = object;
        id2 = (s32)fn_80201C24(ref2);
        if (fn_80157BF4((Object*)id2) != 4) {
            lua_pushnumber(arg, lbl_8064DD38);
            return 1;
        }
        if (fn_80158234(first) == 0) {
            lua_pushnumber(arg, lbl_8064DD38);
            return 1;
        }
        if (!fn_801586FC(id1, (void*)fn_80201B44())) {
            lua_pushnumber(arg, lbl_8064DDB8);
            return 1;
        }
        if ((fn_80158234((Object*)id2) & fn_80158234(first)) == 0) {
            if ((fn_80158234(first) == 0x100 || fn_80158234(first) == 0x400) &&
                (fn_80158234((Object*)id2) == 0x100 || fn_80158234((Object*)id2) == 0x400)) {
                lua_pushnumber(arg, lbl_8064DE08);
                return 1;
            }
            lua_pushnumber(arg, lbl_8064DD40);
            return 1;
        }
    } else {
        second = object;
        first = fn_80201C24(ref2);
        if (fn_80157BF4(first) != 3) {
            lua_pushnumber(arg, lbl_8064DD38);
            return 1;
        }
        if (fn_80158234(first) == 0) {
            lua_pushnumber(arg, lbl_8064DD38);
            return 1;
        }
        if (!fn_801586FC(id2, (void*)fn_80201B44())) {
            lua_pushnumber(arg, lbl_8064DDB8);
            return 1;
        }
        if ((fn_80158234(second) & fn_80158234(first)) == 0) {
            if ((fn_80158234(first) == 0x100 || fn_80158234(first) == 0x400) &&
                (fn_80158234(second) == 0x100 || fn_80158234(second) == 0x400)) {
                lua_pushnumber(arg, lbl_8064DE08);
                return 1;
            }
            lua_pushnumber(arg, lbl_8064DD40);
            return 1;
        }
    }

    if (fn_801579F4(first) || fn_801579EC(first)) {
        Ref* parent_ref;
        Object* parent;
        if (fn_801579F4(first)) {
            parent_ref = fn_80201814(fn_801579F4(first));
        } else {
            parent_ref = fn_80201814(fn_801579EC(first));
        }
        parent = fn_80201C24(parent_ref);
        value1 = fn_80157948(first) + fn_80157948(parent);
        value2 = fn_80157994(first) + fn_80157994(parent);
    } else {
        value1 = fn_80157948(first);
        value2 = fn_80157994(first);
    }

    if ((s32)(u16)value1 - value2 <= 0) {
        lua_pushnumber(arg, lbl_8064DE00);
        return 1;
    }
    lua_pushnumber(arg, lbl_8064DCF8);
    return 1;

invalid_refs:
    lua_pushnumber(arg, lbl_8064DE68);
    return 1;
}
