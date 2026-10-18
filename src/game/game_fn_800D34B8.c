typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern Vec3 lbl_80239958;
extern float lbl_8064F390;
extern void PSVECSubtract();
extern void PSVECScale(Vec3 *, Vec3 *, float);
extern int fn_8012FD1C(void *, int, Vec3 *);
extern void *fn_8011F130(void *);
extern void fn_8012B6FC(void *, Vec3 *, Vec3 *);
extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);

void fn_800D34B8(void *object, Vec3 *output, Vec3 *input, Vec3 *scale)
{
    Vec3 normalized;
    Vec3 direction;
    Vec3 position;
    Vec3 temporary;
    Vec3 basis = lbl_80239958;

    PSVECSubtract(input, output, &normalized);
    PSVECScale(&normalized, &normalized, lbl_8064F390);
    fn_8012FD1C(object, 1, &position);
    PSVECSubtract(fn_8011F130(object), &position, &direction);
    fn_8012B6FC(object, &basis, &basis);
    PSVECAdd(output, &normalized, &temporary);
    PSVECAdd(&temporary, &direction, scale);
    PSVECAdd(scale, &basis, scale);
}
