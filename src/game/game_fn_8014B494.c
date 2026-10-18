typedef unsigned char u8;

typedef struct Params {
    u8 pad0[0x22];
    short rotation[3];
    u8 pad28[0x84];
    u8 count;
    u8 padAD;
    short amplitude;
    float offset_x;
    float offset_y;
    float offset_z;
} Params;

extern double lbl_80650490;
extern float lbl_80650498;
extern double lbl_806504A0;
extern float sinf(float);
extern float cosf(float);
extern void fn_801534D8(void*, short*, float);

/* Honest reconstruction of the interpolated angular/position update. The
 * remaining mismatch is compiler-owned signed/unsigned conversion scheduling. */
void fn_8014B494(void* context, short* output, int phase, int index,
                 Params* params)
{
    float angle = lbl_80650498 * (float)phase / (float)params->count;
    float wave = sinf(angle);

    output[0] = params->amplitude * wave + params->offset_x;
    wave = cosf(angle);
    output[1] = params->amplitude * wave + params->offset_y;
    output[2] = params->offset_z;
    fn_801534D8(context, params->rotation,
                (float)index / (float)(params->count - 1));
}
