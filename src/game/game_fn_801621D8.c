extern char lbl_8064BB1C;
extern char lbl_8024F640[];
extern void sprintf(char*, char*, ...);
extern void luaX_syntaxerror(void*, char*, char*);

void luaX_invalidchar(void* parser, int value)
{
    char buffer[16];

    sprintf(buffer, &lbl_8064BB1C, value);
    luaX_syntaxerror(parser, lbl_8024F640, buffer);
}
