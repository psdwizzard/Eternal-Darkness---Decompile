typedef struct Input Input;
typedef int (*ReadFn)(Input*);

struct Input {
    unsigned int remaining;
    unsigned char* current;
    ReadFn read;
};

typedef struct Parser {
    int current_token;
    char pad04[0x14];
    unsigned int buffer_size;
    unsigned int buffer_used;
    char pad20[8];
    char* buffer;
    void* context;
    Input* input;
    int flag34;
    int flag38;
    int field3C;
} Parser;

void luaX_setinput(void* context, Parser* parser, Input* input, int field3C)
{
    int token;

    parser->context = context;
    parser->buffer_size = 0x11C;
    parser->input = input;
    parser->buffer = 0;
    parser->flag34 = 1;
    parser->flag38 = 1;
    parser->field3C = field3C;

    if (parser->input->remaining-- != 0) {
        token = *parser->input->current++;
    } else {
        token = parser->input->read(parser->input);
    }
    parser->current_token = token;

    if (parser->current_token == '#') {
        do {
            if (parser->input->remaining-- != 0) {
                token = *parser->input->current++;
            } else {
                token = parser->input->read(parser->input);
            }
            parser->current_token = token;
        } while (parser->current_token != '\n' && parser->current_token != -1);
    }
}
