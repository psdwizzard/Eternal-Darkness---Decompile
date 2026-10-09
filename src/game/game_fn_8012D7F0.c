typedef signed short s16;
typedef unsigned char u8;

typedef struct PackedVector {
    s16 values[3];
} PackedVector;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_8012BE18(const s16*, float*, int);
extern void fn_8012BDCC(const float*, s16*, int);

void fn_8012D7F0(u8* state)
{
    PackedVector saved;
    Vec3 vector;

    saved = *(PackedVector*)(state + 0x5A);
    *(PackedVector*)(state + 0x5A) = *(PackedVector*)(state + 0x66);
    *(PackedVector*)(state + 0x54) = *(PackedVector*)(state + 0x5A);
    *(PackedVector*)(state + 0x66) = saved;

    fn_8012BE18((s16*)(state + 0x60), &vector.x, 6);
    vector.x = -vector.x;
    vector.y = -vector.y;
    vector.z = -vector.z;
    fn_8012BDCC(&vector.x, (s16*)(state + 0x60), 6);
}
