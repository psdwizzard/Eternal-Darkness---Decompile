typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern void TRK_memcpy(void *, const void *, u32);
extern int gTRKBigEndian[];

static inline int TRKReadBuffer(TRKBuffer *buffer, void *data, unsigned long length)
{
    int error = 0;
    u32 bytesLeft;

    if (length == 0) {
        return 0;
    }

    bytesLeft = buffer->length - buffer->position;
    if (length > bytesLeft) {
        error = 0x302;
        length = bytesLeft;
    }

    TRK_memcpy(data, buffer->data + buffer->position, length);
    buffer->position += length;
    return error;
}

int TRKReadBuffer1_ui32(TRKBuffer *buffer, u32 *out)
{
    int err;
    u8 *bigEndianData;
    u8 *byteData;
    u8 swapBuffer[sizeof(out)];

    if (gTRKBigEndian[0] != 0) {
        bigEndianData = (u8 *)out;
    } else {
        bigEndianData = swapBuffer;
    }

    err = TRKReadBuffer(buffer, (void *)bigEndianData, sizeof(*out));

    if (gTRKBigEndian[0] == 0 && err == 0) {
        byteData = (u8 *)out;
        byteData[0] = bigEndianData[3];
        byteData[1] = bigEndianData[2];
        byteData[2] = bigEndianData[1];
        byteData[3] = bigEndianData[0];
    }

    return err;
}
