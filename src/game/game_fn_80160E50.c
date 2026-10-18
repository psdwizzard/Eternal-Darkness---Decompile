typedef struct Buffer {
    char data[0x120];
} Buffer;

extern char lbl_8064BA78;
extern void luaZ_mopen(Buffer*, signed char*, void*, void*);
extern int protectedparser(void*, void*, int);

int parse_buffer(void* object, signed char* text, void* value, void* context)
{
    Buffer buffer;

    if (context == 0) {
        context = &lbl_8064BA78;
    }
    luaZ_mopen(&buffer, text, value, context);
    return protectedparser(object, &buffer, *text == 27);
}
