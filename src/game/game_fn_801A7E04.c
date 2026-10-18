typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Shape801A7E04 {
    unsigned int radius;
    Vec3s center;
    unsigned char padA[0x32];
} Shape801A7E04;

typedef struct Object801A7E04 {
    unsigned char pad[0x30];
    Shape801A7E04 shape;
    short type;
} Object801A7E04;

extern void fn_80179DB0(Vec3*, Vec3s*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern int fn_8013D6A4(const Vec3*, const Vec3s*, const Vec3s*);

int fn_801A7E04(const Vec3* point, Object801A7E04* object)
{
    Shape801A7E04* shape = &object->shape;
    short type = object->type;

    if (type == 0) {
        Vec3 center;
        fn_80179DB0(&center, &shape->center);
        return PSVECSquareDistance(&center, point) < shape->radius * shape->radius;
    }
    if (type == 1) {
        return fn_8013D6A4(point, (Vec3s*)shape, (Vec3s*)((unsigned char*)shape + 6));
    }
    return 0;
}
