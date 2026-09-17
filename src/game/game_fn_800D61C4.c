typedef unsigned int u32;

typedef struct Actor {
    unsigned char pad_000[0x24c];
    void *slots[4];
    signed char field_25c;
    signed char slot_index;
} Actor;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned long long fn_8020123C();
extern void* fn_80201B3C();
extern Vec3 fn_80201E78(void *);
extern int fn_801AC9F4(int, int, Vec3 *, int);

int fn_800D61C4(Actor *actor, void *object)
{
    int result = 0;

    while ((unsigned int)actor->slot_index < 4) {
        void *slot = actor->slots[actor->slot_index];
        actor->slot_index++;
        if ((int)slot != 0) {
            if ((u32)(fn_8020123C(0x91, object, slot, 0) & 0xFFFFFFFFULL)) {
                void *source = fn_80201B3C();
                Vec3 position = fn_80201E78(source);
                fn_801AC9F4(0x2b8, 100, &position, 2);
                result = 1;
                break;
            }
        }
    }
    return result;
}
