typedef struct Buffer {
    char padding_00[0x1E];
    short position;
} Buffer;

typedef struct Parser {
    char padding_00[0x28];
    Buffer* buffer;
} Parser;

extern void chunk(Parser*);
extern void luaK_adjuststack(Buffer*, int);
extern void removelocalvars(Parser*, int);

void block(Parser* parser)
{
    Buffer* buffer = parser->buffer;
    short start = buffer->position;

    chunk(parser);
    luaK_adjuststack(buffer, buffer->position - start);
    removelocalvars(parser, buffer->position - start);
}
