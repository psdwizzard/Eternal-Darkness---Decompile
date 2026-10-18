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

extern void luaX_error(Parser*, char*, int);
extern void inclinenumber(Parser*);
extern void luaO_openspace(Buffer*, unsigned int);
extern char* luaS_newlstr(Buffer*, char*, unsigned int);
extern char lbl_8024F6B8[];

void read_long_string(Parser* parser, char** result)
{
    int depth = 0;
    Buffer* buffer = parser->buffer;
    unsigned int index;
    int token;

    if (buffer->capacity < 10) {
        luaO_openspace(buffer, 0x8A);
    }

    buffer->data[0] = '[';
    index = 2;
    buffer->data[1] = parser->current_token;
    if (parser->input->remaining-- != 0) {
        token = *parser->input->current++;
    } else {
        token = parser->input->read(parser->input);
    }
    parser->current_token = token;

    for (;;) {
        if (index + 10 > buffer->capacity) {
            luaO_openspace(buffer, index + 0x8A);
        }

        switch (parser->current_token) {
        case -1:
            buffer->data[index++] = 0;
            luaX_error(parser, lbl_8024F6B8, 0x11B);
            break;

        case '[':
            buffer->data[index++] = parser->current_token;
            if (parser->input->remaining-- != 0) {
                token = *parser->input->current++;
            } else {
                token = parser->input->read(parser->input);
            }
            parser->current_token = token;
            if (parser->current_token == '[') {
                depth++;
                buffer->data[index++] = parser->current_token;
                if (parser->input->remaining-- != 0) {
                    token = *parser->input->current++;
                } else {
                    token = parser->input->read(parser->input);
                }
                parser->current_token = token;
            }
            break;

        case ']':
            buffer->data[index++] = parser->current_token;
            if (parser->input->remaining-- != 0) {
                token = *parser->input->current++;
            } else {
                token = parser->input->read(parser->input);
            }
            parser->current_token = token;
            if (parser->current_token != ']') {
                break;
            }
            if (depth != 0) {
                depth--;
                buffer->data[index++] = parser->current_token;
                if (parser->input->remaining-- != 0) {
                    token = *parser->input->current++;
                } else {
                    token = parser->input->read(parser->input);
                }
                parser->current_token = token;
                break;
            }

            goto finished;

        case '\n':
            buffer->data[index++] = '\n';
            inclinenumber(parser);
            break;

        default:
            buffer->data[index++] = parser->current_token;
            if (parser->input->remaining-- != 0) {
                token = *parser->input->current++;
            } else {
                token = parser->input->read(parser->input);
            }
            parser->current_token = token;
            break;
        }
    }

finished:
    buffer->data[index++] = parser->current_token;
    if (parser->input->remaining-- != 0) {
        token = *parser->input->current++;
    } else {
        token = parser->input->read(parser->input);
    }
    parser->current_token = token;
    buffer->data[index] = 0;
    *result = luaS_newlstr(buffer, buffer->data + 2, index - 4);
}
