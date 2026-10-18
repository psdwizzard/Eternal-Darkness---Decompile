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

extern int isalnum(int);
extern void luaO_openspace(Buffer*, unsigned int);

char* readname(Parser* parser)
{
    Buffer* buffer = parser->buffer;
    unsigned int index = 0;
    int token;

    if (buffer->capacity < 10) {
        luaO_openspace(buffer, 0x8A);
    }

    do {
        if (index + 10 > buffer->capacity) {
            luaO_openspace(buffer, index + 0x8A);
        }
        buffer->data[index] = parser->current_token;
        index++;

        if (parser->input->remaining-- != 0) {
            token = *parser->input->current++;
        } else {
            token = parser->input->read(parser->input);
        }
        parser->current_token = token;
    } while (isalnum(parser->current_token) || parser->current_token == '_');

    buffer->data[index] = 0;
    return buffer->data;
}
