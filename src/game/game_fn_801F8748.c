typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct GlobalState {
    unsigned char pad000[0x198];
    Vec3 position;
    unsigned char pad1A4[0x58];
    float plane;
    unsigned char pad200[0x460];
    unsigned char second[0x198];
    Vec3 second_position;
    unsigned char pad800[0x4BC];
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
extern void fn_802114E0(Vec3*, void*);
extern void fn_80211710(Vec3*, Vec3*, Vec3*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern void fn_801FA410(int);

int fn_801F8748(void* arg0, void* arg1, void* arg2, void* arg3, int unused0,
                int unused1, int check)
{
    GlobalState* g = &lbl_8063C6B8;
    Vec3 object_position;
    Vec3 first_offset;
    Vec3 second_offset;
    Vec3 normal;
    Vec3 ray;
    Vec3 object_copy;
    void* object;
    int allowed = 1;

    if (check && fn_8013BAAC(lbl_806514A4)) {
        allowed = 0;
    }
    if (!allowed) {
        return 0;
    }

    fn_801F8620();
    if (!fn_801FA198(arg0, &g->second[0x198], 0, 0, arg3, 1, 0, 0, (int)arg1)) {
        fn_801F85A4();
        return 0;
    }

    fn_8011F114(&object_position, arg1);
    object_copy = object_position;
    object = fn_8011FE34(arg1);
    fn_801F9AF8(&g->second[0x198], arg2, &first_offset);
    fn_801F9AF8(&g->position, arg2, &second_offset);
    fn_802114E0(&normal, object);
    fn_80211710(&normal, &first_offset, &first_offset);
    fn_80211710(&normal, &second_offset, &second_offset);
    fn_80211A6C(&second_offset, &first_offset, &ray);

    g->second_position.x = first_offset.x + object_copy.x;
    g->second_position.y = first_offset.y + object_copy.y;
    g->second_position.z = first_offset.z + object_copy.z;
    g->position.x = second_offset.x + object_copy.x;
    g->position.y = second_offset.y + object_copy.y;
    g->position.z = second_offset.z + object_copy.z;

    ray.z = lbl_80651464;
    fn_80211A90(&ray, &ray, lbl_80651478 / fn_80211B08(&ray));
    fn_80211A6C(&g->ray_a, &g->ray_b, &normal);
    normal.z = lbl_80651464;
    fn_80211A90(&normal, &normal, lbl_80651478 / fn_80211B08(&normal));
    g->plane = -(normal.y * ray.y + normal.x * ray.x);
    ((float*)g->second)[0x7F] = g->plane;
    fn_801FA410(3);
    g->ray_a_active = 1;
    g->ray_b_active = 1;
    return 1;
}
