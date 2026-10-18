extern signed char lbl_8064BBC8;
extern const char lbl_8024FB14[];
extern int ezgetc(void*, void*);
extern int ZNAME(void*);
extern void luaO_verror(void*, const char*, ...);

void LoadSignature(void* object, void* input)
{
    const signed char* signature = &lbl_8064BBC8;

    while (*signature != 0 && ezgetc(object, input) == *signature)
        ++signature;
    if (*signature != 0)
        luaO_verror(object, lbl_8024FB14, ZNAME(input));
}
