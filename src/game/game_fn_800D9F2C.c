typedef unsigned char u8;

typedef struct Vec {
    float x;
    float y;
    float z;
} Vec;

typedef struct Actor {
    u8 pad0[0x68];
    void *effect;
} Actor;

extern float lbl_8064F440;
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void fn_8011F114();
extern void fn_800CA530(void);
extern void *fn_801D0814(int, int, int, Vec *, int, int, void (*)(void), int,
                         Vec *);

int fn_800D9F2C(void *transform, register void *object)
{
    register unsigned long object_r = (unsigned long)object;
    int owner;
    Actor *actor;
    Vec result;
    Vec position;

    owner = fn_80201B54((void *)object_r);
    actor = *(Actor **)((u8 *)fn_80201B8C((void *)object_r) + 0x64);
    fn_8011F114(&position, transform);
    position.z += lbl_8064F440;
    actor->effect = fn_801D0814(0x11044, 0, owner, &result, 0, 0,
                                fn_800CA530, (owner << 8) | 0x78, &position);
    return 1;
}
