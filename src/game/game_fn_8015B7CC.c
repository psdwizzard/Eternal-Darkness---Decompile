typedef unsigned char u8;

typedef struct Stream {
    u8 pad[0x48];
    void* source;
} Stream;

typedef struct Command {
    int result;
    Stream* stream;
} Command;

extern void OSSendMessage(void*, int, int);

void fn_8015B7CC(Command* command)
{
    OSSendMessage(command->stream->source, 123456, 0);
}
