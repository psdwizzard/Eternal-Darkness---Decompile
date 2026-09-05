typedef unsigned int u32;

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

extern void* fn_80201814(u32);
extern void fn_80201E78(Vec3*, void*);

void fn_801D0BBC(u32 flags, u32 subject, void* data, Vec3* output)
{
    void* object;
    Vec3 position;

    switch (flags & 0x1ff0) {
    case 0x300:
    case 0x410:
    case 0x420:
    case 0x440:
    case 0x480:
    case 0x500:
    case 0x810:
    case 0x820:
    case 0x1010:
    case 0x1040:
        object = fn_80201814(subject);
        if (object != 0) {
            fn_80201E78(&position, object);
            *output = position;
        }
        break;
    }
}
