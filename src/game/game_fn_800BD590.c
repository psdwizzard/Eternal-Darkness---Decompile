typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern void fn_800BCCC4(const short *source, Vec3f *result);
extern int fn_80179004(const float *first, const float *second);

float fn_800BD590(const short **first, const short **second)
{
    Vec3f first_position;
    Vec3f second_position;

    fn_800BCCC4(*first, &first_position);
    fn_800BCCC4(*second, &second_position);
    return (float)(unsigned int)fn_80179004((const float *)&first_position,
                                           (const float *)&second_position);
}
