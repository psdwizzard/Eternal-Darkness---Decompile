typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern int gTRKBigEndian[];
extern int fn_800EFBC8(TRKBuffer *, const void *, u32);

int fn_800EFA84(TRKBuffer *buffer, u32 value)
{
    u8 swapped[4];
    void *source;

    if (gTRKBigEndian[0] != 0) {
        source = &value;
    } else {
        source = swapped;
        swapped[0] = ((u8 *)&value)[3];
        swapped[1] = ((u8 *)&value)[2];
        swapped[2] = ((u8 *)&value)[1];
        swapped[3] = ((u8 *)&value)[0];
    }
    return fn_800EFBC8(buffer, source, sizeof(value));
}
