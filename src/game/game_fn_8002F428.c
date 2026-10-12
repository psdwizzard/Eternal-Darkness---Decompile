typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef int s32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Callback { char pad[0x3C]; void* inner; } Callback;
typedef struct State {
    u8 counter;
    s8 direction;
    u8 pad02[6];
    s32 reset;
    u8 pad0C[8];
    s32 owner_id;
    s32 target_id;
    s32 previous_state;
    float rate;
    float velocity;
} State;

extern const float lbl_8064E064;
extern const float lbl_8064E128;
extern const float lbl_8064E12C;
extern const float lbl_8064E130;
extern const float lbl_8064E134;
extern const float lbl_8064E138;
extern s32 lbl_8064D18C;

extern void* fn_80156938(void*);
extern void* fn_80201B8C(void*);
extern int fn_80201B5C(void*);
extern int fn_80201B54(void*);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern void fn_80121104(void*, float);
extern void* fn_8011FB4C(void*);
extern int fn_80201AE4(void);
extern s32 fn_80047178(void);
extern s32 fn_8012FA54(void*, s32);
extern void fn_8012C478(void*, s32, s32);
extern void fn_801499C4(void*, s16*, void*, void*, s32);
extern void fn_8011F114(Vec3*, Vec3*);
extern unsigned int fn_800FBFB0(void);
extern void fn_8011FB54(void*, void*);
extern void fn_8011F0E8(void*, Vec3*);

void fn_8002F428(void* first_arg, void* second_arg)
{
    void* first;
    void* second;
    State* state;
    void* target_actor;
    void* second_actor;
    s32 actor_state;
    s32 axis_flags;
    s32 blocked;
    s16 position[4];
    Vec3 next;
    Vec3 current;
    float current_z;
    float direction_delta;

    state = first_arg;
    if (state == 0)
        return;
    if (second_arg == 0)
        return;
    first = fn_80156938(state);
    second = fn_80156938(second_arg);
    if (first == 0)
        return;
    state = (State*)((Callback*)fn_80201B8C(first))->inner;
    if (state == 0)
        return;
    if (second == 0 || fn_80201B5C(second) == 0x15) {
        s32 id = fn_80201B54(first);
        fn_8020123C(0x5F, id, id, 0);
        return;
    }

    if (lbl_8064E128 != state->velocity) {
        second_actor = fn_80201BC8(second);
        if (second_actor != 0) {
            state->rate += state->velocity;
            if (state->rate > lbl_8064E12C) {
                state->velocity = lbl_8064E130;
                state->rate = lbl_8064E134;
            } else if (state->rate < lbl_8064E064) {
                state->velocity = lbl_8064E128;
                state->rate = lbl_8064E064;
            }
            fn_80121104(second_actor, state->rate);
        }
    }

    if (state->target_id == 0)
        return;
    target_actor = fn_80201814(state->target_id);
    if (target_actor == 0)
        return;
    target_actor = fn_80201BC8(target_actor);
    if (target_actor == 0)
        return;
    second_actor = fn_80201BC8(second);
    if (second_actor == 0)
        return;
    actor_state = (s32)fn_8011FB4C(second_actor);
    if (!(state->owner_id != fn_80201AE4() ||
          (fn_80047178() && fn_8012FA54(second_actor, 0xF))) ||
        actor_state != lbl_8064D18C) {
        fn_8012C478(target_actor, 0xF, 0);
        return;
    }

    fn_8012C478(target_actor, 0xF, 1);
    fn_801499C4(second, position, 0, 0, 0);

    if (state->previous_state == actor_state &&
        actor_state == (s32)fn_8011FB4C(target_actor) && state->reset == 0) {
        axis_flags = 1;
        blocked = 0;
        fn_8011F114(&current, target_actor);

        if ((s16)current.x < position[0]) {
            s32 distance = (s32)((float)position[0] - current.x);
            if (distance > 15)
                next.x = lbl_8064E12C + current.x;
            else if (distance > 4)
                next.x = lbl_8064E138 + current.x;
            else if (fn_800FBFB0() & 1)
                next.x = lbl_8064E064 + current.x;
            else
                next.x = current.x - lbl_8064E064;
        } else if ((s16)current.x > position[0]) {
            s32 distance = (s32)(current.x - (float)position[0]);
            if (distance > 15)
                next.x = current.x - lbl_8064E12C;
            else if (distance > 4)
                next.x = current.x - lbl_8064E138;
            else if (fn_800FBFB0() & 1)
                next.x = lbl_8064E064 + current.x;
            else
                next.x = current.x - lbl_8064E064;
        } else {
            next.x = current.x;
            axis_flags = 7;
        }

        if ((s16)current.y < position[1]) {
            s32 distance = (s32)((float)position[1] - current.y);
            if (distance > 15)
                next.y = lbl_8064E12C + current.y;
            else if (distance > 4)
                next.y = lbl_8064E138 + current.y;
            else if (fn_800FBFB0() & 1)
                next.y = lbl_8064E064 + current.y;
            else
                next.y = current.y - lbl_8064E064;
            axis_flags = 1;
        } else if ((s16)current.y > position[1]) {
            s32 distance = (s32)(current.y - (float)position[1]);
            if (distance > 15)
                next.y = current.y - lbl_8064E12C;
            else if (distance > 4)
                next.y = current.y - lbl_8064E138;
            else if (fn_800FBFB0() & 1)
                next.y = lbl_8064E064 + current.y;
            else
                next.y = current.y - lbl_8064E064;
            axis_flags = 1;
        } else {
            next.y = current.y;
        }

        current_z = current.z;
        if ((s16)current_z < position[2]) {
            if ((s32)((float)position[2] - current_z) > 12) {
                blocked = 1;
                next.z = lbl_8064E12C + current_z;
            }
        } else if ((s16)current_z > position[2]) {
            if ((s32)(current_z - (float)position[2]) > 12) {
                blocked = 1;
                next.z = current_z - lbl_8064E12C;
            }
        }

        if (!blocked) {
            if (!(state->counter & (u8)axis_flags)) {
                direction_delta = (float)state->direction;
                next.z = current_z + direction_delta;
                if (next.z > 10.0f + (float)position[2])
                    state->direction = -1;
                else if (next.z < (float)position[2] - 10.0f)
                    state->direction = 1;
            } else {
                next.z = current_z;
            }
        }
    } else {
        next.x = (float)position[0];
        next.y = (float)position[1];
        next.z = (float)position[2];
        state->counter = 0;
        state->previous_state = actor_state;
        fn_8011FB54(target_actor, (void*)actor_state);
        state->reset = 0;
    }
    state->counter++;
    fn_8011F0E8(target_actor, &next);
}
