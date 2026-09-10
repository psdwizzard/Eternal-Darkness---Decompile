typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Target Target;
typedef struct Voice Voice;

struct Target {
    Target* next;
    u32 pad04;
    u32 flags;
    char pad0C[0x20];
    void* object;
};

struct Voice {
    Voice* previous;
    Voice* next;
    Target* target;
    u32 pad0C;
    Vec3 position;
    u32 pad1C;
    Vec3 velocity;
    Vec3 direction;
    Vec3 up;
    Vec3 right;
    float matrix[15];
    float level;
};

extern u8 lbl_8064D3A0;
extern Voice* lbl_8064D4C0;
extern double lbl_80650FB8;
extern float lbl_80650FD0;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern void fn_801CA538(Vec3*, Vec3*, Vec3*);
extern void fn_801CA59C(float*, float*);

static inline void ReleaseTarget(Target* target)
{
    u32 count = 0;
    Voice* cursor = lbl_8064D4C0;
    while (cursor != 0) {
        if (cursor->target == target) {
            count++;
        }
        cursor = cursor->previous;
    }
    if (count == 1) {
        target->flags &= 0x7FFFFFFF;
        target->flags |= 0x40000000;
    }
}

int fn_801C9510(Voice* voice, Vec3* position, Vec3* velocity, Vec3* direction,
                Vec3* up, u8 level, Target* target)
{
    float transform[12];

    if (lbl_8064D3A0 != 0) {
        fn_801CE2B8();
        voice->position = *position;
        voice->velocity = *velocity;
        voice->direction = *direction;
        voice->right = *up;
        fn_801CA538(&voice->up, &voice->direction, &voice->right);

        transform[0] = voice->up.x;
        transform[3] = voice->up.y;
        transform[6] = voice->up.z;
        transform[1] = voice->right.x;
        transform[4] = voice->right.y;
        transform[7] = voice->right.z;
        transform[2] = -voice->direction.x;
        transform[5] = -voice->direction.y;
        transform[8] = -voice->direction.z;
        transform[9] = voice->position.x;
        transform[10] = voice->position.y;
        transform[11] = voice->position.z;
        fn_801CA59C(voice->matrix, transform);
        voice->level = (float)level / lbl_80650FD0;

        if (target != voice->target) {
            if (voice->target != 0) {
                ReleaseTarget(voice->target);
            }
            voice->target = target;
            if (target != 0) {
                Target* current = voice->target;
                if ((current->flags & 0x80000000) == 0 && current->object == 0) {
                    current->flags |= 0x80000000;
                }
            }
        }
        fn_801CE280();
        return 1;
    }
    return 0;
}
