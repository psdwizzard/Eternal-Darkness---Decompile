typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

typedef struct TRKFramingState {
    int buffer_id;
    TRKBuffer *buffer;
    u8 state;
    u8 pad9[3];
    int is_escape;
    u8 fcs;
} TRKFramingState;

extern TRKFramingState gTRKFramingState;
extern int TRKReadUARTPoll(u8 *);
extern int TRKGetFreeBuffer(int *, TRKBuffer **);
extern void TRKReleaseBuffer(int);
extern void TRKStandardACK(TRKBuffer *, int, int);

static inline void TRKDiscardFrame(void)
{
    if (gTRKFramingState.buffer_id != -1) {
        TRKReleaseBuffer(gTRKFramingState.buffer_id);
        gTRKFramingState.buffer_id = -1;
    }
    gTRKFramingState.buffer = 0;
    gTRKFramingState.state = 0;
}

static inline int TRKFinishFrame(TRKBuffer *buffer)
{
    if (buffer->length < 2) {
        TRKStandardACK(buffer, 0xFF, 2);
        TRKDiscardFrame();
        return 0;
    }
    buffer->position = 0;
    buffer->length--;
    return 1;
}

static inline int TRKAppendByte(TRKBuffer *buffer, u8 c)
{
    if (buffer->position >= 0x880) {
        return 0x301;
    }
    buffer->data[buffer->position++] = c;
    buffer->length++;
    return 0;
}

int TRKTestForPacket(void)
{
    int err = 0;
    int result;
    signed char c;

    for (result = TRKReadUARTPoll((u8 *)&c); result == 0 && err == 0; result = TRKReadUARTPoll((u8 *)&c)) {
        if (gTRKFramingState.state != 2) {
            gTRKFramingState.is_escape = 0;
        }
        switch (gTRKFramingState.state) {
        case 0:
            if ((int)c == 0x7E) {
                err = TRKGetFreeBuffer(&gTRKFramingState.buffer_id, &gTRKFramingState.buffer);
                gTRKFramingState.fcs = 0;
                gTRKFramingState.state = 1;
            }
            break;
        case 1:
            if ((int)c == 0x7E) {
                break;
            }
            gTRKFramingState.state = 2;
        case 2:
            if (c == 0x7E) {
                if (gTRKFramingState.is_escape) {
                    TRKStandardACK(gTRKFramingState.buffer, 0xFF, 4);
                    TRKDiscardFrame();
                    break;
                }
                if (TRKFinishFrame(gTRKFramingState.buffer)) {
                    int id = gTRKFramingState.buffer_id;
                    gTRKFramingState.buffer_id = -1;
                    gTRKFramingState.buffer = 0;
                    gTRKFramingState.state = 0;
                    return id;
                }
                gTRKFramingState.state = 0;
                break;
            }
            if (gTRKFramingState.is_escape) {
                c ^= 0x20;
                gTRKFramingState.is_escape = 0;
            } else if (c == 0x7D) {
                gTRKFramingState.is_escape = 1;
                break;
            }
            err = TRKAppendByte(gTRKFramingState.buffer, c);
            gTRKFramingState.fcs += c;
            break;
        case 3:
            if ((int)c == 0x7E) {
                TRKDiscardFrame();
            }
            break;
        }
    }
    return -1;
}
