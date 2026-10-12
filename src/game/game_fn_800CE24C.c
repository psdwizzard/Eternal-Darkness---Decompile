typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object Object;
typedef struct Vec8012B8A8 {
    float x, y, z;
} Position;
typedef struct Vec3 {
    u32 x, y, z;
} PositionBits;

extern int fn_80130108(Object* object);
extern u8 fn_801303BC(Object* object);
extern int fn_80130148(Object* object);
extern u8 fn_8012B8A8(void* owner, const Position* position);
extern void* fn_801300F0(Object* object);
extern u32 fn_80178E94(const float* first, const float* second);
extern int fn_8012FF34(Object* object, volatile PositionBits* position, int flags, int index);
extern int fn_8012FFE0(Object* object, int flags, u8 index);
extern void fn_801302BC(Object* object, int state);

int fn_800CE24C(Object* object, const Position* position, int state,
                u32 minimum_distance, int maximum_state)
{
    int active;
    int replace_active;
    /* Retail assigns this result only after the position test succeeds. */
    int use_position;
    int lower_priority;
    u8 index;
    int can_replace;
    int state_matches;

    lower_priority = 0;
    active = fn_80130108(object);
    if (active) {
        index = fn_801303BC(object);
        if (index < 4U) {
            lower_priority = 1;
        }
    }
    replace_active = 0;
    can_replace = active && !lower_priority;
    if (can_replace) {
        state_matches = fn_80130148(object) <= maximum_state && index == 4;
        if (state_matches) {
            replace_active = 1;
        }
    }
    if ((!active || replace_active || lower_priority) && fn_8012B8A8(object, position)) {
        use_position = 1;
        if (replace_active) {
            const float* active_position = fn_801300F0(object);
            if (fn_80178E94((const float*)position, active_position) < minimum_distance) {
                use_position = 0;
            }
        }
        if (use_position) {
            if (fn_8012FF34(object, (volatile PositionBits*)position, 4, 4)) {
                fn_801302BC(object, state);
            }
        } else if (fn_8012FFE0(object, 4, 4)) {
            fn_801302BC(object, state);
        }
    }
    return use_position;
}
