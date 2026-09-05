typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct PackedVec3 {
    s16 x;
    s16 y;
    s16 z;
} PackedVec3;

typedef struct Owner {
    u8 pad0[0x154];
    Vec3f* vectors;
    void* packed_vectors;
} Owner;

typedef struct RangeState {
    u8 pad0[0x10];
    int kind;
    PackedVec3 vector;
} RangeState;

extern void fn_801285D8(int*, int);
extern void fn_801252D8(int);
extern void fn_80128108(void*, PackedVec3*);

void fn_8012744C(Owner* owner, int index, RangeState* state, int flags)
{
    register Vec3f* source;
    register s16* packed;
    register float first;
    register float second;

    if ((flags & 2) != 0) {
        source = &owner->vectors[index];
        packed = &state->vector.x;
        fn_801285D8(&state->kind, 1);
        fn_801252D8(4);
        asm {
            psq_l first, 0(source), 0, 0
            psq_lu second, 8(source), 1, 0
            psq_st first, 0(packed), 0, 2
            psq_stu second, 4(packed), 1, 2
        }
    } else if ((flags & 1) != 0) {
        fn_801285D8(&state->kind, 2);
        fn_80128108((u8*)owner->packed_vectors + index * 0x10,
                    &state->vector);
    }
}
