typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Matrix34 { float m[3][4]; } Matrix34;
typedef struct Matrix44 { float m[4][4]; } Matrix44;
typedef struct Contact {
    unsigned char pad[0xB0];
    unsigned short kind;
    void* value;
} Contact;

extern void* lbl_8064C4E4;
extern float lbl_806502B8;
extern void* fn_80201BD0(void);
extern Contact* fn_8012AB2C(void*);
extern float fn_8011F6F8(void*);
extern void fn_8013F3C0(Matrix34*, const Vec3*, const Vec3*);
extern void fn_8013A538(void*, Contact*, Matrix34*, int, void*, void*);
extern void fn_80139E20(void*, Vec3*, void*);
extern unsigned int fn_8011FAF4(void*);
extern void fn_8011F114();
extern Vec3* fn_8011F130(void*);
extern void fn_80211A6C();
extern void fn_8013F4D0(void*, void*, void*);
extern int fn_8011EB1C(void*);
extern int fn_80201B5C(void*);
extern void fn_8013B538(void*, void*, unsigned short, void*);
extern void fn_80155ABC(Matrix34*, int);

void fn_80139F28(void* object, const Vec3* start, const Vec3* target,
                 Vec3* output, void* flags)
{
    Matrix44 matrix;
    unsigned char result[24];
    void* context = fn_80201BD0();
    Contact* contact = fn_8012AB2C(object);
    Vec3 original = *start;

    if (contact == 0) {
        *output = *start;
        return;
    }

    fn_8011F6F8(object);
    fn_8013F3C0((Matrix34*)&matrix, start, target);
    fn_8013A538(object, contact, (Matrix34*)&matrix, 0, result, flags);
    fn_80139E20(object, (Vec3*)((unsigned char*)&matrix + 12), flags);
    *output = *(Vec3*)((unsigned char*)&matrix + 12);

    if (!(fn_8011FAF4(object) & 0x8000)) {
        Vec3 comparison;
        Vec3 a;
        Vec3 b;
        Vec3 up;
        Vec3 location;
        unsigned char plane[40];
        Vec3* facing;

        fn_8011F114(&location, object);
        comparison = location;
        facing = fn_8011F130(object);
        up.x = lbl_806502B8;
        up.y = lbl_806502B8;
        up.z = fn_8011F6F8(object);
        fn_80211A6C(&original, &up, &a);
        fn_80211A6C((Vec3*)((unsigned char*)&matrix + 12), &up, &b);
        fn_8013F4D0(plane, &a, &b);
        if ((fn_8011EB1C(object) <= 2 && fn_80201B5C(context) != 29) ||
            object == lbl_8064C4E4)
            fn_8013B538(object, contact->value, contact->kind, plane);
        if (fn_8012AB2C(object) == 0)
            return;
        if (facing->x != comparison.x || facing->y != comparison.y ||
            facing->z != comparison.z)
        {
            fn_8011F6F8(object);
            fn_8013F3C0((Matrix34*)&matrix, facing, facing);
        }
    }
    if (object == lbl_8064C4E4)
        fn_80155ABC((Matrix34*)&matrix, 0);
}
