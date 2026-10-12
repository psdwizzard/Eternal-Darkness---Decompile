typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef float Matrix34[3][4];

typedef struct MotionState {
    Vec3 position;
    u8 pad0C[0x34];
    int active;
    u8 pad44[0x20];
    float plane;
    u8 pad68[0x20];
} MotionState;

typedef struct Entry {
    u8 data[0x14];
} Entry;

extern float lbl_80651464;
extern float lbl_80651478;
extern float lbl_806514A4;

extern int fn_8013BAAC(void*, void*, float);
extern void fn_801F8620(void);
extern int fn_801F85A4(void);
extern int fn_801FA198(void*, MotionState*, int, int, int, int, int, int, void*);
extern void fn_8011F114(Vec3*, void*);
extern void* fn_8011FE34(void*);
extern void fn_801F9AF8(MotionState*, int, Vec3*);
extern void fn_802114E0(Matrix34, void*);
extern void fn_80211710(Matrix34, Vec3*, Vec3*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern int fn_801FA410(int);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};
static MotionState current_second = {0};
static Entry entries[5] = {0};

int fn_801F8748(void* arg0, void* arg1, int arg2, int arg3, int check)
{
    Matrix34 object_transform;
    Vec3 object_copy;
    Vec3 first_offset;
    Vec3 second_offset;
    Vec3 ray;
    Vec3 normal;
    Vec3 object_position;
    MotionState* second_state;
    MotionState* state;
    float plane;
    int allowed = 1;
    void* transform_resource;

    if (check && fn_8013BAAC(arg0, arg1, lbl_806514A4)) {
        allowed = 0;
    }
    if (allowed) {
        fn_801F8620();
        second_state = &second[3];
        if (fn_801FA198(arg0, second_state, 0, 0, arg3, 1, 0, 0, arg1)) {
            fn_8011F114(&object_position, arg1);
            object_copy = object_position;
            transform_resource = fn_8011FE34(arg1);
            fn_801F9AF8(second_state, arg2, &first_offset);
            state = &first[3];
            fn_801F9AF8(state, arg2, &second_offset);
            fn_802114E0(object_transform, transform_resource);
            fn_80211710(object_transform, &first_offset, &first_offset);
            fn_80211710(object_transform, &second_offset, &second_offset);
            fn_80211A6C(&second_offset, &first_offset, &ray);

            second[3].position.x = first_offset.x + object_copy.x;
            second[3].position.y = first_offset.y + object_copy.y;
            second[3].position.z = first_offset.z + object_copy.z;
            first[3].position.x = second_offset.x + object_copy.x;
            first[3].position.y = second_offset.y + object_copy.y;
            first[3].position.z = second_offset.z + object_copy.z;

            ray.z = lbl_80651464;
            fn_80211A90(&ray, &ray, lbl_80651478 / fn_80211B08(&ray));
            fn_80211A6C(&current_first.position, &current_second.position, &normal);
            normal.z = lbl_80651464;
            fn_80211A90(&normal, &normal, lbl_80651478 / fn_80211B08(&normal));
            plane = normal.x * ray.x + normal.y * ray.y;
            second[3].plane = -plane;
            first[3].plane = -plane;
            fn_801FA410(3);
            current_first.active = 1;
            current_second.active = 1;
            return 1;
        }
        fn_801F85A4();
    }
    return 0;
}
