/* The loop and result copy match retail. The fixed compiler settings
 * emit GPR save/restore helpers instead of retail stmw/lmw instructions. */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct CollisionWorld CollisionWorld;
typedef struct Obstacle {
    unsigned short id;
} Obstacle;
typedef struct Object80201EB8 Object80201EB8;
typedef struct Object80201CDC Object80201CDC;

extern Obstacle* fn_80137178(void* object, const CollisionWorld* world,
                           const Shape* shape, Result* result,
                           unsigned int flags);
extern unsigned int fn_8011FAEC(void* object);
extern int fn_80136FF8(const void* shape, void* object, Result* result);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void* node);
extern void* fn_80201BC8(void* node);
extern void* fn_80201B94(unsigned char* node);
extern unsigned int fn_80201CDC(Object80201CDC* node);
extern int fn_80201EB8(Object80201EB8* node);
extern float PSVECSquareDistance(const Vec3* a, const Vec3* b);
extern int lbl_8064D18C;
extern float lbl_806502A0;

int fn_80137350(void* object, const Shape* shape,
                const CollisionWorld* world, Result* result,
                unsigned int flags, unsigned short* obstacle_id)
{
    Result candidate;
    float best;
    int found;
    Obstacle* obstacle;
    void* node;
    void* other;

    *obstacle_id = 0;
    best = lbl_806502A0;
    found = 0;
    obstacle = fn_80137178(object, world, shape, result, flags);
    if (obstacle != 0) {
        found = 1;
        *obstacle_id = obstacle->id;
        best = PSVECSquareDistance(&shape->first, &result->point);
    }
    if (flags & 2) {
        node = fn_80201B9C();
        while (node != 0) {
            other = fn_80201BC8(node);
            if (lbl_8064D18C == fn_80201EB8(node) &&
                other != 0 && other != object &&
                fn_80201B94(node) != 0 &&
                (fn_8011FAEC(other) & 0x80) &&
                (fn_80201CDC(node) & 4) &&
                fn_80136FF8(shape, other, &candidate) != 0) {
                float distance = PSVECSquareDistance(&shape->first, &candidate.point);
                found = 1;
                if (distance < best) {
                    best = distance;
                    *obstacle_id = 0;
                    *result = candidate;
                }
            }
            node = fn_80201BC0(node);
        }
    }
    return found;
}
