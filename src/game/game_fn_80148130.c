typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern void *fn_80156938(void *);
extern Vec3s *fn_8017FDE4(void *);

void fn_80148130(void *object, Vec3f *position)
{
    Vec3s *source = fn_8017FDE4(fn_80156938(object));

    position->x = source->x;
    position->y = source->y;
    position->z = source->z;
}
