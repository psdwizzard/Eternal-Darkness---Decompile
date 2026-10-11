typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ActorState {
    u8 pad_00[0xC4];
    u32 effect;
    u8 pad_C8[0x197];
    u8 above;
} ActorState;

extern int fn_80201B54(void *object);
extern void fn_80201E78(void *destination, void *object);
extern int fn_80204508(void *object, void *other);
extern u64 fn_8020123C(int kind, int source, int target, int data);
extern void *fn_801A717C(void);
extern void fn_801A7228(void *event);
extern void fn_801A74D8(void *event, u32 flags);
extern void fn_801A74A0(void *event, u32 source);
extern void fn_801A7538(void *event, u16 value);
extern void fn_801A7518(void *event, s16 value);
extern void fn_801A7588(void *event, u32 flags);
extern void fn_801A764C(void *event, const Vec3 *position);
extern void fn_801A7470(void *event, u32 kind);
extern float lbl_8064F3B0;

int fn_800D39D0(ActorState *state, void *source, void *target, int enabled)
{
    Vec3 target_position;
    Vec3 source_position;
    Vec3 position;
    Vec3 temporary;
    register int result = 0;
    register int above;
    register int source_id;
    register int target_id;
    register void *event;
    register u32 effect;

    /* ASM: lwz keeps the state load after register initialization; C hoists it. */
    asm { lwz effect, 0xC4(r3) }
    if (effect != 0) {
        above = 0;
        source_id = fn_80201B54(source);
        target_id = fn_80201B54(target);
        fn_80201E78(&target_position, target);
        fn_80201E78(&source_position, source);
        if (target_position.y > source_position.y) {
            target_position.y = source_position.y - lbl_8064F3B0;
            fn_8020123C(0x9D, source_id, target_id, (int)&target_position);
            above = 1;
        }
        if (enabled && !above && state->above) {
            fn_80201E78(&temporary, target);
            position = temporary;
            event = fn_801A717C();
            fn_801A74D8(event, 0x100);
            fn_801A74A0(event, source_id);
            fn_801A7538(event, 5);
            fn_801A7518(event, 3);
            fn_801A7588(event, 0x8000);
            fn_801A764C(event, &position);
            if ((u8)fn_80204508(target, source)) {
                fn_801A7470(event, 12);
            } else {
                fn_801A7470(event, 11);
            }
            fn_8020123C(0x27, source_id, target_id, (int)event);
            fn_801A7228(event);
            result = 1;
        }
        state->above = above;
    }
    return result;
}
