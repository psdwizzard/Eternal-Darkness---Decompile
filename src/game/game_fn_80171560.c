extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801296F8(void*, int);
extern void fn_8011FB5C(void*, int);
struct ErrorStrings {
    char argument_count;
    char pad_001[0x343];
    char object_not_found[0x1C];
    char component_not_found[1];
};
extern const struct ErrorStrings lbl_8024FF00;

int fn_80171560(void* state)
{
    const struct ErrorStrings* errors = &lbl_8024FF00;
    int object_id;
    int value;
    void* object;
    void* component;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, &errors->pad_001[-1], 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    object = fn_80201814(object_id);
    if (object == 0) {
        luaO_verror(state, errors->object_not_found, object_id);
        return 0;
    }

    component = fn_80201BC8(object);
    if (component == 0) {
        luaO_verror(state, errors->component_not_found, object_id, object);
        return 0;
    }

    fn_801296F8(component, value);
    fn_8011FB5C(component, value);
    return 0;
}
