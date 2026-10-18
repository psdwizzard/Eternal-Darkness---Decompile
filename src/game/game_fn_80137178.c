typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Segment { Vec3 start; Vec3 end; } Segment;
typedef struct Shape Shape;
typedef struct Input { Vec3 first; Vec3 second; float value; } Input;
typedef struct Collection Collection;
typedef struct CollisionEntry {
    unsigned int condition;
    unsigned char obstacle_index;
    unsigned char flags;
} CollisionEntry;
typedef struct CollisionWorld CollisionWorld;
typedef struct Obstacle { unsigned short id; } Obstacle;

extern Shape* fn_8013F980(Collection*, const Input*, Result*);
extern const CollisionEntry* fn_80137578(void*, const Shape*, const CollisionWorld*, Result*);
extern int fn_801439E0(void*, Segment*, void*, unsigned int);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern float lbl_806502A0;

Obstacle* fn_80137178(void* object, const CollisionWorld* world,
                     const Shape* shape, Result* result, unsigned int flags)
{
    Result entryResult;
    Result surfaceResult;
    union { Segment segment; Result result; } portalResult;
    float distance;
    float best = lbl_806502A0;
    Shape* surface;
    Obstacle* portal;
    signed char selected;
    const CollisionEntry* entry;

    portal = 0;
    selected = 0;

    surface = fn_8013F980((Collection*)((char*)world + 0x20),
                         (const Input*)shape, &surfaceResult);
    entry = fn_80137578(object, shape,
                       (const CollisionWorld*)((char*)world + 0xA0), &entryResult);
    if (flags & 1) {
        /* This callee's int result carries the 32-bit surface address. */
        portal = (Obstacle*)fn_801439E0((void*)shape, &portalResult.segment, object, flags);
    }
    if (surface != 0) {
        best = PSVECSquareDistance((const Vec3*)shape, &surfaceResult.normal);
        selected = 1;
    }
    if (entry != 0) {
        distance = PSVECSquareDistance((const Vec3*)shape, &entryResult.normal);
        if (distance < best) {
            best = distance;
            selected = 2;
        }
    }
    if (portal != 0) {
        if (PSVECSquareDistance((const Vec3*)shape, &portalResult.result.normal) < best) {
            selected = 3;
        }
    }
    if (selected == 1) {
        *result = surfaceResult;
        return (Obstacle*)surface;
    } else if (selected == 2) {
        *result = entryResult;
        return (Obstacle*)(*(char**)((char*)world + 0xE4) + entry->obstacle_index * 0x38);
    } else if (selected == 3) {
        *result = portalResult.result;
        return portal;
    }
    return 0;
}
