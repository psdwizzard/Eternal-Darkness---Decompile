typedef unsigned char u8;
typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    unsigned id;
    int buffer;
} TRKEvent;

void TRKConstructEvent(TRKEvent *event, u8 type)
{
    event->type = type;
    event->id = 0;
    event->buffer = -1;
}
