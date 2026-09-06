typedef unsigned char u8;

typedef struct Transform800A197C {
    u8 pad00[0x74];
    float x;
    float y;
    float z;
    float scale;
} Transform800A197C;

typedef struct Context800A197C {
    u8 pad00[0x38];
    void* resource;
    u8 pad3C[0x88];
    Transform800A197C* transform;
} Context800A197C;

extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern Context800A197C* fn_8006D444(void);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8011F104(void*, float, float, float);
extern void fn_8012B7A0(void*, float);
extern void fn_801D13D8(void*, int);

int fn_800A197C(void)
{
    Transform800A197C* transform;
    Context800A197C* context;
    void* object;

    fn_80204844(fn_80201B9C(), 0x20);
    context = fn_8006D444();
    transform = (Transform800A197C*)context;
    context = (Context800A197C*)transform;
    fn_80201814(context->resource);
    object = fn_80201BC8();
    transform = context->transform;
    fn_8011F104(object, transform->x, transform->y, transform->z);
    fn_8012B7A0(object, transform->scale);
    fn_801D13D8(context->resource, 0);
    return 0;
}
