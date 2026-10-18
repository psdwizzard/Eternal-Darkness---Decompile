typedef struct Lexer {
    char padding_00[8];
    int current_kind;
    char padding_0c[0x28];
    int line;
} Lexer;

extern char lbl_8024F7AC[];
extern void error_expected(Lexer*, int);
extern void luaX_token2str(int, char*);
extern int sprintf(char*, const char*, ...);
extern void luaK_error(Lexer*, char*);
extern void fn_80163DA4(Lexer*);

void check_match(Lexer* lexer, int expected, int opener, int line)
{
    char expected_name[16];
    char opener_name[16];
    char message[100];

    if (lexer->current_kind != expected) {
        if (line == lexer->line) {
            error_expected(lexer, expected);
        } else {
            luaX_token2str(expected, expected_name);
            luaX_token2str(opener, opener_name);
            sprintf(message, lbl_8024F7AC, expected_name, opener_name, line);
            luaK_error(lexer, message);
        }
    }
    fn_80163DA4(lexer);
}
