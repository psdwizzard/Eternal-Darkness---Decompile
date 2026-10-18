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
extern CommBuffer lbl_8032A578;
extern u8 lbl_8032B694[];

int fn_800F5674(void)
{
    int result = 0;
    long count = lbl_8032A578.outputCount;
    u8 *next = lbl_8032B694 + count;

    for (; count < 0x800; ++count) {
        *next++ = 0;
    }
    lbl_8032A578.outputCount = count;
    if (count != 0) {
        int status = gDBCommTable[4]((unsigned int *)lbl_8032B694,
                                     (unsigned int)count);
        result = status ? -1 : 0;
        lbl_8032A578.outputCount = 0;
    }
    return result;
}
