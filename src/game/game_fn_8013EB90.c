typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    float height;
    Vec3 axis;
    float limit;
} Shape;
typedef struct Result { Vec3 normal; Vec3 point; } Result;

extern float lbl_80650350, lbl_80650378, lbl_8065039C;
extern void fn_8013C264(const Vec3*, const Vec3*, Vec3*, const Vec3*, Vec3*);
extern float fn_8013C418(const Vec3*, const Vec3*, const Vec3*, Vec3*);
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern void fn_80211A6C();
extern void fn_80211A90(Vec3*, const Vec3*, float);
extern float fn_80211B08(const Vec3*);
extern float fn_800ED720(float);

int fn_8013EB90(const Shape* shape, const Vec3* point, Result* out,
                float extra, float vertical_extra)
{
    Vec3 closest;
    Vec3 first = shape->first;
    Vec3 second = shape->second;
    Vec3 line_dir, projected;
    float outer = extra + shape->radius;
    float outer2 = outer * outer;
    float distance2;
    float amount;

    first.z = point->z;
    second.z = point->z;
    fn_8013C264(&first, &second, &line_dir, point, &closest);
    distance2 = fn_80211D4C(&closest, point);
    if (!(distance2 < outer2))
        goto fail;
    amount = fn_8013C418(&closest, &shape->first, &shape->axis, &projected);
    if (amount < lbl_80650350)
        closest = shape->first;
    else if (amount > shape->limit)
        closest = shape->second;
    else
        closest = projected;
    if (!(point->z + vertical_extra > closest.z) ||
        !(point->z < closest.z + shape->height))
        goto fail;
    if (fn_80211D4C(&first, point) < outer2 - lbl_8065039C) {
        Vec3 delta;
        float length;
        fn_80211A6C(&shape->first, point, &delta);
        delta.z = lbl_80650350;
        length = fn_80211B08(&delta);
        if (lbl_80650350 != length)
            fn_80211A90(&delta, &delta, lbl_80650378 / length);
        else {
            delta.x = lbl_80650378;
            delta.y = lbl_80650350;
            delta.z = lbl_80650350;
        }
        out->normal.x = point->x + extra * delta.x;
        out->normal.y = point->y + extra * delta.y;
        out->normal.z = point->z;
        out->point.x = point->x + outer * delta.x;
        out->point.y = point->y + outer * delta.y;
        out->point.z = point->z;
        goto success;
    }
    if (lbl_80650350 != distance2) {
        Vec3 projected2;
        Vec3 delta;
        float shift;
        fn_8013C418(point, &first, &line_dir, &projected2);
        shift = fn_800ED720(outer2 - fn_80211D4C(point, &projected2));
        out->point.x = projected2.x - shift * line_dir.x;
        out->point.y = projected2.y - shift * line_dir.y;
        out->point.z = projected2.z - shift * line_dir.z;
        fn_80211A6C(point, &out->point, &delta);
        fn_80211A90(&delta, &delta, lbl_80650378 / outer);
        out->normal.x = out->point.x + shape->radius * delta.x;
        out->normal.y = out->point.y + shape->radius * delta.y;
        out->normal.z = out->point.z + shape->radius * delta.z;
    } else {
        out->normal.x = point->x - extra * line_dir.x;
        out->normal.y = point->y - extra * line_dir.y;
        out->normal.z = point->z;
        out->point.x = out->normal.x - shape->radius * line_dir.x;
        out->point.y = out->normal.y - shape->radius * line_dir.y;
        out->point.z = out->normal.z;
    }
success:
    return 1;
fail:
    return 0;
}
