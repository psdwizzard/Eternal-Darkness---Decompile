typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Shape {
    Vec3 point;
    unsigned char pad0C[0xC];
    float radius;
    Vec3 axis;
    float tolerance;
    Vec3 bound;
    float bound_radius;
} Shape;
typedef struct Obstacle {
    unsigned char pad00[4];
    Vec3 bound;
    float tolerance;
    Vec3 axis;
    float distance;
} Obstacle;

extern float lbl_80650350, lbl_80650380, lbl_80650384, lbl_80650388;
extern float lbl_8065038C, lbl_80650390, lbl_80650394, lbl_80650398;
extern float fn_80211B44(const Vec3*, const Vec3*);
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern float fn_8013C068(const Vec3*, const Obstacle*, const void*, Vec3*);
extern int fn_8013D560(const Vec3*, const Obstacle*, const void*);
extern int fn_8013DE44(const Vec3*, const Vec3*, const Vec3*, float,
                       float*, unsigned char);

int fn_8013E284(const Shape* shape, const Obstacle* obstacle,
                const void* context, Result* out)
{
    float hit;
    Vec3 start;
    Vec3 work;
    Vec3 reverse;
    Vec3 contact;
    float plane = -fn_80211B44(&shape->point, &obstacle->axis);
    float along;

    plane = obstacle->distance - plane;
    if (!(plane >= lbl_80650380))
        goto no_hit;
    along = fn_80211B44(&shape->axis, &obstacle->axis);
    if (along >= lbl_80650384 && along <= lbl_80650388) {
        if (!(plane <= shape->radius - lbl_8065038C))
            goto no_hit;
    }
    if (fn_80211D4C(&shape->bound, &obstacle->bound) >
        (shape->bound_radius + obstacle->tolerance) *
        (shape->bound_radius + obstacle->tolerance))
        return 0;
    reverse.x = -shape->axis.x;
    reverse.y = -shape->axis.y;
    reverse.z = -shape->axis.z;
    if (plane <= lbl_80650390 + shape->radius) {
        contact.x = shape->point.x - plane * obstacle->axis.x;
        contact.y = shape->point.y - plane * obstacle->axis.y;
        contact.z = shape->point.z - plane * obstacle->axis.z;
        if (fn_8013D560(&contact, obstacle, context)) {
            out->normal = contact;
            out->point.x = contact.x + shape->radius * obstacle->axis.x;
            out->point.y = contact.y + shape->radius * obstacle->axis.y;
            out->point.z = contact.z + shape->radius * obstacle->axis.z;
            return 1;
        }
        start = contact;
        fn_8013C068(&start, obstacle, context, &work);
        if (fn_8013DE44(&work, &reverse, &shape->point, shape->radius,
                        &hit, 1) && hit < lbl_80650350 &&
            hit > -(lbl_80650394 + shape->tolerance)) {
            out->normal = work;
            out->point.x = shape->point.x + hit * shape->axis.x;
            out->point.y = shape->point.y + hit * shape->axis.y;
            out->point.z = shape->point.z + hit * shape->axis.z;
            return 1;
        }
    } else {
        float distance = (shape->radius - plane) / along;
        float x;
        float y;
        float z;

        if (distance <= shape->tolerance && distance >= lbl_80650350) {
            out->point.x = shape->point.x + distance * shape->axis.x;
            out->point.y = shape->point.y + distance * shape->axis.y;
            out->point.z = shape->point.z + distance * shape->axis.z;
            out->normal.x = out->point.x - shape->radius * obstacle->axis.x;
            out->normal.y = out->point.y - shape->radius * obstacle->axis.y;
            out->normal.z = out->point.z - shape->radius * obstacle->axis.z;
            if (fn_8013D560(&out->normal, obstacle, context))
                return 1;
        }
        x = shape->point.x - shape->radius * obstacle->axis.x;
        y = shape->point.y - shape->radius * obstacle->axis.y;
        z = shape->point.z - shape->radius * obstacle->axis.z;
        distance = (plane - shape->radius) / -along;
        start.x = x + distance * shape->axis.x;
        start.y = y + distance * shape->axis.y;
        start.z = z + distance * shape->axis.z;
    }

    if (fn_8013C068(&start, obstacle, context, &work) <=
        shape->radius * shape->radius) {
        if (fn_8013DE44(&work, &reverse, (const Vec3*)shape, shape->radius,
                        &hit, 0) && hit >= lbl_80650398 &&
            hit <= shape->tolerance) {
            out->normal = work;
            out->point.x = shape->point.x + hit * shape->axis.x;
            out->point.y = shape->point.y + hit * shape->axis.y;
            out->point.z = shape->point.z + hit * shape->axis.z;
            return 1;
        }
    }
no_hit:
    return 0;
}
