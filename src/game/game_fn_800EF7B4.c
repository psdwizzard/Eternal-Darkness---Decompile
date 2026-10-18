typedef unsigned char u8;
typedef unsigned short u16;
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

static inline int TRKReadBuffer(TRKBuffer *buffer, void *data, register u32 length)
{
    int error = 0;
    register u32 bytes_left;

    if (length == 0) {
        return 0;
    }
    bytes_left = buffer->length - buffer->position;
    /* ASM: cmplw/ble retain the inlined length parameter as a register;
     * CodeWarrior otherwise folds the constant-sized read to cmplwi/bge. */
    asm {
        cmplw length, bytes_left
        ble read_ready
    }
    error = 0x302;
    length = bytes_left;
read_ready:
    TRK_memcpy(data, buffer->data + buffer->position, length);
    buffer->position += length;
    return error;
}

int TRKReadBuffer1_ui16(TRKBuffer *buffer, u16 *out)
{
    int read_err;
    u8 *destination;
    u8 *byte_data;
    u8 swap_buffer[sizeof(out)];

    if (gTRKBigEndian[0] != 0) {
        destination = (u8 *)out;
    } else {
        destination = swap_buffer;
    }
    read_err = TRKReadBuffer(buffer, (void *)destination, sizeof(*out));
    if (gTRKBigEndian[0] == 0 && read_err == 0) {
        byte_data = (u8 *)out;
        byte_data[0] = destination[1];
        byte_data[1] = destination[0];
    }
    return read_err;
}
