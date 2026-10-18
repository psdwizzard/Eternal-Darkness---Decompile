typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKTargetStop(void);
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);

void TRKDoStop(TRKBuffer *buffer)
{
    int response;
    int retry;

    switch (TRKTargetStop()) {
    case 0: response = 0; break;
    case 0x704: response = 0x21; break;
    case 0x705: response = 0x22; break;
    case 0x706: response = 0x20; break;
    default: response = 1; break;
    }
    TRKResetBuffer(buffer, 1);
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = 0x80;
        buffer->length++;
    }
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = response;
        buffer->length++;
    }
    retry = 3;
    do {
        int result = TRKMessageSend(buffer);
        retry--;
        if (result == 0) break;
    } while (retry > 0);
}
