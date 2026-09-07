typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Capsule {
    Vec3 point;
    Vec3 other;
    float radius;
    Vec3 axis;
    float limit;
    Vec3 bound;
    float bound_radius;
} Capsule;
typedef struct Result { Vec3 normal; Vec3 point; } Result;

extern float lbl_80650350, lbl_80650378, lbl_8065039C;
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern void fn_80211A6C();
extern void fn_80211A90(Vec3*, const Vec3*, float);
extern float fn_800ED720(float);
extern void fn_8013C35C(const Vec3*, const Vec3*, const Vec3*,
                        const Vec3*, Vec3*, float);
extern float fn_8013C418(const Vec3*, const Vec3*, const Vec3*, Vec3*);

int fn_8013E714(const Capsule* shape, const Vec3* point, Result* out,
                float extra)
{
    Vec3 closest;
    float outer;
    float outer2;
    float distance2, center2;

    if (fn_80211D4C(&shape->bound, point) <=
        (shape->bound_radius + extra) * (shape->bound_radius + extra)) {
        outer = extra + shape->radius;
        outer2 = outer * outer;
        fn_8013C35C(&shape->point, &shape->other, &shape->axis,
                    point, &closest, shape->limit);
        distance2 = fn_80211D4C(&closest, point);
        if (distance2 < outer2) {
            center2 = fn_80211D4C(&shape->point, point);
            if (center2 <= lbl_8065039C + outer2) {
                Vec3 delta;
                fn_80211A6C(&shape->point, point, &delta);
                if (lbl_80650350 != center2)
                    fn_80211A90(&delta, &delta, lbl_80650378 / fn_800ED720(center2));
                else {
                    delta.x = lbl_80650378;
                    delta.y = lbl_80650350;
                    delta.z = lbl_80650350;
                }
                out->normal.x = point->x + extra * delta.x;
                out->normal.y = point->y + extra * delta.y;
                out->normal.z = point->z + extra * delta.z;
                out->point.x = point->x + outer * delta.x;
                out->point.y = point->y + outer * delta.y;
                out->point.z = point->z + outer * delta.z;
                return 1;
            }
            if (lbl_80650350 == distance2) {
                out->normal.x = point->x - extra * shape->axis.x;
                out->normal.y = point->y - extra * shape->axis.y;
                out->normal.z = point->z - extra * shape->axis.z;
                out->point.x = point->x - outer * shape->axis.x;
                out->point.y = point->y - outer * shape->axis.y;
                out->point.z = point->z - outer * shape->axis.z;
                return 1;
            }
            {
                Vec3 projected;
                Vec3 delta;
                float sign;

                sign = fn_8013C418(point, &shape->point, &shape->axis, &projected);
                distance2 = fn_800ED720(outer2 - fn_80211D4C(point, &projected));
                if (sign < lbl_80650350) {
                    out->point.x = projected.x + distance2 * shape->axis.x;
                    out->point.y = projected.y + distance2 * shape->axis.y;
                    out->point.z = projected.z + distance2 * shape->axis.z;
                } else {
                    out->point.x = projected.x - distance2 * shape->axis.x;
                    out->point.y = projected.y - distance2 * shape->axis.y;
                    out->point.z = projected.z - distance2 * shape->axis.z;
                }
                fn_80211A6C(point, &out->point, &delta);
                fn_80211A90(&delta, &delta, lbl_80650378 / outer);
                out->normal.x = out->point.x + shape->radius * delta.x;
                out->normal.y = out->point.y + shape->radius * delta.y;
                out->normal.z = out->point.z + shape->radius * delta.z;
                return 1;
            }
        }
    }
    return 0;
}
