typedef struct ValueSet {
    char pad00[0x18];
    char* value;
} ValueSet;

typedef struct Parser {
    char pad00[0x2C];
    ValueSet* values;
} Parser;

extern void luaX_token2str(char*, signed char*);
extern void luaX_syntaxerror(Parser*, int, char*);

void luaX_error(Parser* parser, int token, char* source)
{
    signed char value[8];

    luaX_token2str(source, value);
    if (value[0] == 0) {
        luaX_syntaxerror(parser, token, parser->values->value);
    } else {
        luaX_syntaxerror(parser, token, (char*)value);
    }
}
