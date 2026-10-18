typedef struct Lexer {
    char padding[8];
    int current_kind;
} Lexer;

extern void error_expected(Lexer*, int);
extern void fn_80163DA4(Lexer*);

void check(Lexer* lexer, int token)
{
    if (lexer->current_kind != token) {
        error_expected(lexer, token);
    }
    fn_80163DA4(lexer);
}
