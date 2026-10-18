typedef unsigned char u8;
typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    unsigned id;
    int buffer;
} TRKEvent;

extern void TRKReleaseBuffer(int);

void TRKDestructEvent(TRKEvent *event)
{
    TRKReleaseBuffer(event->buffer);
}
