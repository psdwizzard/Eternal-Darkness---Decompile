typedef struct Context Context;
typedef struct Pair Pair;

extern Context* lbl_8064D1C0;
extern void luaL_openlib(Context*, Pair*, int);

void fn_8016B26C(Pair* pairs, int count)
{
    luaL_openlib(lbl_8064D1C0, pairs, count);
}
