extern char lbl_8024F798[];
extern void luaX_token2str(int, char*);
extern int sprintf(char*, const char*, ...);
extern void luaK_error(void*, char*);

void error_expected(void* lexer, int token)
{
    char token_name[16];
    char message[100];

    luaX_token2str(token, token_name);
    sprintf(message, lbl_8024F798, token_name);
    luaK_error(lexer, message);
}
