typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target { struct Target* next; u32 pad04; u32 flags; char pad0C[0x20]; void* object; } Target;
typedef struct Voice {
    struct Voice* previous; struct Voice* next; Target* target; void* data;
    Vec3 position; float roll; Vec3 velocity; Vec3 direction; Vec3 up; Vec3 right;
    float matrix[12]; float a; float b; float c; float level;
} Voice;
extern u8 sndActive;
extern Voice* s3dListenerRoot;
extern float lbl_80650FD0;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void salCrossProduct(Vec3*, Vec3*, Vec3*);
extern void salInvertMatrix(float*, float*);

int sndAddListenerEx(Voice* voice, Vec3* position, Vec3* velocity, Vec3* direction,
                float a, float b, float c, float roll, Vec3* up, void* data,
                u8 level, Target* target)
{
    float transform[12];
    if (sndActive != 0) {
        hwDisableIrq();
        if ((voice->previous = s3dListenerRoot) != 0) {
            s3dListenerRoot->next = voice;
        }
        voice->next = 0;
        s3dListenerRoot = voice;
        voice->position = *position;
        voice->velocity = *velocity;
        voice->direction = *direction;
        voice->right = *up;
        voice->a = a;
        voice->b = b;
        voice->c = c;
        voice->roll = roll;
        salCrossProduct(&voice->up, &voice->direction, &voice->right);
        transform[0] = voice->up.x; transform[3] = voice->up.y; transform[6] = voice->up.z;
        transform[1] = voice->right.x; transform[4] = voice->right.y; transform[7] = voice->right.z;
        transform[2] = -voice->direction.x; transform[5] = -voice->direction.y; transform[8] = -voice->direction.z;
        transform[9] = voice->position.x; transform[10] = voice->position.y; transform[11] = voice->position.z;
        salInvertMatrix(voice->matrix, transform);
        voice->data = data;
        voice->level = (float)level / lbl_80650FD0;
        voice->target = target;
        if (target != 0 && (target->flags & 0x80000000) == 0 && target->object == 0)
            target->flags |= 0x80000000;
        hwEnableIrq();
        return 1;
    }
    return 0;
}
