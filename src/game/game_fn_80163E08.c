typedef struct Lexer {
    char padding[0x18];
    int lookahead_kind;
    int lookahead_padding;
    double lookahead_value;
} Lexer;

extern int luaX_lex(Lexer*, double*);

void fn_80163E08(Lexer* lexer)
{
    lexer->lookahead_kind = luaX_lex(lexer, &lexer->lookahead_value);
}
