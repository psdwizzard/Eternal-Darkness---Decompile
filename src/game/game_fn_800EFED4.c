typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;

typedef struct TRKSerialState {
    int buffer_id;
    int unk4;
    u8 state;
    u8 pad9[3];
    int count;
} TRKSerialState;

extern TRKSerialState gTRKFramingState;
extern void TRKConstructEvent(TRKEvent *, int);
extern int TRKPostEvent(const TRKEvent *);

void TRKProcessInput(int buffer)
{
    TRKEvent event;

    TRKConstructEvent(&event, 2);
    event.buffer = buffer;
    gTRKFramingState.buffer_id = -1;
    TRKPostEvent(&event);
}
