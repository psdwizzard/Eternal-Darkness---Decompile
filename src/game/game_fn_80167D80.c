extern char lbl_8024FAD0[];
extern char* ZNAME(void*);
extern void luaO_verror(void*, const char*, ...);

void unexpectedEOZ(void* object, void* input)
{
    luaO_verror(object, lbl_8024FAD0, ZNAME(input));
}
