typedef signed short s16;
typedef unsigned char u8;

typedef struct Sample801F2370 {
    float x, y, z;
    u8 r, g, b, a;
    int value;
} Sample801F2370;

typedef struct Volume801F2370 {
    int unused0;
    int count;
    float x, y, z;
    s16 half_x, half_y, half_z;
    u8 unused1;
    u8 size_x, size_y, size_z;
    u8 unused2[2];
    Sample801F2370* samples;
} Volume801F2370;

extern float lbl_806513C8;
extern float lbl_806513CC;
extern int lbl_8064A1C8;
extern int lbl_8064A80C;
extern int lbl_8065144C;

extern void fn_801F10BC(int, int, int);
extern void fn_801F2170(int [8][4], Sample801F2370**, int);
extern void fn_800EBF88(float*, float*, int*, int);

int fn_801F2370(Volume801F2370* volume, float* point, int count,
                Sample801F2370* output)
{
    float corner_weight[8];
    Sample801F2370* corners[8];
    int mapping[8][4];
    float minimum[3];
    float maximum[3];
    int ix, iy, iz, index;
    int sx = 1, sy = 1, sz = 1;
    int i, j;

    ix = (int)((point[2] - volume->z) / (float)volume->half_z);
    iy = (int)((point[1] - volume->y) / (float)volume->half_y);
    iz = (int)((point[0] - volume->x) / (float)volume->half_x);
    index = iz + iy * volume->size_x + ix * volume->size_x * volume->size_y;
    if (index < 0 || index >= volume->count) {
        fn_801F10BC(0, 0, 0);
        return -1;
    }

    corners[0] = &volume->samples[index];
    minimum[0] = (float)(corners[0]->x - volume->half_x / 2);
    maximum[0] = (float)(corners[0]->x + volume->half_x / 2);
    minimum[1] = (float)(corners[0]->y - volume->half_y / 2);
    maximum[1] = (float)(corners[0]->y + volume->half_y / 2);
    minimum[2] = (float)(corners[0]->z - volume->half_z / 2);
    maximum[2] = (float)(corners[0]->z + volume->half_z / 2);
    if (lbl_8064A1C8 != 0) {
        int mode = lbl_8065144C;
        fn_800EBF88(maximum, minimum, &mode, 0x40);
    }

    if (point[0] < corners[0]->x) { sx = -1; }
    if (point[1] < corners[0]->y) { sy = -1; }
    if (point[2] < corners[0]->z) { sz = -1; }
    {
        float wx = (point[0] - corners[0]->x);
        float wy = (point[1] - corners[0]->y);
        float wz = (point[2] - corners[0]->z);
        if (wx < 0.0f) wx = -wx;
        if (wy < 0.0f) wy = -wy;
        if (wz < 0.0f) wz = -wz;
        wx /= volume->half_x;
        wy /= volume->half_y;
        wz /= volume->half_z;
        if (iz + sx < 0 || iz + sx >= volume->size_x) { wx = 0.0f; sx = 0; }
        if (iy + sy < 0 || iy + sy >= volume->size_y) { wy = 0.0f; sy = 0; }
        if (ix + sz < 0 || ix + sz >= volume->size_z) { wz = 0.0f; sz = 0; }

        corners[1] = &volume->samples[index + sx];
        corners[2] = &volume->samples[index + sy * volume->size_x];
        corners[3] = &volume->samples[index + sx + sy * volume->size_x];
        corners[4] = &volume->samples[index + sz * volume->size_x * volume->size_y];
        corners[5] = &volume->samples[index + sx + sz * volume->size_x * volume->size_y];
        corners[6] = &volume->samples[index + sy * volume->size_x + sz * volume->size_x * volume->size_y];
        corners[7] = &volume->samples[index + sx + sy * volume->size_x + sz * volume->size_x * volume->size_y];
        corner_weight[0] = (1.0f-wx)*(1.0f-wy)*(1.0f-wz);
        corner_weight[1] = wx*(1.0f-wy)*(1.0f-wz);
        corner_weight[2] = (1.0f-wx)*wy*(1.0f-wz);
        corner_weight[3] = wx*wy*(1.0f-wz);
        corner_weight[4] = (1.0f-wx)*(1.0f-wy)*wz;
        corner_weight[5] = wx*(1.0f-wy)*wz;
        corner_weight[6] = (1.0f-wx)*wy*wz;
        corner_weight[7] = wx*wy*wz;
    }

    fn_801F2170(mapping, corners, count);
    for (i = 0; i < count; i++) {
        float* dst = &output[i].x;
        for (j = 0; j < 3; j++) {
            dst[j] = 0.0f;
            dst[j] += corner_weight[0] * ((float*)corners[0])[mapping[0][i] * 5 + j];
            dst[j] += corner_weight[1] * ((float*)corners[1])[mapping[1][i] * 5 + j];
            dst[j] += corner_weight[2] * ((float*)corners[2])[mapping[2][i] * 5 + j];
            dst[j] += corner_weight[3] * ((float*)corners[3])[mapping[3][i] * 5 + j];
            dst[j] += corner_weight[4] * ((float*)corners[4])[mapping[4][i] * 5 + j];
            dst[j] += corner_weight[5] * ((float*)corners[5])[mapping[5][i] * 5 + j];
            dst[j] += corner_weight[6] * ((float*)corners[6])[mapping[6][i] * 5 + j];
            dst[j] += corner_weight[7] * ((float*)corners[7])[mapping[7][i] * 5 + j];
        }
        output[i].r = output[i].g = output[i].b = 0;
        output[i].a = 255;
        output[i].value = 0;
        for (j = 0; j < 8; j++) {
            Sample801F2370* source = &corners[j][mapping[j][i]];
            output[i].r += (u8)(corner_weight[j] * (source->r - output[i].r));
            output[i].g += (u8)(corner_weight[j] * (source->g - output[i].g));
            output[i].b += (u8)(corner_weight[j] * (source->b - output[i].b));
            output[i].a += (u8)(corner_weight[j] * (source->a - output[i].a));
            output[i].value += (int)(corner_weight[j] * (source->value - output[i].value));
        }
        if (lbl_8064A80C == 0x124) output[i].value *= 8;
        else if (output[i].value > 30000) output[i].value = 30000;
    }
    return index;
}
