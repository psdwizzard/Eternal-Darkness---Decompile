typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern void fn_801870D0(void*, Vec3s*);
extern void fn_80187120(s16, s16, s16, s16, float*, float*);
extern void fn_80193F3C(u8, int, Vec3s*, Vec3s*, float, float, s16, u8, u8);

void fn_801941EC(u8* state, u8* input, Vec3s* output)
{
    s16 points[18][3];
    u8 count;
    s16 offset;
    s16 step;
    u8 interior;
    u8 last;
    u8 last3;
    int i;
    u8 last2;
    int stride;
    float x_offset;
    float y_offset;

    count = state[0xB];
    interior = count - 4;
    last = count - 1;
    last2 = count - 2;
    last3 = count - 3;
    for (i = 1; i < last; i++) {
        fn_801870D0(input + 0xA, (Vec3s*)&points[i]);
        input += 0x38;
    }

    points[0][0] = points[1][0] - (points[2][0] - points[1][0]);
    points[0][1] = points[1][1] - (points[2][1] - points[1][1]);
    points[0][2] = points[1][2] - (points[2][2] - points[1][2]);
    points[last][0] = points[last2][0] + (points[last2][0] - points[last3][0]);
    points[last][1] = points[last2][1] + (points[last2][1] - points[last3][1]);
    points[last][2] = points[last2][2] + (points[last2][2] - points[last3][2]);

    offset = *(s16*)(state + 0x22);
    step = *(s16*)(state + 0x24);
    output[0].x = points[0][0];
    output[0].y = points[0][1];
    output[0].z = points[0][2];
    output[1].x = points[1][0];
    output[1].y = points[1][1];
    output[1].z = points[1][2];
    output += 2;

    for (i = 0; i < interior;) {
        fn_80187120(points[i + 1][0], points[i + 1][1],
                    points[i + 3][0], points[i + 3][1],
                    &x_offset, &y_offset);
        fn_80193F3C(state[0xB], i, (Vec3s*)&points[i + 2], output, x_offset, y_offset,
                    offset, state[4], state[5]);
        offset += step;
        i++;
        output += 2;
    }

    output[0].x = points[last][0];
    output[0].y = points[last][1];
    output[0].z = points[last][2];
    output[1].x = points[last2][0];
    output[1].y = points[last2][1];
    output[1].z = points[last2][2];
    stride = interior * 2 + 1;
    output += 1;
    output += stride;
    output[0].x = points[0][0];
    output[0].y = points[0][1];
    output[0].z = points[0][2];
    output[1].x = points[1][0];
    output[1].y = points[1][1];
    output[1].z = points[1][2];
    output[2].x = points[1][0];
    output[2].y = points[1][1];
    output[2].z = points[1][2];
    output[3].x = points[1][0];
    output[3].y = points[1][1];
    output[3].z = points[1][2];
    output += 3;
    output += stride;
    output[0].x = points[last2][0];
    output[0].y = points[last2][1];
    output[0].z = points[last2][2];
    output[1].x = points[last2][0];
    output[1].y = points[last2][1];
    output[1].z = points[last2][2];
    output += 1;
    output += stride;
    output[0].x = points[1][0];
    output[0].y = points[1][1];
    output[0].z = points[1][2];
    output[1].x = points[1][0];
    output[1].y = points[1][1];
    output[1].z = points[1][2];
}
