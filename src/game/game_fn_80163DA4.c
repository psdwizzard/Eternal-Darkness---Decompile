typedef struct Token {
    int kind;
    int padding;
    double value;
} Token;

typedef struct Lexer {
    char padding[8];
    Token current;
    Token lookahead;
    int padding_30[3];
    int line;
    int last_line;
} Lexer;

extern int luaX_lex(Lexer*, double*);

void fn_80163DA4(Lexer* lexer)
{
    lexer->last_line = lexer->line;
    if (lexer->lookahead.kind != 284) {
        lexer->current = lexer->lookahead;
        lexer->lookahead.kind = 284;
    } else {
        lexer->current.kind = luaX_lex(lexer, &lexer->current.value);
    }
}
