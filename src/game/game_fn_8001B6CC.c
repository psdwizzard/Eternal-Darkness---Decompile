typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern void* fn_80201C24();
extern void fn_80157B94(void*, s32);

s32 fn_8001B6CC(void* script)
{
    s32 state;
    void* object;
    void* object_state;
    void* transform;
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0 && (transform = fn_80201BC8(object)) != 0) {
        state = fn_8011EB04(transform);
        object_state = fn_80201C24(object);
        switch (state) {
    case 32:
        value = 9;
        break;
    case 33:
        value = 12;
        break;
    case 34:
        value = 15;
        break;
    case 35:
        value = 41;
        break;
    case 36:
        value = 18;
        break;
    case 37:
        value = 22;
        break;
    case 39:
        value = 25;
        break;
    case 40:
        value = 28;
        break;
    case 41:
        value = 38;
        break;
    case 42:
        value = 1;
        break;
    case 43:
        value = 3;
        break;
    case 44:
        value = 35;
        break;
        default:
            return 0;
        }
        fn_80157B94(object_state, value);
    }
    return 0;
}
