typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MotionState {
    u8 pad00[0x60];
    void* resource_handle;
    u8 pad64[0x10];
    struct MotionState* child;
} MotionState;

typedef struct ResourceState {
    u8 pad00[0xA2];
    u16 count;
    void* first_resources;
    u8 padA8[4];
    void* second_resources;
    u8 padB0[0x8092];
    signed char ready_a;
    signed char ready_b;
} ResourceState;

extern ResourceState* fn_8015C28C(int);
extern void fn_8011F950(void*);
extern void* fn_8011F9E4(void*, int);
extern int fn_8011FA40(void*);
extern void* fn_8011FA4C(void*, int);
extern void fn_801F7034(MotionState*, int);
extern void fn_801F9CF4(MotionState*, int, int, int, int, int, void*);
extern void fn_80088F4C(void);
extern u8 lbl_8063D378[];

void fn_801FA01C(MotionState* state, int resource_index, int parent_mode,
                 int child_mode, int endpoint, int reverse, int set_global,
                 int clear_existing, void* resource_handle, int finalize)
{
    ResourceState* resource_state = fn_8015C28C(2);
    void* first_resources;
    void* second_resources;
    int count;

    if (resource_index >= 0) {
        if (resource_handle != 0) {
            fn_8011F950(resource_handle);
            first_resources = fn_8011F9E4(resource_handle, 0);
            second_resources = fn_8011FA4C(resource_handle, 0);
            count = fn_8011FA40(resource_handle);
        } else if (resource_state->ready_a != 0 &&
                   resource_state->ready_b != 0) {
            first_resources = resource_state->first_resources;
            second_resources = resource_state->second_resources;
            count = resource_state->count;
        }

        if (first_resources != 0 && second_resources != 0 &&
            resource_index < count) {
            if (clear_existing != 0) {
                fn_801F7034(state, 0);
                fn_801F7034(state->child, 0);
            }

            fn_801F9CF4(state->child, resource_index, endpoint, reverse,
                        parent_mode, 0, second_resources);
            fn_801F9CF4(state, resource_index, endpoint, reverse, 0,
                        child_mode, first_resources);
            state->resource_handle = resource_handle;
            state->child->resource_handle = resource_handle;

            if (set_global == 0) {
                *(int*)(lbl_8063D378 + 0x40) = 1;
            }
            if (finalize != 0 || set_global == 0) {
                fn_80088F4C();
            }
        }
    }
}
