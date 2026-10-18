extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012B7A0(void*, float);
extern const char lbl_8024FF00[];
extern const float lbl_806506C0;

int fn_8016F4CC(void* state)
{
    int object_id;
    float value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    value = (float)lua_tonumber(state, 2);
    fn_8012B7A0(fn_80201BC8(fn_80201814(object_id)), lbl_806506C0 * value);
    return 0;
}
