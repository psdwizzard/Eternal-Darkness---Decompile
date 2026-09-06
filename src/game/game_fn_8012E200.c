typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern void fn_8012BE18(const void*, void*, int);
extern void fn_8012BE64(const void*, void*);
extern void fn_802114B8(void*, float, float, float);
extern void fn_8012E42C(int *, Vec3, void *);
extern void fn_8012E498(int*, const Vec4*, void*);

int fn_8012E200(u8* entry, int alternate, void* matrix)
{
    int initialized = 0;
    Vec3 second_scale;
    Vec3 second_translation;
    Vec4 second_rotation;
    Vec3 first_scale;
    Vec3 first_translation;
    Vec4 first_rotation;
    u16 flags;

    if (alternate != 0 && ((flags = *(u16*)(entry + 0xA)) & 0x38) != 0) {
        if ((flags & 0x20) != 0) {
            fn_8012BE18(entry + 0x3C, &second_scale, 8);
            fn_802114B8(matrix, second_scale.x, second_scale.y, second_scale.z);
            initialized = 1;
        }
        if ((*(u16*)(entry + 0xA) & 0x10) != 0) {
            fn_8012BE18(entry + 0x54, &second_translation, 6);
            fn_8012E42C(&initialized, second_translation, matrix);
        }
        if ((*(u16*)(entry + 0xA) & 8) != 0) {
            fn_8012BE64(entry + 0x6C, &second_rotation);
            fn_8012E498(&initialized, &second_rotation, matrix);
        }
    } else if (alternate == 0 && ((flags = *(u16*)(entry + 0xA)) & 7) != 0) {
        if ((flags & 4) != 0) {
            fn_8012BE18(entry + 0x3C, &first_scale, 8);
            fn_802114B8(matrix, first_scale.x, first_scale.y, first_scale.z);
            initialized = 1;
        }
        if ((*(u16*)(entry + 0xA) & 2) != 0) {
            fn_8012BE18(entry + 0x54, &first_translation, 6);
            fn_8012E42C(&initialized, first_translation, matrix);
        }
        if ((*(u16*)(entry + 0xA) & 1) != 0) {
            fn_8012BE64(entry + 0x6C, &first_rotation);
            fn_8012E498(&initialized, &first_rotation, matrix);
        }
    }
    return initialized;
}
