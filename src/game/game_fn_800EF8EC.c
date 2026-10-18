typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

extern int gTRKBigEndian[];
extern int TRKAppendBuffer(TRKBuffer *, const u8 *, u32);

void TRKAppendBuffer_ui32(TRKBuffer *buffer, u32 *values, int count)
{
    u8 swapped[4];
    u32 value;
    u32 *current;
    u8 *source;
    int i;
    int error;

    current = values;
    i = 0;
    error = 0;
    while (error == 0 && i < count) {
        value = *current;
        if (gTRKBigEndian[0] != 0) {
            source = (u8 *)&value;
        } else {
            source = swapped;
            swapped[0] = ((u8 *)&value)[3];
            swapped[1] = ((u8 *)&value)[2];
            swapped[2] = ((u8 *)&value)[1];
            swapped[3] = ((u8 *)&value)[0];
        }
        error = TRKAppendBuffer(buffer, source, sizeof(value));
        i++;
        current++;
    }
}
