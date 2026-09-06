typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct Key {
    u32 word;
    u16 half;
} Key;

typedef struct Params {
    u8 pad00[0x14];
    u8 first;
    u8 second;
    u8 pad16;
    u8 third;
    u8 fourth;
    u8 pad19[9];
    u16 x;
    u16 y;
    u16 z;
    u8 pad28[0x10];
    u32 flags;
    u8 pad3C[0x54];
} Params;

typedef struct Descriptor {
    u8 bytes[0xC0];
} Descriptor;

extern u32 lbl_80651EC8;
extern u16 lbl_80651ECC;
extern void fn_801938FC(void*);
extern void fn_801D3CAC(int, int, void*);
extern void* fn_80148008(Vec3f*, Key*, Params*, void (*)(void));
extern void fn_801936FC(void);
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern void* fn_80149E04(void);
extern void fn_80147E88(Descriptor*);
extern void fn_80149FDC(Descriptor*, void*);
extern u32 fn_80148300(void*, Descriptor*, void*);
extern void fn_80149EB8(void*);

void* fn_801D551C(Vec3f* position, Vec3f* velocity, int type,
                  int spawn_first, int spawn_third, u8 spawn_second,
                  u8 first, u8 second, int set_4000, int set_8000,
                  u8 third, u8 fourth, u8 kind)
{
    Key key;
    Vec3f submit_position;
    Params params;
    Descriptor descriptor;
    void* owner;
    u8 failed;
    void* child;

    key.word = lbl_80651EC8;
    key.half = lbl_80651ECC;
    fn_801938FC(&params);
    params.x = (u16)(int)velocity->x;
    params.y = (u16)(int)velocity->y;
    params.z = (u16)(int)velocity->z;
    params.third = third;
    params.first = first;
    params.second = second;
    params.flags |= 8;
    if (set_4000 != 0)
        params.flags |= 0x4000;
    if (set_8000 != 0)
        params.flags |= 0x8000U;
    params.fourth = fourth;
    fn_801D3CAC(type, kind & 0x80, &params.first);
    submit_position = *position;
    owner = fn_80148008(&submit_position, &key, &params, fn_801936FC);
    if (owner != 0) {
        failed = 0;
        fn_8017FF1C(fn_80156938(owner), kind);
        if (spawn_first != 0) {
            child = fn_80149E04();
            if (child != 0) {
                fn_80147E88(&descriptor);
                fn_80149FDC(&descriptor, child);
                descriptor.bytes[0xBC] = kind;
                fn_801938FC(&descriptor);
                descriptor.bytes[0x17] = third;
                descriptor.bytes[0x14] = first >> 2;
                descriptor.bytes[0x15] = second >> 1;
                *(u32*)(descriptor.bytes + 0x38) |= 0x651;
                if (set_4000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x4000;
                if (set_8000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x8000U;
                descriptor.bytes[0x18] = fourth;
                fn_801D3CAC(type, kind & 0x80, descriptor.bytes + 0x14);
                if (fn_80148300(owner, &descriptor, child) == 0) {
                    fn_80149EB8(child);
                    failed = 1;
                }
            } else {
                failed = 1;
            }
        }
        if (spawn_second != 0 && failed == 0) {
            child = fn_80149E04();
            if (child != 0) {
                fn_80147E88(&descriptor);
                fn_80149FDC(&descriptor, child);
                descriptor.bytes[0xBC] = kind;
                ((u8*)child)[0] = spawn_second;
                fn_801938FC(&descriptor);
                descriptor.bytes[0x17] = third;
                descriptor.bytes[0x14] = first >> 2;
                descriptor.bytes[0x15] = second >> 1;
                *(u32*)(descriptor.bytes + 0x38) |= 0x352;
                if (set_4000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x4000;
                if (set_8000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x8000U;
                descriptor.bytes[0x18] = fourth;
                fn_801D3CAC(type, kind & 0x80, descriptor.bytes + 0x14);
                if (fn_80148300(owner, &descriptor, child) == 0) {
                    fn_80149EB8(child);
                    failed = 1;
                }
            } else {
                failed = 1;
            }
        }
        if (spawn_third != 0 && failed == 0) {
            child = fn_80149E04();
            if (child != 0) {
                fn_80147E88(&descriptor);
                fn_80149FDC(&descriptor, child);
                descriptor.bytes[0xBC] = kind;
                fn_801938FC(&descriptor);
                descriptor.bytes[0x17] = third;
                descriptor.bytes[0x14] = first >> 2;
                descriptor.bytes[0x15] = second >> 1;
                *(u32*)(descriptor.bytes + 0x38) |= 0x654;
                if (set_4000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x4000;
                if (set_8000 != 0)
                    *(u32*)(descriptor.bytes + 0x38) |= 0x8000U;
                descriptor.bytes[0x18] = fourth;
                fn_801D3CAC(type, kind & 0x80, descriptor.bytes + 0x14);
                if (fn_80148300(owner, &descriptor, child) == 0)
                    fn_80149EB8(child);
            }
        }
    }
    return owner;
}
