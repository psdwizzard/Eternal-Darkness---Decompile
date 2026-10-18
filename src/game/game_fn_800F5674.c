typedef unsigned char u8;

typedef struct CommBuffer {
    int outputCount;
    int readIndex;
    int readCount;
    int reserved;
    u8 data[0x110A];
} CommBuffer;

/* The communication backends have different parameter lists. */
typedef int (*CommFunction)();
extern CommFunction gDBCommTable[7];
extern CommBuffer gWritePos;
extern u8 gWriteBuf[];

int WriteUARTFlush(void)
{
    int result = 0;
    long count = gWritePos.outputCount;
    u8 *next = gWriteBuf + count;

    for (; count < 0x800; ++count) {
        *next++ = 0;
    }
    gWritePos.outputCount = count;
    if (count != 0) {
        int status = gDBCommTable[4]((unsigned int *)gWriteBuf,
                                     (unsigned int)count);
        result = status ? -1 : 0;
        gWritePos.outputCount = 0;
    }
    return result;
}
