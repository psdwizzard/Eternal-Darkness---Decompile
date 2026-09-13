typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Params {
    unsigned char pad[0x14];
    Vec3 position;
    float scale;
    unsigned char type;
} Params;

extern const float lbl_806503A8, lbl_806503B0;
extern void fn_80179C10(Vec3*, float, float, const Vec3*, float, unsigned char);

void fn_8013F6DC(Vec3* out, Params* params)
{
    fn_80179C10(out, lbl_806503B0, lbl_806503A8, &params->position,
                params->scale, params->type);
    fn_80179C10(out + 1, lbl_806503A8, lbl_806503B0, &params->position,
                params->scale, params->type);
    fn_80179C10(out + 2, lbl_806503B0, lbl_806503B0, &params->position,
                params->scale, params->type);
}
