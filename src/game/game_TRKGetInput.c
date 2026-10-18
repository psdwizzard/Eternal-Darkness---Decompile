typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

typedef struct TRKSerialState {
    int buffer_id;
    int unk4;
    u8 state;
    u8 pad9[3];
    int count;
} TRKSerialState;

extern TRKSerialState gTRKFramingState;
extern int TRKTestForPacket(void);
extern TRKBuffer *TRKGetBuffer(int);
extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern void TRKConstructEvent(TRKEvent *, int);
extern int TRKPostEvent(const TRKEvent *);
extern void TRKReleaseBuffer(int);

void TRKGetInput(void)
{
    TRKBuffer *buffer;
    int buffer_id;

    buffer_id = TRKTestForPacket();

    if (buffer_id != -1) {
        u8 command;

        buffer = TRKGetBuffer(buffer_id);
        TRKSetBufferPosition(buffer, 0);
        TRKReadBuffer1_ui8(buffer, &command);
        if (command < 0x80) {
            TRKEvent event;
            TRKConstructEvent(&event, 2);
            event.buffer = buffer_id;
            gTRKFramingState.buffer_id = -1;
            TRKPostEvent(&event);
        } else {
            TRKReleaseBuffer(buffer_id);
        }
    }
}
