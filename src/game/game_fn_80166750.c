typedef struct Parser {
    char pad0[8];
    int token;
} Parser;

extern int stat(Parser*);
extern int optional(Parser*, int);
extern int block_follow(int);

void chunk(Parser* parser)
{
    int result = 0;

    while (!result && !block_follow(parser->token)) {
        result = stat(parser);
        optional(parser, 0x3B);
    }
}
