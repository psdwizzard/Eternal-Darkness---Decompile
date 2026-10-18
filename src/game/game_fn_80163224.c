#pragma use_lmw_stmw on

typedef struct Input Input;
typedef int (*ReadFn)(Input*);

struct Input {
    unsigned int remaining;
    unsigned char* current;
    ReadFn read;
};

typedef struct Buffer {
    char pad00[0x18];
    char* data;
    unsigned int capacity;
} Buffer;

typedef struct Parser {
    int current_token;
    char pad04[0x28];
    Buffer* buffer;
    Input* input;
} Parser;

typedef struct StringEntry {
    char pad00[0x10];
    int token;
} StringEntry;

extern int isdigit(int);
extern int iscntrl(int);
extern int isalpha(int);
extern void luaX_error(Parser*, char*, int);
extern void luaX_invalidchar(Parser*, int);
extern void inclinenumber(Parser*);
extern char* readname(Parser*);
extern void read_number(Parser*, int, void**);
extern void read_long_string(Parser*, void**);
extern void read_string(Parser*, int, void**);
extern StringEntry* luaS_new(void*, char*);
extern char lbl_8024F700[];

#define NEXT_TOKEN() do {                                                     \
    int token;                                                               \
    if (parser->input->remaining-- != 0) {                                   \
        token = *parser->input->current++;                                   \
    } else {                                                                 \
        token = parser->input->read(parser->input);                           \
    }                                                                        \
    parser->current_token = token;                                            \
} while (0)

int luaX_lex(Parser* parser, void** result)
{
    StringEntry* entry;

    for (;;) {
        switch (parser->current_token) {
        case '\t':
        case '\r':
        case ' ':
            NEXT_TOKEN();
            continue;

        case '\n':
            inclinenumber(parser);
            continue;

        case '$':
            luaX_error(parser, lbl_8024F700, '$');
            continue;

        case '-':
            NEXT_TOKEN();
            if (parser->current_token != '-') {
                return '-';
            }
            do {
                NEXT_TOKEN();
            } while (parser->current_token != '\n' && parser->current_token != -1);
            continue;

        case '[':
            NEXT_TOKEN();
            if (parser->current_token != '[') {
                return '[';
            }
            read_long_string(parser, result);
            return 0x11B;

        case '=':
            NEXT_TOKEN();
            if (parser->current_token != '=') {
                return '=';
            }
            NEXT_TOKEN();
            return 0x116;

        case '<':
            NEXT_TOKEN();
            if (parser->current_token != '=') {
                return '<';
            }
            NEXT_TOKEN();
            return 0x118;

        case '>':
            NEXT_TOKEN();
            if (parser->current_token != '=') {
                return '>';
            }
            NEXT_TOKEN();
            return 0x117;

        case '~':
            NEXT_TOKEN();
            if (parser->current_token != '=') {
                return '~';
            }
            NEXT_TOKEN();
            return 0x119;

        case '"':
        case '\'':
            read_string(parser, parser->current_token, result);
            return 0x11B;

        case '.':
            NEXT_TOKEN();
            if (parser->current_token == '.') {
                NEXT_TOKEN();
                if (parser->current_token == '.') {
                    NEXT_TOKEN();
                    return 0x115;
                }
                return 0x114;
            }
            if (!isdigit(parser->current_token)) {
                return '.';
            }
            read_number(parser, 1, result);
            return 0x11A;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            read_number(parser, 0, result);
            return 0x11A;

        case -1:
            return 0x11C;

        case '_':
            goto identifier;

        default:
            if (isalpha(parser->current_token)) {
                goto identifier;
            } else {
                int c = parser->current_token;
                if (iscntrl(c)) {
                    luaX_invalidchar(parser, c);
                }
                NEXT_TOKEN();
                return c;
            }
        }
    }

identifier:
    entry = luaS_new(parser->buffer, readname(parser));
    if (entry->token >= 3) {
        return entry->token + 0xFE;
    }
    *result = entry;
    return 0x113;
}
