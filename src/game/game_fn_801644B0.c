typedef struct Parser {
    char padding_00[0x2C];
    void* allocator;
} Parser;

extern void* luaS_newfixed(void*);
extern void new_localvar(Parser*, void*, int);

void new_localvarstr(Parser* parser, int unused, int count)
{
    new_localvar(parser, luaS_newfixed(parser->allocator), count);
}
