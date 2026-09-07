typedef signed short s16;
typedef unsigned int u32;

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    s16 reserved_c;
    s16 reserved_e;
    u32 flags;
    s16 width;
} TextDescriptor;

extern TextDescriptor* lbl_8064D598;
extern void* lbl_8064D588;
extern void fn_801E6A8C(TextDescriptor*);

void fn_801E6F9C(TextDescriptor* descriptor, void* value)
{
    descriptor->x = 320;
    fn_801E6A8C(descriptor);
    descriptor->reserved_e = 480;
    descriptor->width = descriptor->y - 480;
    descriptor->flags |= 0x110;
    lbl_8064D598 = descriptor;
    lbl_8064D588 = value;
}
