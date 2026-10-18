typedef struct Parser {
    char pad00[8];
    int position;
} Parser;

extern char lbl_8024F5EC[];
extern int sprintf(char*, const char*, ...);
extern void luaX_error(Parser*, char*, int);

void luaX_checklimit(Parser* parser, int current, int limit, int token)
{
    char buffer[100];

    if (current > limit) {
        sprintf(buffer, lbl_8024F5EC, token, limit);
        luaX_error(parser, buffer, parser->position);
    }
}
