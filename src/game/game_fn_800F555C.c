typedef unsigned char u8;

typedef struct CommTable {
    void (*init)(void);
    void (*initInterrupts)(void);
    int (*queryData)(void);
    int (*read)(u8 *, unsigned int);
    int (*write)(const u8 *, unsigned int);
    void (*open)(void);
    void (*close)(void);
} CommTable;

typedef struct CommBuffer {
    int outputCount;
    int readIndex;
    int readCount;
    int reserved;
    u8 data[0x110A];
} CommBuffer;

extern CommTable gDBCommTable;
extern CommBuffer lbl_8032A578;

int fn_800F555C(u8 *value)
{
    CommBuffer *buffer = &lbl_8032A578;
    int result = 4;

    if (buffer->readIndex >= buffer->readCount) {
        buffer->readIndex = 0;
        buffer->readCount = gDBCommTable.queryData();
        if (buffer->readCount > 0) {
            if (buffer->readCount > 0x110A) {
                buffer->readCount = 0x110A;
            }
            result = gDBCommTable.read(buffer->data,
                                      buffer->readCount) ? -1 : 0;
            if (result != 0) {
                buffer->readCount = 0;
            }
        }
    }
    if (buffer->readIndex < buffer->readCount) {
        *value = buffer->data[buffer->readIndex++];
        result = 0;
    }
    return result;
}
