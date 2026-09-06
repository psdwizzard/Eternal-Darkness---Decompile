typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef float f32;
typedef struct Vec3 { f32 x, y, z; } Vec3;

extern u32 lbl_8064D18C;
extern void* fn_801D71A4(u32, void*, void*, u8, void**, void***, u32, f32,
                         void**);
extern void fn_801D7C24(u32, void*, f32, u32, int);
extern s16 fn_801D8710(u32);
extern f32 fn_801D86FC(int);
extern void* fn_800CD6C0(int, int, void*, u8, int, s16, Vec3*, f32,
                         void*);
extern void* fn_80201B54(void*);

void fn_801D6FEC(u32 flags, void* position, f32 value)
{
    void* first;
    void** destination;
    void* last;
    void* descriptor;
    s16 owner;
    f32 time;

    descriptor = fn_801D71A4(flags, position, 0, 4, &first, &destination,
                             lbl_8064D18C, value, &last);
    fn_801D7C24(flags, descriptor, value, 1, 0);
    owner = fn_801D8710(flags);
    time = fn_801D86FC(4);
    *destination = fn_80201B54(fn_800CD6C0(0, flags, first, 4,
                                            lbl_8064D18C, owner, position,
                                            time, last));
}
