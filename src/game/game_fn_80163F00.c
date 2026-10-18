typedef struct Lexer {
    char padding[8];
    int current_kind;
} Lexer;

extern void fn_80163DA4(Lexer*);

int optional(Lexer* lexer, int token)
{
    if (lexer->current_kind == token) {
        fn_80163DA4(lexer);
        return 1;
    }
    return 0;
}
