typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* PSMTXQuat writes all 12 entries; PSMTXMultVec transforms a Vec3. */
typedef float Matrix34[3][4];

typedef struct StatePart {
    unsigned char pad000[0x198];
    Vec3 position;
    unsigned char pad1A4[0x58];
    float plane;
    unsigned char pad200[0x460];
} StatePart;

typedef struct GlobalState {
    StatePart first;
    StatePart second;
    Vec3 ray_a;
    unsigned char padCCC[0x34];
    int ray_a_active;
    unsigned char padD04[0x44];
    Vec3 ray_b;
    unsigned char padD54[0x34];
    int ray_b_active;
} GlobalState;

extern GlobalState lbl_8063C6B8;
extern float lbl_80651464;
extern float lbl_80651478;
extern float lbl_806514A4;

extern int fn_8013BAAC(float);
extern void fn_801F8620(void);
extern int fn_801F85A4(void);
extern int fn_801FA198(void*, void*, int, int, void*, int, int, int, int);
extern void fn_8011F114(Vec3*, void*);
extern void* fn_8011FE34(void*);
extern void fn_801F9AF8(void*, void*, Vec3*);
extern void PSMTXQuat(Matrix34, void*);
extern void PSMTXMultVec(Matrix34, Vec3*, Vec3*);
extern void PSVECSubtract(Vec3*, Vec3*, Vec3*);
extern float PSVECMag(Vec3*);
extern void PSVECScale(Vec3*, Vec3*, float);
extern void fn_801FA410(int);

#pragma opt_lifetimes off
int fn_801F8748(void* arg0, void* arg1, void* arg2, void* arg3, int check)
{
    GlobalState* g = &lbl_8063C6B8;
    Matrix34 object_transform;
    Vec3 object_copy;
    Vec3 first_offset;
    Vec3 second_offset;
    Vec3 ray;
    Vec3 normal;
    Vec3 object_position;
    Vec3* second_position;
    Vec3* position;
    StatePart* second_base;
    StatePart* base;
    float plane;
    int allowed = 1;

    if (check && fn_8013BAAC(lbl_806514A4)) {
        allowed = 0;
    }
    if (!allowed) {
        goto return_false;
    }

    fn_801F8620();
    second_position = &g->second.position;
    if (!fn_801FA198(arg0, second_position, 0, 0, arg3, 1, 0, 0, (int)arg1)) {
        goto failed;
    }

    fn_8011F114(&object_position, arg1);
    object_copy = object_position;
    arg3 = fn_8011FE34(arg1);
    fn_801F9AF8(second_position, arg2, &first_offset);
    position = &g->first.position;
    fn_801F9AF8(position, arg2, &second_offset);
    PSMTXQuat(object_transform, arg3);
    PSMTXMultVec(object_transform, &first_offset, &first_offset);
    PSMTXMultVec(object_transform, &second_offset, &second_offset);
    PSVECSubtract(&second_offset, &first_offset, &ray);

    second_base = &g->second;
    base = &g->first;
    second_position->x = first_offset.x + object_copy.x;
    second_base->position.y = first_offset.y + object_copy.y;
    second_base->position.z = first_offset.z + object_copy.z;
    position->x = second_offset.x + object_copy.x;
    base->position.y = second_offset.y + object_copy.y;
    base->position.z = second_offset.z + object_copy.z;

    ray.z = lbl_80651464;
    PSVECScale(&ray, &ray, lbl_80651478 / PSVECMag(&ray));
    PSVECSubtract(&g->ray_a, &g->ray_b, &normal);
    normal.z = lbl_80651464;
    PSVECScale(&normal, &normal, lbl_80651478 / PSVECMag(&normal));
    plane = normal.x * ray.x + normal.y * ray.y;
    g->second.plane = -plane;
    g->first.plane = -plane;
    fn_801FA410(3);
    g->ray_a_active = 1;
    g->ray_b_active = 1;
    return 1;

failed:
    fn_801F85A4();
return_false:
    return 0;
}
#pragma opt_lifetimes reset
