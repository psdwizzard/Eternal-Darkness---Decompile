typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Surface {
    Vec3 point;
    float pad0C;
    float pad10;
    Vec3 normal;
    float extent;
} Surface;
typedef struct Result { Vec3 normal; Vec3 point; } Result;

extern float lbl_80650350, lbl_8065039C;
extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern void PSVECSubtract();
extern void PSVECNormalize(Vec3*, const Vec3*);
extern int fn_8013D560(Vec3*, const Surface*, const void*);
extern void fn_8013C068(Vec3*, const Surface*, const void*, Vec3*);

int fn_8013F078(const Vec3* point, const Surface* surface, const void* bounds,
                Result* out, float extra)
{
    Vec3 temp, closest, contact, delta;
    float plane = -PSVECDotProduct(point, &surface->normal);
    plane = surface->extent - plane;

    if (plane >= lbl_80650350 && plane <= lbl_8065039C + extra) {
        contact.x = point->x - plane * surface->normal.x;
        contact.y = point->y - plane * surface->normal.y;
        contact.z = point->z - plane * surface->normal.z;
        if (fn_8013D560(&contact, surface, bounds)) {
            out->normal = contact;
            out->point.x = contact.x + extra * surface->normal.x;
            out->point.y = contact.y + extra * surface->normal.y;
            out->point.z = contact.z + extra * surface->normal.z;
            return 1;
        }
        temp = contact;
        fn_8013C068(&temp, surface, bounds, &closest);
        if (PSVECSquareDistance(&closest, point) < extra * extra) {
            PSVECSubtract(point, &closest, &delta);
            PSVECNormalize(&delta, &delta);
            out->normal = closest;
            out->point.x = closest.x + extra * delta.x;
            out->point.y = closest.y + extra * delta.y;
            out->point.z = closest.z + extra * delta.z;
            return 1;
        }
    }
    return 0;
}
