typedef unsigned int u32;
typedef struct Context Context;
typedef void (*Callback)(Context*, int, void*);

extern char lbl_8024FEDC[];
extern char lbl_8064BC00;
extern void* lbl_8064D1C8;
extern void* lbl_8064D1CC;
extern Callback lbl_8064D1D0;
extern u32 lbl_8064D1D4;
extern Context* lbl_8064D1C0;

extern void* fn_801FEA8C(u32, int, const char*, int);
extern void* memset(void*, int, unsigned long);
extern void* luaM_realloc(int, int, int, const char*, int);
extern void fn_8016B030(int);
extern Context* lua_open(int);
extern void fn_80177408(void);
extern void fn_80177434(Context*, int, void*);
extern void lua_setgcthreshold(Context*, int);

void fn_8016B29C(u32 size, Callback callback)
{
    lbl_8064D1C8 = fn_801FEA8C(0x25BB8, 1, lbl_8024FEDC, 452);
    lbl_8064D1D0 = callback;
    lbl_8064D1CC = 0;
    lbl_8064D1D4 = 0;

    if (size != 0) {
        lbl_8064D1CC = fn_801FEA8C(size, 1, lbl_8024FEDC, 460);
        memset(lbl_8064D1CC, 0, size);
        lbl_8064D1D4 = size;
    }

    luaM_realloc(0, 0, -1, lbl_8024FEDC, 468);
    fn_8016B030(0);
    lbl_8064D1C0 = lua_open(0);
    fn_80177408();
    fn_80177434(lbl_8064D1C0, 0, &lbl_8064BC00);
    if (lbl_8064D1D0 != 0) {
        lbl_8064D1D0(lbl_8064D1C0, 0, &lbl_8064BC00);
    }
    lua_setgcthreshold(lbl_8064D1C0, 0);
}
