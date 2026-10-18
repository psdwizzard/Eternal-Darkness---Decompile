typedef int s32;

extern const char lbl_80244EDC[];
extern const char lbl_80244F0C[];
extern unsigned char lbl_8031CD84[];
extern s32 lbl_8064C8F0;
extern const double lbl_8064EA40;

extern int lua_gettop(void *);
extern void *lua_touserdata(void *, int);
extern double lua_tonumber(void *, int);
extern void luaO_verror(void *, const char *, ...);
extern unsigned int fn_801E741C(const char *);

s32 fn_8007F650(void *script)
{
    void *object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_80244EDC, 1, lua_gettop(script));
        return 0;
    }

    object = lua_touserdata(script, 1);
    if (object != 0) {
        if ((signed char)lbl_8031CD84[0x631] == 0) {
            lbl_8031CD84[0x631] = 1;
            if (*(unsigned int *)((unsigned char *)object + 0x2C) == fn_801E741C(lbl_80244F0C)) {
                lbl_8064C8F0 = (signed char)lbl_8031CD84[0x630];
            } else {
                lbl_8064C8F0 = 3;
            }
        }
    } else if (lua_tonumber(script, 1) == lbl_8064EA40) {
        lbl_8031CD84[0x631] = 1;
        lbl_8064C8F0 = (signed char)lbl_8031CD84[0x630];
    } else {
        lbl_8031CD84[0x631] = 0;
    }

    return 0;
}
