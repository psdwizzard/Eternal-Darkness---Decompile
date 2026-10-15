typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Data { u8 pad[0x7C]; u32 value; } Data;

extern void* fn_8012AB2C(u8* owner);
extern void fn_8013F3C0(Shape*, const Vec3*, const Vec3*, float);
extern int fn_8013FDB4(void*, const void*, Result*, void*, u32, unsigned short*);
extern void fn_8012A24C(u8*, unsigned short);
extern void fn_80039FF0(u8*, Result*);
extern void fn_801A74D8(Data*, u32);
extern const float lbl_8064E244;

int fn_80039EF8(int update_owner, Data* data, u8* owner, u8* skip,
                const Vec3* first, const Vec3* second, u32* flags)
{
    Shape shape;
    Result result;
    unsigned short kind;
    void* collision_owner;
    int found = 0;

    collision_owner = fn_8012AB2C(owner);
    fn_8013F3C0(&shape, first, second, lbl_8064E244);
    if (fn_8013FDB4(collision_owner, &shape, &result, skip, 3, &kind)) {
        if (update_owner) {
            if (skip != 0) {
                fn_8012A24C(skip, kind);
                fn_80039FF0(skip, &result);
            }
        } else {
            fn_80039FF0(0, &result);
        }
        if (kind == 0x14) {
            *flags |= 0x40;
        } else {
            *flags |= 0x10;
        }
        fn_801A74D8(data, 0x10);
        found = 1;
    }
    return found;
}
