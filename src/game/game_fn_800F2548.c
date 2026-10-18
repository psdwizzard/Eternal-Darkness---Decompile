typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern void TRKResetBuffer(TRKBuffer *, u8);
extern int TRKMessageSend(TRKBuffer *);
extern int TRKTargetVersions(unsigned char *);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

static inline int appendChecked(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

void TRKDoVersions(TRKBuffer *buffer)
{
    unsigned char state[4];
    u8 value;
    int result;
    int retry;

    if (buffer->length != 1) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 2);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    TRKResetBuffer(buffer, 1);
    append(buffer, 0x80);
    append(buffer, 0);

    result = TRKTargetVersions(state);
    if (result == 0) {
        value = state[0];
        if (buffer->position >= 0x880) {
            result = 0x301;
        } else {
            buffer->data[buffer->position++] = value;
            buffer->length++;
            result = 0;
        }
    }
    if (result == 0) result = appendChecked(buffer, state[1]);
    if (result == 0) result = appendChecked(buffer, state[2]);
    if (result == 0) result = appendChecked(buffer, state[3]);

    if (result != 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 3);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else {
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    }
}
