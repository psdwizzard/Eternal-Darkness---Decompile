typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target { struct Target* next; u32 pad04; u32 flags; char pad0C[0x20]; void* object; } Target;
typedef struct Voice {
    struct Voice* previous; struct Voice* next; Target* target; void* data;
    Vec3 position; float roll; Vec3 velocity; Vec3 direction; Vec3 up; Vec3 right;
    float matrix[12]; float a; float b; float c; float level;
} Voice;
extern u8 lbl_8064D3A0;
extern Voice* lbl_8064D4C0;
extern float lbl_80650FD0;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern void fn_801CA538(Vec3*, Vec3*, Vec3*);
extern void fn_801CA59C(float*, float*);

int fn_801C970C(Voice* voice, Vec3* position, Vec3* velocity, Vec3* direction,
                float a, float b, float c, float roll, Vec3* up, void* data,
                u8 level, Target* target)
{
    float transform[12];
    if (lbl_8064D3A0 != 0) {
        fn_801CE2B8();
        if ((voice->previous = lbl_8064D4C0) != 0) {
            lbl_8064D4C0->next = voice;
        }
        voice->next = 0;
        lbl_8064D4C0 = voice;
        voice->position = *position;
        voice->velocity = *velocity;
        voice->direction = *direction;
        voice->right = *up;
        voice->a = a;
        voice->b = b;
        voice->c = c;
        voice->roll = roll;
        fn_801CA538(&voice->up, &voice->direction, &voice->right);
        transform[0] = voice->up.x; transform[3] = voice->up.y; transform[6] = voice->up.z;
        transform[1] = voice->right.x; transform[4] = voice->right.y; transform[7] = voice->right.z;
        transform[2] = -voice->direction.x; transform[5] = -voice->direction.y; transform[8] = -voice->direction.z;
        transform[9] = voice->position.x; transform[10] = voice->position.y; transform[11] = voice->position.z;
        fn_801CA59C(voice->matrix, transform);
        voice->data = data;
        voice->level = (float)level / lbl_80650FD0;
        voice->target = target;
        if (target != 0 && (target->flags & 0x80000000) == 0 && target->object == 0)
            target->flags |= 0x80000000;
        fn_801CE280();
        return 1;
    }
    return 0;
}
