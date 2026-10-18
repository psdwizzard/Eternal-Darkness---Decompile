typedef unsigned char u8;

typedef struct TRKSerialState {
    int buffer_id;
    int unk4;
    u8 state;
    u8 pad9[3];
    int count;
} TRKSerialState;

extern TRKSerialState gTRKFramingState;

int TRKInitializeSerialHandler(void)
{
    gTRKFramingState.buffer_id = -1;
    gTRKFramingState.state = 0;
    gTRKFramingState.count = 0;
    return 0;
}
