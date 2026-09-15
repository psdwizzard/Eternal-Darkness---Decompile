typedef signed short s16;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SVec3 { s16 x, y, z; } SVec3;

extern Vec3 lbl_8023A718;
extern const Vec3 lbl_8063D378;
extern const float lbl_806504B8;
extern const float lbl_806504BC;
extern const float lbl_806504C0;

extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern void fn_8011F114();
extern void fn_80211A6C();
extern void fn_80211AAC(Vec3*, Vec3*);
extern int fn_80179064(int, int, int, int);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);

void fn_8014BEC4(int unused, Vec3* source, SVec3* out, Vec3* result, Vec3* copy)
{
    Vec3 world;
    Vec3 base;
    Vec3 offset;
    Vec3 direction;
    void* object;

    offset = lbl_8023A718;
    object = fn_80201BC8(fn_80201814());
    fn_8012B690(object, &offset, &base);
    fn_8011F114(&world, object);
    fn_80211A6C(source, &world, &direction);
    if (lbl_806504B8 == direction.x && lbl_806504B8 == direction.y &&
        lbl_806504B8 == direction.z)
        fn_80211A6C((Vec3*)&lbl_8063D378, &world, &direction);
    fn_80211AAC(&direction, &direction);
    fn_80211A90(&direction, &direction,
                fn_80179064((int)world.x, (int)world.y,
                            (int)source->x, (int)source->y) > 200
                    ? lbl_806504BC : lbl_806504C0);
    fn_80211A48(&base, &direction, result);
    out->x = (s16)direction.x;
    out->y = (s16)direction.y;
    out->z = (s16)direction.z;
    if (copy != 0)
        *copy = *result;
}
