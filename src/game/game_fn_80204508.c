typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *fn_80201BC8(void *object);
extern Vec3 fn_8011F114(void *transform);
extern int fn_80204578(void *object, Vec3 *position);

int fn_80204508(void *object, void *other)
{
    void *transform = fn_80201BC8(other);

    if (transform != 0) {
        Vec3 position = fn_8011F114(transform);
        return fn_80204578(object, &position);
    }
    return 0;
}
