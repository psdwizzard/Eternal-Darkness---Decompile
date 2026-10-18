extern char lbl_805FAAB0[];
extern char lbl_8024FEF4[];
extern char lbl_8064BC08;
extern void* lbl_8064D1C0;
extern int lbl_8064D1BC;
extern int lbl_8064D1C4;
extern void* lbl_8064D1DC;
extern void* lbl_8064D1E0;

extern char* fn_800FD40C(char*, const char*);
extern void lua_pushusertag(void*, void*, int);
extern void lua_getglobal(void*, const char*);
extern void lua_setglobal(void*, const char*);
extern void lua_settop(void*, int);
extern void lua_setgcthreshold(void*, int);
extern void* lua_dobuffer(void*, void*, void*, void*);
extern void fn_8016B400(int, void*, void*);
extern void fn_8016B914(int);

#pragma use_lmw_stmw on

void* fn_8016B4B4(void* data, void* size, char* name, void* context, void* value)
{
    void* result;

    fn_800FD40C(lbl_805FAAB0, name);
    fn_8016B914(-1);
    lua_pushusertag(lbl_8064D1C0, context, 0);
    lua_setglobal(lbl_8064D1C0, lbl_8024FEF4);
    lua_pushusertag(lbl_8064D1C0, value, 0);
    lua_setglobal(lbl_8064D1C0, &lbl_8064BC08);
    result = lua_dobuffer(lbl_8064D1C0, data, size, name);
    lua_getglobal(lbl_8064D1C0, lbl_8024FEF4);
    lua_settop(lbl_8064D1C0, -2);
    lua_getglobal(lbl_8064D1C0, &lbl_8064BC08);
    lua_settop(lbl_8064D1C0, -2);
    lua_setgcthreshold(lbl_8064D1C0, 0);
    lbl_8064D1BC = 0;
    fn_8016B914(-2);
    if (lbl_8064D1C4 != 0) {
        fn_8016B400(lbl_8064D1C4, lbl_8064D1E0, lbl_8064D1DC);
    }
    return result;
}
