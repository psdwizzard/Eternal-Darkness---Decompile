typedef struct Parser {
    char pad00[0x2C];
    void* output;
    char pad30[4];
    int position;
    char pad38[4];
    char* source;
} Parser;

extern char lbl_8024F608[];
extern void luaO_chunkid(char*, char*, int);
extern void luaO_verror(void*, const char*, ...);

void luaX_syntaxerror(Parser* parser, int token, char* value)
{
    char context[80];

    luaO_chunkid(context, parser->source + 0x14, sizeof(context));
    luaO_verror(parser->output, lbl_8024F608, token, value,
                parser->position, context);
}
