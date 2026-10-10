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

extern int gTRKBigEndian[];
extern int fn_800EFBC8(TRKBuffer *, const void *, u32);

int fn_800EFAE8(TRKBuffer *buffer, u16 value)
{
    u8 swapped[2];
    void *source;

    if (gTRKBigEndian[0] != 0) {
        source = &value;
    } else {
        source = swapped;
        swapped[0] = ((u8 *)&value)[1];
        swapped[1] = ((u8 *)&value)[0];
    }
    return fn_800EFBC8(buffer, source, sizeof(value));
}
