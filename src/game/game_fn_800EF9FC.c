typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern int gTRKBigEndian[];
extern int fn_800EFBC8(TRKBuffer *, const void *, u32);

void fn_800EF9FC(TRKBuffer *buffer, u64 value)
{
    u8 swapped[8];
    u8 *source;

    if (gTRKBigEndian[0] != 0) {
        source = (u8 *)&value;
    } else {
        source = swapped;
        swapped[0] = ((u8 *)&value)[7];
        swapped[1] = ((u8 *)&value)[6];
        swapped[2] = ((u8 *)&value)[5];
        swapped[3] = ((u8 *)&value)[4];
        swapped[4] = ((u8 *)&value)[3];
        swapped[5] = ((u8 *)&value)[2];
        swapped[6] = ((u8 *)&value)[1];
        swapped[7] = ((u8 *)&value)[0];
    }
    fn_800EFBC8(buffer, source, sizeof(value));
}
