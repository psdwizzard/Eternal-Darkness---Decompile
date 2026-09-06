typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern float lbl_806510A8;
extern u32 lbl_8064D18C;
extern void fn_801D324C(void);
extern Object* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                           u32, u32, u32);
extern void fn_801D0CA4(Object*);
extern void fn_801AAE68(int, int, int, void*, int, int, int, u16, float, int);

void fn_801D313C(u32 id, u32 kind, void* position)
{
    float intensity;
    u16 group;
    Object* object = fn_801D0D78(0, id, kind, position, fn_801D324C,
                                  0, 0, 0, 0, 1);
    object->bytes[0xFF1] = 1;
    fn_801D0CA4(object);
    intensity = lbl_806510A8;
    group = (u16)lbl_8064D18C;
    fn_801AAE68(0x228, 0x7F, 0, position, 2, 2, 0,
                group, intensity, 0);
}
