#pragma use_lmw_stmw on

extern const char lbl_8024FB30[];
extern int ezgetc(void*, void*);
extern int ZNAME(void*);
extern void luaO_verror(void*, const char*, ...);

void TestSize(void* object, int expected, const char* description,
                 void* input)
{
    int actual = ezgetc(object, input);

    if (actual != expected)
        luaO_verror(object, lbl_8024FB30, ZNAME(input), description,
                    expected, actual);
}
